#ifndef TIMESHOWWIDGET_H
#define TIMESHOWWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QStyleOption>
#include <QPainter>
#include "verticalscroll60.h"

/* 含有底色无控件的窗体类 */
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
