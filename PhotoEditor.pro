#-------------------------------------------------
#
# Project created by QtCreator 2021-09-01T18:42:41
#
#-------------------------------------------------
QT += concurrent widgets
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PhotoEditor
TEMPLATE = app

CONFIG += c++11
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        photoeditor.cpp

HEADERS += \
        photoeditor.h

FORMS += \
        photoeditor.ui


unix|win32: LIBS += -L$$PWD/opencv/build/bin/ \
                    -llibopencv_core453 \
                    -llibopencv_highgui453 \
                    -llibopencv_imgproc453 \
                    -llibopencv_features2d453 \
                    -llibopencv_calib3d453 \
                    -llibopencv_imgcodecs453

INCLUDEPATH += $$PWD/opencv/build/include
DEPENDPATH += $$PWD/opencv/build/include
