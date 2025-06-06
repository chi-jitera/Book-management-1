PROGRAM Main
; Keyence KV Studio Ladder Logic
LD     POWER_ON
SET    ST_SYS_READY
LD     MODE_AUTO
SET    FEED_1_ON
LD     FEED_1_ON
SET    ALIGN_1_READY
LD     ALIGN_1_READY
SET    CONV_1_ON
LD     MODE_AUTO
SET    FEED_2_ON
LD     FEED_2_ON
SET    ALIGN_2_READY
LD     ALIGN_2_READY
SET    CONV_2_ON
LD     MODE_AUTO
SET    FEED_3_ON
LD     FEED_3_ON
SET    ALIGN_3_READY
LD     ALIGN_3_READY
SET    CONV_3_ON
LD     MODE_AUTO
SET    FEED_4_ON
LD     FEED_4_ON
SET    ALIGN_4_READY
LD     ALIGN_4_READY
SET    CONV_4_ON
LD     MODE_AUTO
SET    FEED_5_ON
LD     FEED_5_ON
SET    ALIGN_5_READY
LD     ALIGN_5_READY
SET    CONV_5_ON
LD     CONV_1_ON
SET    STEP_1_1
LD     STEP_1_1
TMR    T_110 DONE_1_1
LD     STEP_1_1
SET    STEP_1_2
LD     STEP_1_2
TMR    T_120 DONE_1_2
LD     STEP_1_2
SET    STEP_1_3
LD     STEP_1_3
TMR    T_130 DONE_1_3
LD     STEP_1_3
SET    STEP_1_4
LD     STEP_1_4
TMR    T_140 DONE_1_4
LD     STEP_1_4
SET    STEP_1_5
LD     STEP_1_5
TMR    T_150 DONE_1_5
LD     CONV_2_ON
SET    STEP_2_1
LD     STEP_2_1
TMR    T_210 DONE_2_1
LD     STEP_2_1
SET    STEP_2_2
LD     STEP_2_2
TMR    T_220 DONE_2_2
LD     STEP_2_2
SET    STEP_2_3
LD     STEP_2_3
TMR    T_230 DONE_2_3
LD     STEP_2_3
SET    STEP_2_4
LD     STEP_2_4
TMR    T_240 DONE_2_4
LD     STEP_2_4
SET    STEP_2_5
LD     STEP_2_5
TMR    T_250 DONE_2_5
LD     CONV_3_ON
SET    STEP_3_1
LD     STEP_3_1
TMR    T_310 DONE_3_1
LD     STEP_3_1
SET    STEP_3_2
LD     STEP_3_2
TMR    T_320 DONE_3_2
LD     STEP_3_2
SET    STEP_3_3
LD     STEP_3_3
TMR    T_330 DONE_3_3
LD     STEP_3_3
SET    STEP_3_4
LD     STEP_3_4
TMR    T_340 DONE_3_4
LD     STEP_3_4
SET    STEP_3_5
LD     STEP_3_5
TMR    T_350 DONE_3_5
LD     CONV_4_ON
SET    STEP_4_1
LD     STEP_4_1
TMR    T_410 DONE_4_1
LD     STEP_4_1
SET    STEP_4_2
LD     STEP_4_2
TMR    T_420 DONE_4_2
LD     STEP_4_2
SET    STEP_4_3
LD     STEP_4_3
TMR    T_430 DONE_4_3
LD     STEP_4_3
SET    STEP_4_4
LD     STEP_4_4
TMR    T_440 DONE_4_4
LD     STEP_4_4
SET    STEP_4_5
LD     STEP_4_5
TMR    T_450 DONE_4_5
LD     CONV_5_ON
SET    STEP_5_1
LD     STEP_5_1
TMR    T_510 DONE_5_1
LD     STEP_5_1
SET    STEP_5_2
LD     STEP_5_2
TMR    T_520 DONE_5_2
LD     STEP_5_2
SET    STEP_5_3
LD     STEP_5_3
TMR    T_530 DONE_5_3
LD     STEP_5_3
SET    STEP_5_4
LD     STEP_5_4
TMR    T_540 DONE_5_4
LD     STEP_5_4
SET    STEP_5_5
LD     STEP_5_5
TMR    T_550 DONE_5_5
LD     DONE_1_5
SET    OR      
LD     INSPECT_PASS
SET    EJECT_GOOD
LD     INSPECT_FAIL
SET    EJECT_REJECT
LD     EJECT_GOOD
ADD    COUNT_GOOD 1
LD     EJECT_REJECT
ADD    COUNT_REJECT 1
LD     COUNT_GOOD
CMP    >= 500
SET    M200
LD     PALLET_FULL
SET    PALLET_LOAD_ON
LD     PALLET_LOAD_ON
SET    PALLET_PLACING
LD     ERR_TIMEOUT1
SET    RETRY_MODE1
LD     TEMP_HIGH
SET    COOLER_ON
LD     TEMP_LOW
SET    HEATER_ON
LD     DONE_5_5
ADD    RUN_HOURS 1
LD     RUN_HOURS
CMP    >= 10000
SET    M200
LD     MAINT_ALERT
SET    INDICATOR_MAINT
LD     MODE_MANUAL
SET    BYPASS_FEED
LD     MODE_MANUAL
SET    BYPASS_PROC
LD     MODE_MANUAL
SET    BYPASS_EJECT
END_PROGRAM