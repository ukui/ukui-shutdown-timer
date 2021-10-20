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

#include "timeshowwidget.h"
#include <QPainterPath>

BlankShadowWidget::BlankShadowWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(312, 40);
}

void BlankShadowWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    QPainterPath path;
    opt.rect.adjust(0,0,0,0);
    p.setBrush(opt.palette.color(QPalette::Button));
    p.setOpacity(0.5);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(opt.rect, 6, 6);
    p.setRenderHint(QPainter::Antialiasing); //反锯齿
    setProperty("blurRegion", QRegion(path.toFillPolygon().toPolygon()));
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

timeShowWidget::timeShowWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariable();
    setLabelFont();
    initLayout();
}

void timeShowWidget::initMemberVariable()
{
    this->setContentsMargins(0, 0, 0, 0);
    this->setFixedWidth(372);
    this->setFixedHeight(155);
    m_pHourLabel = new QLabel(QObject::tr("hours"), this);
//    m_pHourLabel->setFixedHeight(20);

    m_pMinuteLabel = new QLabel(QObject::tr("minute"), this);
//    m_pMinuteLabel->setFixedHeight(20);

    m_pSeparatedLabel   = new QLabel(":", this);
    m_pSeparatedLabel->setFixedSize(8, 45);

    m_pHourRollWidget   = new VerticalScroll_60(23, this);
    m_pMinuteRollWidget = new VerticalScroll_60(59, this);
}

void timeShowWidget::initLayout()
{
    m_pHourLabel->move(128, 0);
    m_pMinuteLabel->move(230, 0);
    m_pHourRollWidget->move(117, 10);
    m_pSeparatedLabel->move(182, 60);
    m_pMinuteRollWidget->move(222, 10);
    return;
}

void timeShowWidget::setLabelFont()
{
    QFont font = m_pHourLabel->font();
    font.setPixelSize(14);
//    m_pHourLabel->setFont(font);

    font = m_pMinuteLabel->font();
    font.setPixelSize(14);
//    m_pHourLabel->setFont(font);

    font = m_pSeparatedLabel->font();
    font.setPixelSize(30);
    m_pSeparatedLabel->setFont(font);
    return;
}
