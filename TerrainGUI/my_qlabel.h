#ifndef MY_QLABEL_H
#define MY_QLABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QEvent>

class my_qlabel : public QLabel
{
    Q_OBJECT
public:
    explicit my_qlabel(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent * ev);
    void mouseMoveEvent(QMouseEvent * ev);
    void leaveEvent(QEvent * ev);

    int x, y;

signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_Left();

public slots:
};

#endif // MY_QLABEL_H
