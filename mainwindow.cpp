#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->streamButton, &QPushButton::clicked, this, &MainWindow::streamButtonClicked);
    QObject::connect(ui->recordButton, &QPushButton::clicked, this, &MainWindow::recordButtonClicked);
    QObject::connect(ui->shotButton, &QPushButton::clicked, this, &MainWindow::saveImage);

    streamingTimer = new QTimer(this);
    QObject::connect(streamingTimer, &QTimer::timeout, this, &MainWindow::streamingEvent);
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::streamButtonClicked(){
    if (!streaming){
        bool isInt;
        int stream = ui->adressEdit->text().toInt(&isInt);
        if (isInt)
            cap.open(stream);
        else
            cap.open(ui->adressEdit->text().toStdString());
        if(!cap.isOpened())
        {
            QMessageBox *msg = new QMessageBox(this);
            msg->setText(QString("Не могу открыть поток или устройство"));
            msg->exec();
        }else{
            streaming = true;
            ui->streamButton->setText(QString("Закрыть поток"));
            ui->recordButton->setEnabled(true);
            ui->adressEdit->setEnabled(false);
            ui->shotButton->setEnabled(true);
            streamingTimer->start(100);
        }
    }else{
        ui->streamButton->setText(QString("Открыть поток"));
        ui->recordButton->setEnabled(false);
        ui->recordButton->setText(QString("Начать запись"));
        streaming = false;
        recording = false;
        ui->shotButton->setEnabled(false);
        ui->adressEdit->setEnabled(true);

        streamingTimer->stop();
        cap.release();
    }
}

void MainWindow::streamingEvent(){
    if (cap.read(frame)){

        if (recording){
            if (!init){
                std::string filename =  "video.avi";
                int fcc =   CV_FOURCC('D','I','V','X');
                int fps =   10; // Since timer works per 100ms
                cv::Size frameSize(cap.get(CV_CAP_PROP_FRAME_WIDTH),cap.get(CV_CAP_PROP_FRAME_HEIGHT));
                writer = cv::VideoWriter(filename,fcc,fps,frameSize);
                init = true;
            }

            putText(frame,"[REC]",cv::Point(0,30),5,1,cv::Scalar(0,0,225));
            writer.write(frame);
        }
        cvtColor(frame, frame, CV_BGR2RGB);
        qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
        ui->label->setPixmap(QPixmap::fromImage(qt_image));
        ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        ui->label->setScaledContents(true);
        ui->label->adjustSize();
    }
}

void MainWindow::saveImage(){
    qt_image.save("picture.jpg");
}

void MainWindow::recordButtonClicked(){
    if (!recording){
        recording = true;
        ui->recordButton->setText(QString("Остановить запись"));
    }else{
        ui->recordButton->setText(QString("Начать запись"));
        recording = false;
        writer.release();
    }
}

