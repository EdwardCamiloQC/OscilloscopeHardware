/**
    @file adc.h
    @brief Esta biblioteca configura lo relacionado con el ADC del chip FRDM-KL25Z
    @author Edward Camilo
    @version v1.0
    @date mayo 2025
 */
#ifndef _ADC_H_
    #define _ADC_H_

    #include <stdint.h>
    #include <stdbool.h>

    /**
        @brief Función de interrupción propia del ADC.
     */
    void _irqHandler_ADC0(void);

    /**
        @brief Configura el ADC0.
        @param sample: Configura como son los muestreos. 0->una muestra. 1->muestras continuas.
        @param trigger: Configura el tipo de disparo. 0->por software. 1->por hardware.
        @param enableDma: Habilita las solicitudes hacia el DMA.
     */
    void adc0_config(bool sample, bool trigger, bool enableDma);

    /**
        @brief Habilita o desabilita las interrupciones del ADC para el canal 0.
        @param irqAdc: Habilitación de las interrupciones cuando completa una muestra.
     */
    void adc0_init(bool irqAdc);

    void adc0_read();

    void adc0_set_sample_rate(uint32_t sampleRate);
#endif
