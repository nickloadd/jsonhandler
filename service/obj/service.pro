QT += core network websockets
QT -= gui

OBJECTS_DIR = ./
DESTDIR = ../bin

#INCLUDEPATH += /usr/lib/i386-linux-gnu
#LIBS += -L/usr/lib/i386-linux-gnu

TARGET = service.bin
CONFIG += console c++11
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    ../src/main.cpp \
    ../src/tserver.cpp \
    ../src/tfilemanager.cpp \
    ../src/tjsonhandler.cpp \
    ../src/webservice.cpp

HEADERS += \
    ../src/tserver.h \
    ../src/tfilemanager.h \
    ../src/tjsonhandler.h \
    ../src/types.h \
    ../src/webservice.h

