#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>
#include <fstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pictureFrame, SIGNAL(Mouse_Pos()), this, SLOT(Mouse_current_pos()));
    connect(ui->pictureFrame, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_Pressed()));
    connect(ui->pictureFrame, SIGNAL(Mouse_Left()), this, SLOT(Mouse_left));
//    QPixmap image("2.jpg");
//    QList<QWidget *> wlist = parent->findChildren<QWidget *>();
////    std::cout<< wlist;
//    QLabel* pictureFrame = qobject_cast<QLabel *>(wlist.at(0));
////    pictureFrame->setText("HI");
//    if(pictureFrame != 0)
//    {
//        pictureFrame->setPixmap(image);
//    }
//    else
//        std::cout<< "it breaks";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                tr("Pictures (*.jpg)"));

        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                return;
            }
//            QByteArray array = file.readAll();
//            QImage image(array.data(), 1000, 500, QImage::Format_RGB16);
//            QImage temp;
//            temp.load(fileName);
//            this->image = &temp;

            QPixmap *mypix = new QPixmap(fileName);
            *mypix = mypix->scaled(1000, 500, Qt::KeepAspectRatio);
            ui->pictureFrame->setPixmap(*mypix);

            file.close();
        }
}

void MainWindow::Mouse_current_pos()
{
    int x = ui->pictureFrame->x, y = ui->pictureFrame->y;
//    QImage image = ui->pictureFrame->pixmap()->toImage();
//    QColor color = image.pixel(x, y);
//    QWidget* colorBox = ui->label_color;

//    QPalette p = colorBox->palette();
//    p.setColor(colorBox->backgroundRole(), color);
//    colorBox->setPalette(p);

    ui->lineEdit->setText(QString("x = %1, y = %2").arg(x).arg(y));
}

void MainWindow::Mouse_Pressed()
{
    ofstream outfile;
    outfile.open("points.txt");

    int x = ui->pictureFrame->x, y = ui->pictureFrame->y;
    QImage image = ui->pictureFrame->pixmap()->toImage();
    QColor color = image.pixel(x, y);
    QWidget* colorBox = ui->label_color;

    QPalette p = colorBox->palette();
    p.setColor(colorBox->backgroundRole(), color);
    colorBox->setPalette(p);

    outfile << x << ", " << y << "\n";
    outfile.close();
}

void MainWindow::Mouse_left()
{
    std::cout << "Mouse Left";
}
