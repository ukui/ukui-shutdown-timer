#ifndef WIDGET_H
#define WIDGET_H

#include <QCoreApplication>
#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QThread>
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <stdio.h>
#include <unistd.h>
#include <QProcess>
#include <QStringLiteral>
#include <QMouseEvent>
#include <QGSettings>
#include <QTranslator>
#include <QApplication>
#include "confirmareawidget.h"
#include "timeshowwidget.h"
#include "comboxwidget.h"
#include "dropdownbox.h"

#define UKUITIMESHUTDOWN "org.ukui.time-shutdwon.settings"

/* 窗管部分界面 */
class menuBarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit menuBarWidget(QWidget *parent = nullptr);
    QLabel      *m_pIconLabel   = nullptr;
    QLabel      *m_pTileLabel   = nullptr;
    QPushButton *m_pHideButton  = nullptr;
    QPushButton *m_pCloseButton = nullptr;
    QHBoxLayout *m_pHBoxLayout  = nullptr;

private:
    void initMemberVariable();
    void initLayout();
};

/* app主类 */
class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private:
    void initMemberVariable();
    void initLayout();

    void initMenuBarAction();
    void initComBoxInfo();
    void initSignalSlots();
    void initDropDownBoxLabelStatus();

    // getstting初始化、值获取、 设置getsetting值
    void initGsetting();
    void getComBoxShutdownFrequency();
    void getShutDownTime();
    bool getTimedShutdownState();
    void initTimeShutdownWidget();
    void setTimeShutdownValue(bool value);
    void setShutDownTimeValue(QString value);
    void setFrequencyValue(QString value);

    // 根据关机频率来选择是否能进行定时关机
    void setWeekSelectShutdownFrequency();
    void setShutdownFrequency(QString value);

    // 获取下拉链表中的Widget
    dateSelectionWidget* getDropDownBoxWidget(int i);

    // 设置距离下一次关机时间
    QString setNextShutDownTime();
    int     getCurrentShutDownNum();
    int     getNextShutDownNum(int currentTmp, QString weekSelect);
    QString GetCalculateTimeDifference(QString weekselect);

private:
    QVBoxLayout *m_pVMainLayout             = nullptr;
    QLabel      *m_pTimeRemainLabel         = nullptr;
    QString      m_WeekSelect               = nullptr;                                          // 显示在combox中的字符串
    QString      m_pShowDownTime;
    QTimer      *m_pMonitorTime             = nullptr;
    QWidget     *m_pTransparentWidget       = nullptr;
    QGSettings  *m_pTimeShutdown            = nullptr;
    QString m_traslate;
    QString m_traslateHours;
    QString m_traslateMinute;
    QTranslator *m_ptranslator;

    int          m_Hours;                                               // 时
    int          m_Minute;                                              // 分钟
    bool         m_timeShotdown             = false;

    dropdownbox       *m_pDropDownBox       = nullptr;
    menuBarWidget     *m_pMenuBarWidget     = nullptr;
    comBoxWidget      *m_pComBoxWidget      = nullptr;
    confirmAreaWidget *m_pConfirmAreaWidget = nullptr;
    timeShowWidget    *m_pTimeShowWidget    = nullptr;
    BlankShadowWidget *m_pBlankShadowWidget = nullptr;
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

public slots:
    void dropDownBoxShowHideSlots();
    void updatedropDownBoxSelectSlots(const QModelIndex &index);
    void confirmButtonSlots();
    void canceButtonSlots();
    void threadSlots();

signals:
    void hideDropDownBox();
};
#endif // WIDGET_H
