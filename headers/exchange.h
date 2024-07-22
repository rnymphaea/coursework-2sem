#ifndef CW_EXCHANGE_H
#define CW_EXCHANGE_H

#include "libs.h"
#include "structures.h"
#include "errors.h"

void initExchange(Exchange * ex); // инициализация полей структуры Exchange

RGB ** exchange(RGB ** arr, unsigned int H, unsigned int W, Exchange ex);

#endif //CW_EXCHANGE_H
