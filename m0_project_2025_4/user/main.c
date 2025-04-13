#include "common.h"

//#include "log_config.h"
#include "log.h"


int main(void)
{
    SYSCFG_DL_init();
		Gray_Detection_Init();
		OLED_Init();
		OLED_Test();
    for (;;)
    {
			Gray_ReadData();
			delay_ms(1000);
    }
    return 0;
}
