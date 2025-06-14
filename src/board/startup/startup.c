#include <stdint.h>
#include <system_MKL25Z4.h>
#include <tpm.h>
#include <pit.h>
#include <uart0.h>
#include <adc.h>
#include <dma.h>

// Símbolos para copiar .data y limpiar .bss
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
// Símbolos de inicialización/finalización de C++
extern void (*__preinit_array_start[])(void);
extern void (*__preinit_array_end[])(void);
extern void _init(void) __attribute__((weak));
extern void (*__init_array_start[])(void);
extern void (*__init_array_end[])(void);
// Símbolos de finalización de C++
extern void (*__fini_array_start[])(void);
extern void (*__fini_array_end[])(void);
extern void _finit(void) __attribute__((weak));
// Símbolos de heap/stack
extern uint32_t _sheap;
extern uint32_t _eheap;
extern uint32_t _sstack;
extern uint32_t _estack;

//  Prototipos de handlers, main
int main(void);
//eventos del core
void _reset_handler(void)           __attribute__((noreturn));
void _non_maskable_interrupt(void)  __attribute__((weak, alias("_default_handler")));
void _hard_fault(void)              __attribute__((weak, alias("_default_handler")));
void _supervisor_call(void)         __attribute__((weak, alias("_default_handler")));
void _pendableSrvReq(void)          __attribute__((weak, alias("_default_handler")));
void _system_tick_timer(void)       __attribute__((weak, alias("_default_handler")));

void _default_handler(void){
    while(1);
}

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
    _irqHandler_DMA0,                //DMA channel 0 transfer complete and error
    _irqHandler_DMA1,                //DMA channel 1 transfer complete and error
    _irqHandler_DMA2,                //DMA channel 2 transfer complete and error
    _irqHandler_DMA3,                //DMA channel 3 transfer complete and error
    _hard_fault,
    _hard_fault,                     //command complete and read collision
    _hard_fault,                     //Low voltage detect, low voltage warnning
    _hard_fault,                     //Low leakage wakeup
    _hard_fault,                     //I2C 0
    _hard_fault,                     //I2C 1
    _hard_fault,                     //Single interrupt vector for all sources (SPI 0)
    _hard_fault,                     //Single interrupt vector for all sources (SPI 1)
    _irqHandler_UART0,               //Status and error (UART 0)
    _hard_fault,                     //Status and error (UART 1)
    _hard_fault,                     //Status and error (UART 2)
    _irqHandler_ADC0,                //ADC 0
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
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;

    // Copiar .data de flash a ram
    while(dst < &_edata){
        *dst++ = *src++;
    }

    // .bss a cero
    dst = &_sbss;
    while(dst < &_ebss){
        *dst++ = 0;
    }

    // Ejecutar funciones en .preinit_array
    {
        void (**fn)(void) = __preinit_array_start;
        for(;fn < __preinit_array_end; fn++){
            (*fn)();
        }
    }

    // Ejecutar _init
    if(_init){
        _init();
    }

    // Ejecutar funciones .init_array (constructores)
    {
        void (**fn)(void) = __init_array_start;
        for(; fn < __init_array_end; fn++){
            (*fn)();
        }
    }

    //__libc_init_array();

    SystemInit();
    main();

    // Ejecutar funciones en .fini_array (destructores)
    {
        void (**fn)(void) = __fini_array_start;
        for(; fn < __fini_array_end; fn++){
            (*fn)();
        }
    }

    // Ejecutar _fini
    if(_fini){
        _fini();
    }
    
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
