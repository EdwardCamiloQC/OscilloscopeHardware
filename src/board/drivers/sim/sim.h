#ifndef _SIM_H_
    #define _SIM_H_

    #include <MKL25Z4.h>
    #include <stdbool.h>
    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    /*
        usbregen:
            0:  USB voltage regulator is disabled
            1:  USB voltage regulator is enabled
        usbsstby:
            0:  USB voltage regulator not in standby during Stop, VLPS, LLS and VLLS modes 
            1:  USB voltage regulator in standby during Stop, VLPS, LLS and VLLS modes
        usbvstby:
            0:  USB voltage regulator not in standby during VLPR and VLPW modes
            1:  USB volatge regulator in standby during VLPR and VLPW modes
    */
    typedef enum{
        SYSTEM_OSCILLATOR,  //OSC32KCLK
        RTC_CLKIN = 0x02,
        LPO                 //1kHz
    }Osc32ksel;
    //NOTE! is only reset on POR or LVD
    void sim_systemOptionRegister1(bool usbregen, bool usbsstby, bool usbvstby, Osc32ksel osc32ksel);   //configura voltajes del USB y selecciona el oscilador de 32kHz para el RTC y el LPTMR
    
    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    /*
        usswe:
            0:  SOPT1 USBSSTB cannot be written
            1:  SOPT1 USBSSTB can be written
        uvswe:
            0:  SOPT1 USBVSTB cannot be written
            1:  SOPT1 USBVSTB can be written
        urwe:
            0:  SOPT1 USBREGEN cannot be written
            1:  SOPT1 USBREGEN can be written 
    */
    //NOTE! is reset on System Reset not VLLS
    void sim_systemOptionRegister1Config(bool usswe, bool uvswe, bool urwe);//habilita cambios en el registro anterior
    
    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    typedef enum{
        CLKSRC_CLOCK_DISABLED,
        CLKSRC_MCGFLLCLK,      //MCGFLLCLK or MCGPLLCLK/2
        CLKSRC_OSCERCLK,
        CLKSRC_MCGIRCLK
    }Clksrc;
    /*
        usbsrc:
            0:  External bypass clock (USB_CLKIN)
            1:  MCGPLLCLK/2 or MCGFLLCLK
        pllfllsel:
            0:  MCGFLLCLK
            1:  MCGPLLCLK with fixed divide by two
    */
    typedef enum{
        BUS_CLOCK = 0x02,
        LPO_CLOCK,          //1kHz
        MCGIRCLK,
        OSCERCLK = 0x06,
    }Clkoutsel;//selects the clock to output on the CLKOUT pin
    /*
        rtcclkoutsel:
            0:  RTC 1 Hz clock is output on the RTC_CLKOUT pin
            1:  OSCERCLK clock is output on the RTC_CLKOUT pin
    */
    void sim_systemOptionRegister2(Clksrc uart0src, Clksrc tpmsrc, bool usbsrc, bool pllfllsel, Clkoutsel clkoutsel, bool rtcclkoutsel);
    
    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    /*
        tpm2clksel: NOTE! The selected pin must also be configured for the TPM external clock function
                    through the appropiate pin control register in the port control module
            0:  TPM2 external clock driven by TPM_CLKIN0 pin
            1:  TPM2 external clock driven by TPM_CLKIN1 pin
        tpm1clksel: NOTE! The selected pin must also be configured for the TPM external clock function
                    through the appropiate pin control register in the port control module
            0:  TPM1 external clock driven by TPM_CLKIN0 pin
            1:  TPM1 external clock driven by TPM_CLKIN1 pin
        tpm0clksel: NOTE! The selected pin must also be configured for the TPM external clock function
                    through the appropiate pin control register in the port control module
            0:  TPM0 external clock driven by TPM_CLKIN0 pin
            1:  TPM0 external clock driven by TPM_CLKIN1 pin
        tpm2ch0src: NOTE! When TPM2 is not in input capture mode, clear this field
            0:  TPM2_CH0 signal
            1:  CMP0 output
        tpm1ch0src: NOTE! When TPM1 is not in input capture mode, clear this field
            0:  TPM1_CH0 signal
            1:  CMP0 output
    */
    void sim_systemOptionRegister4(bool tpm2clksel, bool tpm1clksel, bool tpm0clksel, bool tpm2ch0src, bool tpm1ch0src);

    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    /*
        uart2ode:
            0:  open drain is disabled on uart2
            1:  open drian is enabled on uart2
        uart1ode:
            0:  open drain is disabled on uart1
            1:  open drain is disabled on uart1
        uart0ode:
            0:  open drain is disabled on uart0
            1:  open drain is disabled on uart0
        uart1rxsrc: selects the source for the UART1 receive data
            0:  UART1_RX pin
            1:  CMP0 output
    */
    typedef enum{   //selects the source for the UART1 transmit data
        UART1_TX_PIN,
        UART1_TX_PIN_MOD_TPM1,  //uart1_tx pin modulated with TPM1 channel 0 output
        UART1_TX_PIN_MOD_TPM2,  //uart1_tx pin modulated with TPM2 channel 0 output
    }Uart1txsrc;
    /*
        uart0rxsrc: selects the source for the UART0 receive data
            0:  UART0_RX pin
            1:  CMP0 output
    */
    typedef enum{   //selects the source for the UART0 transmit data
        UART0_TX_PIN,
        UART0_TX_PIN_MOD_TPM1,  //uart0_tx pin modulated with TPM1 channel 0 output
        UART0_TX_PIN_MOD_TPM2,  //uart0_tx pin modulated with TPM2 channel 0 output
    }Uart0txsrc;
    
    void sim_systemOptionRegister5(bool uart2ode, bool uart1ode, bool uart0ode, bool uart1rxsrc, Uart1txsrc uart1txsrc, bool uart0rxsrc, Uart0txsrc uart0txsrc);

    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    /*
        adc0alttrgen:   enable alternative conversion triggers for ADC0
            0:  TPM1 channel 0 (A) and cahnnel 1 (B) triggers selected for ADC0
            1:  Alternate trigger selected for ADC0
        adc0pretrgsel:  selects the ADC0 pre-trigger source when alternative triggers are enabled through ADC0ALTTRGEN
            0:  Pre-trigger A
            1:  Pre-trigger B
    */
    typedef enum{   //selects the ADC0 trigger source when alternative triggers are functional in stop and VLPS modes
        EXTERNAL_TRIGGER,       //(EXTRG_IN)
        CMP0,
        PIT_TRIGGER_0 = 0x04,
        PIT_TRIGGER_1,
        TPM0_OVERFLOW = 0x08,
        TPM1_OVERFLOW,
        TPM2_OVERFLOW,
        RTC_ALARM = 0x0C,
        RTC_SECONDS,
        LPTMR0_TRIGGER
    }Adc0trgsel;
    void sim_systemOptionRegister7(bool adc0alttrgen, bool adc0pretrgsel, Adc0trgsel adc0trgsel);

    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    uint32_t sim_systemDeviceIdentification();//provee información sobre del dispositivo de a que familia pertenece y sus características principales

    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    typedef enum{
        I2C0 = 6,
        I2C1,
        UART0 = 10,
        UART1,
        UART2,
        USBOTG = 18,
        CMP,
        SPI0 = 22,
        SPI1,

        LPTMR = 0,
        TSI = 5,
        PORTA = 9,
        PORTB,
        PORTC,
        PORTD,
        PORTE,

        FTF = 0,
        DMAMUX,
        PIT = 23,
        TPM0,
        TPM1,
        TPM2,
        ADC0,
        RTC = 29,
        DAC0 = 31
    }ClkEnable;
    /*
        enable:
            0:  Clock disabled
            1:  Clock enabled
        rtc:
            0:  Access and interrupts disabled
            1:  Access and interrupts enabled
    */
    void sim_systemClock_spi_cmp_usb_uart_i2c(ClkEnable clkEnable, bool enable);
    void sim_systemClock_portx_tsi_lptmr(ClkEnable clkEnable, bool enable);
    void sim_systemClock_dac_rtc_adc_tpm_pit_dmamux_ftf(ClkEnable clkEnable, bool enable);
    void sim_systemClock_dma(bool dma);

    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    typedef enum{
        OUTDIV1_DIVIDE_BY_1,
        OUTDIV1_DIVIDE_BY_2,
        OUTDIV1_DIVIDE_BY_3,
        OUTDIV1_DIVIDE_BY_4,
        OUTDIV1_DIVIDE_BY_5,
        OUTDIV1_DIVIDE_BY_6,
        OUTDIV1_DIVIDE_BY_7,
        OUTDIV1_DIVIDE_BY_8,
        OUTDIV1_DIVIDE_BY_9,
        OUTDIV1_DIVIDE_BY_10,
        OUTDIV1_DIVIDE_BY_11,
        OUTDIV1_DIVIDE_BY_12,
        OUTDIV1_DIVIDE_BY_13,
        OUTDIV1_DIVIDE_BY_14,
        OUTDIV1_DIVIDE_BY_15,
        OUTDIV1_DIVIDE_BY_16
    }Outdiv1;
    typedef enum{
        OUTDIV4_DIVIDE_BY_1,
        OUTDIV4_DIVIDE_BY_2,
        OUTDIV4_DIVIDE_BY_3,
        OUTDIV4_DIVIDE_BY_4,
        OUTDIV4_DIVIDE_BY_5,
        OUTDIV4_DIVIDE_BY_6,
        OUTDIV4_DIVIDE_BY_7,
        OUTDIV4_DIVIDE_BY_8
    }Outdiv4;
    void sim_systemClockDivider(Outdiv1 outdiv1, Outdiv4 outdiv4);

    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    uint16_t sim_uniqueIdentificationRegisterMidHigh();//unique identification for the device

    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    uint32_t sim_uniqueIdentificationRegisterMidLow();

    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    uint32_t sim_uniqueIdentificationRegisterLow();

    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    typedef enum{
        COP_DISABLED,
        COP_TIMEOUT_1,  //timeout after 2^5 LPO cycles or 2^13 bus clock cycles
        COP_TIMEOUT_2,  //timeout after 2^8 LPO cycles or 2^16 bus clock cycles
        COP_TIMEOUT_3   //timeout after 2^10 LPO cycles or 2^18 bus clock cycles
    }Copt;
    /*
        copclks:
            0:  Internal 1kHz clock is source to COP
            1:  Bus clock is source to COP
        copw:
            0:  Normal mode
            1:  Windowed mode
    */
    void sim_controlRegister(Copt copt, bool copclks, bool copw);

    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    typedef enum{
        X55,    //write 0x55 and then 0xAA
        XAA
    }Srvcop;
    void sim_(Srvcop srvcop);

#endif
