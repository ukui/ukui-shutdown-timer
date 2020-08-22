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
