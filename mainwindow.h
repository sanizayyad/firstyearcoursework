#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include<QMessageBox>
#include <cstring>
#include "label.h"
#include "circledialog.h"
#include "filterdialog.h"
#include "cutdiaolog.h"
#include "rectdialog.h"
#include <QDebug>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionCircle_triggered();
    int LoadFile(QString filename);
    void on_actionSave_triggered();
    void on_actionNew_triggered();
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();
    void on_actionFile_Info_triggered();
    void on_actionFilter_triggered();    
    void on_actionDivide_triggered();
    void on_actionHighlight_Rectangle_triggered();

    void on_actiondefense_triggered();

private:
    Label* label;
    Ui::MainWindow *ui;
    QString filename;
    char* good_filename;

};

#endif // MAINWINDOW_H
