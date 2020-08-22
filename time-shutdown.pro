QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = time-shutdown
CONFIG += c++11 link_pkgconfig
include(src/src.pri)
PKGCONFIG += gsettings-qt

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

isEmpty(PREFIX){
    PREFIX = /usr
}

SOURCES += \
    src/main.cpp \

HEADERS += \

RESOURCES += \
    images.qrc

TRANSLATIONS += translations/time-shutdown_zh_CN.ts

translation.files += translations/*.qm
translation.path = /usr/share/ukui-time-shutdown/

schemes.files += data/org.ukui.time.shutdown.settings.gschema.xml
schemes.path = /usr/share/glib-2.0/schemas/

desktopfile.files = data/ukui-time-shotdown.desktop
desktopfile.path = /usr/share/applications/

target.path = $${PREFIX}/lib/ukui-notification-daemon

INSTALLS += target schemes desktopfile translation
# Default rules for deployment.

