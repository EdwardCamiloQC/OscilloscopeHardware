#include <dma.h>
#include <MKL25Z4.h>
#include <sim.h>
#include <nvic.h>

//~~~~~~~~~~
//      IRQ
//~~~~~~~~~~
void _irqHandler_DMA0(void){
    if(DMA_DSR_BCR0 & DMA_DSR_BCR_CE_MASK){
        return;
    }
    DMA_DSR_BCR0 = ((uint32_t)(~(DMA_DSR_BCR_DONE_MASK | DMA_DSR_BCR_BCR_MASK)) & DMA_DSR_BCR0) |
        ((uint32_t)1<<DMA_DSR_BCR_DONE_SHIFT) | DMA_DSR_BCR_BCR(8);

    DMA_DCR1 = ((uint32_t)(~(DMA_DCR_START_MASK)) & DMA_DCR1) |
        ((uint32_t)1<<DMA_DCR_START_SHIFT);
}

void _irqHandler_DMA1(void){
    DMA_DSR_BCR1 = ((uint32_t)(~(DMA_DSR_BCR_DONE_MASK | DMA_DSR_BCR_BCR_MASK)) & DMA_DSR_BCR1) |
        ((uint32_t)1<<DMA_DSR_BCR_DONE_SHIFT) | DMA_DSR_BCR_BCR(10);
    
    ADC0_SC1A = ADC_SC1_ADCH(8);
}

void _irqHandler_DMA2(void){
}

void _irqHandler_DMA3(void){
}

