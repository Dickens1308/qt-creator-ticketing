QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

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

TRANSLATIONS += \
    UiSystem_en_TZ.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
