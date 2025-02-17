QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Cross-compilation settings
#QMAKE_CXX = arm-linux-gnueabihf-g++
#QMAKE_CC = arm-linux-gnueabihf-gcc
#QMAKE_LINK = arm-linux-gnueabihf-g++

# Sysroot and library paths
#QMAKE_CXXFLAGS += --sysroot=/opt/raspi/sysroot
#QMAKE_LFLAGS += --sysroot=/opt/raspi/sysroot
#QMAKE_LIBDIR += /opt/raspi/sysroot/usr/lib/arm-linux-gnueabihf
#QMAKE_LIBDIR += /opt/raspi/sysroot/lib/arm-linux-gnueabihf

# Include paths
#INCLUDEPATH += /opt/raspi/sysroot/usr/include/arm-linux-gnueabihf
#INCLUDEPATH += /opt/raspi/sysroot/usr/include/arm-linux-gnueabihf/qt5

# Set target path
target.path = /home/dart/UiSystem
INSTALLS += target

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000   
# disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bookingdialog.cpp \
    historydialog.cpp \
    main.cpp \
    mainwindow.cpp \
    ticketdialog.cpp \
    welcomescreendialog.cpp

HEADERS += \
    bookingdialog.h \
    historydialog.h \
    mainwindow.h \
    ticketdialog.h \
    welcomescreendialog.h

FORMS += \
    bookingdialog.ui \
    historydialog.ui \
    mainwindow.ui \
    ticketdialog.ui \
    welcomescreendialog.ui

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target