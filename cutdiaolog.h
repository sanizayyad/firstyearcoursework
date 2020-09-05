#ifndef CUTDIAOLOG_H
#define CUTDIAOLOG_H

#include <QDialog>
#include <QSpinBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

class CutDiaolog :public QDialog
{
    Q_OBJECT
public:
    explicit CutDiaolog();
    ~CutDiaolog();
    QSpinBox *horizontal_input;
    QSpinBox *vertical_input;
private:
    QLabel *horizontal_label;
    QLabel *vertical_label;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    QGridLayout *layout;

};

#endif // CUTDIAOLOG_H
