#include <port.h>

void port_pinControlRegisters(PORT_MemMapPtr port, uint8_t pin, Irqc irqc, Mux mux, Dse dse, Pfe pfe, Sre sre, Pe pe, Ps ps){
    uint32_t val = ((uint32_t)irqc << PORT_PCR_IRQC_SHIFT) | ((uint32_t)mux << PORT_PCR_MUX_SHIFT) | ((uint32_t)dse << PORT_PCR_DSE_SHIFT) | ((uint32_t)pfe << PORT_PCR_PFE_SHIFT) | ((uint32_t)sre << PORT_PCR_SRE_SHIFT) | ((uint32_t)pe << PORT_PCR_PE_SHIFT) |((uint32_t)ps << PORT_PCR_PS_SHIFT);
    PORT_PCR_REG(port, pin) = ((uint32_t)PORT_PCR_REG(port, pin) & (uint32_t)PORT_PCR_ISF_MASK) | val;
}

uint32_t port_interruptStatusFlag(PORT_MemMapPtr port, uint8_t pin){
    uint32_t flagIrq;
    flagIrq = (PORT_PCR_REG(port, pin) & PORT_PCR_ISF_MASK) >> PORT_PCR_ISF_SHIFT;
    return flagIrq;
}

void port_cleanFlagISF(PORT_MemMapPtr port, uint8_t pin){
    PORT_PCR_REG(port, pin) &= ~((uint32_t)PORT_PCR_ISF_MASK);
}

void port_globalControl(PORT_MemMapPtr port, uint16_t gpwe_low, uint16_t gpwd_low, uint16_t gpwe_high, uint16_t gpwd_high){
    PORT_GPCLR_REG(port) = ((uint16_t)gpwe_low << PORT_GPCLR_GPWE_SHIFT) | ((uint16_t)gpwd_low << PORT_GPCLR_GPWD_SHIFT);
    PORT_GPCHR_REG(port) = ((uint16_t)gpwe_high << PORT_GPCHR_GPWE_SHIFT) | ((uint16_t)gpwd_high << PORT_GPCHR_GPWD_SHIFT);
}

uint32_t port_interruptFlags(PORT_MemMapPtr port){
    uint32_t flagsIrq;
    flagsIrq = PORT_ISFR_REG(port);
    return flagsIrq;
}