//~~~~~~~~~~
//      FUNCTIONS
//~~~~~~~~~~
void dma_config(
    DmaSource source0, bool modeCh0, uint32_t sar0, uint32_t dar0, bool cicleSteal0, bool align0, bool sourceInc0, BytesDma sizeS0, bool destInc0, BytesDma sizeD0, BytesCircularBuffer saModule0, BytesCircularBuffer daModule0,
    DmaSource source1, bool modeCh1, uint32_t sar1, uint32_t dar1, bool cicleSteal1, bool align1, bool sourceInc1, BytesDma sizeS1, bool destInc1, BytesDma sizeD1, BytesCircularBuffer saModule1, BytesCircularBuffer daModule1,
    DmaSource source2, bool modeCh2, uint32_t sar2, uint32_t dar2, bool cicleSteal2, bool align2, bool sourceInc2, BytesDma sizeS2, bool destInc2, BytesDma sizeD2, BytesCircularBuffer saModule2, BytesCircularBuffer daModule2,
    DmaSource source3, bool modeCh3, uint32_t sar3, uint32_t dar3, bool cicleSteal3, bool align3, bool sourceInc3, BytesDma sizeS3, bool destInc3, BytesDma sizeD3, BytesCircularBuffer saModule3, BytesCircularBuffer daModule3){
        //  Habilita relojes del DMAMUX y el DMA
        sim_systemClock_dac_rtc_adc_tpm_pit_dmamux_ftf(DMAMUX, true);
        sim_systemClock_dma(true);

        //  Configura el multiplexor del DMA para los cuatro canales
        DMAMUX0_CHCFG0 = ((uint8_t)(~(DMAMUX_CHCFG_TRIG_MASK | DMAMUX_CHCFG_SOURCE_MASK)) & DMAMUX0_CHCFG0) |
            ((uint8_t)modeCh0 << DMAMUX_CHCFG_TRIG_SHIFT) | DMAMUX_CHCFG_SOURCE(source0);
        DMAMUX0_CHCFG1 = ((uint8_t)(~(DMAMUX_CHCFG_TRIG_MASK | DMAMUX_CHCFG_SOURCE_MASK)) & DMAMUX0_CHCFG1) |
            ((uint8_t)modeCh1 << DMAMUX_CHCFG_TRIG_SHIFT) | DMAMUX_CHCFG_SOURCE(source1);
        DMAMUX0_CHCFG2 = ((uint8_t)(~(DMAMUX_CHCFG_TRIG_MASK | DMAMUX_CHCFG_SOURCE_MASK)) & DMAMUX0_CHCFG2) |
            ((uint8_t)modeCh2 << DMAMUX_CHCFG_TRIG_SHIFT) | DMAMUX_CHCFG_SOURCE(source2);
        DMAMUX0_CHCFG3 = ((uint8_t)(~(DMAMUX_CHCFG_TRIG_MASK | DMAMUX_CHCFG_SOURCE_MASK)) & DMAMUX0_CHCFG3) |
            ((uint8_t)modeCh3 << DMAMUX_CHCFG_TRIG_SHIFT) | DMAMUX_CHCFG_SOURCE(source3);
        
        //  Configura el canal0
        DMA_SAR0 = sar0;
        DMA_DAR0 = dar0;
        DMA_DCR0 = ((uint32_t)(~(DMA_DCR_CS_MASK |
                                DMA_DCR_AA_MASK |
                                DMA_DCR_SINC_MASK |
                                DMA_DCR_SSIZE_MASK |
                                DMA_DCR_DINC_MASK | 
                                DMA_DCR_DSIZE_MASK |
                                DMA_DCR_SMOD_MASK | 
                                DMA_DCR_DMOD_MASK)) & DMA_DCR0) |
            ((uint32_t)cicleSteal0 << DMA_DCR_CS_SHIFT) |
            ((uint32_t)align0<<DMA_DCR_AA_SHIFT) |
            ((uint32_t)sourceInc0<<DMA_DCR_SINC_SHIFT) |
            DMA_DCR_SSIZE(sizeS0) |
            ((uint32_t)destInc0<<DMA_DCR_DINC_SHIFT) |
            DMA_DCR_DSIZE(sizeD0) |
            DMA_DCR_SMOD(saModule0) |
            DMA_DCR_DMOD(daModule0);
        
        //  Configura el canal1
        DMA_SAR1 = sar1;
        DMA_DAR1 = dar1;
        DMA_DCR1 = ((uint32_t)(~(DMA_DCR_CS_MASK |
                                DMA_DCR_AA_MASK |
                                DMA_DCR_SINC_MASK |
                                DMA_DCR_SSIZE_MASK |
                                DMA_DCR_DINC_MASK |
                                DMA_DCR_DSIZE_MASK |
                                DMA_DCR_SMOD_MASK |
                                DMA_DCR_DMOD_MASK)) & DMA_DCR1) |
            ((uint32_t)cicleSteal1 << DMA_DCR_CS_SHIFT) |
            ((uint32_t)align1<<DMA_DCR_AA_SHIFT) |
            ((uint32_t)sourceInc1<<DMA_DCR_SINC_SHIFT) |
            DMA_DCR_SSIZE(sizeS1) |
            ((uint32_t)destInc1<<DMA_DCR_DINC_SHIFT) |
            DMA_DCR_DSIZE(sizeD1) |
            DMA_DCR_SMOD(saModule1) |
            DMA_DCR_DMOD(daModule1);
        
        //  Configura el canal2
        DMA_SAR2 = sar2;
        DMA_DAR2 = dar2;
        DMA_DCR2 = ((uint32_t)(~(DMA_DCR_CS_MASK |
                                DMA_DCR_AA_MASK |
                                DMA_DCR_SINC_MASK |
                                DMA_DCR_SSIZE_MASK |
                                DMA_DCR_DINC_MASK |
                                DMA_DCR_DSIZE_MASK |
                                DMA_DCR_SMOD_MASK |
                                DMA_DCR_DMOD_MASK)) & DMA_DCR2) |
            ((uint32_t)cicleSteal2 << DMA_DCR_CS_SHIFT) |
            ((uint32_t)align2<<DMA_DCR_AA_SHIFT) |
            ((uint32_t)sourceInc2<<DMA_DCR_SINC_SHIFT) |
            DMA_DCR_SSIZE(sizeS2) |
            ((uint32_t)destInc2<<DMA_DCR_DINC_SHIFT) |
            DMA_DCR_DSIZE(sizeD2) |
            DMA_DCR_SMOD(saModule2) |
            DMA_DCR_DMOD(daModule2);
        
        //  Configura el canal3
        DMA_SAR3 = sar3;
        DMA_DAR3 = dar3;
        DMA_DCR3 = ((uint32_t)(~(DMA_DCR_CS_MASK |
                                DMA_DCR_AA_MASK |
                                DMA_DCR_SINC_MASK |
                                DMA_DCR_SSIZE_MASK |
                                DMA_DCR_DINC_MASK |
                                DMA_DCR_DSIZE_MASK |
                                DMA_DCR_SMOD_MASK |
                                DMA_DCR_DMOD_MASK)) & DMA_DCR3) |
            ((uint32_t)cicleSteal3 << DMA_DCR_CS_SHIFT) |
            ((uint32_t)align3<<DMA_DCR_AA_SHIFT) |
            ((uint32_t)sourceInc3<<DMA_DCR_SINC_SHIFT) |
            DMA_DCR_SSIZE(sizeS3) |
            ((uint32_t)destInc3<<DMA_DCR_DINC_SHIFT) |
            DMA_DCR_DSIZE(sizeD3) |
            DMA_DCR_SMOD(saModule3) |
            DMA_DCR_DMOD(daModule3);
}

