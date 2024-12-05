#include <rgb.h>
#include <port.h>
#include <sim.h>
#include <gpio.h>

void init_red(){
    sim_systemClock_portx_tsi_lptmr(PORTB, 1);//Habilita el reloj del puerto b
    port_pinControlRegisters(PORTB_BASE_PTR, 18, IRQ_DMA_DISABLE, ALTERNATIVE1, LOW_DRIVE, FILTER_DISABLED, FAST_SLEW, ENABLE_PULL_RESISTOR, PULLDOWN);
    gpio_inputsOutputs(PTB_BASE_PTR, PTx18, OUTPUT); //habilita en PTB18 como salida
}

void red_on(){
    gpio_logicPin(PTB_BASE_PTR, PTx18, 0);
}

void red_off(){
    gpio_logicPin(PTB_BASE_PTR, PTx18, 1);
}

void red_toggle(){
    gpio_toggle(PTB_BASE_PTR, PTx18, 1);
}

void green_on(){
}

void green_off(){
}

void blue_on(){
}

void blue_off(){
}
