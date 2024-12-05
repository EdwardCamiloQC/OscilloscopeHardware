#include <pit.h>
#include <MKL25Z4.h>
#include <sim.h>
#include <nvic.h>
#include <rgb.h>

extern uint32_t SystemCoreClock;

void _irqHandler_PIT(void){
    if(pit_timerFlag(0, 0)){
        pit_timerFlag(1, 0);
        red_toggle();
    }
}

void pit_init(uint32_t time_us){
    sim_systemClock_dac_rtc_adc_tpm_pit_dmamux_ftf(PIT, 1);
    pit_moduleControl(0, 0);
    // Calcular el valor de recarga del timer
    uint32_t load_value = (SystemCoreClock * (time_us / 1000000)) - 1;
    
    // Cargar el valor del timer en el canal 0
    pit_timerLoadValue(load_value, 0);
    
    // Habilitar la interrupción para el canal 0
    // Habilitar el timer (inicia el conteo)
    pit_timerControl(0, 1, 1, 0);
    
    // Habilitar las interrupciones en el NVIC para el PIT
    nvic_irqEnable(VECTOR_PIT);
}

void pit_stop(){
    pit_moduleControl(1, 0);
}

void pit_moduleControl(bool mdis, bool frz){
    PIT_MCR = ((uint32_t)mdis << PIT_MCR_MDIS_SHIFT) | ((uint32_t)frz << PIT_MCR_FRZ_SHIFT);
}

uint64_t pit_lifetimeTimer(){
    uint64_t lifetime = 0;
    lifetime = ((uint64_t)PIT_LTMR64H << 32) | ((uint64_t)PIT_LTMR64L);
    return lifetime;
}

void pit_timerLoadValue(uint32_t value, bool n){
    PIT_LDVAL(n) = value;
}

uint32_t pit_currentTimerValue(bool n){
    uint32_t reg = PIT_CVAL(n);
    return reg;
}

void pit_timerControl(bool chn, bool tie, bool ten, bool n){
    PIT_TCTRL(n) = ((uint32_t)chn << PIT_TCTRL_CHN_SHIFT) | ((uint32_t)tie << PIT_TCTRL_TIE_SHIFT) | ((uint32_t)ten << PIT_TCTRL_TEN_SHIFT);
}

bool pit_timerFlag(bool clean, bool n){
    bool reg;
    if(clean){
        PIT_TFLG(0) = 0x00000000UL;
    }else{
        reg = PIT_TFLG(n) & PIT_TFLG_TIF_MASK;
        return reg;
    }
    return 0;
}
