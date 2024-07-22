#ifndef CW_FREQ_COLOR_H
#define CW_FREQ_COLOR_H

#include "structures.h"
#include "libs.h"
#include "errors.h"

RGB ** processFreqColor(BitmapInfoHeader * bmih, RGB ** arr, RGB newc); // выполнение действий с часто встречаемым цветом

RGB ** changeFreqColor(RGB ** arr, RGB freqc, RGB newc, unsigned int H, unsigned int W); // изменение цвета пикселей, если он совпадает с часто встречаемым

RGB findFreqColor(RGB * sortedPixels, int sizePixels); // нахождение самого часто встречаемого цвета

int colorsEqual(RGB a, RGB b); // проверка на то, являются ли цвета одинаковыми

int cmp(const void * a, const void * b); // функция-компаратор цветов для qsort

#endif //CW_FREQ_COLOR_H
