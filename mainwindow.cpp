#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(600, 400);
    label = new Label;
    label->getImg()->createNew();
    label->setPixmap(label->getImg()->getPixmap());
    label->resize(label->getImg()->pictureWidth(),
                  label->getImg()->pictureHeight());
    label->getPnt()->LoadPicture(label->getImg()->getPixelsArr());
    label->getPnt()->LoadSize(label->getImg()->pictureWidth(),label->getImg()->pictureHeight());
    setCentralWidget(label);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete label;
}

void MainWindow::on_actionOpen_triggered()
{
    filename = QFileDialog::getOpenFileName(this, "Choose File", ".", "*.bmp");
       if (!filename.isEmpty() && !LoadFile(filename))
       {
           QMessageBox::StandardButton reply = QMessageBox::question(this, "Info",
                                                                     "Do you want to try again?");
           if (reply == QMessageBox::Yes)
               on_actionOpen_triggered();
   }
}

int MainWindow::LoadFile(QString filename)
{
    good_filename = new char[filename.length() + 1];
    std::strcpy(good_filename, filename.toLatin1().constData());

    int f = label->getImg()->load(good_filename);
    if (f <= 0)
    {
        QMessageBox::warning(this, "Error", "I can't open this file or his type is uncorrect!");
        return 0;
    }

    label->resize(label->getImg()->pictureWidth(), label->getImg()->pictureHeight());
    label->setPixmap(label->getImg()->getPixmap());
    label->getPnt()->LoadSize(label->getImg()->pictureWidth(),label->getImg()->pictureHeight());
    label->getPnt()->LoadPicture(label->getImg()->getPixelsArr());

    delete [] good_filename;
    return 1;
}


void MainWindow::on_actionNew_triggered()
{
    if (!(label->getImg()->isNull()))
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Information",
                                                                  "Do you want to save current image?");
        if (reply == QMessageBox::Yes)
            on_actionSave_triggered();

    }

    label->getImg()->createNew();
    label->setPixmap(label->getImg()->getPixmap());
    label->resize(label->getImg()->pictureWidth(),label->getImg()->pictureHeight());
    label->getPnt()->LoadPicture(label->getImg()->getPixelsArr());
    label->getPnt()->LoadSize(label->getImg()->pictureWidth(),label->getImg()->pictureHeight());
}
void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить как...", "./", "*.bmp");
    if (fileName.isNull()) return;

    good_filename = new char[fileName.length() + 1];
    std::strcpy(good_filename, fileName.toLatin1().constData());
    for (unsigned int i = 0; i < std::strlen(good_filename); i++) if (good_filename[i] == '\\') good_filename[i] = '/';
    label->getImg()->save(good_filename);
}

void MainWindow::on_actionQuit_triggered()
{
     QApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "Info", "This program was created by Sani Zayyad Bakeko using the QtCreator(v. 4.9.0)\n");
}

void MainWindow::on_actionFile_Info_triggered()
{
     QMessageBox::information(this, "File info", label->getImg()->info());

}


///// messsssed up shittt
void MainWindow::on_actionCircle_triggered(){
    CircleDialog circle_dialog;
    if (circle_dialog.exec() == QDialog::Accepted)
    {
        label->activateDrawingCircle(circle_dialog.radius_input->value(),
                                     circle_dialog.thickness_input->value(),
                                     circle_dialog.is_fill_check->isChecked(),
                                     circle_dialog.outline_color_pick->toRgb(),
                                     circle_dialog.fill_color_pick->toRgb()
                                     );
    }

}

void MainWindow::on_actionFilter_triggered()
{
    FilterDialog filter_dialog;

    if (filter_dialog.exec() == QDialog::Accepted)
    {
        label->activateFilter(filter_dialog.color_box->currentIndex(),filter_dialog.value_box->currentIndex());
        label->setPixmap(label->getImg()->getPixmap());
    }
}


void MainWindow::on_actionDivide_triggered()
{

    CutDiaolog cut_dialog;
    if (cut_dialog.exec() == QDialog::Accepted)
    {
        label->getImg()->createImages("C:/Users/saniz/OneDrive/Desktop/test/",
                                      cut_dialog.vertical_input->value(),
                                      cut_dialog.horizontal_input->value());

    }


}

void MainWindow::on_actionHighlight_Rectangle_triggered()
{
    RectDialog rect_dialog;
    if(rect_dialog.exec() == QDialog::Accepted)
    {

        label->getPnt()->highlightRectangles(label->getImg(),
                                           rect_dialog.search_color->toRgb(),
                                           rect_dialog.line_color->toRgb(),
                                           rect_dialog.thickness_input->value());
        label->setPixmap(label->getImg()->getPixmap());


    }
}



void MainWindow::on_actiondefense_triggered()
{
//    label->getImg()->defense("C:/Users/saniz/OneDrive/Desktop/test/",
//                             1,
//                             2,
//                             1);
    label->getImg()->defense("C:/Users/saniz/OneDrive/Desktop/test/",
                             1,
                            2,
                             2);
//    label->setPixmap(label->getImg()->getPixmap());
}
