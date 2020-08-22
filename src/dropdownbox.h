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
};

#endif // DROPDOWNBOX_H
