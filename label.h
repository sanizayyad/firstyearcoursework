#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <QMouseEvent>
#include "image.h"
#include "painter.h"

class Label : public QLabel
{
public:
    Label();
    Image* getImg();
    Painter* getPnt();
    void mousePressEvent(QMouseEvent * ev);
    void activateDrawingCircle(int new_r,int new_thickness,bool fill,QColor outline,QColor fillC);
    void activateFilter(int component,int value);
    void disconnect_options();

private:
    Image img;
    Painter painter;
    bool Circle = false;
    int radius;
    int thickness;
    bool is_fill;
    QColor outline_color;
    QColor fill_color;

};

#endif // LABEL_H
