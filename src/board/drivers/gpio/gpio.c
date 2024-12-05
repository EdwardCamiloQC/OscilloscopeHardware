#include <gpio.h>

void gpio_logicLevels(GPIO_MemMapPtr port, PINx pin, uint8_t level){
    if(level){
        GPIO_PDOR_REG(port) &= ~((uint32_t)level << pin);
    }else{
        GPIO_PDOR_REG(port) |= (uint32_t)level << pin;
    }
}

void gpio_logicPin(GPIO_MemMapPtr port, PINx pin, uint8_t level){
    GPIO_PSOR_REG(port) |= level << pin;
}

void gpio_clearLevels(GPIO_MemMapPtr port, PINx pin, uint8_t clear){
    GPIO_PCOR_REG(port) |= clear << pin;
}

void gpio_toggle(GPIO_MemMapPtr port, PINx pin, uint8_t pins){
    GPIO_PTOR_REG(port) |= ((uint32_t)pins << pin);
}

uint32_t gpio_getLevels(GPIO_MemMapPtr port){
    return GPIO_PDIR_REG(port);
}

void gpio_inputsOutputs(GPIO_MemMapPtr port, PINx pin, IOpin io){
    GPIO_PDDR_REG(port) |= io << pin;
}
