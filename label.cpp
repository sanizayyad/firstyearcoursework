#include "label.h"

Label::Label()
{

}

void Label::mousePressEvent(QMouseEvent *ev)
{
    if (Circle)
    {
        painter.CreateCircle(radius,thickness,is_fill, outline_color,fill_color,ev->pos());
        setPixmap(img.getPixmap());
        disconnect_options();
    }

}

Image *Label::getImg()
{
    return &img;
}

Painter *Label::getPnt()
{
    return  &painter;
}

void Label::activateDrawingCircle(int new_r,int new_thickness,bool fill,QColor outline,QColor fillC)
{
    Circle = true;
    radius = new_r;
    thickness = new_thickness;
    is_fill = fill;
    outline_color = outline;
    fill_color = fillC;
}

void Label::activateFilter(int component, int component_value)
{
    painter.filterRgb(component,component_value);
}


void Label::disconnect_options()
{
    Circle = false;
}
