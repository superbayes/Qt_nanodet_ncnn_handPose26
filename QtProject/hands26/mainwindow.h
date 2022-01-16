#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "mythread.h"
#include <QImage>
#include <QDebug>
#include <QPainter>
#include "opencv2/opencv.hpp"
#include "myutils.h"
#include "NanoDetPLUS1.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QThread *thread_camera;
    MyTHread* MyCamera;
    cv::Mat frame;
    cv::Mat frame_3D;
    QImage frame2QImage;
    QImage frame2QImage_3D;
    NanoDetPLUS1* detector;
public:
    void paintEvent(QPaintEvent *e);

signals:
    void signal_openIR(int deviceid);
    void signal_openCAM(int deviceid);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
