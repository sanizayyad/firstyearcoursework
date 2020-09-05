#ifndef IMAGE_H
#define IMAGE_H

#include <QPixmap>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <QDebug>

typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;


#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEADER{
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
} BITMAPFILEHEADER;
#pragma pack(pop)


typedef struct tagBITMAPINFOHEADER{
    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
} BITMAPINFOHEADER;


struct PIXEL{
        unsigned char b;
        unsigned char g;
        unsigned char r;
};

class Image
{
public:
    Image();
    int load(char* path);
    int save(const char* path);
    void createNew();
    QPixmap getPixmap();
    int pictureHeight();
    int pictureWidth();
    PIXEL** getPixelsArr();
    bool isNull();
    QString info() const;
    void createImages(const char* string, int vertical,int horizontal);
    int save3(const char* string,int numX,int numY,int vertical,int horizontal);
    void defense(const char* string, int vertical,int horizontal, int type);
    int defenseSave(const char* string,int numX,int numY,int vertical,int horizontal,int type);
    void drawPixel(int y, int x, QColor currentLineColor);
    void paintwhite(BITMAPINFOHEADER bih);

private:
    bool is_load = false;
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
    PIXEL** picture;
    int max;

};

#endif // IMAGE_H
