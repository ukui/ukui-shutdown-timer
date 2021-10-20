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

#ifndef DROPDOWNBOX_H
#define DROPDOWNBOX_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QHBoxLayout>
#include <QScroller>
#include <QPainter>
#include <QStyleOption>
#include <QTimer>
#include <QDebug>
#include <QMouseEvent>
#include <QScrollBar>

/* ListWidget中条目， 周一 ----------- √ */
class dateSelectionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit dateSelectionWidget(QString week, QWidget *parent = nullptr);
    void setLabeldata(QString week);
    QLabel       *m_pweekLabel;
    QLabel       *m_pselectedLabelIcon;
    QHBoxLayout  *m_pHWeekLayout;

protected:
    void mouseReleaseEvent(QMouseEvent *event);

signals:

};

/* 下拉框主体 */
class dropdownbox : public QWidget
{
    Q_OBJECT
public:
    explicit dropdownbox(QWidget *parent = nullptr);

    int                     m_currentRow;
    QHBoxLayout            *m_pHboxLayout;
    QStringList             m_pWeekDateList;
    QListWidget            *m_pListWidget;
    QListWidgetItem        *m_pItem[10];
    dateSelectionWidget    *m_pDateSelectionWidgetArray[10];

    void initMemberVariable();
    void initLayout();

    void initWeekDateList();
    void initAllDateWidget();
    void cleanWeekday();
    void cleanSpecialSelect();
    void cleanSpecialbeforeSelect(int tmp);
    QStringList traverseListWidget();

protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    bool event(QEvent *event);
};

#endif // DROPDOWNBOX_H
