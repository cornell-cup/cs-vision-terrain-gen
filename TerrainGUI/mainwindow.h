#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <iostream>
#include <QWidget>
#include <QLabel>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include "my_qlabel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_openFile_clicked();
    void Mouse_current_pos();
    void Mouse_Pressed();
    void Mouse_left();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
