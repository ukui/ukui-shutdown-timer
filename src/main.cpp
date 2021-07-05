#include "widget.h"
#include "qtsingleapplication.h"
#include <QApplication>
#include <QStandardPaths>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <QDebug>
#include <syslog.h>
#include <X11/Xlib.h>

int getScreenWidth() {
    Display *disp = XOpenDisplay(NULL);
    Screen *scrn = DefaultScreenOfDisplay(disp);
    if (NULL == scrn) {
        return 0;
    }
    int width = scrn->width;

    if (NULL != disp) {
        XCloseDisplay(disp);
    }
    return width;
}

int main(int argc, char *argv[])
{

    #if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
            QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
            QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    #endif

    QString id = QString("time-shutdown-" + QLatin1String(getenv("DISPLAY")));
    QtSingleApplication a(id, argc, argv);
    if (a.isRunning()) {
        a.sendMessage(nullptr);
        qDebug() << QObject::tr("time-shutdown is already running!");
        return EXIT_SUCCESS;
    } else {
        Widget w;
        w.show();
        QObject::connect(&a, SIGNAL(messageReceived(const QString&)), &w, SLOT(bootOptionsFilter(const QString&)));
        return a.exec();
    }
}
