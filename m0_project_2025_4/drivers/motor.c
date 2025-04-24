#include "motor.h"
/*
*@brief �����ʼ��
*/
void Motor_Init(void)
{
    // ȷ������PWMͨ����ʼֵΪ0����ֹ����ڳ�ʼ��ʱ������ת
    LEFT_MOTOR_SET_CC(0, LEFT_MOTOR_FORWARD_INDEX);
    LEFT_MOTOR_SET_CC(0, LEFT_MOTOR_BACKWARD_INDEX);
    RIGHT_MOTOR_SET_CC(0, RIGHT_MOTOR_FORWARD_INDEX);
    RIGHT_MOTOR_SET_CC(0, RIGHT_MOTOR_BACKWARD_INDEX);
}
/**
 * @brief ������ƺ���
 * 
 * @param leftSpeed  �����ٶȣ���Χ-3000~3000����ֵ��ʾ��ת����ֵ��ʾ��ת��0��ʾֹͣ
 * @param rightSpeed �ҵ���ٶȣ���Χ-3000~3000����ֵ��ʾ��ת����ֵ��ʾ��ת��0��ʾֹͣ
 */
void Motor_Control(int32_t leftSpeed, int32_t rightSpeed)
{
    // �����ٶȷ�Χ��-MOTOR_PWM_MAX_VALUE~MOTOR_PWM_MAX_VALUE
    if (leftSpeed > MOTOR_PWM_MAX_VALUE)
        leftSpeed = MOTOR_PWM_MAX_VALUE;
    else if (leftSpeed < -MOTOR_PWM_MAX_VALUE)
        leftSpeed = -MOTOR_PWM_MAX_VALUE;
        
    if (rightSpeed > MOTOR_PWM_MAX_VALUE)
        rightSpeed = MOTOR_PWM_MAX_VALUE;
    else if (rightSpeed < -MOTOR_PWM_MAX_VALUE)
        rightSpeed = -MOTOR_PWM_MAX_VALUE;
    
    // �������� - �޸ĺ���߼�
    if (leftSpeed >= 0) {
        // ��ת��ͨ��1���PWM��ͨ��0���0������������תͨ����
        LEFT_MOTOR_SET_CC(0, LEFT_MOTOR_FORWARD_INDEX);
        LEFT_MOTOR_SET_CC(leftSpeed, LEFT_MOTOR_BACKWARD_INDEX);
    } else {
        // ��ת��ͨ��1���0��ͨ��0���PWM������������תͨ����
        LEFT_MOTOR_SET_CC(-leftSpeed, LEFT_MOTOR_FORWARD_INDEX);
        LEFT_MOTOR_SET_CC(0, LEFT_MOTOR_BACKWARD_INDEX);
    }
    
    // �����ҵ�� (���ֲ��䣬��Ϊ�ҵ����������)
    if (rightSpeed >= 0) {
        // ��ת��ͨ��0���PWM��ͨ��1���0
        RIGHT_MOTOR_SET_CC(rightSpeed, RIGHT_MOTOR_FORWARD_INDEX);
        RIGHT_MOTOR_SET_CC(0, RIGHT_MOTOR_BACKWARD_INDEX);
    } else {
        // ��ת��ͨ��0���0��ͨ��1���PWM
        RIGHT_MOTOR_SET_CC(0, RIGHT_MOTOR_FORWARD_INDEX);
        RIGHT_MOTOR_SET_CC(-rightSpeed, RIGHT_MOTOR_BACKWARD_INDEX);
    }
}

/**
 * @brief ֹͣ���е��
 */
void Motor_Stop(void)
{
    // ������PWMͨ������Ϊ0
    LEFT_MOTOR_SET_CC(0, LEFT_MOTOR_FORWARD_INDEX);
    LEFT_MOTOR_SET_CC(0, LEFT_MOTOR_BACKWARD_INDEX);
    RIGHT_MOTOR_SET_CC(0, RIGHT_MOTOR_FORWARD_INDEX);
    RIGHT_MOTOR_SET_CC(0, RIGHT_MOTOR_BACKWARD_INDEX);
}

/**
 * @brief ���õ����ǰ��ʻ
 * 
 * @param speed �ٶ�ֵ����Χ0~3000
 */
void Motor_Forward(uint32_t speed)
{
    // �����ٶȷ�Χ
    if (speed > MOTOR_PWM_MAX_VALUE)
        speed = MOTOR_PWM_MAX_VALUE;
        
    // �����������ǰ
    Motor_Control(speed, speed);
}

/**
 * @brief ���õ�������ʻ
 * 
 * @param speed �ٶ�ֵ����Χ0~3000
 */
void Motor_Backward(uint32_t speed)
{
    // �����ٶȷ�Χ
    if (speed > MOTOR_PWM_MAX_VALUE)
        speed = MOTOR_PWM_MAX_VALUE;
        
    // ������������
    Motor_Control(-speed, -speed);
}