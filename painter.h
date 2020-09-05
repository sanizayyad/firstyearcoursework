#ifndef PAINTER_H
#define PAINTER_H

#include "image.h"
#include <QDebug>
#include <QColor>
#include <QImage>
#include <QPixmap>
#include <list>
#include <cmath>

class Painter
{
public:
    Painter();
    void LoadSize(int width, int height);
    void LoadPicture(PIXEL** new_picture);
    void CreateCircle(int radius,int thickness,bool is_fill, QColor outline_color, QColor fill_color, QPoint center);
    void drawPixel(int x, int y, QColor currentLineColor);
    void filterRgb(int component, int value);
    void drawRectangle(int x1, int y1, int x2, int y2, QColor lineColor, int lineWidth);
    void highlightRectangles(Image* img, QColor rectColor, QColor lineColor, int lineWidth);
    void findRectangles(Image* img, QColor rectColor, std::list<int*>* rectList);
    void checkRectangle(QImage* img, int x1, int y1, QColor rectColor, std::list<int*>* rectList, int** flagMatrix);
private:
    PIXEL** picture;
    int PictWidth;
    int PictHeight;
};

#endif // PAINTER_H
