#include <adc.h>
#include <sim.h>
#include <port.h>
#include <nvic.h>
#include <uart0.h>

#define BUFFER_SIZE 64
volatile uint16_t valuesADC_A0[BUFFER_SIZE];

void _irqHandler_ADC0(void){
    if(ADC0_SC1A & ADC_SC1_COCO_MASK){
        valuesADC_A0[0] = ADC0_RA;
    }
}

void adc0_config(bool sample, bool trigger, bool enableDma){
    sim_systemClock_portx_tsi_lptmr(PORTB, true);
    sim_systemClock_dac_rtc_adc_tpm_pit_dmamux_ftf(ADC0, 1);
    port_pinControlRegisters(PORTB_BASE_PTR, 0, IRQ_DMA_DISABLE, ALTERNATIVE0, LOW_DRIVE, FILTER_DISABLED, FAST_SLEW, DISABLED_PULL_RESISTOR, PULLDOWN);

    ADC0_CFG1 = ((uint32_t)(~(ADC_CFG1_ADLPC_MASK | ADC_CFG1_ADIV_MASK | ADC_CFG1_ADLSMP_MASK | ADC_CFG1_MODE_MASK | ADC_CFG1_ADICLK_MASK)) & ADC0_CFG1) |
        ((uint32_t)0<<ADC_CFG1_ADLPC_SHIFT) | ADC_CFG1_ADIV(2) | ((uint32_t)0<<ADC_CFG1_ADLSMP_SHIFT) | ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(0);

    ADC0_SC2 = ((uint32_t)(~(ADC_SC2_ADTRG_MASK | ADC_SC2_ACFE_MASK | ADC_SC2_ACFGT_MASK | ADC_SC2_ACREN_MASK | ADC_SC2_DMAEN_MASK | ADC_SC2_REFSEL_MASK)) & ADC0_SC2) |
        ((uint32_t)trigger<<ADC_SC2_ADTRG_SHIFT) | ((uint32_t)0<<ADC_SC2_ACFE_SHIFT) | ((uint32_t)0<<ADC_SC2_ACFGT_SHIFT) | ((uint32_t)0<<ADC_SC2_ACREN_SHIFT) | ((uint32_t)enableDma<<ADC_SC2_DMAEN_SHIFT) | ADC_SC2_REFSEL(0);
    
    ADC0_SC3 = ((uint32_t)(~(ADC_SC3_ADCO_MASK | ADC_SC3_AVGE_MASK | ADC_SC3_AVGS_MASK)) & ADC0_SC3) |
        ((uint32_t)sample<<ADC_SC3_ADCO_SHIFT) | ((uint32_t)0<<ADC_SC3_AVGE_SHIFT) | ADC_SC3_AVGS(0);
}

void adc0_init(bool irqAdc){
    ADC0_SC1A = ((uint32_t)(~(ADC_SC1_AIEN_MASK | ADC_SC1_DIFF_MASK | ADC_SC1_ADCH_MASK)) & ADC0_SC1A) |
        ((uint32_t)irqAdc<<ADC_SC1_AIEN_SHIFT) | ((uint32_t)0<<ADC_SC1_DIFF_SHIFT) | ADC_SC1_ADCH(8);

    if(irqAdc){
        nvic_irqEnable(VECTOR_ADC0);
    }
}

void adc0_read(){
    ADC0_SC1A = ((uint32_t)(~(ADC_SC1_AIEN_MASK | ADC_SC1_DIFF_MASK | ADC_SC1_ADCH_MASK)) & ADC0_SC1A) |
        ((uint32_t)0<<ADC_SC1_AIEN_SHIFT) | ((uint32_t)0<<ADC_SC1_DIFF_SHIFT) | ADC_SC1_ADCH(8);
}

void adc0_set_sample_rate(uint32_t sampleRate){
}
