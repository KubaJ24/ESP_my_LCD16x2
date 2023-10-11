#include "main.h"

void app_main(void)
{
    int data_pins[8] = {23, 22, 32, 33, 25, 27, 26, 16};

    my_lcd16x2_gpio_conf();

    my_lcd16x2_init(data_pins[8]);
}
