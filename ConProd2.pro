#-------------------------------------------------
#
# Project created by QtCreator 2013-09-27T15:43:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ConProd2
TEMPLATE = app


SOURCES += main.cpp\
        conproddialog.cpp \
    consumer.cpp \
    producer.cpp \
    gz_clk.cpp \
    gpio-sysfs.cpp \
    output_program.cpp

HEADERS  += conproddialog.h \
    consumer.h \
    producer.h \
    common.h \
    myConstants.h \
    gz_clk.h \
    gpio-sysfs.h \
    output_program.h

FORMS    += conproddialog.ui

LIBS += -lqwt -lm -lbcm2835 -lpthread 
