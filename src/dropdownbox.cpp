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

#include "dropdownbox.h"
#include <QPainterPath>
#include <QApplication>

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

dateSelectionWidget::dateSelectionWidget(QString week, QWidget *parent) : QWidget(parent)
{
    /* 安装事件过滤器 */
    installEventFilter(this);
    m_pweekLabel = new QLabel();
    QPalette palette = m_pweekLabel->palette();
    palette.setColor(QPalette::WindowText,Qt::white);
    m_pweekLabel->setPalette(palette);

    m_pweekLabel->setFixedHeight(20);
    m_pweekLabel->setText(week);

    m_pselectedLabelIcon = new QLabel();
    m_pselectedLabelIcon->setFixedSize(16, 16);
    QIcon labelIcon = QIcon::fromTheme("object-select-symbolic");
    m_pselectedLabelIcon->setPixmap(labelIcon.pixmap(QSize(16, 16)));
    m_pselectedLabelIcon->setVisible(false);
    m_pselectedLabelIcon->setProperty("useIconHighlightEffect", 0x8);
    m_pHWeekLayout = new QHBoxLayout();
    m_pHWeekLayout->setContentsMargins(17, 0, 0, 0);
    m_pHWeekLayout->addWidget(m_pweekLabel);
    m_pHWeekLayout->addItem(new QSpacerItem(232, 10, QSizePolicy::Expanding));
    m_pHWeekLayout->addWidget(m_pselectedLabelIcon);
    m_pHWeekLayout->addItem(new QSpacerItem(10, 5));
    this->setLayout(m_pHWeekLayout);
    this->setFixedSize(305, 34);
}

void dateSelectionWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (!this->m_pselectedLabelIcon->isVisible()) {
        m_pselectedLabelIcon->setVisible(true);
    } else {
        m_pselectedLabelIcon->setVisible(false);
    }
    QWidget::mouseReleaseEvent(event);
}

dropdownbox::dropdownbox(QWidget *parent) : QWidget(parent)
{
    initMemberVariable();
    initWeekDateList();
    initAllDateWidget();
}

void dropdownbox::initMemberVariable()
{
    this->setFixedSize(324, 273);
    this->setContentsMargins(8, 8, 6, 8);
    m_pHboxLayout = new QHBoxLayout();
    m_pListWidget = new QListWidget();
    m_pListWidget->verticalScrollBar()->setProperty("drawScrollBarGroove", false);
    m_pListWidget->setFixedSize(312, 256);
    m_pListWidget->setContentsMargins(0, 0, 0, 0);
    m_pListWidget->setFrameShape(QListWidget::NoFrame);
    m_pHboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pHboxLayout->addWidget(m_pListWidget);
    this->setLayout(m_pHboxLayout);
}

void dropdownbox::initLayout()
{

}

/* 初始化链表， 将所有的选项保存到链表中 */
void dropdownbox::initWeekDateList()
{
    m_pWeekDateList.append(QObject::tr("never"));
    m_pWeekDateList.append(QObject::tr("Only this shutdown"));
    m_pWeekDateList.append(QObject::tr("Everyday"));
    m_pWeekDateList.append(QObject::tr("Mon"));
    m_pWeekDateList.append(QObject::tr("Tue"));
    m_pWeekDateList.append(QObject::tr("Wed"));
    m_pWeekDateList.append(QObject::tr("Thu"));
    m_pWeekDateList.append(QObject::tr("Fri"));
    m_pWeekDateList.append(QObject::tr("Sat"));
    m_pWeekDateList.append(QObject::tr("Sun"));
    return;
}

/* 初始化下拉列表中的内容 */
void dropdownbox::initAllDateWidget()
{
    for (int i = 0; i < m_pWeekDateList.count(); i++) {
        m_pDateSelectionWidgetArray[i] = new dateSelectionWidget(m_pWeekDateList[i]);
        m_pItem[i]                     = new QListWidgetItem();
//        m_pItem[i]->setFlags(Qt::NoItemFlags);
        m_pItem[i]->setSizeHint(m_pDateSelectionWidgetArray[i]->size());
        m_pListWidget->addItem(m_pItem[i]);
        m_pListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_pListWidget->setItemWidget(m_pItem[i], m_pDateSelectionWidgetArray[i]);
        QScroller::grabGesture(m_pListWidget, QScroller::LeftMouseButtonGesture); //设置鼠标左键拖动
        m_pListWidget -> setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); // 设置像素级滑动
    }
    return;
}

