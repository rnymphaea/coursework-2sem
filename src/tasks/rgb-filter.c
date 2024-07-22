#include "../../headers/rgb-filter.h"

RGB ** filter(RGB ** arr, unsigned int H, unsigned int W, enum RGB componentName, unsigned char componentValue) {
    for (unsigned int i = 0; i < H; i++) {
        for (unsigned int j = 0; j < W; j++) {
            switch (componentName) {
                case red:
                    arr[i][j].r = componentValue;
                    break;
                case green:
                    arr[i][j].g = componentValue;
                    break;
                case blue:
                    arr[i][j].b = componentValue;
                    break;
            }
        }
    }
    return arr;
}