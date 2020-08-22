#include "widget.h"
#include <QApplication>
#include <QStandardPaths>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <QDebug>
#include <syslog.h>

int main(int argc, char *argv[])
{
    /* 如果系统中有实例在运行则退出 */
    QStringList strlistHomePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
    QString strLockPath = strlistHomePath.at(0) + "/.config/time-shutdown";

    int fd = open(strLockPath.toUtf8().data(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0)
        exit(1);

    if (lockf(fd, F_TLOCK, 0)) {
        syslog(LOG_ERR, "Can't lock single file, ukui-sidebar is already running!");
        qDebug()<<"Can't lock single file, ukui-sidebar is already running!";
        exit(0);
    }

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
