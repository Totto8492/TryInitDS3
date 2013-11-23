TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

QMAKE_LFLAGS += --static

SOURCES += main.cpp \
    libusb_dyn.c

HEADERS += \
    lusb0_usb.h

