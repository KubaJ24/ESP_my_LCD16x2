#include "main.h"

void app_main(void)
{
    my_lcd16x2_gpio_conf();

    vTaskDelay(15 / portTICK_PERIOD_MS);
    
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << RS));
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << RW));
    my_lcd16x2_data_port(0x30);
    REG_WRITE(GPIO_OUT_W1TS_REG, (1 << E));

    vTaskDelay(10 / portTICK_PERIOD_MS);

    my_lcd16x2_data_port(0x38);
    vTaskDelay(5 / portTICK_PERIOD_MS);
    my_lcd16x2_data_port(0x0E);
    vTaskDelay(5 / portTICK_PERIOD_MS);
    my_lcd16x2_data_port(0x06);
    vTaskDelay(5 / portTICK_PERIOD_MS);
    my_lcd16x2_data_port(0x01);
    vTaskDelay(5 / portTICK_PERIOD_MS);
    my_lcd16x2_data_port(0x02);
    vTaskDelay(5 / portTICK_PERIOD_MS);

    my_lcd16x2_print_data(0x61);

   // while(1){}

}
