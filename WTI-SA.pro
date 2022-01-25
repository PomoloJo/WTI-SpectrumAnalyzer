QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/CShareMemory/CShareMemory.cpp \
    source/main.cpp \
    source/mainwindow.cpp \
    source/qcustomplot.cpp \
    source/CWorkThread.cpp

HEADERS += \
    include/CShareMemory/CShareMemory.h \
    include/mainwindow.h \
    include/qcustomplot.h \
    include/CWorkThread.h

FORMS += \
    ui_file/mainwindow.ui

UI_DIR += \
    ./include

DESTDIR += \
    bin

MOC_DIR += \
    moc

RESOURCES += \
    resource/res.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

