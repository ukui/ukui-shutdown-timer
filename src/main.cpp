/*
 * Ukui-shutdown-timer
 *
 * Copyright (C) 2020, KylinSoft Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Authors:  liushanwen <liushanwen@kylinos.cn>
 *
 */

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
