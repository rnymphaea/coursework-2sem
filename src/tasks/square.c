#include "../../headers/square.h"

void initSquare(Square * sq) {
    sq -> x = 0;
    sq -> y = 0;
    sq -> sideSize = 0;
    sq -> thickness = 0;
    RGB color = {0, 0, 0};
    sq -> color = color;
    RGB fillColor = {0, 0, 0};
    sq -> fillColor = fillColor;
    sq -> fill = 0;
}

RGB ** drawLine(RGB ** arr, unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, RGB color) {
    if (x1 == x2) {
        for (unsigned int col = y1; col < y2; col++) {
            arr[col][x1] = color;
        }
    } else if (y1 == y2) {
        for (unsigned int row = x1; row < x2; row++) {
            arr[y1][row] = color;
        }
    }
    return arr;
}

RGB ** drawSquare(RGB ** arr, unsigned int H, unsigned int W, Square sq) {
    sq.y = H - sq.y;

    if (sq.x > (int)W || (int)(sq.x + sq.sideSize + sq.thickness / 2) <= 0) {
        printf("Error: cannot draw square - invalid x coordinate!\n");
        exit(INVALID_OPTION_ARG_ERROR);
    } else if ((int)(sq.y + sq.thickness / 2) < 0) {
        printf("Error: cannot draw square - invalid y coordinate!\n");
        exit(INVALID_OPTION_ARG_ERROR);
    }

    unsigned int x1, x2, y1, y2;
    sq.x += sq.thickness / 2;

    sq.y -= sq.thickness / 2;
    sq.sideSize -= sq.thickness + 1;

    for (unsigned int t = 0; t < sq.thickness; t++) {

        if ((int)(sq.y + t) < (int)H && (int)(sq.y + t) >= 0) {
            y1 = sq.y + t;
            if ((int)(sq.x - t) < 0) {
                x1 = 0;
            } else {
                x1 = sq.x - t;
            }
            if ((int)(sq.x + sq.sideSize + t) > (int)W) {
                x2 = W;
            } else {
                if ((int)(sq.x + sq.sideSize + t) < 0) {
                    continue;
                }
                x2 = sq.x + sq.sideSize + t;
            }
            drawLine(arr, x1, x2, y1, y1, sq.color);
        }

        if ((int)(sq.y - sq.sideSize - t) >= 0 && sq.y - sq.sideSize - t < H) {
            y1 = sq.y - sq.sideSize - t;
            if ((int)(sq.x - t) < 0) {
                x1 = 0;
            } else {
                x1 = sq.x - t;
            }
            if (sq.x + sq.sideSize + t > W) {
                x2 = W;
            } else {
                x2 = sq.x + sq.sideSize + t;
            }
            drawLine(arr, x1, x2, y1, y1, sq.color);
        }

        if ((int)(sq.x - t) >= 0) {
            x1 = sq.x - t;
            if (sq.y + t > H) {
                y2 = H;
            } else {
                y2 = sq.y + t;
            }
            if ((int)(sq.y - sq.sideSize - t) < 0) {
                y1 = 0;
            } else {
                y1 = sq.y - sq.sideSize - t;
            }
            drawLine(arr, x1, x1, y1, y2, sq.color);

        }

        if (sq.x + sq.sideSize + t <= W) {
            x1 = sq.x + sq.sideSize + t;
            if ((int)(sq.y + t + 1) > (int)H) {
                y2 = H;
            } else if ((int)(sq.y + t + 1) >= 0){
                y2 = sq.y + t + 1;
            }
            else {
                continue;
            }
            if ((int)(sq.y - sq.sideSize - t) < 0) {
                y1 = 0;
            } else {
                y1 = sq.y - sq.sideSize - t;
            }
            drawLine(arr, x1, x1, y1, y2, sq.color);

        }
    }


    if (sq.fill) {
        if ((int)(sq.x + sq.sideSize) < 0) {
            printf("Square wasn't filled!\n");
            return arr;
        }
        sq.sideSize += sq.thickness - 1;
        for (y1 = sq.y - 1; (int)y1 > (int)(sq.y - sq.sideSize + sq.thickness - 1); y1--) {
            if (y1 > (H - 1)) {
                continue;
            }
            if (sq.x < 0) {
                x1 = 0;
            } else {
                x1 = sq.x + 1;
            }
            if ((int)(sq.x + sq.sideSize - 1) > (int)W) {
                x2 = W;
            } else {
                x2 = sq.x + sq.sideSize - sq.thickness + 1;
            }
            drawLine(arr, x1, x2, y1,y1, sq.fillColor);
        }
    }

    return arr;
}


