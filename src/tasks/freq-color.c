#include "../../headers/freq-color.h"


RGB ** processFreqColor(BitmapInfoHeader * bmih, RGB ** arr, RGB newc) {
    RGB * pixels =(RGB *)malloc(bmih -> height * bmih -> width * sizeof(RGB)); // одномерный массив пикселей
    if (pixels == NULL) {
        printf("Error: cannot allocate memory!\n");
        exit(MEMORY_ALLOCATION_ERROR);
    }

    int sizep = 0; // размер одномерного массива пикселей

    for (unsigned int i = 0; i < bmih -> height; i++) {
        for (unsigned int j = 0; j < bmih -> width; j++) {
            pixels[sizep++] = arr[i][j];
        }
    }

    qsort(pixels, bmih -> height * bmih -> width, sizeof(RGB), cmp);

    RGB freq = findFreqColor(pixels, sizep);
    RGB ** rgb = changeFreqColor(arr, freq, newc, bmih -> height, bmih -> width);
    free(pixels);
    return rgb;
}

RGB ** changeFreqColor(RGB ** arr, RGB freqc, RGB newc, unsigned int H, unsigned int W) {
    for (unsigned int i = 0; i < H; i++) {
        for (unsigned int j = 0; j < W; j++) {
            if (colorsEqual(arr[i][j], freqc)) {
                arr[i][j] = newc;
            }
        }
    }
    return arr;
}

int colorsEqual(RGB a, RGB b) {
    return a.r == b.r && a.g == b.g && a.b == b.b;
}

RGB findFreqColor(RGB * sortedPixels, int sizePixels) {
    int max = 1; // максимальное количество вхождений одного цвета
    int curr = 1; // текущее количество вхождений цвета
    RGB maxc; // цвет с максимальным количеством вхождений

    for (int i = 1; i < sizePixels; i++) {
        if (colorsEqual(sortedPixels[i], sortedPixels[i - 1])) {
            curr++;
        }
        else {
            curr = 1;
        }
        if (curr > max) {
            max = curr;
            maxc = sortedPixels[i];
        }
    }

    return maxc;
}

int cmp(const void * a, const void * b) {
    RGB f = *(RGB *)a;
    RGB s = *(RGB *)b;
    if (f.r > s.r) {
        return 1;
    }
    else if (f.r == s.r) {
        if (f.g > s.g) {
            return 1;
        }
        else if (f.g == s.g) {
            if (f.b > s.b) {
                return 1;
            }
            else if (f.b == s.b) {
                return 0;
            }
            else {
                return -1;
            }
        } else {
            return -1;
        }
    }
    else {
        return -1;
    }
}
