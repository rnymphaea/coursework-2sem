#include "../../headers/exchange.h"

void initExchange(Exchange * ex) {
    ex -> extype = undefined;
    ex -> lx = 0;
    ex -> ly = 0;
    ex -> rx = 0;
    ex -> ry = 0;
}

RGB ** exchange(RGB ** arr, unsigned int H, unsigned int W, Exchange ex) {
    if ((ex.lx < 0 && ex.rx < 0) || (ex.lx > (int)W && ex.rx > (int)W) || (ex.ly > (int)H && ex.ry > (int)H) || (ex.ry < 0 && ex.ly < 0)) {
        printf("Error: invalid coordinates!\n");
        exit(INVALID_OPTION_ARG_ERROR);
    }


    // перевод координат y в индексы массива пикселей
    ex.ly = ((int)H) - ex.ly;
    ex.ry = ((int)H) - ex.ry;

    // выделение левого верхнего и правого нижнего углов
    if (ex.ly < ex.ry) {
        int tmp = ex.ly;
        ex.ly = ex.ry;
        ex.ry = tmp;
    }
    if (ex.lx > ex.rx) {
        int tmp = ex.lx;
        ex.lx = ex.rx;
        ex.rx = tmp;
    }

    // проверки на выход за границы изображения
    if (ex.lx < 0){
        ex.lx = 0;
    }
    if (ex.rx > (int)W) {
        ex.rx = W;
    }
    if (ex.ly > (int)H) {
        ex.ly = H;
    }
    if (ex.ry < 0) {
        ex.ry = 0;
    }

    if ((ex.rx - ex.lx) % 2) {
        ex.rx--;
    }
    if ((ex.ly - ex.ry) % 2) {
        ex.ly--;
    }

    switch (ex.extype) {
        case diagonals:
            for (int i = ex.ly; i > (ex.ly + ex.ry) / 2; i--) {
                for (int j = ex.lx; j < (ex.rx + ex.lx) / 2; j++) {
                    RGB tmp = arr[i][j];
                    arr[i][j] = arr[i - ((ex.ly - ex.ry) / 2)][j + (ex.rx - ex.lx) / 2];
                    arr[i - ((ex.ly - ex.ry) / 2)][j + (ex.rx - ex.lx) / 2] = tmp;
                }
            }
            for (int i = (ex.ly + ex.ry) / 2; i > ex.ry; i--) {
                for (int j = ex.lx; j < (ex.rx + ex.lx) / 2; j++) {
                    RGB tmp = arr[i][j];
                    arr[i][j] = arr[i + ((ex.ly - ex.ry) / 2)][j + (ex.rx - ex.lx) / 2];
                    arr[i + ((ex.ly - ex.ry) / 2)][j + (ex.rx - ex.lx) / 2] = tmp;
                }
            }
            break;
        case clockwise:
            for (int i = ex.ly; i > (ex.ly + ex.ry) / 2; i--) {
                for (int j = ex.lx; j < (ex.rx + ex.lx) / 2; j++) {
                    RGB tmp = arr[i][j];
                    arr[i][j] = arr[i][j + (ex.rx - ex.lx) / 2];
                    arr[i][j + (ex.rx - ex.lx) / 2] = tmp;
                }
            }
            for (int i = (ex.ly + ex.ry) / 2; i > ex.ry; i--) {
                for (int j = ex.lx; j < (ex.rx + ex.lx) / 2; j++) {
                    RGB tmp = arr[i][j];
                    arr[i][j] = arr[i][j + (ex.rx - ex.lx) / 2];
                    arr[i][j + (ex.rx - ex.lx) / 2] = tmp;
                }
            }
            for (int i = ex.ly; i > (ex.ly + ex.ry) / 2; i--) {
                for (int j = ex.lx; j < (ex.rx + ex.lx) / 2; j++) {
                    RGB tmp = arr[i][j];
                    arr[i][j] = arr[i - ((ex.ly - ex.ry) / 2)][j + (ex.rx - ex.lx) / 2];
                    arr[i - ((ex.ly - ex.ry) / 2)][j + (ex.rx - ex.lx) / 2] = tmp;
                }
            }
            break;
        case counterclockwise:
            for (int i = ex.ly; i > (ex.ly + ex.ry) / 2; i--) {
                for (int j = ex.lx; j < (ex.rx + ex.lx) / 2; j++) {
                    RGB tmp = arr[i][j];
                    arr[i][j] = arr[i][j + (ex.rx - ex.lx) / 2];
                    arr[i][j + (ex.rx - ex.lx) / 2] = tmp;
                }
            }
            for (int i = (ex.ly + ex.ry) / 2; i > ex.ry; i--) {
                for (int j = ex.lx; j < (ex.rx + ex.lx) / 2; j++) {
                    RGB tmp = arr[i][j];
                    arr[i][j] = arr[i][j + (ex.rx - ex.lx) / 2];
                    arr[i][j + (ex.rx - ex.lx) / 2] = tmp;
                }
            }
            for (int i = (ex.ly + ex.ry) / 2; i > ex.ry; i--) {
                for (int j = ex.lx; j < (ex.rx + ex.lx) / 2; j++) {
                    RGB tmp = arr[i][j];
                    arr[i][j] = arr[i + ((ex.ly - ex.ry) / 2)][j + (ex.rx - ex.lx) / 2];
                    arr[i + ((ex.ly - ex.ry) / 2)][j + (ex.rx - ex.lx) / 2] = tmp;
                }
            }
            break;
        case undefined:
            printf("Error: undefined type of exchange!\n");
            exit(INVALID_OPTION_ARG_ERROR);
    }

    return arr;
}

