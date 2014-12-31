#-------------------------------------------------
#
# Project created by QtCreator 2014-12-29T12:48:34
#
#-------------------------------------------------

QT       += core
QT       += gui
QT       += multimedia

TARGET = CircularBuffer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    global.cpp \
    audiorecorder.cpp

HEADERS += \
    global.h \
    Consumer.h \
    Producer.h \
    audiorecorder.h

target.path = /home/pi
INSTALLS += target
