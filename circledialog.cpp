#include "circledialog.h"

CircleDialog::CircleDialog()
{
    setWindowTitle("Circle");
    setModal(true);

    button_ok = new QPushButton;
    button_cancel = new QPushButton;
    radius_input = new QSpinBox;
    thickness_input = new QSpinBox;
    button_thickness_color = new QPushButton;
    button_fill_color = new QPushButton;
    text_0 = new QLabel;
    text_1 = new QLabel;
    text_2 = new QLabel;
    outline_color_pick = new QColor;
    fill_color_pick = new QColor;
    is_fill_check = new QCheckBox(this);

    text_0->setText("Radius: ");
    text_1->setText("Thickness: ");
    text_2->setText("Fill Circle: ");
    button_thickness_color->setText("Set Outline color");
    button_fill_color->setText("Set Fill color");
    button_ok->setText("Ok");
    button_cancel->setText("Cancel");
    radius_input->setRange(1, 100);
    radius_input->setValue(50);
    thickness_input->setRange(1, 100);
    thickness_input->setValue(5);
    outline_color_pick->setRgb(0, 0, 0);
    fill_color_pick->setRgb(255,255,255);


    layout = new QGridLayout;
    layout->addWidget(text_0, 0, 0);
    layout->addWidget(radius_input, 0, 1);
    layout->addWidget(text_1, 1, 0);
    layout->addWidget(thickness_input, 1, 1);
    layout->addWidget(button_thickness_color, 1, 2);
    layout->addWidget(text_2,2, 0);
    layout->addWidget(is_fill_check,2, 1);
    layout->addWidget(button_fill_color, 2, 2);
    layout->addWidget(button_ok, 3, 0);
    layout->addWidget(button_cancel, 3, 1);
    setLayout(layout);

    connect(button_ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(button_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(button_thickness_color, SIGNAL(clicked()), this, SLOT(set_outline_color()));
    connect(button_fill_color, SIGNAL(clicked()), this, SLOT(set_fill_color()));



}

CircleDialog::~CircleDialog()
{
    delete radius_input;
    delete thickness_input;
    delete outline_color_pick;
    delete fill_color_pick;
    delete is_fill_check;
    delete button_ok;
    delete button_cancel;
    delete button_thickness_color;
    delete button_fill_color;
    delete text_0;
    delete text_1;
    delete text_2;
    delete layout;
}

void CircleDialog::set_outline_color()
{
    *outline_color_pick = QColorDialog::getColor();

}

void CircleDialog::set_fill_color()
{
    *fill_color_pick = QColorDialog::getColor();

}

