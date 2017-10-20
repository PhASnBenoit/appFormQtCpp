#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T13:21:02
#
#-------------------------------------------------

QT       += core gui sql serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = appFormQtCpp
TEMPLATE = app


SOURCES += main.cpp\
    cled.cpp \
    cihmappformqtcpp.cpp \
    ../biblis/cgpio.cpp \
    ../biblis/ci2c.cpp \
    ../biblis/cspi.cpp \
    ccapteurtemphumI2c.cpp \
    ccapteurtempspi.cpp \
    cbouton.cpp \
    cperiphrs232.cpp \
    csharedmemory.cpp

HEADERS  += \
    cled.h \
    cihmappformqtcpp.h \
    ../biblis/cgpio.h \
    ../biblis/ci2c.h \
    ../biblis/cspi.h \
    ccapteurtemphumi2c.h \
    ccapteurtempspi.h \
    cbouton.h \
    cperiphrs232.h \
    global.h \
    csharedmemory.h

FORMS    += \
    cihmappformqtcpp.ui

OTHER_FILES +=
