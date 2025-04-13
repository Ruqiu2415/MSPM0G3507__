/*
 * Copyright (c) 2023, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerA_backupConfig gMotor_PWM1Backup;
DL_TimerA_backupConfig gTIMER_delayBackup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_Motor_PWM1_init();
    SYSCFG_DL_Motor_PWM2_init();
    SYSCFG_DL_TIMER_delay_init();
    SYSCFG_DL_UART_DEBUG_init();
    /* Ensure backup structures have no valid state */
	gMotor_PWM1Backup.backupRdy 	= false;
	gTIMER_delayBackup.backupRdy 	= false;


}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_saveConfiguration(Motor_PWM1_INST, &gMotor_PWM1Backup);
	retStatus &= DL_TimerA_saveConfiguration(TIMER_delay_INST, &gTIMER_delayBackup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_restoreConfiguration(Motor_PWM1_INST, &gMotor_PWM1Backup, false);
	retStatus &= DL_TimerA_restoreConfiguration(TIMER_delay_INST, &gTIMER_delayBackup, false);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerA_reset(Motor_PWM1_INST);
    DL_TimerG_reset(Motor_PWM2_INST);
    DL_TimerA_reset(TIMER_delay_INST);
    DL_UART_Main_reset(UART_DEBUG_INST);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerA_enablePower(Motor_PWM1_INST);
    DL_TimerG_enablePower(Motor_PWM2_INST);
    DL_TimerA_enablePower(TIMER_delay_INST);
    DL_UART_Main_enablePower(UART_DEBUG_INST);
    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralOutputFunction(GPIO_Motor_PWM1_C0_IOMUX,GPIO_Motor_PWM1_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_Motor_PWM1_C0_PORT, GPIO_Motor_PWM1_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_Motor_PWM1_C1_IOMUX,GPIO_Motor_PWM1_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_Motor_PWM1_C1_PORT, GPIO_Motor_PWM1_C1_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_Motor_PWM2_C0_IOMUX,GPIO_Motor_PWM2_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_Motor_PWM2_C0_PORT, GPIO_Motor_PWM2_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_Motor_PWM2_C1_IOMUX,GPIO_Motor_PWM2_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_Motor_PWM2_C1_PORT, GPIO_Motor_PWM2_C1_PIN);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_DEBUG_IOMUX_TX, GPIO_UART_DEBUG_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_DEBUG_IOMUX_RX, GPIO_UART_DEBUG_IOMUX_RX_FUNC);

    DL_GPIO_initDigitalOutput(PCA9555_SCL1_IOMUX);

    DL_GPIO_initDigitalOutput(PCA9555_SDA1_IOMUX);

    DL_GPIO_initDigitalOutput(OLED_SCL2_IOMUX);

    DL_GPIO_initDigitalOutput(OLED_SDA2_IOMUX);

    DL_GPIO_clearPins(PCA9555_PORT, PCA9555_SCL1_PIN |
		PCA9555_SDA1_PIN);
    DL_GPIO_enableOutput(PCA9555_PORT, PCA9555_SCL1_PIN |
		PCA9555_SDA1_PIN);
    DL_GPIO_clearPins(OLED_PORT, OLED_SCL2_PIN |
		OLED_SDA2_PIN);
    DL_GPIO_enableOutput(OLED_PORT, OLED_SCL2_PIN |
		OLED_SDA2_PIN);

}



SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);

    
	DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);

}


/*
 * Timer clock configuration to be sourced by  / 8 (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   4000000 Hz = 4000000 Hz / (8 * (0 + 1))
 */
static const DL_TimerA_ClockConfig gMotor_PWM1ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 0U
};

