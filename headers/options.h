#ifndef CW_OPTIONS_H
#define CW_OPTIONS_H

#include "libs.h"
#include "bmp-handler.h"
#include "errors.h"
#include "exchange.h"
#include "freq-color.h"
#include "rgb-filter.h"
#include "square.h"
#include "ornament.h"

typedef struct {
    // info
    unsigned char check_info;

    // rgb-filter
    unsigned char check_rgbfilter;
    unsigned char check_component_name;
    unsigned char check_component_value;

    // input file
    unsigned char check_input;

    // output file
    unsigned char check_output;

    // square
    unsigned char check_square;
    unsigned char check_thickness;
    unsigned char check_side_size;
    unsigned char check_fill;
    unsigned char check_fill_color;

    // freq color
    unsigned char check_freq_color;

    // color
    unsigned char check_color;

    // exchange
    unsigned char check_exchange;
    unsigned char check_right_down;
    unsigned char check_exchange_type;

    // left_up for exchange or square
    unsigned char check_left_up;

    unsigned char check_ornament;
} Tasks;


void initTasks(Tasks * tasks); // иницилизация списка заданий

int checkCoordinates(char * coords); // проверка на валидность координат

int checkNum(char * string); // проверка на то, является ли строка числом

int checkColor(char * color); // проверка на валидность цвета

void handleInput(int argc, char * argv[]); // обработка опций (cli)

#endif //CW_OPTIONS_H
