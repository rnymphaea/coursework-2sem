#ifndef CW_SQUARE_H
#define CW_SQUARE_H

#include "structures.h"
#include "libs.h"
#include "errors.h"

void initSquare(Square * sq); // инициализация полей структуры Square

RGB ** drawLine(RGB ** arr, unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, RGB color); // рисование линии

RGB ** drawSquare(RGB ** arr, unsigned int H, unsigned int W, Square sq); // рисование квадрата

#endif //CW_SQUARE_H
