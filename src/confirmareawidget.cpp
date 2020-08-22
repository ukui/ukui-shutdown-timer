#include "confirmareawidget.h"
#include "CanceButtonStyle.h"
#include "ConfirmButtonStyle.h"

confirmAreaWidget::confirmAreaWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariable();
    initLayout();
}

/* 初始化成员变量 */
void confirmAreaWidget::initMemberVariable()
{
    m_pCancelButton = new QPushButton(QObject::tr("Cancel"));
    m_pCancelButton->setStyle(new CanceButtonStyle("ukui-default"));
    m_pCancelButton->setFixedSize(80, 34);
    m_pConfirmButton = new QPushButton(QObject::tr("Confirm"));
    m_pConfirmButton->setStyle(new ConfirmButtonStyle("ukui-default"));
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
