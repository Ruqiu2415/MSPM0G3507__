#include "common.h"
#include "log.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "encoder.h" // ����������ı�����ͷ�ļ�


int main(void)
{
    // ϵͳ��Ӳ����ʼ��
    SYSCFG_DL_init();
    Gray_Detection_Init();
    OLED_Init();
    // OLED_Test(); // �������Ҫ���ԣ�����ע�͵�
    Motor_Init(); // �����ʼ��
    Encoder_init(); // ��������ʼ�������� FreeRTOS �����ʱ����
    // ���ó�ʼ����ٶ�
//    Motor_Control(1200, 1200);
    // ������ʾ����
    xTaskCreate(DisplayTask, "DisplayTask", configMINIMAL_STACK_SIZE * 4, NULL, tskIDLE_PRIORITY + 1, NULL);
    // ���� FreeRTOS ������
    vTaskStartScheduler();

    while (1) {
    }

    return 0;
}