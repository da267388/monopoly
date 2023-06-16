QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ItemDialog.cpp \
    carddialog.cpp \
    changedialog.cpp \
    choosedialog.cpp \
    dart.cpp \
    dice.cpp \
    ending.cpp \
    fortune.cpp \
    jaildialog.cpp \
    land_event.cpp \
    land_space.cpp \
    main.cpp \
    mainwindow.cpp \
    other.cpp \
    player.cpp \
    ruledialog.cpp \
    space.cpp \
    storedialog.cpp \
    turn.cpp

HEADERS += \
    CenterObject.h \
    GAME.h \
    carddialog.h \
    changedialog.h \
    choosedialog.h \
    dart.h \
    dice.h \
    ending.h \
    fortune.h \
    initialStates.h \
    itemDialog.h \
    jaildialog.h \
    land_event.h \
    land_space.h \
    mainwindow.h \
    other.h \
    player.h \
    ruledialog.h \
    space.h \
    storedialog.h \
    turn.h

FORMS += \
    carddialog.ui \
    changedialog.ui \
    choosedialog.ui \
    itemDialog.ui \
    jaildialog.ui \
    mainwindow.ui \
    ruledialog.ui \
    storedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    dice.png

RESOURCES += \
    audio.qrc \
    pic.qrc
