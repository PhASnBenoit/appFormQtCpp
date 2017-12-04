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
    cperiphrs232.cpp \
    csharedmemory.cpp \
    ../biblis/cgpio.cpp \
    ../biblis/ci2c.cpp \
    ../biblis/cspi.cpp \
    ccapteur_i2c_sht20.cpp \
    ccapteur_spi_tc72.cpp \
    cboutonpoussoir.cpp \
    cspiioctl.cpp \
    caff_i2c_grovelcdrgb.cpp

HEADERS  += \
    cled.h \
    cihmappformqtcpp.h \
    cperiphrs232.h \
    global.h \
    csharedmemory.h \
    ../biblis/cgpio.h \
    ../biblis/ci2c.h \
    ../biblis/cspi.h \
    ccapteur_i2c_sht20.h \
    ccapteur_spi_tc72.h \
    cboutonpoussoir.h \
    cspiioctl.h \
    caff_i2c_grovelcdrgb.h

FORMS    += \
    cihmappformqtcpp.ui

OTHER_FILES +=
