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

#include "comboxwidget.h"
#include <QPainterPath>

comBoxWidget::comBoxWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(312, 34);
    initMemberVariable();
    initLayout();
}

void comBoxWidget::initMemberVariable()
{
    m_pLabel_1 = new QLabel();
    QFont font  = m_pLabel_1->font();
    font.setPixelSize(14);
    m_pLabel_1->setFont(font);
    m_pLabel_1->setText(QObject::tr("Shutdown"));
    m_pLabel_1->setFixedHeight(20);

    m_pLabel_2 = new QLabel();
    m_pLabel_2->setAlignment(Qt::AlignRight);
    m_pLabel_2->setFont(font);
    m_pLabel_2->setFixedHeight(20);
    m_pLabel_2->setFixedWidth(178);

    m_pLabel_3 = new QLabel();
    QIcon labelIcon = QIcon::fromTheme("pan-down-symbolic");
    m_pLabel_3->setPixmap(labelIcon.pixmap(QSize(16, 16)));

    m_pHcomBoxWidgetLayout = new QHBoxLayout();
    m_pHcomBoxWidgetLayout->setSpacing(0);
    m_pHcomBoxWidgetLayout->setContentsMargins(0, 7, 0, 7);
    this->setContentsMargins(0, 0, 0, 0);
}

void comBoxWidget::initLayout()
{
    m_pHcomBoxWidgetLayout->addItem(new QSpacerItem(16, 10));
    m_pHcomBoxWidgetLayout->addWidget(m_pLabel_1);
    m_pHcomBoxWidgetLayout->addItem(new QSpacerItem(14, 10));
    m_pHcomBoxWidgetLayout->addWidget(m_pLabel_2);
    m_pHcomBoxWidgetLayout->addItem(new QSpacerItem(16, 10));
    m_pHcomBoxWidgetLayout->addWidget(m_pLabel_3);
    this->setLayout(m_pHcomBoxWidgetLayout);
}

void comBoxWidget::setLabelWeekSelect(QString text)
{
    this->m_pLabel_2->setText(text);
}

void comBoxWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit comBoxWidgetClicked();
    QWidget::mouseReleaseEvent(event);
    return;
}

void comBoxWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    QPainterPath path;
    opt.rect.adjust(0,0,0,0);
    p.setBrush(opt.palette.color(QPalette::Button));
    p.setOpacity(1);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(opt.rect, 6, 6);
    p.setRenderHint(QPainter::Antialiasing); //反锯齿
    setProperty("blurRegion", QRegion(path.toFillPolygon().toPolygon()));
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}
