#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    QLabel *label;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override; 

private:
    float calculate(int angle);
    float calculateSpeed();
    void drawGraph(float power);
    QString redText(QString str);

private:
    bool _ctrl = false;
    bool _tab = false;
    bool _alt = false;
    bool _space = false;

    QPoint _start{0,0};
    QPoint _end{0,0};
    QString _num = "00";

    QGraphicsView *view = new QGraphicsView(this);
    QGraphicsScene *scene = new QGraphicsScene(this);

    int _winSize = 0;
    int _sx = 0;
    int _sy = 0;

    int _angle = 0;

    const float _gravity = -379.106;
    const float _reg = 0.518718;
};
#endif // MAINWINDOW_H
