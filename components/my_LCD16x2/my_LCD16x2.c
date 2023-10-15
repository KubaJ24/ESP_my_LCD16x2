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
    RS_ON; RW_OFF;
    E_ON;
    delms(1);
    E_OFF;
}

 void my_lcd16x2_print_cmd(uint8_t cmd){
    my_lcd16x2_data_port(cmd);
    RS_OFF; RW_OFF;
    E_ON;
    delms(1);
    E_OFF;
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

    delms(15);
    
    //#1
    my_lcd16x2_print_cmd(0x30);
    delms(5);
    //#2
    delms(1);
    //#3
    my_lcd16x2_print_cmd(0x30);
    delms(1);

    my_lcd16x2_print_cmd(LCD_16x2);
    delms(1);
    my_lcd16x2_print_cmd(DISPLAY_ON);
    delms(1);
    my_lcd16x2_print_cmd(0x01);
    delms(1);
    my_lcd16x2_print_cmd(CURSOR_SHIFT);
    delms(1);
    //Inicjalizacja zakończona

    my_lcd16x2_print_cmd(DISPLAY_ON);
    delms(1);
    //my_lcd16x2_print_cmd(AUTO_INC);
    delms(1);
    my_lcd16x2_print_cmd(HOME);
    delms(1);
}

void delms(uint16_t ms){
    vTaskDelay(ms / portTICK_PERIOD_MS);
}