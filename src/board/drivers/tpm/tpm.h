#ifndef _TPM_H_
    #define _TPM_H_

    void _irqHandler_TPM0(void);
#endif

/*void _irqHandler_TPM0(void){
    if(TPM0_SC && TPM_SC_TOF_MASK){     //verificar si el overflow es causada por el Timer0
        TPM0_SC &= ~TPM_SC_TOF_MASK;    //limpiar el flag de overflow
        red_toggle();
    }
}*/