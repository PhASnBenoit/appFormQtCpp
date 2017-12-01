#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T13:21:02
#
#-------------------------------------------------

QT       += core gui sql serialport network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = appFormQtCpp
TEMPLATE = app


SOURCES += main.cpp\
    cled.cpp \
    cihmappformqtcpp.cpp \
    cbouton.cpp \
    cperiphrs232.cpp \
    csharedmemory.cpp \
    ../biblis/cgpio.cpp \
    ../biblis/ci2c.cpp \
    ../biblis/cspi.cpp \
    ccapteuri2csht20.cpp \
    ccapteurspitc72.cpp

HEADERS  += \
    cled.h \
    cihmappformqtcpp.h \
    cbouton.h \
    cperiphrs232.h \
    global.h \
    csharedmemory.h \
    ../biblis/cgpio.h \
    ../biblis/ci2c.h \
    ../biblis/cspi.h \
    ccapteuri2csht20.h \
    ccapteurspitc72.h

FORMS    += \
    cihmappformqtcpp.ui

OTHER_FILES +=
