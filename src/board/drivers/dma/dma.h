/**
    @file dma.h
    @brief Configura el DMA del chip FRDM-KL25Z
    @author Edward Camilo
    @version 1.0
    @date mayo 2025
 */
#ifndef _DMA_H_
    #define _DMA_H_

    #include <stdbool.h>
    #include <stdint.h>

    /**
        @brief Función de interrupción del canal 0 del DMA
     */
    void _irqHandler_DMA0(void);

    /**
        @brief Función de interrupción del canal 1 del DMA
     */
    void _irqHandler_DMA1(void);

    /**
        @brief Función de interrupción del canal 2 del DMA
     */
    void _irqHandler_DMA2(void);

    /**
        @brief Función de interrupción del canal 3 del DMA
     */
    void _irqHandler_DMA3(void);

    /**
        @brief Vaores asociados a las posibles fuentes del DMA.
        @enum
        @typedef DMA_SOURCE
     */
    typedef enum{
        DISABLED_SOURCE,                        /**< canal desabilitado */
        UART0_RX_SOURCE = 2,                    /**< UART0_RX como fuente */
        UART0_TX_SOURCE,                        /**< UART0_TX como fuente */
        UART1_RX_SOURCE,                        /**< UART1_RX como fuente */
        UART1_TX_SOURCE,                        /**< UART1_TX como fuente */
        UART2_RX_SOURCE,                        /**< UART2_RX como fuente */
        UART2_TX_SOURCE,                        /**< UART2_TX como fuente */
        SPI0_RX_SOURCE = 16,                    /**< SPI0_RX como fuente */
        SPI0_TX_SOURCE,                         /**< SPI0_TX como fuente */
        SPI1_RX_SOURCE,                         /**< SPI1_RX como fuente */
        SPI1_TX_SOURCE,                         /**< SPI1_TX como fuente */
        I2C0_SOURCE = 22,                       /**< I2C0 como fuente */
        I2C1_SOURCE,                            /**< I2C1 como fuente */
        TPM0_CHANNEL0_SOURCE,                   /**< TPM0_CHANNEL0 como fuente */
        TPM0_CHANNEL1_SOURCE,                   /**< TPM0_CHANNEL1 como fuente */
        TPM0_CHANNEL2_SOURCE,                   /**< TPM0_CHANNEL2 como fuente */
        TPM0_CHANNEL3_SOURCE,                   /**< TPM0_CHANNEL3 como fuente */
        TPM0_CHANNEL4_SOURCE,                   /**< TPM0_CHANNEL4 como fuente */
        TPM0_CHANNEL5_SOURCE,                   /**< TPM0_CHANNEL5 como fuente */
        TPM1_CHANNEL0_SOURCE = 32,              /**< TPM1_CHANNEL0 como fuente */
        TPM1_CHANNEL1_SOURCE,                   /**< TPM1_CHANNEL1 como fuente */
        TPM2_CHANNEL0_SOURCE,                   /**< TPM2_CHANNEL0 como fuente */
        TPM2_CHANNEL1_SOURCE,                   /**< TPM2_CHANNEL1 como fuente */
        ADC0_SOURCE = 40,                       /**< ADC0 como fuente */
        CMP0_SOURCE = 42,                       /**< CMP0 como fuente */
        DAC0_SOURCE = 45,                       /**< DAC0 como fuente */
        PORT_CONTROL_MODULE_PORTA_SOURCE = 49,  /**< PORTA como fuente */
        PORT_CONTROL_MODULE_PORTD_SOURCE = 52,  /**< PORTD como fuente */
        TPM0_OVERFLOW_SOURCE = 54,              /**< TPM0_OVERFLOW como fuente */
        TPM1_OVERFLOW_SOURCE,                   /**< TPM1_OVERFLOW como fuente */
        TPM2_OVERFLOW_SOURCE,                   /**< TPM2_OVERFLOW como fuente */
        TSI_SOURCE,                             /**< TSI como fuente */
        DMAMUX_OP1_SOURCE = 60,                 /**< DMAMUX_OP1 como fuente */
        DMAMUX_OP2_SOURCE,                      /**< DMAMUX_OP2 como fuente */
        DMAMUX_OP3_SOURCE,                      /**< DMAMUX_OP3 como fuente */
        DMAMUX_OP4_SOURCE                       /**< DMAMUX_OP4 como fuente */
    }DmaSource;

    /**
        @brief Bytes de destino o fuente
        @enum
        @typedef BytesDma
     */
    typedef enum{
        BITS_32,    /**< 32bits */
        BITS_8,     /**< 8bits */
        BITS_16     /**< 16bits */
    }BytesDma;

    typedef enum{
        CIRCULAR_BUFFER_DISABLED = 0,
        CIRCULAR_BUFFER_16_BYTES,
        CIRCULAR_BUFFER_32_BYTES,
        CIRCULAR_BUFFER_64_BYTES,
        CIRCULAR_BUFFER_128_BYTES,
        CIRCULAR_BUFFER_256_BYTES,
        CIRCULAR_BUFFER_512_BYTES,
        CIRCULAR_BUFFER_1K_BYTES,
        CIRCULAR_BUFFER_2K_BYTES,
        CIRCULAR_BUFFER_4K_BYTES,
        CIRCULAR_BUFFER_8K_BYTES,
        CIRCULAR_BUFFER_16K_BYTES,
        CIRCULAR_BUFFER_32K_BYTES,
        CIRCULAR_BUFFER_64K_BYTES,
        CIRCULAR_BUFFER_128K_BYTES,
        CIRCULAR_BUFFER_256K_BYTES,
    }BytesCircularBuffer;

    /**
        @brief configura el DMA.
        @param sourceN: Periférico fuente a asociar al canal N del DMA.
        @param modeChN: Redirección 0->modo normal.
                                    1->el DMAMUX está en modo de disparo periódico.
        @param sarN: Dirección de la fuente.
        @param darN: Dirección del destino.
        @param cicleStealN: 0->DMA continuamente transfiere hasta decrementar BCR.
                            1->DMA fuerza un transferencia simple por solicitud.
        @param alignN:  0->Alineamiento desabilitado.
                        1->Alineamiento activado.
        @param sourceIncN:  0->No cambiar el sar luego de una transferencia exitosa.
                            1->El sar incrementa por 1,2,4 como se determine por el ancho de transferencia.
        @param sizeSN: Ancho en bits del dato en la fuente.
        @param destIncN:0->No cambia el dar despues de una tranferencia exitosa
                        1->El dar incrementa por 1,2,4 dependiendo el tamaño de la transferencia.
        @param sizeDN: Ancho en bits del dato en el destino.
        @param saModuleN: Ancho del buffer circular de la fuente.
        @param daModule: Ancho del buffer circular del destino.
     */
    void dma_config(DmaSource source0, bool modeCh0, uint32_t sar0, uint32_t dar0, bool cicleSteal0, bool align0, bool sourceInc0, BytesDma sizeS0, bool destInc0, BytesDma sizeD0, BytesCircularBuffer saModule0, BytesCircularBuffer daModule0,
                    DmaSource source1, bool modeCh1, uint32_t sar1, uint32_t dar1, bool cicleSteal1, bool align1, bool sourceInc1, BytesDma sizeS1, bool destInc1, BytesDma sizeD1, BytesCircularBuffer saModule1, BytesCircularBuffer daModule1,
                    DmaSource source2, bool modeCh2, uint32_t sar2, uint32_t dar2, bool cicleSteal2, bool align2, bool sourceInc2, BytesDma sizeS2, bool destInc2, BytesDma sizeD2, BytesCircularBuffer saModule2, BytesCircularBuffer daModule2,
                    DmaSource source3, bool modeCh3, uint32_t sar3, uint32_t dar3, bool cicleSteal3, bool align3, bool sourceInc3, BytesDma sizeS3, bool destInc3, BytesDma sizeD3, BytesCircularBuffer saModule3, BytesCircularBuffer daModule3);

    /**
        @brief
        @param bytes: Bytes a mover.
        @param irqN: Habilitar interrupciones cuando se completa una transferencia u ocurre un error.
        @param enableRequestN: Habilita las solicitudes.
     */
    void dma_init(uint16_t bytes0, bool irq0, bool enableRequest0, bool enDmaMux0,
                uint16_t bytes1, bool irq1, bool enableRequest1, bool enDmaMux1,
                uint16_t bytes2, bool irq2, bool enableRequest2, bool enDmaMux2,
                uint16_t bytes3, bool irq3, bool enableRequest3, bool enDmaMux3);
#endif
