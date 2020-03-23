#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

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
    void streamButtonClicked();
    void recordButtonClicked();
    void streamingEvent();
    void saveImage();
private:
    Ui::MainWindow *ui;

    QTimer *streamingTimer;
    cv::VideoCapture cap;

    cv::Mat frame;
    QImage qt_image;

    cv::VideoWriter writer;

    bool init = false;
    bool streaming = false;
    bool recording = false;

    void streamingProcess();
    void recordingProcess();
};

#endif // MAINWINDOW_H
