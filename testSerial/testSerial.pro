QT += core serialport
CONFIG += c++11
TARGET = SerialCommunicatie
CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp \
    receive.cpp \
    send.cpp

HEADERS += \
    main.h \
    receive.h \
    send.h
