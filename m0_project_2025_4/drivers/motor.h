#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>
#include "ti_msp_dl_config.h"

/* ����������ź궨�� */
// ����PWM����
#define LEFT_MOTOR_PWM_INST           Motor_PWM1_INST   // ����PWM��ʱ��ʵ��
#define LEFT_MOTOR_FORWARD_INDEX      DL_TIMER_CC_0_INDEX  // ������תͨ��
#define LEFT_MOTOR_BACKWARD_INDEX     DL_TIMER_CC_1_INDEX  // ������תͨ��
#define LEFT_MOTOR_SET_CC(value, index)  DL_TimerA_setCaptureCompareValue(LEFT_MOTOR_PWM_INST, value, index)

// �ҵ��PWM����
#define RIGHT_MOTOR_PWM_INST          Motor_PWM2_INST   // �ҵ��PWM��ʱ��ʵ��
#define RIGHT_MOTOR_FORWARD_INDEX     DL_TIMER_CC_0_INDEX  // �ҵ����תͨ��
#define RIGHT_MOTOR_BACKWARD_INDEX    DL_TIMER_CC_1_INDEX  // �ҵ����תͨ��
#define RIGHT_MOTOR_SET_CC(value, index)  DL_TimerG_setCaptureCompareValue(RIGHT_MOTOR_PWM_INST, value, index)

// ���PWM��������
#define MOTOR_PWM_MAX_VALUE           3000              // PWM���ֵ

/**
*@brief �����ʼ��
*/
void Motor_Init(void);
/**
 * @brief ������ƺ���
 * 
 * @param leftSpeed  �����ٶȣ���Χ-3000~3000����ֵ��ʾ��ת����ֵ��ʾ��ת��0��ʾֹͣ
 * @param rightSpeed �ҵ���ٶȣ���Χ-3000~3000����ֵ��ʾ��ת����ֵ��ʾ��ת��0��ʾֹͣ
 */
void Motor_Control(int32_t leftSpeed, int32_t rightSpeed);

/**
 * @brief ֹͣ���е��
 */
void Motor_Stop(void);

/**
 * @brief ���õ����ǰ��ʻ
 * 
 * @param speed �ٶ�ֵ����Χ0~3000
 */
void Motor_Forward(uint32_t speed);

/**
 * @brief ���õ�������ʻ
 * 
 * @param speed �ٶ�ֵ����Χ0~3000
 */
void Motor_Backward(uint32_t speed);

#endif /* MOTOR_H */