static const DL_TimerA_PWMConfig gMotor_PWM1Config = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN_UP,
    .period = 3000,
    .isTimerWithFourCC = true,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_Motor_PWM1_init(void) {

    DL_TimerA_setClockConfig(
        Motor_PWM1_INST, (DL_TimerA_ClockConfig *) &gMotor_PWM1ClockConfig);

    DL_TimerA_initPWMMode(
        Motor_PWM1_INST, (DL_TimerA_PWMConfig *) &gMotor_PWM1Config);

    DL_TimerA_setCaptureCompareOutCtl(Motor_PWM1_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_0_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(Motor_PWM1_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_0_INDEX);
    DL_TimerA_setCaptureCompareValue(Motor_PWM1_INST, 0, DL_TIMER_CC_0_INDEX);

    DL_TimerA_setCaptureCompareOutCtl(Motor_PWM1_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_1_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(Motor_PWM1_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_1_INDEX);
    DL_TimerA_setCaptureCompareValue(Motor_PWM1_INST, 0, DL_TIMER_CC_1_INDEX);

    DL_TimerA_enableClock(Motor_PWM1_INST);


    
    DL_TimerA_setCCPDirection(Motor_PWM1_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT );


}
/*
 * Timer clock configuration to be sourced by  / 8 (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   4000000 Hz = 4000000 Hz / (8 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gMotor_PWM2ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 0U
};

static const DL_TimerG_PWMConfig gMotor_PWM2Config = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN_UP,
    .period = 3000,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_Motor_PWM2_init(void) {

    DL_TimerG_setClockConfig(
        Motor_PWM2_INST, (DL_TimerG_ClockConfig *) &gMotor_PWM2ClockConfig);

    DL_TimerG_initPWMMode(
        Motor_PWM2_INST, (DL_TimerG_PWMConfig *) &gMotor_PWM2Config);

    DL_TimerG_setCaptureCompareOutCtl(Motor_PWM2_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(Motor_PWM2_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
    DL_TimerG_setCaptureCompareValue(Motor_PWM2_INST, 0, DL_TIMER_CC_0_INDEX);

    DL_TimerG_setCaptureCompareOutCtl(Motor_PWM2_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(Motor_PWM2_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);
    DL_TimerG_setCaptureCompareValue(Motor_PWM2_INST, 0, DL_TIMER_CC_1_INDEX);

    DL_TimerG_enableClock(Motor_PWM2_INST);


    
    DL_TimerG_setCCPDirection(Motor_PWM2_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT );


}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   40404.0404040404 Hz = 4000000 Hz / (8 * (98 + 1))
 */
static const DL_TimerA_ClockConfig gTIMER_delayClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 98U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_delay_INST_LOAD_VALUE = (0.01ms * 40404.0404040404 Hz) - 1
 */
static const DL_TimerA_TimerConfig gTIMER_delayTimerConfig = {
    .period     = TIMER_delay_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_ONE_SHOT,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_delay_init(void) {

    DL_TimerA_setClockConfig(TIMER_delay_INST,
        (DL_TimerA_ClockConfig *) &gTIMER_delayClockConfig);

    DL_TimerA_initTimerMode(TIMER_delay_INST,
        (DL_TimerA_TimerConfig *) &gTIMER_delayTimerConfig);
    DL_TimerA_enableInterrupt(TIMER_delay_INST , DL_TIMERA_INTERRUPT_ZERO_EVENT);
    DL_TimerA_enableClock(TIMER_delay_INST);





}



static const DL_UART_Main_ClockConfig gUART_DEBUGClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_DEBUGConfig = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_DEBUG_init(void)
{
    DL_UART_Main_setClockConfig(UART_DEBUG_INST, (DL_UART_Main_ClockConfig *) &gUART_DEBUGClockConfig);

    DL_UART_Main_init(UART_DEBUG_INST, (DL_UART_Main_Config *) &gUART_DEBUGConfig);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115211.52
     */
    DL_UART_Main_setOversampling(UART_DEBUG_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_DEBUG_INST, UART_DEBUG_IBRD_32_MHZ_115200_BAUD, UART_DEBUG_FBRD_32_MHZ_115200_BAUD);



    DL_UART_Main_enable(UART_DEBUG_INST);
}

