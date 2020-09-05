#include "filterdialog.h"

FilterDialog::FilterDialog()
{
    setWindowTitle("Filter");
    setModal(true);

    color_box = new QComboBox;
    value_box = new QComboBox;
    QStringList color_list,value_list;
    color_list << "RED" << "GREEN" << "BLUE";
    value_list << "0" << "255";

    color_box->addItems(color_list);
    value_box->addItems(value_list);

    ok = new QPushButton;
    cancel = new QPushButton;
    ok->setText("Ok");
    cancel->setText("Cancel");

    color_label = new QLabel("Select Component: ");
    value_label = new QLabel("Select the value: ");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(color_label, 0, 0);
    layout->addWidget(color_box, 0, 1);
    layout->addWidget(value_label, 1, 0);
    layout->addWidget(value_box, 1, 1);
    layout->addWidget(ok, 2, 0);
    layout->addWidget(cancel, 2, 1);
    setLayout(layout);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

}

FilterDialog::~FilterDialog()
{
    delete  color_label;
    delete  value_label;
    delete ok;
    delete cancel;

}
