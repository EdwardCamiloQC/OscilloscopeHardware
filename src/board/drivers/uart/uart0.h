/** \file uart0.h
    \brief Esta biblioteca maneja todo lo relacionado con el UART0 de una FRDM-KL25Z
    \author Edward Camilo
    \version 1.0
    \date mayo 2025
 */
#ifndef _UART_H_
    #define _UART_H_

    #include <stdint.h>
    #include <stdbool.h>

    /**
        \brief Función de interrupción del UART.
     */
    void _irqHandler_UART0(void);

    /**
        @brief Baudios establecidos para el UART
        @enum
        @typedef Baudrate
     */
    typedef enum{
        Baudrate_9600 = 9600,       /**< 9600 */
        Baudrate_14400 = 14400,     /**< 14400*/
        Baudrate_19200 = 19200,     /**< 19200*/
        Baudrate_38400 = 38400,     /**< 38400*/
        Baudrate_57600 = 57600,     /**< 57600*/
        Baudrate_115200 = 115200,   /**< 115200*/
        Baudrate_230400 = 230400,   /**< 230400*/
        Baudrate_460800 = 460800    /**< 460800*/
    }Baudrate;
    
    /**
        \brief Configura el UART0 ajustando los baudios, los bits de stop, la paridad y el tipo de
        paridad.
        \param baudRate: baudios para la transmisión y recepción de datos.
        \param stopBits: Configura si es 1 o 2 bits de stop. 0->1bit. 1->2bits.
        \param parity: Configura si hay o no paridad. 0->no. 1->si.
        \param typeParity: 0->paridad par. 1->paridad impar.
     */
    void uart0_config(Baudrate baudRate, bool stopBits, bool parity, bool typeParity);
    
    /**
        \brief Inicializa el UART0.
        \param irqTxTDRE: Habilita las interrupciones cuando esta vacio el registro de dato.
        \param irqTxTC: Habilita las interrupciones cuando la transmisión fue completada.
        \param irqRxRDRF: Habilita las interrupciones cuando el registro de dato está lleno.
        \param irqIdle: Habilita las interrupciones cuando la línea está en reposo.
        \param enableTx: habilita el transmisor.
        \param enableRx: Habilita el receptor.
        \param dmaTx: Habilita las solicitudes hacia el DMA con el flag TDRE.
        \param dmaRx: Habilita las solicitudes hacia el DMA con el flag RDRF.
     */
    void uart0_init(bool irqTxTDRE, bool irqTxTC, bool irqRxRDRF, bool irqIdle, bool enableTx, bool enableRx, bool dmaTx, bool dmaRx);
    
    /**
        \brief Envía datos por UART0.
        \param data: dirección de memoria donde empiezan los datos.
        \param size: cantidad de datos a enviar.
     */
    void uart0_sendData(const uint8_t* data, uint8_t size);
#endif
