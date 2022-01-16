#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    thread_camera = new QThread();
    MyCamera = new MyTHread();
    MyCamera->moveToThread(thread_camera);
    //detector.load("model/hair");
    detector = new NanoDetPLUS1(
                "./model/nanodet-plus-m-1.5x_416_hand26_20220116.param",
                "./model/nanodet-plus-m-1.5x_416_hand26_20220116.bin");
    //===========================================================
    connect(ui->pb_opencam,&QPushButton::clicked,this,[&](){
        if(!thread_camera->isRunning())
        {
            qDebug()<<"打开camera";
            thread_camera->start();
            emit signal_openCAM(0);
        }else
        {
            qDebug()<<"camera is running!!!";
        }
    });
    connect(this,&MainWindow::signal_openCAM,MyCamera,&MyTHread::videoThread);
    connect(MyCamera,&MyTHread::signal_frame,[&](cv::Mat& irImg_){
        frame = irImg_.clone();
        auto results = detector->detect(frame, 0.7, 0.5);
        detector->draw(frame, results);
        MyUtils::Mat2QImage(frame,frame2QImage);
        //qDebug()<<QString("ir红外width:%1;height:%2").arg(frame.cols).arg(frame.rows);
        this->update();
    });
    //===========================================================
    //===========================================================
    //关闭线程
    connect(this,&MainWindow::destroyed,[&](){
        if(thread_camera->isRunning())
        {
            MyCamera->flag_exitCamera=true;
            thread_camera->quit();
            thread_camera->wait();
        }
        qDebug()<<"关闭线程====";
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete MyCamera;
    delete thread_camera;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter;
    painter.begin(ui->ogl_cam);
    painter.drawPixmap(0,0,ui->ogl_cam->width(),ui->ogl_cam->height(),QPixmap::fromImage(this->frame2QImage));
    painter.end();
}
