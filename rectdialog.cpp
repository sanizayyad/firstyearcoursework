#include "rectdialog.h"

RectDialog::RectDialog()
{

    setWindowTitle("Circle");
    setModal(true);

    button_ok = new QPushButton;
    button_cancel = new QPushButton;
    thickness_input = new QSpinBox;
    button_search_color = new QPushButton;
    button_line_color = new QPushButton;
    text_0 = new QLabel;
    text_1 = new QLabel;
    text_2 = new QLabel;
    search_color = new QColor;
    line_color = new QColor;

    text_0->setText("Search Color: ");
    text_1->setText("Line Color: ");
    text_2->setText("Line weight: ");
    button_search_color->setText("Set Search color");
    button_line_color->setText("Set Line color");
    button_ok->setText("Ok");
    button_cancel->setText("Cancel");
    thickness_input->setRange(1, 100);
    thickness_input->setValue(5);
    search_color->setRgb(255, 0, 0);
    line_color->setRgb(0,0,0);


    layout = new QGridLayout;
    layout->addWidget(text_0, 0, 0);
    layout->addWidget(button_search_color, 0, 1);
    layout->addWidget(text_1, 1, 0);
    layout->addWidget(button_line_color, 1, 1);
    layout->addWidget(text_2,2, 0);
    layout->addWidget(thickness_input,2, 1);
    layout->addWidget(button_ok, 3, 0);
    layout->addWidget(button_cancel, 3, 1);
    setLayout(layout);

    connect(button_ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(button_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(button_search_color, SIGNAL(clicked()), this, SLOT(set_search_color()));
    connect(button_line_color, SIGNAL(clicked()), this, SLOT(set_line_color()));

}

RectDialog::~RectDialog()
{
    delete search_color;
    delete line_color;
    delete thickness_input;
    delete button_ok;
    delete button_cancel;
    delete button_search_color;
    delete button_line_color;
    delete text_0;
    delete text_1;
    delete text_2;
    delete layout;
}

void RectDialog::set_search_color()
{
    *search_color = QColorDialog::getColor();

}

void RectDialog::set_line_color()
{
    *line_color = QColorDialog::getColor();
}
