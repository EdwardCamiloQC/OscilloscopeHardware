#include <mcg.h>
#include <MKL25Z4.h>
#include <stdbool.h>

void mcg_preconfig(){
    OSC0_CR = ((uint8_t)1 << OSC_CR_ERCLKEN_SHIFT) | ((uint8_t)0 << OSC_CR_EREFSTEN_SHIFT) | ((uint8_t)1 << OSC_CR_SC2P_SHIFT) | ((uint8_t)0 << OSC_CR_SC4P_SHIFT) | ((uint8_t)0 << OSC_CR_SC8P_SHIFT) | ((uint8_t)1 << OSC_CR_SC16P_SHIFT);
    MCG_C1 = ((uint8_t)(~(MCG_C1_FRDIV_MASK | MCG_C1_IRCLKEN_MASK | MCG_C1_IREFSTEN_MASK)) & MCG_C1) | MCG_C1_FRDIV(3) | ((uint8_t)1 << MCG_C1_IRCLKEN_SHIFT) | ((uint8_t)0 << MCG_C1_IREFSTEN_SHIFT);
    MCG_C2 = ((uint8_t)(~(MCG_C2_RANGE0_MASK | MCG_C2_HGO0_MASK | MCG_C2_IRCS_MASK)) & MCG_C2) | MCG_C2_RANGE0(1) | ((uint8_t)0 << MCG_C2_HGO0_SHIFT) | ((uint8_t)0 << MCG_C2_IRCS_SHIFT);
    MCG_C4 = ((uint8_t)(~(MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS_MASK)) & MCG_C4) | ((uint8_t)1 << MCG_C4_DMX32_SHIFT) | MCG_C4_DRST_DRS(1);
    MCG_SC = ((uint8_t)(~(MCG_SC_FLTPRSRV_MASK)) & MCG_SC) | ((uint8_t)0 << MCG_SC_FLTPRSRV_SHIFT);
    MCG_C5 = ((uint8_t)(~(MCG_C5_PLLCLKEN0_MASK | MCG_C5_PLLSTEN0_MASK | MCG_C5_PRDIV0_MASK)) & MCG_C5) | ((uint8_t)1 << MCG_C5_PLLCLKEN0_SHIFT) | ((uint8_t)0 << MCG_C5_PLLSTEN0_SHIFT) | MCG_C5_PRDIV0(3);
    MCG_C6 = ((uint8_t)(~(MCG_C6_VDIV0_MASK)) & MCG_C6) | MCG_C6_VDIV0(0);
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
bool checkFEImode(){
    if((MCG_S & (MCG_S_PLLST_MASK | MCG_S_IREFST_MASK | MCG_S_CLKST_MASK)) ==
        (((uint8_t)0 << MCG_S_PLLST_SHIFT) | ((uint8_t)1 << MCG_S_IREFST_SHIFT) | MCG_S_CLKST(0)))
    {
        return 0;
    }
    return 1;
}

bool checkFEEmode(){
    if((MCG_S & (MCG_S_PLLST_MASK | MCG_S_IREFST_MASK | MCG_S_CLKST_MASK)) ==
        (((uint8_t)0 << MCG_S_PLLST_SHIFT) | ((uint8_t)0 << MCG_S_IREFST_SHIFT) | MCG_S_CLKST(0)))
    {
        return 0;
    }
    return 1;
}

bool checkFBImode(){
    if((MCG_S & (MCG_S_PLLST_MASK | MCG_S_IREFST_MASK | MCG_S_CLKST_MASK)) ==
        (((uint8_t)0 << MCG_S_PLLST_SHIFT) | ((uint8_t)1 << MCG_S_IREFST_SHIFT) | MCG_S_CLKST(1)))
    {
        return 0;
    }
    return 1;
}

bool checkFBEmode(){
    if((MCG_S & (MCG_S_PLLST_MASK | MCG_S_IREFST_MASK | MCG_S_CLKST_MASK)) ==
        (((uint8_t)0 << MCG_S_PLLST_SHIFT) | ((uint8_t)0 << MCG_S_IREFST_SHIFT) | MCG_S_CLKST(2)))
    {
        return 0;
    }
    return 1;
}

bool checkPEEmode(){
    if((MCG_S & (MCG_S_PLLST_MASK | MCG_S_IREFST_MASK | MCG_S_CLKST_MASK)) ==
        (((uint8_t)1 << MCG_S_PLLST_SHIFT) | ((uint8_t)0 << MCG_S_IREFST_SHIFT) | MCG_S_CLKST(0)))
    {
        return 0;
    }
    return 1;
}

bool checkPBEmode(){
    if((MCG_S & (MCG_S_PLLST_MASK | MCG_S_IREFST_MASK | MCG_S_CLKST_MASK)) ==
        (((uint8_t)1 << MCG_S_PLLST_SHIFT) | ((uint8_t)0 << MCG_S_IREFST_SHIFT) | MCG_S_CLKST(2)))
    {
        return 0;
    }
    return 1;
}

bool checkBLPImode(){
    if((MCG_S & (MCG_S_PLLST_MASK | MCG_S_IREFST_MASK | MCG_S_CLKST_MASK)) ==
        (((uint8_t)0 << MCG_S_PLLST_SHIFT) | ((uint8_t)1 << MCG_S_IREFST_SHIFT) | MCG_S_CLKST(1)))
    {
        return 0;
    }
    return 1;
}

bool checkBLPEmode(){
    if((MCG_S & ( MCG_S_IREFST_MASK | MCG_S_CLKST_MASK)) ==
        (((uint8_t)0 << MCG_S_IREFST_SHIFT) | MCG_S_CLKST(2)))
    {
        return 0;
    }
    return 1;
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
int mcg_fei(){
    mcg_preconfig();
    MCG_C1 = ((uint8_t)(~(MCG_C1_CLKS_MASK | MCG_C1_IREFS_MASK)) & MCG_C1) | MCG_C1_CLKS(0) | ((uint8_t)1 << MCG_C1_IREFS_SHIFT);
    MCG_C6 = ((uint8_t)(~(MCG_C6_PLLS_MASK)) & MCG_C6) | ((uint8_t)0 << MCG_C6_PLLS_SHIFT);
    for(uint8_t t=0; t<200; t++){
        if(checkFEImode()){
            return 0;
        }
    }
    return 1;
}

int mcg_fee(){
    MCG_C1 = ((uint8_t)(~(MCG_C1_CLKS_MASK | MCG_C1_FRDIV_MASK | MCG_C1_IREFS_MASK)) & MCG_C1) | MCG_C1_CLKS(0) | MCG_C1_FRDIV(3) | ((uint8_t)0 << MCG_C1_IREFS_SHIFT);
    MCG_C6 = ((uint8_t)(~(MCG_C6_PLLS_MASK)) & MCG_C6) | ((uint8_t)0 << MCG_C6_PLLS_SHIFT);
    for(uint8_t t=0; t<200; t++){
        if(checkFEEmode()){
            return 0;
        }
    }
    return 1;
}

int mcg_fbi(){
    MCG_C1 = ((uint8_t)(~(MCG_C1_CLKS_MASK | MCG_C1_IREFS_MASK)) & MCG_C1) | MCG_C1_CLKS(1) | ((uint8_t)1 << MCG_C1_IREFS_SHIFT);
    MCG_C6 = ((uint8_t)(~(MCG_C6_PLLS_MASK)) & MCG_C6) | ((uint8_t)0 << MCG_C6_PLLS_SHIFT);
    MCG_C2 = ((uint8_t)(~(MCG_C2_LP_MASK)) & MCG_C2) | ((uint8_t)0 << MCG_C2_LP_SHIFT);
    for(uint8_t t=0; t<200; t++){
        if(checkFBImode()){
            return 0;
        }
    }
    return 1;
}

int mcg_fbe(){
    MCG_C1 = ((uint8_t)(~(MCG_C1_CLKS_MASK | MCG_C1_FRDIV_MASK | MCG_C1_IREFS_MASK)) & MCG_C1) | MCG_C1_CLKS(2) | MCG_C1_FRDIV(3) | ((uint8_t)0 << MCG_C1_IREFS_SHIFT);
    MCG_C6 = ((uint8_t)(~(MCG_C6_PLLS_MASK)) & MCG_C6) | ((uint8_t)0 << MCG_C6_PLLS_SHIFT);
    MCG_C2 = ((uint8_t)(~(MCG_C2_LP_MASK)) & MCG_C2) | ((uint8_t)0 << MCG_C2_LP_SHIFT);
    for(uint8_t t=0; t<200; t++){
        if(checkFBEmode()){
            return 0;
        }
    }
    return 1;
}

int mcg_pee(){
    MCG_C1 = ((uint8_t)(~(MCG_C1_CLKS_MASK | MCG_C1_IREFS_MASK)) & MCG_C1) | MCG_C1_CLKS(0) | ((uint8_t)0 << MCG_C1_IREFS_SHIFT);
    MCG_C6 = ((uint8_t)(~(MCG_C6_PLLS_MASK)) & MCG_C6) | ((uint8_t)1 << MCG_C6_PLLS_SHIFT);
    for(uint8_t t=0; t<200; t++){
        if(checkPEEmode()){
            return 0;
        }
    }
    return 1;
}

int mcg_pbe(){
    MCG_C1 = ((uint8_t)(~(MCG_C1_CLKS_MASK | MCG_C1_IREFS_MASK)) & MCG_C1) | MCG_C1_CLKS(2) | ((uint8_t)0 << MCG_C1_IREFS_SHIFT);
    MCG_C6 = ((uint8_t)(~(MCG_C6_PLLS_MASK)) & MCG_C6) | ((uint8_t)1 << MCG_C6_PLLS_SHIFT);
    MCG_C2 = ((uint8_t)(~(MCG_C2_LP_MASK)) & MCG_C2) | ((uint8_t)0 << MCG_C2_LP_SHIFT);
    for(uint8_t t=0; t<200; t++){
        if(checkPBEmode()){
            return 0;
        }
    }
    return 1;
}

int mcg_blpi(){
    MCG_C1 = ((uint8_t)(~(MCG_C1_CLKS_MASK | MCG_C1_IREFS_MASK)) & MCG_C1) | MCG_C1_CLKS(1) | ((uint8_t)1 << MCG_C1_IREFS_SHIFT);
    MCG_C6 = ((uint8_t)(~(MCG_C6_PLLS_MASK)) & MCG_C6) | ((uint8_t)0 << MCG_C6_PLLS_SHIFT);
    MCG_C2 = ((uint8_t)(~(MCG_C2_LP_MASK)) & MCG_C2) | ((uint8_t)1 << MCG_C2_LP_SHIFT);
    for(uint8_t t=0; t<200; t++){
        if(checkBLPImode()){
            return 0;
        }
    }
    return 1;
}

int mcg_blpe(){
    MCG_C1 = ((uint8_t)(~(MCG_C1_CLKS_MASK | MCG_C1_IREFS_MASK)) & MCG_C1) | MCG_C1_CLKS(2) | MCG_C1_FRDIV(3) | ((uint8_t)0 << MCG_C1_IREFS_SHIFT);
    MCG_C2 = ((uint8_t)(~(MCG_C2_LP_MASK)) & MCG_C2) | ((uint8_t)1 << MCG_C2_LP_SHIFT);
    for(uint8_t t=0; t<200; t++){
        if(checkBLPEmode()){
            return 0;
        }
    }
    return 1;
}

void mcg_stop(){
    //MCG_C1 = ((uint8_t)(~(MCG_C1_IRCLKEN_MASK | MCG_C1_IREFSTEN_MASK)) & MCG_C1) | ((uint8_t)1 << MCG_C1_IRCLKEN_SHIFT) | ((uint8_t)1 << MCG_C1_IREFSTEN_SHIFT);
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
int mcg_fei_to_fee(){
    if(checkFEImode()){
        return 1;
    }
    mcg_fee();
    return 0;
}

int mcg_fei_to_fbi(){
    if(checkFEImode()){
        return 1;
    }
    mcg_fbi();
    return 0;
}

int mcg_fei_to_fbe(){
    if(checkFEImode()){
        return 1;
    }
    mcg_fbe();
    return 0;
}

int mcg_fbi_to_fei(){
    if(checkFBImode()){
        return 1;
    }
    mcg_fei();
    return 0;
}

int mcg_fbi_to_fee(){
    if(checkFBImode()){
        return 1;
    }
    mcg_fee();
    return 0;
}

int mcg_fbi_to_fbe(){
    if(checkFBImode()){
        return 1;
    }
    mcg_fbe();
    return 0;
}

int mcg_fbi_to_blpi(){
    if(checkFBImode()){
        return 1;
    }
    mcg_blpi();
    return 0;
}

int mcg_fee_to_fei(){
    if(checkFEEmode()){
        return 1;
    }
    mcg_fei();
    return 0;
}

int mcg_fee_to_fbi(){
    if(checkFEEmode()){
        return 1;
    }
    mcg_fbi();
    return 0;
}

int mcg_fee_to_fbe(){
    if(checkFEEmode()){
        return 1;
    }
    mcg_fbe();
    return 0;
}

int mcg_fbe_to_fei(){
    if(checkFBEmode()){
        return 1;
    }
    mcg_fei();
    return 0;
}

int mcg_fbe_to_fee(){
    if(checkFBEmode()){
        return 1;
    }
    mcg_fee();
    return 0;
}

int mcg_fbe_to_fbi(){
    if(checkFBEmode()){
        return 1;
    }
    mcg_fbi();
    return 0;
}

int mcg_fbe_to_blpe(){
    if(checkFBEmode()){
        return 1;
    }
    mcg_blpe();
    return 0;
}

int mcg_fbe_to_pbe(){
    if(checkFBEmode()){
        return 1;
    }
    mcg_pbe();
    return 0;
}

int mcg_blpi_to_fbi(){
    if(checkBLPImode()){
        return 1;
    }
    mcg_fbi();
    return 0;
}

int mcg_blpe_to_fbe(){
    if(checkBLPEmode()){
        return 1;
    }
    mcg_fbe();
    return 0;
}

int mcg_blpe_to_pbe(){
    if(checkBLPEmode()){
        return 1;
    }
    mcg_pbe();
    return 0;
}

int mcg_pbe_to_fbe(){
    if(checkPBEmode()){
        return 1;
    }
    mcg_fbe();
    return 0;
}

int mcg_pbe_to_blpe(){
    if(checkPBEmode()){
        return 1;
    }
    mcg_blpe();
    return 0;
}

int mcg_pbe_to_pee(){
    if(checkPBEmode()){
        return 1;
    }
    mcg_pee();
    return 0;
}

int mcg_pee_to_pbe(){
    if(checkPEEmode()){
        return 1;
    }
    mcg_pbe();
    return 0;
}
