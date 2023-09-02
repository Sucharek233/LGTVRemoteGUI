QT       += core gui websockets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auth.cpp \
    commands.cpp \
    controls/applications.cpp \
    controls/audio.cpp \
    controls/channels.cpp \
    controls/custom.cpp \
    controls/input.cpp \
    controls/magicremote.cpp \
    controls/miscellaneous.cpp \
    controls/notifications.cpp \
    controls/soundoutput.cpp \
    controls/system.cpp \
    main.cpp \
    mainwindow.cpp \
    rawdataviewer.cpp \
    scanner.cpp \
    tvs.cpp

HEADERS += \
    auth.h \
    commands.h \
    controls/applications.h \
    controls/audio.h \
    controls/channels.h \
    controls/custom.h \
    controls/input.h \
    controls/magicremote.h \
    controls/miscellaneous.h \
    controls/notifications.h \
    controls/soundoutput.h \
    controls/system.h \
    mainwindow.h \
    payloadContent.h \
    rawdataviewer.h \
    scanner.h \
    tvs.h

FORMS += \
    controls/applications.ui \
    controls/audio.ui \
    controls/channels.ui \
    controls/custom.ui \
    controls/input.ui \
    controls/magicremote.ui \
    controls/miscellaneous.ui \
    controls/notifications.ui \
    controls/soundoutput.ui \
    controls/system.ui \
    mainwindow.ui \
    rawdataviewer.ui \
    scanner.ui \
    tvs.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
