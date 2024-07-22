#ifndef CW_RGB_FILTER_H
#define CW_RGB_FILTER_H

#include "structures.h"

RGB ** filter(RGB ** arr, unsigned int H, unsigned int W, enum RGB componentName, unsigned char componentValue);

#endif //CW_RGB_FILTER_H
