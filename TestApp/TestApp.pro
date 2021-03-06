#-------------------------------------------------
#
# Project created by QtCreator 2018-03-23T21:43:55
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestApp
TEMPLATE = app

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
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-DLLMySql-Desktop_Qt_5_10_0_MinGW_32bit-Debug/release/ -lDLLMySql
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-DLLMySql-Desktop_Qt_5_10_0_MinGW_32bit-Debug/debug/ -lDLLMySql

INCLUDEPATH += $$PWD/../DLLMySql
DEPENDPATH += $$PWD/../DLLMySql

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-ServiceFee-Desktop_Qt_5_10_0_MinGW_32bit-Debug/release/ -lServiceFee
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-ServiceFee-Desktop_Qt_5_10_0_MinGW_32bit-Debug/debug/ -lServiceFee

INCLUDEPATH += $$PWD/../ServiceFee
DEPENDPATH += $$PWD/../ServiceFee

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-DLLSerialPort-Desktop_Qt_5_10_0_MinGW_32bit-Debug/release/ -lDLLSerialPort
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-DLLSerialPort-Desktop_Qt_5_10_0_MinGW_32bit-Debug/debug/ -lDLLSerialPort

INCLUDEPATH += $$PWD/../DLLSerialPort
DEPENDPATH += $$PWD/../DLLSerialPort

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-DLLPinCode-Desktop_Qt_5_10_0_MinGW_32bit-Debug/release/ -lDLLPinCode
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-DLLPinCode-Desktop_Qt_5_10_0_MinGW_32bit-Debug/debug/ -lDLLPinCode

INCLUDEPATH += $$PWD/../DLLPinCode
DEPENDPATH += $$PWD/../DLLPinCode
