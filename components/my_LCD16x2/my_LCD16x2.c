#include "my_LCD16x2.h"

void my_lcd16x2_gpio_conf(void){
    //OUTPUT ENABLE
    REG_WRITE(GPIO_ENABLE_W1TS_REG, (1 << RS) | (1 << RW) | (1 << E) | (1 << D0) | (1 << D1) | (1 << D4) | (1 << D5) | (1 << D6) | (1 << D7));
    REG_WRITE(GPIO_ENABLE1_W1TS_REG, (1 << D2) | (1 << D3));
    //OUTPUTS TO "0"
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << RS) | (1 << RW) | (1 << E) | (1 << D0) | (1 << D1) | (1 << D4) | (1 << D5) | (1 << D6) | (1 << D7));
    REG_WRITE(GPIO_OUT1_W1TC_REG, (1 << D2) | (1 << D3));
}

void my_lcd16x2_data_port(uint8_t data){
    uint8_t var = data;

    if((var &= 0x01) == 0x01){ REG_WRITE(GPIO_OUT_W1TS_REG, (1 << D0)); } else { REG_WRITE(GPIO_OUT_W1TC_REG, (1 << D0)); }
    var = data;
    if((var &= 0x02) == 0x02){ REG_WRITE(GPIO_OUT_W1TS_REG, (1 << D1)); } else { REG_WRITE(GPIO_OUT_W1TC_REG, (1 << D1)); }
    var = data;
    if((var &= 0x04) == 0x04){ REG_WRITE(GPIO_OUT1_W1TS_REG, (1 << D2)); } else { REG_WRITE(GPIO_OUT1_W1TC_REG, (1 << D2)); }
    var = data;
    if((var &= 0x08) == 0x08){ REG_WRITE(GPIO_OUT1_W1TS_REG, (1 << D3)); } else { REG_WRITE(GPIO_OUT1_W1TC_REG, (1 << D3)); }
    var = data;
    if((var &= 0x10) == 0x10){ REG_WRITE(GPIO_OUT_W1TS_REG, (1 << D4)); } else { REG_WRITE(GPIO_OUT_W1TC_REG, (1 << D4)); }
    var = data;
    if((var &= 0x20) == 0x20){ REG_WRITE(GPIO_OUT_W1TS_REG, (1 << D5)); } else { REG_WRITE(GPIO_OUT_W1TC_REG, (1 << D5)); }
    var = data;
    if((var &= 0x40) == 0x40){ REG_WRITE(GPIO_OUT_W1TS_REG, (1 << D6)); } else { REG_WRITE(GPIO_OUT_W1TC_REG, (1 << D6)); }
    var = data;
    if((var &= 0x80) == 0x80){ REG_WRITE(GPIO_OUT_W1TS_REG, (1 << D7)); } else { REG_WRITE(GPIO_OUT_W1TC_REG, (1 << D7)); }
}

void my_lcd16x2_print_data(uint8_t data){
    printf("data to print: %x\n", data);
    my_lcd16x2_data_port(data);
    REG_WRITE(GPIO_OUT_W1TS_REG, (1 << RS));
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << RW));
    REG_WRITE(GPIO_OUT_W1TS_REG, (1 << E));
    vTaskDelay(5 / portTICK_PERIOD_MS);
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << E));
/*     //SHIFT LEFT 
    my_lcd16x2_data_port(data << 4);
    REG_WRITE(GPIO_OUT_W1TS_REG, (1 << RS));
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << RW));
    REG_WRITE(GPIO_OUT_W1TS_REG, (1 << E));
    vTaskDelay(5 / portTICK_PERIOD_MS);
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << E)); */
}

 void my_lcd16x2_print_cmd(uint8_t cmd){
    my_lcd16x2_data_port(cmd);
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << RS));
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << RW));
    REG_WRITE(GPIO_OUT_W1TS_REG, (1 << E));
    vTaskDelay(5 / portTICK_PERIOD_MS);
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << E));
/*     //SHIFT LEFT 
    my_lcd16x2_data_port(cmd << 4);
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << RS));
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << RW));
    REG_WRITE(GPIO_OUT_W1TS_REG, (1 << E));
    vTaskDelay(5 / portTICK_PERIOD_MS);
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << E)); */
}

 void my_lcd16x2_print_string(char str[]){
    uint8_t str_len = *(&str + 1) - str + 1;
    printf("string to print in print_string: %c\n", str[0]);
    //printf("%d\n", str_len);
    for(uint8_t i = 0; i < 1; i++){
        my_lcd16x2_print_data(str[i]);
        //printf("data printed %d time/s\n", i + 1);
    }
}

void my_lcd16x2_init(void){

/*     vTaskDelay(16 / portTICK_PERIOD_MS);
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << RS));
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << RW));
    REG_WRITE(GPIO_OUT_W1TS_REG, (1 << D4));
    REG_WRITE(GPIO_OUT_W1TS_REG, (1 << D5));
    REG_WRITE(GPIO_OUT_W1TS_REG, (1 << E));
    vTaskDelay(5 / portTICK_PERIOD_MS);
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << E));

    vTaskDelay(5 / portTICK_PERIOD_MS);

    REG_WRITE(GPIO_OUT_W1TS_REG, (1 << E));
    vTaskDelay(5 / portTICK_PERIOD_MS);
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << E));

    vTaskDelay(5 / portTICK_PERIOD_MS);
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << D4));
    REG_WRITE(GPIO_OUT_W1TS_REG, (1 << E));
    vTaskDelay(5 / portTICK_PERIOD_MS);
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << E)); */

    my_lcd16x2_set16x2();
    my_lcd16x2_print_cmd(0x0F);
    my_lcd16x2_print_cmd(0x01);
    my_lcd16x2_print_cmd(0x03);
    my_lcd16x2_print_cmd(0x02);
    // my_lcd16x2_display();
    // my_lcd16x2_auto_inc();
    // my_lcd16x2_clear();
    // my_lcd16x2_home();
}

void my_lcd16x2_set16x2(void){
    my_lcd16x2_print_cmd(0x38);
}

void my_lcd16x2_display(void){
    //Display on, cursor off
    my_lcd16x2_print_cmd(0x0C);
}

void my_lcd16x2_auto_inc(void){
    my_lcd16x2_print_cmd(0x06);
}

void my_lcd16x2_clear(void){
    my_lcd16x2_print_cmd(0x01);
}

void my_lcd16x2_home(void){
    my_lcd16x2_print_cmd(0x02);
}