#include "painter.h"

Painter::Painter()
{

}

void Painter::LoadSize(int width, int height)
{
    PictWidth = width;
    PictHeight = height;
}

void Painter::LoadPicture(PIXEL **new_picture)
{
    picture = new_picture;
}

void Painter::CreateCircle(int radius,int thickness, bool is_fill,QColor outline_color, QColor fill_color, QPoint center)
{



    for (int i = 0; i < PictHeight; i++)
    {
        for (int j = 0; j < PictWidth; j++)
        {
            if (is_fill && abs((i - center.y()) * (i - center.y()) + (j - center.x()) * (j - center.x())) < radius * radius)
            {
                drawPixel(i, j, fill_color);

            }

            if (abs((i - center.y()) * (i - center.y()) + (j - center.x()) * (j - center.x()) - radius * radius) <= radius * thickness )
            {
                 drawPixel(i, j, outline_color);
            }
        }
    }
}

void Painter::drawPixel(int y, int x, QColor currentLineColor)
{
    picture[y][x].r = static_cast<unsigned char>(currentLineColor.red());
    picture[y][x].g = static_cast<unsigned char>(currentLineColor.green());
    picture[y][x].b = static_cast<unsigned char>(currentLineColor.blue());
}

void Painter::filterRgb(int component, int value)
{
    int n;
    if(value == 0){
        n = 0;
    }else {
        n = 255;
    }
    for (int i = 0; i < PictHeight; i++)
        for (int j = 0; j < PictWidth; j++)
    {
        if (component ==0)
            picture[i][j].r = static_cast<unsigned char>(n);
        else if (component == 1)
            picture[i][j].g = static_cast<unsigned char>(n);
        else
            picture[i][j].b = static_cast<unsigned char>(n);
    }
}

void Painter::drawRectangle(int x1, int y1, int x2, int y2, QColor lineColor, int lineWidth)
{
    qDebug() << lineColor;
    for (int x = x1 - lineWidth; x < x2 + lineWidth; x++) {
        for(int i = 0; i < lineWidth; i++){
            if(x >= 0 && x < PictWidth && y1 - i >= 0){
                drawPixel(y1 - i, x, lineColor);
            }
            if(x >= 0 && x < PictWidth && y2 + i < PictHeight){
                drawPixel(y2 + i, x, lineColor);
            }
        }
    }

    for (int y = y1; y < y2; y++) {
        for(int i = 0; i < lineWidth; i++){
            if(y >= 0 && y < PictHeight && x1 - i >= 0){
                drawPixel(y, x1 - i, lineColor);
            }
            if(y >= 0 && y < PictHeight && x2 + i < PictWidth){
                drawPixel(y, x2 + i, lineColor);
            }
        }
    }
}

void Painter::highlightRectangles(Image* img, QColor rectColor, QColor lineColor, int lineWidth)
{
    std::list<int*> rectList;
    findRectangles(img, rectColor, &rectList);
    for(const auto rect : rectList){
        drawRectangle(rect[0], rect[1], rect[2], rect[3], lineColor, lineWidth);
        delete [] rect;
    }
}

void Painter::findRectangles(Image* img, QColor rectColor, std::list<int*> *rectList)
{
    QImage image = img->getPixmap().toImage();
    int** flagMatrix = new int*[PictHeight];
    for(int i = 0; i < PictHeight; i++){
        flagMatrix[i] = new int[PictWidth];
        for (int j = 0;j < PictWidth; j++) {
            flagMatrix[i][j] = 0;
        }
    }

    for (int y = 0; y < PictHeight; y++) {
        for(int x = 0; x < PictWidth; x++){
            if(image.pixelColor(x, y) == rectColor && flagMatrix[y][x] == 0){
                checkRectangle(&image, x, y, rectColor, rectList, flagMatrix);
            }
            flagMatrix[y][x] = 1;
        }
    }

    for(int i = 0; i < PictHeight; i++){
        delete [] flagMatrix[i];
    }
    delete[] flagMatrix;
}

void Painter::checkRectangle(QImage *img, int x1, int y1, QColor rectColor, std::list<int*> *rectList, int **flagMatrix)
{
    int* coords = new int[4];
    int x2 = x1;
    int y2 = y1;
    int isCorrect = 1;

    for(; x2 < PictWidth; x2++){
        flagMatrix[y1][x2] = 1;
        if(img->pixelColor(x2, y1) != rectColor){
            break;
        }
    }

    for(; y2 < PictHeight; y2++){
        flagMatrix[y2][x1] = 1;
        if(img->pixelColor(x1, y2) != rectColor){
            break;
        }
    }

    for(int y = y1; y < y2; y++){
        for(int x = x1; x < x2; x++){
            if(img->pixelColor(x, y) != rectColor){
                isCorrect = 0;
            }
            else{
                flagMatrix[y][x] = 1;
            }
        }
    }

    for(int x = x1 - 1; x < x2 + 1; x++){
        if(x >= 0 && y1 - 1 >= 0 && x < PictWidth){
            if(img->pixelColor(x, y1 - 1) == rectColor){
                isCorrect = 0;
                break;
            }
        }

        if(x >= 0 && y2 + 1 < PictHeight && x < PictWidth){
            if(img->pixelColor(x, y2 + 1) == rectColor){
                isCorrect = 0;
                break;
            }
        }
    }

    for(int y = y1 - 1; y < y2 + 1; y++){
        if(y >= 0 && x1 - 1 >= 0 && y < PictHeight){
            if(img->pixelColor(x1 - 1, y) == rectColor){
                isCorrect = 0;
                break;
            }
        }

        if(y >= 0 && x2 + 1 < PictWidth && y < PictHeight){
            if(img->pixelColor(x2 + 1, y) == rectColor){
                isCorrect = 0;
                break;
            }
        }
    }


    if(isCorrect){
        coords[0] = x1;
        coords[1] = y1;
        coords[2] = x2;
        coords[3] = y2;

        rectList->push_back(coords);
    }
}


