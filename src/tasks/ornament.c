#include "../../headers/ornament.h"

RGB ** ornament(BitmapInfoHeader * bmih, RGB ** arr, RGB color, unsigned int thick) {
    // printf("ok\n");
    unsigned int newH = bmih -> height + thick * 2;
    unsigned int newW = bmih -> width + thick * 2;
    RGB ** new = malloc(sizeof(RGB *) * newH);
    if (new == NULL) {
        printf("Error: cannot allocate memory!\n");
        exit(MEMORY_ALLOCATION_ERROR);
    }
    for (unsigned int i = 0; i < newH; i++) {
        new[i] = malloc(newW * sizeof(RGB) + (4 - newW * sizeof(RGB) % 4) % 4);
        if (new[i] == NULL) {
            printf("Error: cannot allocate memory!\n");
            exit(MEMORY_ALLOCATION_ERROR);
        }
    }

    unsigned int x1 = thick;
    unsigned int x2 = x1 + bmih->width - 1;
    unsigned int y1 = thick;
    unsigned int y2 = y1 + bmih->height - 1;

    int currx = 0;
    int curry = 0;

    int check = 0;
    printf("thick - %u color - [%d %d %d]\n", thick, color.r, color.g, color.b);
    for (unsigned int i = 0; i < newH; i++) {
        for (unsigned int j = 0; j < newW; j++) {
            if (i >= y1 && i <= y2 && j >= x1 && j <= x2) {
                new[i][j] = arr[curry][currx++];
                check++;
            } 
            else {
                new[i][j] = color;
            }
        }
        if (check) {
            currx = 0;
            curry++;
            check = 0;
        }

    }
    bmih -> height = newH;
    bmih -> width = newW;
    return new;
}
