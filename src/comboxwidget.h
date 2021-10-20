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

#ifndef COMBOXWIDGET_H
#define COMBOXWIDGET_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QStyleOption>
#include <QPainter>


class comBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit comBoxWidget(QWidget *parent = nullptr);

    void initMemberVariable();
    void initLayout();
    void setLabelWeekSelect(QString text);
    QLabel      *m_pLabel_1 = nullptr;
    QLabel      *m_pLabel_2 = nullptr;
    QLabel      *m_pLabel_3 = nullptr;
    QHBoxLayout *m_pHcomBoxWidgetLayout = nullptr;

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
signals:
    void comBoxWidgetClicked();
};

#endif // COMBOXWIDGET_H
