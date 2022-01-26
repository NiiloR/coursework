QT += testlib
QT += core gui widgets network multimedia

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

TARGET = tst_stattest.cpp

SOURCES += \
     tst_stattest.cpp \
    ../Game/statistics.cpp \
 #   ../Game/bettermainwindow.cpp

HEADERS += \
#    ../Game/bettermainwindow.hh \
    ../Game/statistics.hh


INCLUDEPATH += \
    ../Game \
    ../Course/CourseLib



DEPENDPATH += \
    ../Game \
    ../Course/CourseLib
