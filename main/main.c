#include "main.h"

void app_main(void)
{
    my_lcd16x2_gpio_conf();

    my_lcd16x2_init();

    my_lcd16x2_print_data(0x41);

}
