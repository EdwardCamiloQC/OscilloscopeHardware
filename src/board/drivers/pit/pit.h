#ifndef _PIT_H_
    #define _PIT_H_

    #include <stdint.h>
    #include <stdbool.h>

    void _irqHandler_PIT(void);

    void pit_init(uint32_t time_us);
    void pit_stop();

    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    /*
        MDIS:   module disable
            0:  Clock for the standard PIT timers is enabled
            1:  Clock for the standard PIT timers is disabled
        FRZ:    permite a los timers ser detenidos cuando el dispositivo dentra en modo debug
            0:  Timers continue to run in debug mode
            1:  Timers are stopped in Debug mode
    */
    void pit_moduleControl(bool mdis, bool frz);

    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    uint64_t pit_lifetimeTimer();

    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    /*
        n:
            0:  PIT0
            1:  PIT1
    */
    void pit_timerLoadValue(uint32_t value, bool n);
    uint32_t pit_currentTimerValue(bool n);

    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    /*
        CHN:    Chain mode
            0:  Timer is not chained
            1:  Timer is chained to previus timer. For example, for Channel 2, if this field is set, Timer 2 is chained to Timer 1
        TIE:    Timer interrupt enable
            0:  Interrupt requests from Timer n are disabled
            1:  Interrupt will be requested whenever TIF is set
        TEN:    Timer enable
            0:  Timer n is disabled
            1:  Timer n is enabled
        n:
            0:  PIT0
            1:  PIT1
    */
    void pit_timerControl(bool chn, bool tie, bool ten, bool n);

    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    bool pit_timerFlag(bool clean, bool n);
#endif
