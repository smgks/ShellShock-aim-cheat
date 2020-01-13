#include "mainwindow.h"

#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtMath>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
    //this->setStyleSheet("background:transparent;");
    this->setStyleSheet("background-color: rgba(0,0,0,20)");
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);

    QWidget *widget = new QWidget(this);
    widget->setWindowState(Qt::WindowMaximized);
    view->setGeometry(0,0,1920,1080);
    view->setScene(scene);
    widget->setGeometry(0,0,1920,1080);

    scene->setSceneRect(QRect(0,0,1920,1080));

    label = new QLabel(this);
    label->move(0,0);
    label->setText(redText("started"));

    label->setPalette(QPalette(QColor(255,0,0)));
    this->setWindowState(Qt::WindowMaximized);

}

QString MainWindow::redText(QString str){
    return QString(tr("<font color='red'>%2</font>")).arg(str);
}

float MainWindow::calculate(int angle){
    // TODO: Add wind correction
    _angle = angle;
    float power = -2/(_gravity * _reg) *
            calculateSpeed();
    drawGraph(power);
    return power*10;
}

float MainWindow::calculateSpeed(){
    return qSqrt((-1 * _gravity * _sx * _sx ) /
                 (2*qCos(_angle * M_PI / 180) *
                 qCos(_angle * M_PI / 180) *
                 (qTan(_angle * M_PI / 180) *
                  _sx - _sy)));
}

void MainWindow::drawGraph(float power){
    float speed = -0.5 * power * _gravity * _reg / qCos(float(_angle) * M_PI / 180.0);
    float time = _sx / speed / qCos(float(_angle) * M_PI / 180.0);
    float timeUnit = time / 40.0;
    // TODO: Fix gravity calculation

    int yDir = (_end.y() - _start.y())/std::abs(_end.y() - _start.y());
    float k = 2 * (yDir * _sy - speed * qSin(float(_angle) * M_PI / 180.0)) / _gravity / time / time;

    // TODO: Fix viualising trajectory

    //for (auto i = .0; i < time; i += timeUnit) {
    //    float x1 = speed * qCos(float(_angle) * M_PI / 180.0) * i;
    //    float y1 = speed * qSin(float(_angle) * M_PI / 180.0) * i + k * _gravity * i * i / 2;
    //    i += timeUnit;
    //    float x2 = speed * qCos(float(_angle) * M_PI / 180.0) * i;
    //    float y2 = speed * qSin(float(_angle) * M_PI / 180.0) * i + k * _gravity * i * i / 2;
    
    //    int direction = (_end.x() - _start.x())/std::abs((_end.x() - _start.x()));
    
    //    scene->addLine(_start.x() + direction * x1,
    //                   _start.y() - y1,
    //                   _start.x() + direction * x2,
    //                   _start.y() - y2,
    //                   QPen(QColor(255,0,0))
    //                   );
    //}
}

void MainWindow::mousePressEvent(QMouseEvent *event){

    label->setText(redText(QString::number(event->x()) + ":" + QString::number(event->y())));

    _start = _end;
    _end = event->pos();
    label->setText(redText(QString::number(_start.x()) +
                   ";" +
                   QString::number(_start.y()) +
                   " -> " +
                   QString::number(_end.x()) +
                   ";" +
                   QString::number(_end.y())
                   ));
    _sx = std::abs(_end.x() - _start.x());
    _sy = -1*(_end.y() - _start.y());
    scene->clear();
    scene->setPalette(QPalette(QColor(230,10,10)));
    scene->addEllipse(_start.x(), _start.y(), 5, 5, QPen(QColor(255,0,0)));
    scene->addEllipse(_end.x(), _end.y(), 5, 5, QPen(QColor(255,0,0)));
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Alt:
        _alt = true;
        break;
    case Qt::Key_Control:
        _ctrl = true;
        _num = "+00";
        break;
    case Qt::Key_Tab:
        _tab = true;
        break;
    case Qt::Key_Space:
        _space = true;
        label->setText(redText(QString::number(calculate(_num.toInt()))));
        break;
    case Qt::Key_0 ... Qt::Key_9:
        if(this->_ctrl){
            this->_num = (QString(this->_num.at(0)) + this->_num.at(2) + QString(event->key()));
            label->setText(redText("angle: " + _num));
            if(this->_alt)
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
        label->setText(redText(QString::number(_winSize)));
        break;
    case Qt::Key_Space:
        _space = false;
        break;
    }
}

MainWindow::~MainWindow(){

}

