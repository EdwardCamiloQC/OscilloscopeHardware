//#include <MKL25Z4.h>
#include <uart0.h>
#include <adc.h>
//#include <dma.h>

volatile uint8_t adc0[4] = {'#', 0, 0, '\n'};

int main(void){
    uart0_config(Baudrate_460800, 0, 0, 0);
    adc0_config(0, 0, 1);
    /*dma_config(
        ADC0_SOURCE,    0,(uint32_t)(&ADC0_RA),(uint32_t)&adc0[1],  0,0,0,BITS_16,1,BITS_8, CIRCULAR_BUFFER_DISABLED,CIRCULAR_BUFFER_DISABLED,
        UART0_TX_SOURCE,0,(uint32_t)adc0,      (uint32_t)(&UART0_D),0,0,1,BITS_8, 0,BITS_8 ,CIRCULAR_BUFFER_DISABLED,CIRCULAR_BUFFER_DISABLED,
        DISABLED_SOURCE,0,0,                   0,                   0,0,0,BITS_32,0,BITS_32,CIRCULAR_BUFFER_DISABLED,CIRCULAR_BUFFER_DISABLED,
        DISABLED_SOURCE,0,0,                   0,                   0,0,0,BITS_32,0,BITS_32,CIRCULAR_BUFFER_DISABLED,CIRCULAR_BUFFER_DISABLED);*/

    uart0_init(0, 0, 0, 0, 1, 0, 1, 0);
    adc0_init(0);
    //dma_init(2,1,1,1,  4,1,1,1,  0,0,0,0,  0,0,0,0);

    while(1){
    }

    return 0;
}
