#ifndef _PORT_H_
    #define _PORT_H_

    #include <MKL25Z4.h>

    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    /*
        port:
            PORTA_BASE_PTR
            PORTB_BASE_PTR
            PORTC_BASE_PTR
            PORTD_BASE_PTR
            PORTE_BASE_PTR
        pin:
            0
            ...
            31
    */
    /*
        gpwe:
            0xZZZZ  global pin write enable
        gpwd:
            0xZZZZ  global pin write data
    */
    
    typedef enum{
        IRQ_DMA_DISABLE = 0x00,
        DMA_RISING_EDGE,
        DMA_FALLING_EDGE,
        DMA_EITHER_EDGE,
        IRQ_LOGIC_ZERO = 0x08,
        IRQ_RISING_EDGE,
        IRQ_FALLING_EDGE,
        IRQ_EITHER_EDGE,
        IRQ_LOGIC_ONE
    }Irqc;

    typedef enum{
        ALTERNATIVE0 = 0,   //
        ALTERNATIVE1,   //
        ALTERNATIVE2,   //
        ALTERNATIVE3,   //
        ALTERNATIVE4,   //
        ALTERNATIVE5,   //
        ALTERNATIVE6,   //
        ALTERNATIVE7    //
    }Mux;

    typedef enum{
        LOW_DRIVE = 0,  //low drive strength
        HIGH_DRIVE      //high drive strength
    }Dse;

    typedef enum{
        FILTER_DISABLED = 0,    //passive input filter is disabled
        FILTER_ENABLE           //passive input filter is enabled
    }Pfe;

    typedef enum{
        FAST_SLEW = 0,  //fast slew rate
        SLOW_SLEW       //slow slew rate
    }Sre;

    typedef enum{
        DISABLED_PULL_RESISTOR = 0, //internal pullup or pulldown resistor is disabled
        ENABLE_PULL_RESISTOR        //internal pullup or pulldown resistor is enabled
    }Pe;

    typedef enum{
        PULLDOWN = 0,   //internal pulldown resistor is enabled
        PULLUP          //internal pullup resistor is enabled
    }Ps;

    void port_pinControlRegisters(PORT_MemMapPtr port, uint8_t pin, Irqc irqc, Mux mux, Dse dse, Pfe pfe, Sre sre, Pe pe, Ps ps);
    uint32_t port_interruptStatusFlag(PORT_MemMapPtr port, uint8_t pin);
    void port_cleanFlagISF(PORT_MemMapPtr port, uint8_t pin);
    void port_globalControl(PORT_MemMapPtr port, uint16_t gpwe_low, uint16_t gpwd_low, uint16_t gpwe_high, uint16_t gpwd_high);
    uint32_t port_interruptFlags(PORT_MemMapPtr port);
#endif
