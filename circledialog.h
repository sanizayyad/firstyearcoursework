#ifndef CIRCLEDIALOG_H
#define CIRCLEDIALOG_H

#include <QSpinBox>
#include <QBoxLayout>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QColorDialog>
#include <QColor>
#include <QCheckBox>

class CircleDialog: public QDialog
{
    Q_OBJECT
public:
    explicit CircleDialog();
    ~CircleDialog();
    QSpinBox *radius_input;
    QSpinBox *thickness_input;
    QColor *outline_color_pick;
    QColor *fill_color_pick;
    QCheckBox *is_fill_check;

private slots:
    void set_outline_color();
    void set_fill_color();

private:
    QPushButton *button_ok;
    QPushButton *button_cancel;
    QPushButton *button_thickness_color;
    QPushButton *button_fill_color;
    QLabel *text_0;
    QLabel *text_1;
    QLabel *text_2;
   QGridLayout* layout;

};

#endif // CIRCLEDIALOG_H

