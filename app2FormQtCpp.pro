#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T13:21:02
#
#-------------------------------------------------

QT       += core gui sql serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app2FormQtCpp
TEMPLATE = app


SOURCES += main.cpp\
    ../biblis/cgpio2024.cpp \
    cgui.cpp \
    cled.cpp \
    cperiphrs232.cpp \
    csharedmemory.cpp \
    ../biblis/ci2c.cpp \
    ../biblis/cspi.cpp \
    ccapteur_i2c_sht20.cpp \
    ccapteur_spi_tc72.cpp \
    cboutonpoussoir.cpp \
    caff_i2c_grovelcdrgb.cpp \
    ../biblis/crs232c.cpp \
    cbdd.cpp \
    cclienttcp.cpp \
    cserveurtcp.cpp

HEADERS  += \
    ../biblis/cgpio2024.h \
    cgui.h \
    cled.h \
    cperiphrs232.h \
    global.h \
    csharedmemory.h \
    ../biblis/ci2c.h \
    ../biblis/cspi.h \
    ccapteur_i2c_sht20.h \
    ccapteur_spi_tc72.h \
    cboutonpoussoir.h \
    caff_i2c_grovelcdrgb.h \
    cclienttcp.h \
    ../biblis/crs232c.h \
    cbdd.h \
    cserveurtcp.h

FORMS    += \
    cgui.ui

OTHER_FILES +=
