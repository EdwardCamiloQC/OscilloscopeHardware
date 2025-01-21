/*
** ###################################################################
**     Processor:           MKL25Z128VLK4
**     Compilers:           ARM Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    KL25RM, Rev.1, Jun 2012
**     Version:             rev. 1.1, 2012-06-21
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright: 2012 Freescale Semiconductor, Inc. All Rights Reserved.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2012-06-13)
**         Initial version.
**     - rev. 1.1 (2012-06-21)
**         Update according to reference manual rev. 1.
**
** ###################################################################
*/

/**
 * @file MKL25Z4
 * @version 1.1
 * @date 2012-06-21
 * @brief Device specific configuration file for MKL25Z4 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "MKL25Z4.h"
#include <sim.h>
#include <port.h>
#include <mcg.h>

#define DISABLE_WDOG    1

#ifdef USB
#define CLOCK_SETUP     2
#else
#define CLOCK_SETUP     1
#endif

/* Predefined clock setups
   0 ... Multipurpose Clock Generator (MCG) in FLL Engaged Internal (FEI) mode
         Reference clock source for MCG module is the slow internal clock source 32.768kHz
         Core clock = 41.94MHz, BusClock = 13.98MHz
   1 ... Multipurpose Clock Generator (MCG) in PLL Engaged External (PEE) mode
         Reference clock source for MCG module is an external crystal 8MHz
         Core clock = 48MHz, BusClock = 24MHz
   2 ... Multipurpose Clock Generator (MCG) in Bypassed Low Power External (BLPE) mode
         Core clock/Bus clock derived directly from an external crystal 8MHz with no multiplication
         Core clock = 8MHz, BusClock = 8MHz
*/

/*----------------------------------------------------------------------------
  Define clock source values
 *----------------------------------------------------------------------------*/
#if (CLOCK_SETUP == 0)
    #define CPU_XTAL_CLK_HZ                 8000000u /* Value of the external crystal or oscillator clock frequency in Hz */
    #define CPU_INT_SLOW_CLK_HZ             32768u   /* Value of the slow internal oscillator clock frequency in Hz  */
    #define CPU_INT_FAST_CLK_HZ             4000000u /* Value of the fast internal oscillator clock frequency in Hz  */
    #define DEFAULT_SYSTEM_CLOCK            41943040u /* Default System clock value */
#elif (CLOCK_SETUP == 1)
    #define CPU_XTAL_CLK_HZ                 8000000u /* Value of the external crystal or oscillator clock frequency in Hz */
    #define CPU_INT_SLOW_CLK_HZ             32768u   /* Value of the slow internal oscillator clock frequency in Hz  */
    #define CPU_INT_FAST_CLK_HZ             4000000u /* Value of the fast internal oscillator clock frequency in Hz  */
    #define DEFAULT_SYSTEM_CLOCK            48000000u /* Default System clock value */
#elif (CLOCK_SETUP == 2)
    #define CPU_XTAL_CLK_HZ                 8000000u /* Value of the external crystal or oscillator clock frequency in Hz */
    #define CPU_INT_SLOW_CLK_HZ             32768u   /* Value of the slow internal oscillator clock frequency in Hz  */
    #define CPU_INT_FAST_CLK_HZ             4000000u /* Value of the fast internal oscillator clock frequency in Hz  */
    #define DEFAULT_SYSTEM_CLOCK            96000000u /* Default System clock value */
#endif /* (CLOCK_SETUP == 2) */


