#include "cutdiaolog.h"

CutDiaolog::CutDiaolog()
{
    buttonOk = new QPushButton;
    buttonCancel = new QPushButton;
    horizontal_input = new QSpinBox;
    vertical_input = new QSpinBox;
    horizontal_label = new QLabel;
    vertical_label = new QLabel;

    horizontal_label->setText("Horizontal: ");
    vertical_label->setText("Vertical: ");

    buttonOk->setText("Ok");
    buttonCancel->setText("Cancel");
    horizontal_input->setRange(1, 10);
    horizontal_input->setValue(3);
    vertical_input->setRange(1, 10);
    vertical_input->setValue(3);


    layout = new QGridLayout;
    layout->addWidget(horizontal_label, 0, 0);
    layout->addWidget(horizontal_input, 0, 1);
    layout->addWidget(vertical_label, 1, 0);
    layout->addWidget(vertical_input, 1, 1);
    layout->addWidget(buttonOk, 2, 0);
    layout->addWidget(buttonCancel, 2, 1);
    setLayout(layout);

    connect(buttonOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));

}

CutDiaolog::~CutDiaolog()
{
    delete horizontal_input;
    delete vertical_input;
    delete horizontal_label;
    delete vertical_label;
    delete buttonOk;
    delete buttonCancel;
    delete layout;
}
