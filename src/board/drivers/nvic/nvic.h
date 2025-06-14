#ifndef _NVIC_H_
    #define _NVIC_H_

    #include <stdint.h>

    typedef enum{
        VECTOR_DMA_CHANNEL_0 = 0,
        VECTOR_DMA_CHANNEL_1,
        VECTOR_DMA_CHANNEL_2,
        VECTOR_DMA_CHANNEL_3,
        VECTOR_FTFA = 5,
        VECTOR_PMC,
        VECTOR_LLWU,
        VECTOR_I2C0,
        VECTOR_I2C1,
        VECTOR_SPI0,
        VECTOR_SPI1,
        VECTOR_UART0,
        VECTOR_UART1,
        VECTOR_UART2,
        VECTOR_ADC0,
        VECTOR_CMP0,
        VECTOR_TPM0,
        VECTOR_TPM1,
        VECTOR_TPM2,
        VECTOR_RTC_ALARM,
        VECTOR_RTC_SECONDS,
        VECTOR_PIT,
        VECTOR_USB_OTG = 24,
        VECTOR_DAC0,
        VECTOR_TSI0,
        VECTOR_MCG,
        VECTOR_LPTMR0,
        VECTOR_PORTA = 30,
        VECTOR_PORTD
    }VectorIrq;
    void nvic_irqEnable(VectorIrq irq);
    void nvic_irqDisable(uint8_t irq);
    void nvic_irqPriority(uint8_t ipr, uint8_t irq, uint32_t priority);
    void nvic_cleanFlagPending(VectorIrq irq);
#endif
