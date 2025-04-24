/*
 * encoder.c
 *    - Motor 1: P1 (Pulse) -> PB4 (Encoder_GPIO_Encoder_P1_PIN)
 *    - Motor 1: D1 (Direction) -> PB5 (Encoder_GPIO_Encoder_D1_PIN)
 *    - Motor 2: P2 (Pulse) -> PB6 (Encoder_GPIO_Encoder_P2_PIN)
 *    - Motor 2: D2 (Direction) -> PB7 (Encoder_GPIO_Encoder_D2_PIN)
 */

#include "encoder.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "semphr.h"
//#include "log_config.h"
#include "log.h"

// ����ȫ�ֱ���
int left_motor_period_cnt = 0;     // �����������
int right_motor_period_cnt = 0;    // �ҵ���������

// ����ȫ�ֱ��� NEncoder
encoder NEncoder = {
    .left_motor_period_ms = 20,
    .right_motor_period_ms = 20,
    .left_motor_speed_rpm = 0.0f,
    .left_motor_speed_mps = 0.0f,    // �ٶȵ�λ��Ϊ m/s
    .right_motor_speed_rpm = 0.0f,
    .right_motor_speed_mps = 0.0f    // �ٶȵ�λ��Ϊ m/s
};

// ����״̬����
uint8_t D_State[2];

typedef struct {
    float pulse_num_per_circle; // ÿһȦ��������
    float wheel_radius_cm;      // ���ӵİ뾶����λΪ cm
} TracklessMotor;

TracklessMotor trackless_motor = {
    .pulse_num_per_circle = 570.0f, 
    .wheel_radius_cm = 3.5f     
};

// ���廥���������ڱ��������������
SemaphoreHandle_t xMotorCountMutex = NULL;

// ���������ʱ�����
TimerHandle_t xSpeedTimer = NULL;

// �����ʱ���ص�����
void SpeedTimerCallback(TimerHandle_t xTimer)
{
    int temp_left_cnt = 0;
    int temp_right_cnt = 0;
    
    // ��ȡ���������������������
    if (xSemaphoreTake(xMotorCountMutex, portMAX_DELAY) == pdTRUE) {
        temp_left_cnt = left_motor_period_cnt;
        temp_right_cnt = right_motor_period_cnt;
        left_motor_period_cnt = 0;  // ���ü���
        right_motor_period_cnt = 0;
        xSemaphoreGive(xMotorCountMutex);
    }
    
    // ���������ٶ�
    NEncoder.left_motor_period_ms = 20;
    NEncoder.left_motor_speed_rpm = 60.0f * (temp_left_cnt / trackless_motor.pulse_num_per_circle) / (NEncoder.left_motor_period_ms * 0.001f);
    // �ٶȵ�λΪ m/s�����Ӱ뾶��λΪ cm��תΪ m/s ��Ҫ���� 100
    NEncoder.left_motor_speed_mps = (2.0f * 3.14f * trackless_motor.wheel_radius_cm * (NEncoder.left_motor_speed_rpm / 60.0f)) / 100.0f;
    
    // �����ҵ���ٶ�
    NEncoder.right_motor_period_ms = 20;
    NEncoder.right_motor_speed_rpm = 60.0f * (temp_right_cnt / trackless_motor.pulse_num_per_circle) / (NEncoder.right_motor_period_ms * 0.001f);
    // �ٶȵ�λΪ m/s�����Ӱ뾶��λΪ cm��תΪ m/s ��Ҫ���� 100
    NEncoder.right_motor_speed_mps = (2.0f * 3.14f * trackless_motor.wheel_radius_cm * (NEncoder.right_motor_speed_rpm / 60.0f)) / 100.0f;
    
    // �����־�������¼���ҵ���ٶ�
    log_i("Motor Speeds - Left: %.3f m/s, Right: %.3f m/s", NEncoder.left_motor_speed_mps, NEncoder.right_motor_speed_mps);
}

void Encoder_init(void)
{
    // ��ʼ���������ж�
    NVIC_ClearPendingIRQ(ENCODER_INT_IRQN);
    NVIC_EnableIRQ(ENCODER_INT_IRQN);
    
    // ����������
    xMotorCountMutex = xSemaphoreCreateMutex();
    if (xMotorCountMutex == NULL) {
        // ����������������ʧ��
        while (1);
    }
    
    // ���������������ʱ��������20ms
    xSpeedTimer = xTimerCreate("SpeedTimer", pdMS_TO_TICKS(20), pdTRUE, NULL, SpeedTimerCallback);
    if (xSpeedTimer == NULL) {
        // ��������ʱ������ʧ��
        while (1);
    }
    if (xTimerStart(xSpeedTimer, 0) != pdPASS) {
        // ��������ʱ������ʧ��
        while (1);
    }
}

void QEI0_IRQHandler(void)
{
    D_State[0] = DL_GPIO_readPins(ENCODER_PORT, ENCODER_D1_PIN);
    // ���ж���ʹ��ISR�汾�Ļ���������
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if (xSemaphoreTakeFromISR(xMotorCountMutex, &xHigherPriorityTaskWoken) == pdTRUE) {
        if (!D_State[0]) {
            left_motor_period_cnt--;
        } else {
            left_motor_period_cnt++;
        }
        xSemaphoreGiveFromISR(xMotorCountMutex, &xHigherPriorityTaskWoken);
    }
    // ����и������ȼ������񱻻��ѣ������������л�
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void QEI1_IRQHandler(void)
{
    D_State[1] = DL_GPIO_readPins(ENCODER_PORT, ENCODER_D2_PIN);
    // ���ж���ʹ��ISR�汾�Ļ���������
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if (xSemaphoreTakeFromISR(xMotorCountMutex, &xHigherPriorityTaskWoken) == pdTRUE) {
        if (!D_State[1]) {
            right_motor_period_cnt++;
        } else {
            right_motor_period_cnt--;
        }
        xSemaphoreGiveFromISR(xMotorCountMutex, &xHigherPriorityTaskWoken);
    }
    // ����и������ȼ������񱻻��ѣ������������л�
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void GROUP1_IRQHandler(void)
{
    if (DL_Interrupt_getStatusGroup(DL_INTERRUPT_GROUP_1, DL_INTERRUPT_GROUP1_GPIOB)) {
        if (DL_GPIO_getEnabledInterruptStatus(ENCODER_PORT, ENCODER_P1_PIN)) {
            QEI0_IRQHandler();
            DL_GPIO_clearInterruptStatus(ENCODER_PORT, ENCODER_P1_PIN);
        }

        if (DL_GPIO_getEnabledInterruptStatus(ENCODER_PORT, ENCODER_P2_PIN)) {
            QEI1_IRQHandler();
            DL_GPIO_clearInterruptStatus(ENCODER_PORT, ENCODER_P2_PIN);
        }
        DL_Interrupt_clearGroup(DL_INTERRUPT_GROUP_1, DL_INTERRUPT_GROUP1_GPIOB);
    }
}

float get_left_motor_speed(void)
{
    return NEncoder.left_motor_speed_mps; // �����ٶȣ���λΪ m/s
}

float get_right_motor_speed(void)
{
    return NEncoder.right_motor_speed_mps; // �����ٶȣ���λΪ m/s
}