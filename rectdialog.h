#ifndef RECTDIALOG_H
#define RECTDIALOG_H

#include <QSpinBox>
#include <QBoxLayout>
#include <QRadioButton>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QColorDialog>
#include <QColor>
#include <QCheckBox>

class RectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RectDialog();
    ~RectDialog();
    QColor *search_color;
    QColor *line_color;
    QSpinBox *thickness_input;

private slots:
    void set_search_color();
    void set_line_color();

private:
    QPushButton *button_ok;
    QPushButton *button_cancel;
    QPushButton *button_search_color;
    QPushButton *button_line_color;
    QLabel *text_0;
    QLabel *text_1;
    QLabel *text_2;
    QGridLayout* layout;


};

#endif // RECTDIALOG_H
