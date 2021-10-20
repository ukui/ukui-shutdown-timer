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
#ifndef TIMESHOWWIDGET_H
#define TIMESHOWWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QStyleOption>
#include <QPainter>
#include <QApplication>
#include "verticalscroll60.h"

/* 含有底色无控件的窗体类,中间选中条目底色 */
class BlankShadowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BlankShadowWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);
};

/* 显示中间部分的widget */
class timeShowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit timeShowWidget(QWidget *parent = nullptr);
    VerticalScroll_60 *m_pHourRollWidget;
    VerticalScroll_60 *m_pMinuteRollWidget;

private:
    void initMemberVariable();
    void initLayout();
    void setLabelFont();

private:
    QLabel *m_pHourLabel;
    QLabel *m_pMinuteLabel;
    QLabel *m_pSeparatedLabel;
signals:
};

#endif // TIMESHOWWIDGET_H
