#include "../headers/bmp-handler.h"

RGB ** readBMP(char * file_name, BitmapFileHeader * bmfh, BitmapInfoHeader * bmih){
    FILE *f = fopen(file_name, "rb");
    if (f == NULL) {
        printf("Error: file doesn't exist!\n");
        exit(FILE_ERROR);
    }
    fread(bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(bmih, 1, sizeof(BitmapInfoHeader), f);

    fseek(f, bmfh -> pixelArrOffset, SEEK_SET);
    unsigned int H = bmih -> height;
    unsigned int W = bmih -> width;

    RGB **arr = malloc(H * sizeof(RGB*));
    if (arr == NULL) {
        printf("Error: cannot allocate memory!\n");
        exit(MEMORY_ALLOCATION_ERROR);
    }

    for(unsigned int i = 0; i < H; i++){
        arr[i] = malloc(W * sizeof(RGB) + (4 - W * sizeof(RGB) % 4) % 4);
        if (arr[i] == NULL) {
            printf("Error: cannot allocate memory!\n");
            exit(MEMORY_ALLOCATION_ERROR);
        }
        fread(arr[i], 1, W * sizeof(RGB) + (4 - W * sizeof(RGB) % 4) % 4,f);
    }
    fclose(f);
    return arr;
}

int checkBMP(BitmapFileHeader * bmfh, BitmapInfoHeader * bmih) {
    return bmfh -> signature == 0x4D42 && bmih -> compression == 0 && bmih -> bitsPerPixel == 24;
}

void writeBMP(char * filename, RGB ** arr, unsigned int H, unsigned int W, BitmapFileHeader * bmfh, BitmapInfoHeader * bmih) {
    FILE * file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: cannot open the file [%s]!\n", filename);
        exit(FILE_ERROR);
    }
    fwrite(bmfh, 1, sizeof(BitmapFileHeader), file);
    fwrite(bmih, 1, sizeof(BitmapInfoHeader), file);
    fseek(file, bmfh->pixelArrOffset, SEEK_SET);
    for (unsigned int i = 0; i < H; i++) {
        fwrite(arr[i], 1,   W * sizeof(RGB) + (4 - W * sizeof(RGB) % 4) % 4, file);
    }
    fclose(file);
}

void printFileHeader(BitmapFileHeader header){
    printf("signature:\t%x (%hu)\n", header.signature,
           header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize,
           header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1,
           header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2,
           header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void printInfoHeader(BitmapInfoHeader header){
    printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
    printf("width: \t%x (%u)\n", header.width, header.width);
    printf("height: \t%x (%u)\n", header.height, header.height);
    printf("planes: \t%x (%hu)\n", header.planes, header.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("compression:\t%x (%u)\n", header.compression, header.compression);
    printf("imageSize:\t%x (%u)\n", header.imageSize,header.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}

void help() {
    printf("Course work for option 5.3, created by Alexandr Lvov.\n");
    printf("Available options:\n");
    printf("'--help' ['-h'] - вывод справки.\n\n");
    printf("--input ['-i'] - имя входного файла.\n\n");
    printf("--output ['-o'] - имя выходного файла. Если флаг не использован, имя выходного файла - 'out.bmp'.\n\n");
    printf("--info - вывод информации о файле.\n\n");
    printf("'--rgbfilter' ['-f'] - этот инструмент позволяет для всего изображения либо установить в диапазоне от 0 до 255 значение заданной компоненты.\n");
    printf("├── '--component_name' - какую компоненту требуется изменить. Возможные значения: red, green, blue.\n");
    printf("└── '--component_value' - новое значение изменяемой компоненты. Возможные значения в диапазоне [0, 255].\n\n");
    printf("'--square' ['-s'] - рисование квадрата.\n");
    printf("├── '--left_up' - координата левого верхнего угла, значение задаётся в формате `left.up`, где left – координата по x, up – координата по y.\n");
    printf("├── '--size_size' - размер стороны. Целое число, больше 0.\n");
    printf("├── '--thickness' ['-t'] - толщина линий. Целое число, больше 0.\n");
    printf("├── '--color' ['-c'] - цвет линий. Задаётся строкой `rrr.ggg.bbb`, где rrr/ggg/bbb – числа, задающие цветовую компоненту.\n");
    printf("├── '--fill' - заливка. Работает как бинарное значение: флаг есть - true, в ином случае - false.\n");
    printf("└──|── '--fill_color'- цвет заливки, если был введён флаг '--fill'. Принимает значения, аналогичные флагу '--color'.\n\n");
    printf("'--exchange' ['-x'] - поменять местами 4 куска области. Выбранная пользователем прямоугольная область делится на 4 части и эти части меняются местами\n");
    printf("├── '--left_up' - координата левого верхнего угла, значение задаётся в формате `left.up`, где left – координата по x, up – координата по y.\n");
    printf("├── '--right_down' - координата правого нижнего угла, значение задаётся в формате `right.down`, где right – координата по x, down – координата по y.\n");
    printf("└── '--exchange_type' - способ обмена частей. Возможные значения: `clockwise`, `counterclockwise`, `diagonals`.\n\n");
    printf("'--freq_color' - найти самый часто встречаемый цвет и заменить его другим.\n");
    printf("└── '--color' - цвет, на который необходимо заменить старый. Задаётся строкой `rrr.ggg.bbb`, где rrr/ggg/bbb – числа, задающие цветовую компоненту.\n");
}