void dma_init(uint16_t bytes0, bool irq0, bool enableRequest0, bool enDmaMux0,
    uint16_t bytes1, bool irq1, bool enableRequest1, bool enDmaMux1,
    uint16_t bytes2, bool irq2, bool enableRequest2, bool enDmaMux2,
    uint16_t bytes3, bool irq3, bool enableRequest3, bool enDmaMux3){
        DMA_DSR_BCR0 = ((uint32_t)(~(DMA_DSR_BCR_DONE_MASK | DMA_DSR_BCR_BCR_MASK)) & DMA_DSR_BCR0) |
            ((uint32_t)1<<DMA_DSR_BCR_DONE_SHIFT) | DMA_DSR_BCR_BCR(bytes0);
        DMA_DCR0 = ((uint32_t)(~(DMA_DCR_EINT_MASK | DMA_DCR_ERQ_MASK)) & DMA_DCR0) |
            ((uint32_t)irq0<<DMA_DCR_EINT_SHIFT) | ((uint32_t)enableRequest0<<DMA_DCR_ERQ_SHIFT);

        DMA_DSR_BCR1 = ((uint32_t)(~(DMA_DSR_BCR_DONE_MASK | DMA_DSR_BCR_BCR_MASK)) & DMA_DSR_BCR1) |
            ((uint32_t)1<<DMA_DSR_BCR_DONE_SHIFT) | DMA_DSR_BCR_BCR(bytes1);
        DMA_DCR1 = ((uint32_t)(~(DMA_DCR_EINT_MASK | DMA_DCR_ERQ_MASK)) & DMA_DCR1) |
            ((uint32_t)irq1<<DMA_DCR_EINT_SHIFT) | ((uint32_t)enableRequest1<<DMA_DCR_ERQ_SHIFT);

        DMA_DSR_BCR2 = ((uint32_t)(~(DMA_DSR_BCR_DONE_MASK | DMA_DSR_BCR_BCR_MASK)) & DMA_DSR_BCR2) |
            ((uint32_t)1<<DMA_DSR_BCR_DONE_SHIFT) | DMA_DSR_BCR_BCR(bytes2);
        DMA_DCR2 = ((uint32_t)(~(DMA_DCR_EINT_MASK | DMA_DCR_ERQ_MASK)) & DMA_DCR2) |
            ((uint32_t)irq2<<DMA_DCR_EINT_SHIFT) | ((uint32_t)enableRequest2<<DMA_DCR_ERQ_SHIFT);

        DMA_DSR_BCR3 = ((uint32_t)(~(DMA_DSR_BCR_DONE_MASK | DMA_DSR_BCR_BCR_MASK)) & DMA_DSR_BCR3) |
            ((uint32_t)1<<DMA_DSR_BCR_DONE_SHIFT) | DMA_DSR_BCR_BCR(bytes3);
        DMA_DCR3 = ((uint32_t)(~(DMA_DCR_EINT_MASK | DMA_DCR_ERQ_MASK)) & DMA_DCR3) |
            ((uint32_t)irq3<<DMA_DCR_EINT_SHIFT) | ((uint32_t)enableRequest3<<DMA_DCR_ERQ_SHIFT);

        if(irq0){
            nvic_irqEnable(VECTOR_DMA_CHANNEL_0);
        }
        if(irq1){
            nvic_irqEnable(VECTOR_DMA_CHANNEL_1);
        }
        if(irq2){
            nvic_irqEnable(VECTOR_DMA_CHANNEL_2);
        }
        if(irq3){
            nvic_irqEnable(VECTOR_DMA_CHANNEL_3);
        }

        DMAMUX0_CHCFG0 = ((uint8_t)(~(DMAMUX_CHCFG_ENBL_MASK)) & DMAMUX0_CHCFG0) |
            ((uint8_t)enDmaMux0 << DMAMUX_CHCFG_ENBL_SHIFT);
        DMAMUX0_CHCFG1 = ((uint8_t)(~(DMAMUX_CHCFG_ENBL_MASK)) & DMAMUX0_CHCFG1) |
            ((uint8_t)enDmaMux1 << DMAMUX_CHCFG_ENBL_SHIFT);
        DMAMUX0_CHCFG2 = ((uint8_t)(~(DMAMUX_CHCFG_ENBL_MASK)) & DMAMUX0_CHCFG2) |
            ((uint8_t)enDmaMux2 << DMAMUX_CHCFG_ENBL_SHIFT);
        DMAMUX0_CHCFG3 = ((uint8_t)(~(DMAMUX_CHCFG_ENBL_MASK)) & DMAMUX0_CHCFG3) |
            ((uint8_t)enDmaMux3 << DMAMUX_CHCFG_ENBL_SHIFT);
}
