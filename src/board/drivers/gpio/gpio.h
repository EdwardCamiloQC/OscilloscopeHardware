#ifndef _GPIO_H_
    #define _GPIO_H_

    #include <MKL25Z4.h>

    typedef enum{
        PTx0,
        PTx1,
        PTx2,
        PTx3,
        PTx4,
        PTx5,
        PTx6,
        PTx7,
        PTx8,
        PTx9,
        PTx10,
        PTx11,
        PTx12,
        PTx13,
        PTx14,
        PTx15,
        PTx16,
        PTx17,
        PTx18,
        PTx19,
        PTx20,
        PTx21,
        PTx22,
        PTx23,
        PTx24,
        PTx25,
        PTx26,
        PTx27,
        PTx28,
        PTx29,
        PTx30,
        PTx31
    }PINx;

    typedef enum{
        INPUT,
        OUTPUT
    }IOpin;

    /*
        port:
            PTA_BASE_PTR
            PTB_BASE_PTR
            PTC_BASE_PTR
            PTD_BASE_PTR
            PTE_BASE_PTR
        level:
            0
            1
        clear:
            0
            1
        pins:
            0
            1
    */
    void gpio_logicLevels(GPIO_MemMapPtr port, PINx pin, uint8_t level);
    void gpio_logicPin(GPIO_MemMapPtr port, PINx pin, uint8_t level);
    void gpio_clearLevels(GPIO_MemMapPtr port, PINx pin, uint8_t clear);
    void gpio_toggle(GPIO_MemMapPtr port, PINx pin, uint8_t pins);
    uint32_t gpio_getLevels(GPIO_MemMapPtr port);
    void gpio_inputsOutputs(GPIO_MemMapPtr port, PINx pin, IOpin io);

#endif
