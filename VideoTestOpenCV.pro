#-------------------------------------------------
#
# Project created by QtCreator 2017-02-26T14:13:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoTestOpenCV
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += \
    icons.qrc

RC_FILE = myapp.rc


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

# add system variable OPENCV_SDK_DIR with path to opencv build directory and install subdirectory
# in my case it is
# OPENCV_SDK_DIR = D:/opencv/opencv-build/install
INCLUDEPATH += $$(OPENCV_SDK_DIR)/include

LIBS += -L$$(OPENCV_SDK_DIR)/x64/mingw/lib \
libopencv_calib3d320 \
libopencv_core320 \
libopencv_features2d320 \
libopencv_flann320 \
libopencv_highgui320 \
libopencv_imgcodecs320 \
libopencv_imgproc320 \
libopencv_ml320 \
libopencv_objdetect320 \
libopencv_photo320 \
libopencv_shape320 \
libopencv_stitching320 \
libopencv_superres320 \
libopencv_video320 \
libopencv_videoio320 \
libopencv_videostab320
