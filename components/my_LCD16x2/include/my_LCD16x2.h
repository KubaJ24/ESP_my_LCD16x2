#ifndef MY_LCD16X2_H
#define MY_LCD16X2_H

#include <stdio.h>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/timer.h"

#include "soc/gpio_reg.h"
#include "soc/io_mux_reg.h"

#define RS 18
#define RW 19
#define E 21
#define D0 23
#define D1 22
#define D2 0        //gpio 32
#define D3 1        //gpio 33
#define D4 25
#define D5 27
#define D6 26
#define D7 16


void my_lcd16x2_gpio_conf(void);
/*
Konfiguracja pinów
*/

void my_lcd16x2_data_port(uint8_t data);
/*
Ustawia stany D4 - D7 odpowiednio w stosunku do zmiennej "data"
*/

void my_lcd16x2_print_data(uint8_t data);
/*
Wysyła pojedyńczą daną do pamięci wyświtlacza
*/

void my_lcd16x2_print_cmd(uint8_t cmd);
/*
Wysyła pojedyńczą komendę do pamięci wyświtlacza
*/

void my_lcd16x2_print_string(char str[]);
/*
Wyświetla ciąg znaków zapisany w tablicy "str[]"
*/

void my_lcd16x2_init(void);
/*
Podstawowa konfiguracja wyświetlacza
*/

void my_lcd16x2_set16x2(void);

void my_lcd16x2_display(void);
/*
Display on, cursor off
*/

void my_lcd16x2_auto_inc(void);

void my_lcd16x2_clear(void);

void my_lcd16x2_home(void);
/*
Pozycja 0,0
*/

#endif //MY_LCD16X2_H