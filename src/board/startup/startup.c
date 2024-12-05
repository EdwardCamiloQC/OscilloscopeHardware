#include <system_MKL25Z4.h>
#include <tpm.h>
#include <pit.h>

int main(void);

//eventos del core
void _reset_handler(void);
void _non_maskable_interrupt(void);
void _hard_fault(void);
void _supervisor_call(void);
void _pendableSrvReq(void);
void _system_tick_timer(void);

extern unsigned int _estack;
extern unsigned int _sidata, _sdata, _edata, _sbss, _ebss;

__attribute__((section(".isr_vector"))) void (* const g_pfnVectors[])(void) = {
    //ARM Core System Handler Vectors
    (void (*)(void))(&_estack),     //initial start pointer
    _reset_handler,                  //initial program counter
    _non_maskable_interrupt,         //non-maskable interrupt
    _hard_fault,                     //hard fault
    _hard_fault,
    _hard_fault,
    _hard_fault,
    _hard_fault,
    _hard_fault,
    _hard_fault,
    _hard_fault,
    _supervisor_call,                //Supervisor call
    _hard_fault,
    _hard_fault,
    _pendableSrvReq,                 //pendable request for system service
    _system_tick_timer,              //system tick timer
    //Non-Core Vectors
    _hard_fault,                     //DMA channel 0 transfer complete and error
    _hard_fault,                     //DMA channel 1 transfer complete and error
    _hard_fault,                     //DMA channel 2 transfer complete and error
    _hard_fault,                     //DMA channel 3 transfer complete and error
    _hard_fault,
    _hard_fault,                     //command complete and read collision
    _hard_fault,                     //Low voltage detect, low voltage warnning
    _hard_fault,                     //Low leakage wakeup
    _hard_fault,                     //I2C 0
    _hard_fault,                     //I2C 1
    _hard_fault,                     //Single interrupt vector for all sources (SPI 0)
    _hard_fault,                     //Single interrupt vector for all sources (SPI 1)
    _hard_fault,                     //Status and error (UART 0)
    _hard_fault,                     //Status and error (UART 1)
    _hard_fault,                     //Status and error (UART 2)
    _hard_fault,                     //ADC 0
    _hard_fault,                     //CMP 0
    _irqHandler_TPM0,                //TPM 0
    _hard_fault,                     //TPM 1
    _hard_fault,                     //TPM 2
    _hard_fault,                     //Alarm interrupt (RTC)
    _hard_fault,                     //Seconds interrupt (RTC)
    _irqHandler_PIT,                 //Single interrupt vector for all channels (PIT)
    _hard_fault,
    _hard_fault,                     //USB OTG
    _hard_fault,                     //DAC 0
    _hard_fault,                     //TSI 0
    _hard_fault,                     //MCG
    _hard_fault,                     //LPTMR 0
    _hard_fault,
    _hard_fault,                     //Pin detect (Port A) port control module
    _hard_fault                      //Pin detect (Port D) port control module
};

void _reset_handler(void){
    unsigned int *src = &_sidata;
    unsigned int *dst = &_sdata;

    while(dst < &_edata){
        *dst++ = *src++;
    }

    dst = &_sbss;
    while(dst < &_ebss){
        *dst++ = 0;
    }

    SystemInit();

    main();
    while(1);
}

void _non_maskable_interrupt(void){
    while(1);
}

void _hard_fault(void){
    while(1);
}

void _supervisor_call(void){
    while(1);
}

void _pendableSrvReq(void){
    while(1);
}

void _system_tick_timer(void){
    while(1);
}
