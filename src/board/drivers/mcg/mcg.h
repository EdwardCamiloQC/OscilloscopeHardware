#ifndef _MCG_H_
    #define _MCG_H_

    #include <stdint.h>

    extern uint32_t mcgOutClk_div;

    void mcg_preconfig();
    int mcg_fei();
    //----------------------
    int mcg_fei_to_fee();
    int mcg_fei_to_fbi();
    int mcg_fei_to_fbe();
    //----------------------
    int mcg_fbi_to_fei();
    int mcg_fbi_to_fee();
    int mcg_fbi_to_fbe();
    int mcg_fbi_to_blpi();
    //----------------------
    int mcg_fee_to_fei();
    int mcg_fee_to_fbi();
    int mcg_fee_to_fbe();
    //----------------------
    int mcg_fbe_to_fei();
    int mcg_fbe_to_fee();
    int mcg_fbe_to_fbi();
    int mcg_fbe_to_blpe();
    int mcg_fbe_to_pbe();
    //----------------------
    int mcg_blpi_to_fbi();
    //----------------------
    int mcg_blpe_to_fbe();
    int mcg_blpe_to_pbe();
    //----------------------
    int mcg_pbe_to_fbe();
    int mcg_pbe_to_blpe();
    int mcg_pbe_to_pee();
    //----------------------
    int mcg_pee_to_pbe();
    //----------------------
    void mcg_stop();
#endif
