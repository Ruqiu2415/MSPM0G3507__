/*
 * encoder.h
 *  Pin mapping (based on configuration):
 *    - Motor 1: P1 (Pulse) -> PB4 (Encoder_GPIO_Encoder_P1_PIN)
 *    - Motor 1: D1 (Direction) -> PB5 (Encoder_GPIO_Encoder_D1_PIN)
 *    - Motor 2: P2 (Pulse) -> PB6 (Encoder_GPIO_Encoder_P2_PIN)
 *    - Motor 2: D2 (Direction) -> PB7 (Encoder_GPIO_Encoder_D2_PIN)
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "FreeRTOS.h"

// ���������ݽṹ��
typedef struct {
    int left_motor_period_ms;       // �����������ڣ�ms��
    int right_motor_period_ms;      // �ҵ���������ڣ�ms��
    float left_motor_speed_rpm;     // �����ٶȣ�ת/���ӣ�
    float left_motor_speed_mps;     // �����ٶȣ�m/s��
    float right_motor_speed_rpm;    // �ҵ���ٶȣ�ת/���ӣ�
    float right_motor_speed_mps;    // �ҵ���ٶȣ�m/s��
} encoder;

// �ⲿ���������������Ҫ�������ļ��з��ʣ�
extern encoder NEncoder;

// ��������
void Encoder_init(void);
float get_left_motor_speed(void);
float get_right_motor_speed(void);

#endif /* ENCODER_H_ */