/* 当选择从不、本次、每天清除选择的周几等选择 */
void dropdownbox::cleanWeekday()
{
    int tmp = m_pListWidget->count();
    for (int i = 3; i < tmp; i++) {
        dateSelectionWidget *w = dynamic_cast<dateSelectionWidget *>(m_pListWidget->itemWidget(m_pListWidget->item(i)));
            w->m_pselectedLabelIcon->setVisible(false);
    }
    this->update();
    return;
}

/* 选择每天的时清除从不、本次、每天等几个选项 */
void dropdownbox::cleanSpecialSelect()
{
    for (int i = 0; i < 3; i++) {
        dateSelectionWidget *w = dynamic_cast<dateSelectionWidget *>(m_pListWidget->itemWidget(m_pListWidget->item(i)));
        w->m_pselectedLabelIcon->setVisible(false);
    }
    this->update();
    return;
}

/* 点击特殊的三个选择时，需要清除之前的选择 */
void dropdownbox::cleanSpecialbeforeSelect(int tmp)
{
    for (int i = 0; i < 3; i++) {
        dateSelectionWidget *w = dynamic_cast<dateSelectionWidget *>(m_pListWidget->itemWidget(m_pListWidget->item(i)));
        if (i != tmp)
            w->m_pselectedLabelIcon->setVisible(false);
    }
    this->update();
}

/* 遍历ListWidget， 获取其中选中的条目 */
QStringList dropdownbox::traverseListWidget()
{
    QStringList WeekStringList;
    WeekStringList.clear();
    int currentIndex = m_pListWidget->currentRow();
    bool clickRow = false;
    int tmp = m_pListWidget->count();
    for (int i = 0; i < tmp; i++) {
        dateSelectionWidget *w = dynamic_cast<dateSelectionWidget *>(m_pListWidget->itemWidget(m_pListWidget->item(i)));
        if (w->m_pselectedLabelIcon->isVisible()) {
            qDebug() << "当前存在的label" << w->m_pweekLabel->text();
            if (currentIndex <= 2) {
                dateSelectionWidget *w = dynamic_cast<dateSelectionWidget *>(m_pListWidget->itemWidget(m_pListWidget->item(currentIndex)));
                WeekStringList.append(w->m_pweekLabel->text());
                cleanSpecialbeforeSelect(currentIndex);
                clickRow = false;
                this->hide();
            } else {
                if (i > 2) {
                    WeekStringList.append(w->m_pweekLabel->text());
                    clickRow = true;
                }
            }
        }
    }
    if (clickRow)
        cleanSpecialSelect();
    else
        cleanWeekday();
    qDebug() << "当前的字符串" << WeekStringList;
    return WeekStringList;
}

/* 事件过滤器 */
bool dropdownbox::eventFilter(QObject *obj, QEvent *event)
{

    if (obj == this) {
        if (event->type() == QEvent::WindowDeactivate) {
            this->setEnabled(false);
            return true;
        }
    }
    return false;
}

bool dropdownbox::event(QEvent *event)
{
    qDebug() << "---------------------------->" << event->type();
    if (event->type() == QEvent::ActivationChange) {
        if (QApplication::activeWindow() != this) {
            this->close();
        }
     }
     return QWidget::event(event);
}

void dropdownbox::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath rectPath;
    rectPath.addRoundedRect(this->rect().adjusted(6, 6, -6, -6), 6, 6);

    QPixmap pixmap(this->rect().size());
    pixmap.fill(Qt::transparent);
    QPainter pixmapPainter(&pixmap);
    pixmapPainter.setRenderHint(QPainter::Antialiasing);
    pixmapPainter.setPen(Qt::transparent);
    pixmapPainter.setBrush(QBrush(qApp->palette().color(QPalette::WindowText)));
    pixmapPainter.drawPath(rectPath);
    pixmapPainter.end();

    QImage img = pixmap.toImage();
    qt_blurImage(img, 6, false, false);

    pixmap = QPixmap::fromImage(img);
    QPainter pixmapPainter2(&pixmap);
    pixmapPainter2.setRenderHint(QPainter::Antialiasing);
    pixmapPainter2.setCompositionMode(QPainter::CompositionMode_Clear);
    pixmapPainter2.setPen(Qt::transparent);
    pixmapPainter2.setBrush(Qt::transparent);
    pixmapPainter2.drawPath(rectPath);
    p.setOpacity(1);
    p.drawPixmap(this->rect(), pixmap, pixmap.rect());
    p.save();
    p.fillPath(rectPath, qApp->palette().color(QPalette::Base));
    p.restore();
    QWidget::paintEvent(event);
}
