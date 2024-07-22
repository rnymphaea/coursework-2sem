#ifndef CW_BMP_HANDLER_H
#define CW_BMP_HANDLER_H

#include "libs.h"
#include "structures.h"
#include "errors.h"

RGB **readBMP(char * file_name, BitmapFileHeader * bmfh, BitmapInfoHeader * bmih); // чтение BMP файла

int checkBMP(BitmapFileHeader * bmfh, BitmapInfoHeader * bmih); // проверка на корректный формат BMP

void printFileHeader(BitmapFileHeader header); // вывод информации о заголовке файла

void printInfoHeader(BitmapInfoHeader header); // вывод информации о заголовке изображения

void writeBMP(char * filename, RGB ** arr, unsigned int H, unsigned int W, BitmapFileHeader * bmfh, BitmapInfoHeader * bmih); // запись в BMP файл

void help(); // вывод справки

#endif //CW_BMP_HANDLER_H