/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;
uint32_t mcgOutClk_div;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit (void) {
  //int returnStatus = 0;
  #if(DISABLE_WDOG)
    sim_controlRegister(COP_DISABLED, 0, 0);  /* Disable the WDOG module */
  #endif
  #if(CLOCK_SETUP == 0)
    sim_systemClockDivider(OUTDIV1_DIVIDE_BY_1, OUTDIV4_DIVIDE_BY_3); /* Update system prescalers */
    mcg_fei();
  #elif (CLOCK_SETUP == 1)
    sim_systemClock_portx_tsi_lptmr(PORTA, 1);//Enable portA and configure PTA18, PTA19 for the cristal
    sim_systemClockDivider(OUTDIV1_DIVIDE_BY_1, OUTDIV4_DIVIDE_BY_2); /* Update system prescalers */
    port_pinControlRegisters(PORTA_BASE_PTR, 18, IRQ_DMA_DISABLE, PIN_DISABLE, LOW_DRIVE, FILTER_DISABLED, FAST_SLEW, DISABLED_PULL_RESISTOR, PULLDOWN);
    port_cleanFlagISF(PORTA_BASE_PTR, 18);
    port_pinControlRegisters(PORTA_BASE_PTR, 19, IRQ_DMA_DISABLE, PIN_DISABLE, LOW_DRIVE, FILTER_DISABLED, FAST_SLEW, DISABLED_PULL_RESISTOR, PULLDOWN);
    port_cleanFlagISF(PORTA_BASE_PTR, 19);
    /*returnStatus =*/ mcg_preconfig();
    /*returnStatus =*/ mcg_fei_to_fbe();
    /*returnStatus =*/ mcg_fbe_to_pbe();
    /*returnStatus =*/ mcg_pbe_to_pee();
    SystemCoreClock = DEFAULT_SYSTEM_CLOCK;
    mcgOutClk_div = SystemCoreClock / (1*2);
  #elif (CLOCK_SETUP == 2)
    sim_systemClock_portx_tsi_lptmr(PORTA, 1);  /* Enable clock gate for ports to enable pin routing */
    sim_systemClockDivider(OUTDIV1_DIVIDE_BY_2, OUTDIV4_DIVIDE_BY_2); /* Update system prescalers */
    port_pinControlRegisters(PORTA_BASE_PTR, 18, IRQ_DMA_DISABLE, PIN_DISABLE, LOW_DRIVE, FILTER_DISABLED, FAST_SLEW, DISABLED_PULL_RESISTOR, PULLDOWN);
    port_cleanFlagISF(PORTA_BASE_PTR, 18);
    port_pinControlRegisters(PORTA_BASE_PTR, 19, IRQ_DMA_DISABLE, PIN_DISABLE, LOW_DRIVE, FILTER_DISABLED, FAST_SLEW, DISABLED_PULL_RESISTOR, PULLDOWN);
    port_cleanFlagISF(PORTA_BASE_PTR, 19);
    mcg_fei_to_fbe();
    mcg_fbe_to_pbe();
    mcg_pbe_to_pee();
    SystemCoreClock = DEFAULT_SYSTEM_CLOCK;
  #endif
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {
  uint32_t MCGOUTClock;                                                        /* Variable to store output clock frequency of the MCG module */
  uint8_t Divider;

  if ((MCG_C1 & MCG_C1_CLKS_MASK) == 0x0u) {
    /* Output of FLL or PLL is selected */
    if ((MCG_C6 & MCG_C6_PLLS_MASK) == 0x0u) {
      /* FLL is selected */
      if ((MCG_C1 & MCG_C1_IREFS_MASK) == 0x0u) {
        /* External reference clock is selected */
        MCGOUTClock = CPU_XTAL_CLK_HZ;                                       /* System oscillator drives MCG clock */
        Divider = (uint8_t)(1u << ((MCG_C1 & MCG_C1_FRDIV_MASK) >> MCG_C1_FRDIV_SHIFT));
        MCGOUTClock = (MCGOUTClock / Divider);  /* Calculate the divided FLL reference clock */
        if ((MCG_C2 & MCG_C2_RANGE0_MASK) != 0x0u) {
          MCGOUTClock /= 32u;                                                  /* If high range is enabled, additional 32 divider is active */
        } /* ((MCG->C2 & MCG_C2_RANGE0_MASK) != 0x0u) */
      } else { /* (!((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0u)) */
        MCGOUTClock = CPU_INT_SLOW_CLK_HZ;                                     /* The slow internal reference clock is selected */
      } /* (!((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0u)) */
      /* Select correct multiplier to calculate the MCG output clock  */
      switch (MCG_C4 & (MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS_MASK)) {
        case 0x0u:
          MCGOUTClock *= 640u;
          break;
        case 0x20u:
          MCGOUTClock *= 1280u;
          break;
        case 0x40u:
          MCGOUTClock *= 1920u;
          break;
        case 0x60u:
          MCGOUTClock *= 2560u;
          break;
        case 0x80u:
          MCGOUTClock *= 732u;
          break;
        case 0xA0u:
          MCGOUTClock *= 1464u;
          break;
        case 0xC0u:
          MCGOUTClock *= 2197u;
          break;
        case 0xE0u:
          MCGOUTClock *= 2929u;
          break;
        default:
          break;
      }
    } else { /* (!((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0u)) */
      /* PLL is selected */
      Divider = (1u + (MCG_C5 & MCG_C5_PRDIV0_MASK));
      MCGOUTClock = (uint32_t)(CPU_XTAL_CLK_HZ / Divider);                     /* Calculate the PLL reference clock */
      Divider = ((MCG_C6 & MCG_C6_VDIV0_MASK) + 24u);
      MCGOUTClock *= Divider;                       /* Calculate the MCG output clock */
    } /* (!((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0u)) */
  } else if ((MCG_C1 & MCG_C1_CLKS_MASK) == 0x40u) {
    /* Internal reference clock is selected */
    if ((MCG_C2 & MCG_C2_IRCS_MASK) == 0x0u) {
      MCGOUTClock = CPU_INT_SLOW_CLK_HZ;                                       /* Slow internal reference clock selected */
    } else { /* (!((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0u)) */
      MCGOUTClock = CPU_INT_FAST_CLK_HZ / (1 << ((MCG_SC & MCG_SC_FCRDIV_MASK) >> MCG_SC_FCRDIV_SHIFT));  /* Fast internal reference clock selected */
    } /* (!((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0u)) */
  } else if ((MCG_C1 & MCG_C1_CLKS_MASK) == 0x80u) {
    /* External reference clock is selected */
    MCGOUTClock = CPU_XTAL_CLK_HZ;                                           /* System oscillator drives MCG clock */
  } else { /* (!((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80u)) */
    /* Reserved value */
    return;
  } /* (!((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80u)) */
  SystemCoreClock = (MCGOUTClock / (1u + ((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT)));
}
