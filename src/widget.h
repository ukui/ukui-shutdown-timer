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
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QDesktopWidget>
#include "confirmareawidget.h"
#include "timeshowwidget.h"
#include "comboxwidget.h"
#include "dropdownbox.h"

#define UKUITIMESHUTDOWN "org.ukui.time-shutdwon.settings"
#define ORG_UKUI_STYLE            "org.ukui.style"
/* app主类 */
class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private:
    void initTranslation();
    void initMemberVariable();
    void initLayout();

    void initSignalSlots();
    void initDropDownBoxLabelStatus();

    // 初始化托盘图标
    void createActions();
    void createTrayIcon();
    void setIcon(QIcon icon);

    // getstting初始化、值获取、 设置getsetting值
    void initGsetting();
    void initRemainLableFnotGsetting();
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
    QGSettings  *m_pGsettingFont            = nullptr;
    QString m_traslate;
    QString m_traslateHours;
    QString m_traslateMinute;
    QTranslator *m_ptranslator;

    /* 托盘栏图标 */
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    int          m_Hours;                                               // 时
    int          m_Minute;                                              // 分钟
    bool         m_timeShotdown             = false;
    bool         m_bShowFlag                = false;

    dropdownbox       *m_pDropDownBox       = nullptr;
    comBoxWidget      *m_pComBoxWidget      = nullptr;
    confirmAreaWidget *m_pConfirmAreaWidget = nullptr;
    timeShowWidget    *m_pTimeShowWidget    = nullptr;
    BlankShadowWidget *m_pBlankShadowWidget = nullptr;

protected:
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);

public slots:
    void dropDownBoxShowHideSlots();
    void updatedropDownBoxSelectSlots(const QModelIndex &index);
    void confirmButtonSlots();
    void canceButtonSlots();
    void threadSlots();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void bootOptionsFilter(const QString&);
signals:
    void hideDropDownBox();
};
#endif // WIDGET_H
