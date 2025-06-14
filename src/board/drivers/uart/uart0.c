#include <uart0.h>
#include <MKL25Z4.h>
#include <nvic.h>
#include <stddef.h>
#include <tgmath.h>
#include <sim.h>
#include <port.h>

extern uint32_t SystemCoreClock;
volatile char received_char;
volatile bool flagReceived = 0;

void _irqHandler_UART0(void){
  //Interrupcion por recepcion
  if(UART0_S1 & UART0_S1_RDRF_MASK){
    received_char = UART0_D;
    flagReceived = 1;
  }
}

void uart0_config(Baudrate baudRate, bool stopBits, bool parity, bool typeParity){
  uint32_t br, baudCalculate;
  uint8_t osr = 4, diference1, diference2;
  br = (uint32_t)(SystemCoreClock / (baudRate * (osr + 1)));
  baudCalculate = (uint32_t)(SystemCoreClock / (br * (osr + 1)));
  diference1 = (uint8_t)(fabs(baudRate - baudCalculate));
  for(uint8_t i = 5; i <= 32; i++){
    br = (uint32_t)(SystemCoreClock / (baudRate * (i + 1)));
    baudCalculate = (uint32_t)(SystemCoreClock / (br * (i + 1)));
    diference2 = (uint8_t)(fabs(baudRate - baudCalculate));
    if(diference2 <= diference1){
      osr = i;
    }
  }
  br = (uint32_t)(SystemCoreClock / (baudRate * (osr + 1)));
  sim_systemClock_spi_cmp_usb_uart_i2c(UART0, 1);
  port_pinControlRegisters(PORTA_BASE_PTR, 1, IRQ_DMA_DISABLE, ALTERNATIVE2, LOW_DRIVE, FILTER_DISABLED, FAST_SLEW, DISABLED_PULL_RESISTOR, PULLDOWN);
  port_pinControlRegisters(PORTA_BASE_PTR, 2, IRQ_DMA_DISABLE, ALTERNATIVE2, LOW_DRIVE, FILTER_DISABLED, FAST_SLEW, DISABLED_PULL_RESISTOR, PULLDOWN);
  sim_systemOptionRegister2(CLKSRC_MCGFLLCLK, CLKSRC_CLOCK_DISABLED, 0, 0, BUS_CLOCK, 0);
  UART0_C2 = ((uint8_t)(~(UART0_C2_TE_MASK | UART0_C2_RE_MASK)) & UART0_C2) |
    ((uint8_t)0 << UART0_C2_TE_SHIFT) | ((uint8_t)0 << UART0_C2_RE_SHIFT);
  UART0_BDH = ((uint8_t)(~(UART0_BDH_LBKDIE_MASK | UART0_BDH_RXEDGIE_MASK | UART0_BDH_SBNS_MASK | UART0_BDH_SBR_MASK)) & UART0_BDH) |
    ((uint8_t)0 << UART0_BDH_LBKDIE_SHIFT) | ((uint8_t)0 << UART0_BDH_RXEDGIE_SHIFT) | ((uint8_t)stopBits << UART0_BDH_SBNS_SHIFT) | UART0_BDH_SBR((br & 0x1F00) >> 8);
  UART0_BDL = (uint8_t)(br & UART0_BDL_SBR_MASK);
  UART0_C1 = ((uint8_t)(~(UART0_C1_PE_MASK | UART0_C1_PT_MASK)) & UART0_C1) |
    ((uint8_t)parity << UART0_C1_PE_SHIFT) | ((uint8_t)typeParity << UART0_C1_PT_SHIFT);
  UART0_C4 = ((uint8_t)(~(UART0_C4_OSR_MASK)) & UART0_C4) |
    UART0_C4_OSR(osr);
}

void uart0_init(bool irqTxTDRE, bool irqTxTC, bool irqRxRDRF, bool irqIdle, bool enableTx, bool enableRx, bool dmaTx, bool dmaRx){
  UART0_C5 = ((uint8_t)(~(UART0_C5_TDMAE_MASK | UART0_C5_RDMAE_MASK | UART0_C5_BOTHEDGE_MASK)) & UART0_C5) |
    ((uint8_t)dmaTx<<UART0_C5_TDMAE_SHIFT) | ((uint8_t)dmaRx<<UART0_C5_RDMAE_SHIFT) | ((uint8_t)1 << UART0_C5_BOTHEDGE_SHIFT);
  UART0_C2 = ((uint8_t)(~(UART0_C2_TIE_MASK | UART0_C2_TCIE_MASK | UART0_C2_RIE_MASK | UART0_C2_ILIE_MASK | UART0_C2_TE_MASK | UART0_C2_RE_MASK)) & UART0_C2) |
    ((uint8_t)irqTxTDRE<<UART0_C2_TIE_SHIFT) | ((uint8_t)irqTxTC<<UART0_C2_TCIE_SHIFT) | ((uint8_t)irqRxRDRF << UART0_C2_RIE_SHIFT) | ((uint8_t)irqIdle<<UART0_C2_ILIE_SHIFT) | ((uint8_t)enableTx<<UART0_C2_TE_SHIFT) | ((uint8_t)enableRx<<UART0_C2_RE_SHIFT);
  if(irqTxTDRE || irqTxTC || irqRxRDRF){
    nvic_irqEnable(VECTOR_UART0);
  }
}

void uart0_sendData(const uint8_t* data, uint8_t size){
  for(size_t i = 0; i < size; i++){
    while(!(UART0_S1 & UART0_S1_TDRE_MASK));
    UART0_D = data[i];
  }
}
