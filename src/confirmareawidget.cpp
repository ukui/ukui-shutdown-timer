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

#include "confirmareawidget.h"

confirmAreaWidget::confirmAreaWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariable();
    initLayout();
}

/* 初始化成员变量 */
void confirmAreaWidget::initMemberVariable()
{
    m_pCancelButton = new QPushButton(QObject::tr("Cancel"));
    m_pCancelButton->setProperty("isWindowButton", 0x1);
    m_pCancelButton->setProperty("useIconHighlightEffect", 0x2);
    m_pCancelButton->setFixedSize(80, 34);
    m_pConfirmButton = new QPushButton(QObject::tr("Confirm"));
    m_pConfirmButton->setFixedSize(80, 34);
    m_pconfirmAreaWidgetHLayout = new QHBoxLayout();
    m_pconfirmAreaWidgetHLayout->setSpacing(0);
    m_pconfirmAreaWidgetHLayout->setContentsMargins(0, 0, 0, 0);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

void confirmAreaWidget::initLayout()
{
    m_pconfirmAreaWidgetHLayout->addItem(new QSpacerItem(98, 10, QSizePolicy::Expanding));
    m_pconfirmAreaWidgetHLayout->addWidget(m_pCancelButton);
    m_pconfirmAreaWidgetHLayout->addItem(new QSpacerItem(16, 10, QSizePolicy::Fixed));
    m_pconfirmAreaWidgetHLayout->addWidget(m_pConfirmButton);
    m_pconfirmAreaWidgetHLayout->addItem(new QSpacerItem(98, 10, QSizePolicy::Expanding));
    this->setLayout(m_pconfirmAreaWidgetHLayout);
    return;
}
