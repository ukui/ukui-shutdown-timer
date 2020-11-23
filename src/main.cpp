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
    if (getScreenWidth() > 2560) {
        #if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
                QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
                QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
        #endif
    }

//    /* 如果系统中有实例在运行则退出 */
//    QStringList strlistHomePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
//    QString strLockPath = strlistHomePath.at(0) + "/.config/time-shutdown";

//    int fd = open(strLockPath.toUtf8().data(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
//    if (fd < 0)
//        exit(1);

//    if (lockf(fd, F_TLOCK, 0)) {
//        syslog(LOG_ERR, "Can't lock single file, ukui-sidebar is already running!");
//        qDebug()<<"Can't lock single file, ukui-sidebar is already running!";
//        exit(0);
//    }
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
