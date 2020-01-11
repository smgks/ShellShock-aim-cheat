#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //this->setStyleSheet("background:transparent;");
    this->setStyleSheet("background-color: rgba(0,0,0,20)");
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);

    QWidget *widget = new QWidget(this);
    widget->setWindowState(Qt::WindowMaximized);
    widget->setGeometry(0,0,1920,1080);

    label = new QLabel(this);
    label->move(0,0);
    label->setText("qwe");
    this->setWindowState(Qt::WindowMaximized);

}

float MainWindow::calculate(int angle){
    float power = -2/(_gravity * _reg) *
            qSqrt((-1 * _gravity * _sx * _sx )/
                  (2*qCos(angle * M_PI / 180) * qCos(angle * M_PI / 180) * (qTan(angle * M_PI / 180) * _sx - _sy)));
    return power;
}

void MainWindow::mousePressEvent(QMouseEvent *event){

    label->setText(QString::number(event->x()) + ":" + QString::number(event->y()));
    if (_tab){
        _start = _end;
        _end = event->pos();
        label->setText(QString::number(_start.x()) +
                       ";" +
                       QString::number(_start.y()) +
                       " -> " +
                       QString::number(_end.x()) +
                       ";" +
                       QString::number(_end.y())
                       );
        _winSize = std::abs(_end.x()-_start.x());
    } else {
        _start = _end;
        _end = event->pos();
        label->setText(QString::number(_start.x()) +
                       ";" +
                       QString::number(_start.y()) +
                       " -> " +
                       QString::number(_end.x()) +
                       ";" +
                       QString::number(_end.y())
                       );
        _sx = std::abs(_end.x() - _start.x());
        _sy = -1*(_end.y() - _start.y());
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Alt:
        _alt = true;
        _num = "+00";
        break;
    case Qt::Key_Control:
        _ctrl = true;
        break;
    case Qt::Key_Tab:
        _tab = true;
        break;
    case Qt::Key_Space:
        _space = true;
        label->setText(QString::number(calculate(_num.toInt())));
        break;
    case Qt::Key_0 ... Qt::Key_9:
        if(this->_alt){
            this->_num = (QString(this->_num.at(0)) + this->_num.at(2) + QString(event->key()));
            label->setText("power: " + _num);
            if(this->_ctrl)
                this->_num[0] = '-';
            else{
                this->_num[0] = '+';
            }
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Alt:
        _alt = false;
        break;
    case Qt::Key_Control:
        _ctrl = false;
        break;
    case Qt::Key_Tab:
        _tab = false;
        label->setText(QString::number(_winSize));
        break;
    case Qt::Key_Space:
        _space = false;
        break;
    }
}

MainWindow::~MainWindow()
{

}

