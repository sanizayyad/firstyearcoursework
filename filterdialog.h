#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QSpinBox>
#include <QBoxLayout>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QColorDialog>
#include <QColor>
#include <QComboBox>


class FilterDialog: public QDialog
{
        Q_OBJECT
public:
    explicit FilterDialog();
    ~FilterDialog();
    QComboBox *color_box;
    QComboBox *value_box;

private:
    QLabel* color_label;
    QLabel* value_label;
    QPushButton *ok;
    QPushButton *cancel;

};

#endif // FILTERDIALOG_H


