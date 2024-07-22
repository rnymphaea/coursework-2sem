#ifndef CW_STRUCTURES_H
#define CW_STRUCTURES_H

#pragma pack(push, 1)

typedef struct {
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} BitmapFileHeader;

typedef struct {
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int xPixelsPerMeter;
    unsigned int yPixelsPerMeter;
    unsigned int colorsInColorTable;
    unsigned int importantColorCount;
} BitmapInfoHeader;

#pragma pack(pop)

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} RGB;


enum RGB {
    red,
    green,
    blue
};

typedef struct {
    enum RGB componentName;
    unsigned char componentValue;
} RGBFilter;

typedef struct {
    int x, y;
    unsigned int sideSize, thickness;
    RGB color, fillColor;
    unsigned char fill; // 1 if true else 0
} Square;

enum ExchangeType {
    clockwise,
    counterclockwise,
    diagonals,
    undefined
};

typedef struct {
    enum ExchangeType extype;
    int lx, ly; // left-up coordinates
    int rx, ry; // right-down coordinates
} Exchange;

#endif //CW_STRUCTURES_H
