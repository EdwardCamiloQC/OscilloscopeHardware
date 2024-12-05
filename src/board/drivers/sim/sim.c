#include <sim.h>

void sim_systemOptionRegister1(bool usbregen, bool usbsstby, bool usbvstby, Osc32ksel osc32ksel){
    SIM_SOPT1 = ((uint32_t)usbregen << SIM_SOPT1_USBREGEN_SHIFT) | ((uint32_t)usbsstby << SIM_SOPT1_USBSSTBY_SHIFT) | ((uint32_t)usbvstby << SIM_SOPT1_USBVSTBY_SHIFT) | ((uint32_t)osc32ksel << SIM_SOPT1_OSC32KSEL_SHIFT);
}

void sim_systemOptionRegister1Config(bool usswe, bool uvswe, bool urwe){
    SIM_SOPT1CFG = ((uint32_t)usswe << SIM_SOPT1CFG_USSWE_SHIFT) | ((uint32_t)uvswe << SIM_SOPT1CFG_UVSWE_SHIFT) | ((uint32_t)urwe << SIM_SOPT1CFG_URWE_SHIFT);
}

void sim_systemOptionRegister2(Clksrc uart0src, Clksrc tpmsrc, bool usbsrc, bool pllfllsel, Clkoutsel clkoutsel, bool rtcclkoutsel){
    SIM_SOPT2 = ((uint32_t)uart0src << SIM_SOPT2_UART0SRC_SHIFT) | ((uint32_t)tpmsrc << SIM_SOPT2_TPMSRC_SHIFT) | ((uint32_t)usbsrc << SIM_SOPT2_USBSRC_SHIFT) | ((uint32_t)pllfllsel << SIM_SOPT2_PLLFLLSEL_SHIFT) | ((uint32_t)clkoutsel << SIM_SOPT2_CLKOUTSEL_SHIFT) | ((uint32_t)rtcclkoutsel << SIM_SOPT2_RTCCLKOUTSEL_SHIFT);
}

void sim_systemOptionRegister4(bool tpm2clksel, bool tpm1clksel, bool tpm0clksel, bool tpm2ch0src, bool tpm1ch0src){
    SIM_SOPT4 = ((uint32_t)tpm2clksel << SIM_SOPT4_TPM2CLKSEL_SHIFT) | ((uint32_t)tpm1clksel << SIM_SOPT4_TPM1CLKSEL_SHIFT) | ((uint32_t)tpm0clksel << SIM_SOPT4_TPM0CLKSEL_SHIFT) | ((uint32_t)tpm2ch0src << SIM_SOPT4_TPM2CH0SRC_SHIFT) | ((uint32_t)tpm1ch0src << SIM_SOPT4_TPM1CH0SRC_SHIFT);
}

void sim_systemOptionRegister5(bool uart2ode, bool uart1ode, bool uart0ode, bool uart1rxsrc, Uart1txsrc uart1txsrc, bool uart0rxsrc, Uart0txsrc uart0txsrc){
    SIM_SOPT5 = ((uint32_t)uart2ode << SIM_SOPT5_UART2ODE_SHIFT) | ((uint32_t)uart1ode << SIM_SOPT5_UART1ODE_SHIFT) | ((uint32_t)uart0ode << SIM_SOPT5_UART0ODE_SHIFT) | ((uint32_t)uart1rxsrc << SIM_SOPT5_UART1RXSRC_SHIFT) | ((uint32_t)uart1txsrc << SIM_SOPT5_UART1TXSRC_SHIFT) | ((uint32_t)uart0rxsrc << SIM_SOPT5_UART0RXSRC_SHIFT) | ((uint32_t)uart0txsrc << SIM_SOPT5_UART0TXSRC_SHIFT);
}

void sim_systemOptionRegister7(bool adc0alttrgen, bool adc0pretrgsel, Adc0trgsel adc0trgsel){
    SIM_SOPT7 = ((uint32_t)adc0alttrgen << SIM_SOPT7_ADC0ALTTRGEN_SHIFT) | ((uint32_t)adc0pretrgsel << SIM_SOPT7_ADC0PRETRGSEL_SHIFT) | ((uint32_t)adc0trgsel << SIM_SOPT7_ADC0TRGSEL_SHIFT);
}

uint32_t sim_systemDeviceIdentification(){
    uint32_t reg;
    reg = SIM_SDID;
    return reg;
}

void sim_systemClock_spi_cmp_usb_uart_i2c(ClkEnable clkEnable, bool enable){
    if(enable){
        SIM_SCGC4 |= ((uint32_t)enable << clkEnable);
    }else{
        SIM_SCGC4 &= ~((uint32_t)enable << clkEnable);
    }
}

void sim_systemClock_portx_tsi_lptmr(ClkEnable clkEnable, bool enable){
    if(enable){
        SIM_SCGC5 |= ((uint32_t)enable << clkEnable);
    }else{
        SIM_SCGC5 &= ~((uint32_t)enable << clkEnable);
    }
}

void sim_systemClock_dac_rtc_adc_tpm_pit_dmamux_ftf(ClkEnable clkEnable, bool enable){
    if(enable){
        SIM_SCGC6 |= ((uint32_t)enable << clkEnable);
    }else{
        SIM_SCGC6 &= ~((uint32_t)enable << clkEnable);
    };
}

void sim_systemClock_dma(bool dma){
    SIM_SCGC7 = ((uint32_t)dma << SIM_SCGC7_DMA_SHIFT);
}

void sim_systemClockDivider(Outdiv1 outdiv1, Outdiv4 outdiv4){
    SIM_CLKDIV1 = ((uint32_t)outdiv1 << SIM_CLKDIV1_OUTDIV1_SHIFT) | ((uint32_t)outdiv4 << SIM_CLKDIV1_OUTDIV4_SHIFT);
}

uint16_t sim_uniqueIdentificationRegisterMidHigh(){
    uint32_t reg;
    reg = SIM_UIDMH;
    return (uint16_t)reg;
}

uint32_t sim_uniqueIdentificationRegisterMidLow(){
    return (uint32_t)SIM_UIDML;
}

uint32_t sim_uniqueIdentificationRegisterLow(){
    return (uint32_t)SIM_UIDL;
}

void sim_controlRegister(Copt copt, bool copclks, bool copw){
    SIM_COPC = ((uint32_t)copt << SIM_COPC_COPT_SHIFT) | ((uint32_t)copclks << SIM_COPC_COPCLKS_SHIFT) | ((uint32_t)copw << SIM_COPC_COPW_SHIFT);
}

void sim_(Srvcop srvcop){
    SIM_SRVCOP = ((uint32_t)srvcop << SIM_SRVCOP_SRVCOP_SHIFT);
}
