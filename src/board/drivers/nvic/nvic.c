#include <nvic.h>
#include <MKL25Z4.h>

void nvic_irqEnable(VectorIrq irq){
    if(irq < 32){
        NVIC_ISER |= (uint32_t)(1 << irq);
    }
}

void nvic_irqDisable(VectorIrq irq){
    if(irq < 32){
        NVIC_ICER |= (uint32_t)(1 << irq);
    }
}

void nvic_irqPriority(uint8_t ipr, VectorIrq irq, uint32_t priority){
    if(ipr < 8 && priority < 4 && irq < 32){
        NVIC_IP(ipr) |= (~((uint32_t)(priority << (8*(irq%4)+6))) & (NVIC_IP(ipr))) | ((uint32_t)(priority << (8*(irq%4)+6)));
    }
}

void nvic_cleanFlagPending(VectorIrq irq){
    NVIC_ICPR |= (uint32_t)(1 << irq);
}
