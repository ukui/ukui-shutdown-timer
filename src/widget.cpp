#include "widget.h"

/* 上方Menu界面 */
menuBarWidget::menuBarWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariable();
    initLayout();
}

void menuBarWidget::initMemberVariable()
{
    m_pIconLabel   =  new QLabel();                                             // 显示标题图标
    m_pIconLabel->setFixedSize(24, 24);
    QIcon icon = QIcon::fromTheme("kylin-alarm-clock");
    QPixmap pixmap = icon.pixmap(QSize(24, 24));
    m_pIconLabel->setPixmap(pixmap);

    // 显示标题文本
    m_pTileLabel   =  new QLabel();
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);
    m_pTileLabel->setPalette(palette);
    m_pTileLabel->setFixedHeight(20);
    m_pTileLabel->setText(QObject::tr("time-shutdown"));

    // 隐藏按钮
    m_pHideButton  =  new QPushButton();
    m_pHideButton->setFixedSize(30, 30);
    m_pHideButton->setIcon(QIcon::fromTheme("window-minimize-symbolic"));

    // 关闭按钮
    m_pCloseButton =  new QPushButton();
    m_pCloseButton->setFixedSize(30, 30);
    m_pCloseButton->setIcon(QIcon::fromTheme("window-close"));

    m_pHideButton->setStyleSheet("QPushButton{border-image: url(://image/mini_light.png);}"
                  "QPushButton:hover{border-image: url(://image/mini2.png);}"
                  "QPushButton:pressed{border-image: url(://image/mini3.png);}");
    m_pCloseButton->setStyleSheet("QPushButton{border-image: url(://image/close_light.png);}"
                  "QPushButton:hover{border-image: url(://image/close2.png);}"
                  "QPushButton:pressed{border-image: url(://image/close3.png);}");

    m_pHBoxLayout  =  new QHBoxLayout();
    m_pHBoxLayout->setSpacing(0);
    m_pHBoxLayout->setContentsMargins(12, 0, 4, 0);

    this->setContentsMargins(0, 0, 0, 0);
    this->setFixedSize(372, 34);
}

void menuBarWidget::initLayout()
{
    m_pHBoxLayout->addWidget(m_pIconLabel);
    m_pHBoxLayout->addItem(new QSpacerItem(8, 1));
    m_pHBoxLayout->addWidget(m_pTileLabel);
    m_pHBoxLayout->addItem(new QSpacerItem(204, 10, QSizePolicy::Expanding));
    m_pHBoxLayout->addWidget(m_pHideButton);
    m_pHBoxLayout->addItem(new QSpacerItem(4, 1));
    m_pHBoxLayout->addWidget(m_pCloseButton);
    this->setLayout(m_pHBoxLayout);
}

/* widget主类 */
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_ptranslator = new QTranslator;
    QTranslator *translator_qt = new QTranslator;
    //获取系统语言环境 选择翻译文件
    if (m_ptranslator->load(QLocale(), QLatin1String("time-shutdown"), QLatin1String("_"), QLatin1String("/usr/share/ukui-time-shutdown/")))
        QApplication::installTranslator(m_ptranslator);
    else
        qDebug() << "cannot load translator ukui-clipboard_" << QLocale::system().name() << ".qm!";

    if (translator_qt->load("/usr/share/qt5/translations/qt_"+QLocale::system().name()))
        QApplication::installTranslator(translator_qt);
    else
        qDebug() << "cannot load translator ukui-feedback_" << QLocale::system().name() << ".qm!";

    // 初始化成员变量
    initMemberVariable();

    // 初始化界面布局
    initLayout();

    // 初始化窗口按钮动作
    initMenuBarAction();

    // 初始化所有成员变量的信号槽
    initSignalSlots();

    // 初始化gsetting值
    initGsetting();

    // 获取保存在gsetting中的定时关机设置状态
    getTimedShutdownState();

    // 获取当前关机频率
    getComBoxShutdownFrequency();

    // 获取保存在gsetting中的设置的时间
    getShutDownTime();

    // 初始化定时关机显示界面
    initTimeShutdownWidget();

    // 初始化下拉框状态
    initDropDownBoxLabelStatus();

    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowIcon(QIcon::fromTheme("kylin-alarm-clock"));
}

Widget::~Widget()
{

}

void Widget::initMemberVariable()
{
    this->setContentsMargins(0, 0, 0, 0);
    this->setFixedSize(372, 376);

    m_pVMainLayout = new QVBoxLayout();
    m_pVMainLayout->setSpacing(0);
    m_pVMainLayout->setContentsMargins(0, 0, 0, 0);

    // 提示关机时间Label
    m_pTimeRemainLabel = new QLabel();
    QFont font = m_pTimeRemainLabel->font();
    font.setPixelSize(12);
    m_pTimeRemainLabel->setFont(font);
    QPalette RemainLabelpalette;
    RemainLabelpalette.setColor(QPalette::WindowText,Qt::white);
    m_pTimeRemainLabel->setPalette(RemainLabelpalette);
//    m_pTimeRemainLabel->setText("距离下一次自动关机还有12小时31分钟");
    m_pTimeRemainLabel->setAlignment(Qt::AlignHCenter);
    m_pTimeRemainLabel->setFixedHeight(18);

    m_traslate                      = QObject::tr("next shutdown");
    m_traslateHours                 = QObject::tr("hour");
    m_traslateMinute                = QObject::tr("minute");

    // 初始化定时器
    m_pMonitorTime       = new QTimer();

    // 初始化透明窗口
    m_pTransparentWidget = new QWidget();
    m_pTransparentWidget->move(120, 119);
    m_pTransparentWidget->setAttribute(Qt::WA_TranslucentBackground);
    m_pTransparentWidget->setFixedSize(372, 155);

    m_pMenuBarWidget     = new menuBarWidget();
    m_pComBoxWidget      = new comBoxWidget(this);
    m_pDropDownBox       = new dropdownbox();
    m_pConfirmAreaWidget = new confirmAreaWidget();
    m_pTimeShowWidget    = new timeShowWidget();
    m_pBlankShadowWidget = new BlankShadowWidget(this);
}

void Widget::initLayout()
{
    m_pBlankShadowWidget->move(30, 178);
    m_pComBoxWidget->move(30, 60);

    m_pVMainLayout->addWidget(m_pMenuBarWidget);
    m_pVMainLayout->addItem(new QSpacerItem(10, 82));
    m_pVMainLayout->addWidget(m_pTimeShowWidget);
    m_pVMainLayout->addItem(new QSpacerItem(10, 16));
    m_pVMainLayout->addWidget(m_pTimeRemainLabel);
    m_pVMainLayout->addItem(new QSpacerItem(10, 24));
    m_pVMainLayout->addWidget(m_pConfirmAreaWidget);
    m_pVMainLayout->addItem(new QSpacerItem(10, 32, QSizePolicy::Fixed));
    this->setLayout(m_pVMainLayout);
    m_pTransparentWidget->setParent(this);
    m_pDropDownBox->setParent(this);
    m_pDropDownBox->move(30, 96);
    m_pDropDownBox->setVisible(false);
    return;
}

void Widget::initMenuBarAction()
{
    connect(m_pMenuBarWidget->m_pHideButton, &QPushButton::clicked, this, [=](){
       this->showMinimized();
    });
    connect(m_pMenuBarWidget->m_pCloseButton, &QPushButton::clicked, this, [=](){
        qApp->quit();
    });
}

void Widget::initComBoxInfo()
{
    // 读取gsetting值
//    getComBoxShutdownFrequency();

    return;
}

void Widget::initSignalSlots()
{
    connect(m_pComBoxWidget, &comBoxWidget::comBoxWidgetClicked, this, &Widget::dropDownBoxShowHideSlots);          // 下拉框点击槽函数
    connect(m_pDropDownBox->m_pListWidget, &QListWidget::clicked, this, &Widget::updatedropDownBoxSelectSlots);     // ListWidget条目点击槽函数
    connect(m_pMonitorTime, &QTimer::timeout, this, &Widget::threadSlots);                                          // 定时器
    connect(m_pConfirmAreaWidget->m_pConfirmButton, &QPushButton::clicked, this, &Widget::confirmButtonSlots);      // 确认按钮槽函数
    connect(m_pConfirmAreaWidget->m_pCancelButton, &QPushButton::clicked, this, &Widget::canceButtonSlots);         // 取消按钮槽函数
}

void Widget::initDropDownBoxLabelStatus()
{
    int tmp = m_pDropDownBox->m_pListWidget->count();
    QStringList weekList = m_WeekSelect.split(" ");
    qDebug() << weekList;
    for (int i = 0; i < weekList.count(); i++) {
        for(int j = 0; j < tmp; j++) {
            if (weekList.at(i) == getDropDownBoxWidget(j)->m_pweekLabel->text()) {
                getDropDownBoxWidget(j)->m_pselectedLabelIcon->setVisible(true);
            }
        }
    }
    return;
}

void Widget::initGsetting()
{
    /* 链接time-shutdown的dgsetting接口 */
    if(QGSettings::isSchemaInstalled(UKUITIMESHUTDOWN))
        m_pTimeShutdown = new QGSettings(UKUITIMESHUTDOWN);
    if (m_pTimeShutdown != nullptr) {
        qDebug() << "当前的gsetting的key值" << m_pTimeShutdown->keys();
    }
    return;
}

/* 获取关机频率字符串 */
void Widget::getComBoxShutdownFrequency()
{
    if (m_timeShotdown && m_pTimeShutdown != nullptr) {
        QStringList keyList = m_pTimeShutdown->keys();
        if (keyList.contains("shutdownfrequency")) {
            m_WeekSelect = m_pTimeShutdown->get("shutdownfrequency").toString();
        }
        disconnect(m_pComBoxWidget, &comBoxWidget::comBoxWidgetClicked, this, &Widget::dropDownBoxShowHideSlots);
    } else {
        dateSelectionWidget* w = getDropDownBoxWidget(0); //读取listWidget中item(0)的值
        m_WeekSelect = w->m_pweekLabel->text();
    }
    return;
}

/* 获取关机时间 */
void Widget::getShutDownTime()
{
    if (m_timeShotdown && m_pTimeShutdown != nullptr) {
        QStringList keyList = m_pTimeShutdown->keys();
        if (keyList.contains("shutdowntime")) {
            m_pShowDownTime = m_pTimeShutdown->get("shutdowntime").toString();
        }
    } else {
        m_pShowDownTime.clear();
        QTime time = QTime::currentTime();
        int timeH = time.hour();
        int timeM = time.minute();
        m_Hours = timeH;
        m_Minute = timeM;
        return;
    }
    QStringList timeList = m_pShowDownTime.split(":");
    m_Hours  = QString(timeList.at(0)).toInt();
    m_Minute = QString(timeList.at(1)).toInt();
    return;
}

/*  获取定时关机状态 */
bool Widget::getTimedShutdownState()
{
    if (m_pTimeShutdown != nullptr) {
        QStringList keyList = m_pTimeShutdown->keys();
        if (keyList.contains("timeshutdown")) {
            m_timeShotdown = m_pTimeShutdown->get("timeshutdown").toBool();
        }
    }
    return m_timeShotdown;
}

/* 初始化当前的启动界面 */
void Widget::initTimeShutdownWidget()
{
    if (m_timeShotdown) {
        // 设置保存在gsetting中已设置好的时:分
        m_pTimeShowWidget->m_pHourRollWidget->setCurrentValue(m_Hours);
        m_pTimeShowWidget->m_pMinuteRollWidget->setCurrentValue(m_Minute);
        m_pComBoxWidget->setLabelWeekSelect(m_WeekSelect);
        m_pMonitorTime->start(1000);                                            // 开始轮训，每秒轮训一次
        m_pTimeShowWidget->m_pHourRollWidget->setColor(false);                  // 修改时间界面透明度
        m_pTimeShowWidget->m_pMinuteRollWidget->setColor(false);
        m_pTimeShowWidget->m_pHourRollWidget->update();
        m_pTimeShowWidget->m_pMinuteRollWidget->update();
        m_pTransparentWidget->setVisible(true);                                 // 置时间调试界面为不可滚动
        m_pShowDownTime = QStringLiteral("%1:%2").arg(m_Hours).arg(m_Minute);
        m_pConfirmAreaWidget->m_pConfirmButton->setEnabled(false);
    } else {
        m_pTimeShowWidget->m_pHourRollWidget->setCurrentValue(m_Hours);
        m_pTimeShowWidget->m_pMinuteRollWidget->setCurrentValue(m_Minute);
        m_pComBoxWidget->setLabelWeekSelect(m_WeekSelect);

        m_pMonitorTime->stop();
        m_pTimeShowWidget->m_pHourRollWidget->setColor(true);
        m_pTimeShowWidget->m_pMinuteRollWidget->setColor(true);
        m_pTimeShowWidget->m_pHourRollWidget->update();
        m_pTimeShowWidget->m_pMinuteRollWidget->update();
        m_pTransparentWidget->setVisible(false);
    }
    return;
}

/* 设置定时关机时状态 */
void Widget::setTimeShutdownValue(bool value)
{
    m_pTimeShutdown->set("timeshutdown", value);
    m_timeShotdown = value;
    return;
}

/* 设置定时关机时间 */
void Widget::setShutDownTimeValue(QString value)
{
    m_pTimeShutdown->set("shutdowntime", value);
    m_pShowDownTime = value;
    return;
}

/* 设置定时关机频率 */
void Widget::setFrequencyValue(QString value)
{
    m_pTimeShutdown->set("shutdownfrequency", value);
    m_WeekSelect = value;
    return;
}

void Widget::setWeekSelectShutdownFrequency()
{
    if (m_WeekSelect == getDropDownBoxWidget(0)->m_pweekLabel->text()) {
        setTimeShutdownValue(false);
    } else if (m_WeekSelect == getDropDownBoxWidget(1)->m_pweekLabel->text()) {
        setTimeShutdownValue(false);
        canceButtonSlots();
    } else if (m_WeekSelect == getDropDownBoxWidget(2)->m_pweekLabel->text()) {
        setTimeShutdownValue(true);
    } else {
        setTimeShutdownValue(true);
    }
    return;
}

void Widget::setShutdownFrequency(QString value)
{
    if (value == getDropDownBoxWidget(0)->m_pweekLabel->text()) {
        setTimeShutdownValue(false);
    } else if (value == getDropDownBoxWidget(1)->m_pweekLabel->text()) {
        setTimeShutdownValue(true);
    } else if (value == getDropDownBoxWidget(2)->m_pweekLabel->text()) {
        setTimeShutdownValue(true);
    } else if (value == "") {
        setTimeShutdownValue(false);
    } else {
        setTimeShutdownValue(true);
    }
}

dateSelectionWidget* Widget::getDropDownBoxWidget(int i)
{
    return dynamic_cast<dateSelectionWidget*>(m_pDropDownBox->m_pListWidget \
                                                               ->itemWidget(m_pDropDownBox->m_pListWidget->item(i)));
}

QString Widget::setNextShutDownTime()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString weekSelect;
    QString shutDownTime;
    if (m_WeekSelect == getDropDownBoxWidget(0)->m_pweekLabel->text()) {
        m_pTimeRemainLabel->setVisible(false);
    } else if (m_WeekSelect == getDropDownBoxWidget(1)->m_pweekLabel->text()) {
       if (!m_pTimeRemainLabel->isVisible()) {
           m_pTimeRemainLabel->setVisible(true);
       }
       weekSelect = current_date_time.toString("ddd");
       shutDownTime = GetCalculateTimeDifference(weekSelect);
    } else if (m_WeekSelect == getDropDownBoxWidget(2)->m_pweekLabel->text()) {
        if (!m_pTimeRemainLabel->isVisible()) {
            m_pTimeRemainLabel->setVisible(true);
        }
        for (int i = 0; i < m_pDropDownBox->m_pListWidget->count(); i++) {
            if (i == 0)
                weekSelect = getDropDownBoxWidget(i)->m_pweekLabel->text();
            else
                weekSelect = weekSelect + " " + getDropDownBoxWidget(i)->m_pweekLabel->text();
        }
        shutDownTime = GetCalculateTimeDifference(weekSelect);
    } else {
        if (!m_pTimeRemainLabel->isVisible()) {
            m_pTimeRemainLabel->setVisible(true);
        }
        shutDownTime = GetCalculateTimeDifference(m_WeekSelect);
    }
    qDebug() << shutDownTime;
    QStringList timeList = shutDownTime.split(":");
    m_pTimeRemainLabel->setText(QStringLiteral("%1%2%3%4%5").arg(m_traslate).arg(timeList.at(0)).arg(m_traslateHours).arg(timeList.at(1)).arg(m_traslateMinute));
    return nullptr;
}

int Widget::getCurrentShutDownNum()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString week = current_date_time.toString("ddd");
    int tmp = m_pDropDownBox->m_pListWidget->count();
    int currentTmp;
    for (int i = 0; i < tmp; i++) {
        if (getDropDownBoxWidget(i)->m_pweekLabel->text() == week) {
            currentTmp = i;
            break;
        }
    }
    return currentTmp;
}

int Widget::getNextShutDownNum(int currentTmp, QString weekSelect)
{

    int tmp = m_pDropDownBox->m_pListWidget->count();
    QStringList weekSelectList = weekSelect.split(" ");
    QList<int> weekList;
    weekList.clear();
    QTime time = QTime::currentTime();
    int timeHours = time.hour();
    for (int j = 0; j < weekSelectList.count(); j++) {
        for (int i = 0; i < tmp; i++) {
            if (weekSelectList.at(j) == getDropDownBoxWidget(i)->m_pweekLabel->text()) {
                weekList.append(i);
            }
        }
    }

    bool cotanl = weekList.contains(currentTmp);
    if (cotanl) {
        for (int k = 0; k < weekSelectList.count(); k++) {
            if (currentTmp == weekList.at(k) &&
                    timeHours >= m_pTimeShowWidget->m_pHourRollWidget->readValue()) {
                if ((k + 1) < weekSelectList.count()) {
                    return weekList.at(k + 1);
                } else if ((k - 1) >= 0) {
                    return weekList.at(k - 1);
                } else {
                    return weekList.at(k);
                }
            } else if (currentTmp == weekList.at(k) &&
                       timeHours < m_pTimeShowWidget->m_pHourRollWidget->readValue()) {
                    return weekList.at(k);
            }
        }
    } else {
        for (int k = 0; k < weekSelectList.count(); k++) {
            if (currentTmp > weekList.at(k) && (k + 1) < weekSelectList.count() && currentTmp < weekList.at(k + 1)) {
                return weekList.at(k + 1);
            } else {
                return weekList.at(k);
            }
        }
    }
}

QString Widget::GetCalculateTimeDifference(QString weekselect)
{
    int currentTmp = getCurrentShutDownNum();
    int nextCurrenttmp = getNextShutDownNum(currentTmp, weekselect);

    QTime time = QTime::currentTime();
    int timeMinute = time.minute();
    int timeHours = time.hour();
    int hour, minute = 0;
    qDebug() << "当前关机序号" << currentTmp << "下一次关机序号" << nextCurrenttmp;

    if (nextCurrenttmp > currentTmp) {
        hour = 24 * (nextCurrenttmp - currentTmp);
    } else if (nextCurrenttmp < currentTmp) {
        hour = 24 * (7 - (currentTmp - nextCurrenttmp));
        // 今天之前
    } else if (nextCurrenttmp == currentTmp &&
               timeHours >= m_pTimeShowWidget->m_pHourRollWidget->readValue()) {
        hour = 24 * (7 - (currentTmp - nextCurrenttmp));
    } else if (nextCurrenttmp == currentTmp &&
               timeHours < m_pTimeShowWidget->m_pHourRollWidget->readValue()) {
        hour = m_pTimeShowWidget->m_pHourRollWidget->readValue() - timeHours;
    }

    if (timeMinute > m_pTimeShowWidget->m_pMinuteRollWidget->readValue()) {
        minute = 60 - (timeMinute - m_pTimeShowWidget->m_pMinuteRollWidget->readValue());
        hour = hour - 1;
    } else {
        minute = m_pTimeShowWidget->m_pMinuteRollWidget->readValue() - timeMinute;
    }

//    if (timeHours > m_pTimeShowWidget->m_pHourRollWidget->readValue()) {
//        hour = hour - (timeHours - m_pTimeShowWidget->m_pHourRollWidget->readValue());
//    } else{
//        hour = hour + (timeHours - m_pTimeShowWidget->m_pHourRollWidget->readValue());
//    }
    return QStringLiteral("%1:%2").arg(hour).arg(minute);
}

void Widget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    QPainterPath path;
    opt.rect.adjust(0,0,0,0);
    p.setBrush(QBrush(QColor("#131314")));
    p.setOpacity(1);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(opt.rect, 6, 6);
    p.setRenderHint(QPainter::Antialiasing); //反锯齿
    setProperty("blurRegion", QRegion(path.toFillPolygon().toPolygon()));
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->pos().x() < 30 || event->x() > 342 || event->pos().y() < 60 || event->pos().y() > 94 ) {
        m_pDropDownBox->setVisible(false);
    }
    QWidget::mousePressEvent(event);
}

void Widget::dropDownBoxShowHideSlots()
{
    if (!m_pDropDownBox->isVisible()) {
        m_pDropDownBox->show();
    } else {
        m_pDropDownBox->hide();
    }
    return;
}

void Widget::updatedropDownBoxSelectSlots(const QModelIndex &index)
{
    Q_UNUSED(index);
    m_WeekSelect.clear();
    QStringList WeekStringList = m_pDropDownBox->traverseListWidget();
    for (int i = 0; i <WeekStringList.count(); i ++) {
        if (i == 0)
            m_WeekSelect = WeekStringList.at(i);
        else
            m_WeekSelect = m_WeekSelect + " " + WeekStringList.at(i);
    }
    setShutdownFrequency(m_WeekSelect);
    if (m_WeekSelect == "") {
        m_WeekSelect = dynamic_cast<dateSelectionWidget*>(m_pDropDownBox->m_pListWidget->
                                                          itemWidget(m_pDropDownBox->m_pListWidget->item(0)))->m_pweekLabel->text();
        dynamic_cast<dateSelectionWidget*>(m_pDropDownBox->m_pListWidget-> \
                                                                  itemWidget(m_pDropDownBox->m_pListWidget->item(0))) \
                                                                    ->m_pselectedLabelIcon->setVisible(true);
        m_pDropDownBox->m_pListWidget->setCurrentRow(0);
    }
    m_pComBoxWidget->setLabelWeekSelect(m_WeekSelect);
    return;
}

void Widget::confirmButtonSlots()
{
    setShutdownFrequency(m_WeekSelect);
    m_timeShotdown = getTimedShutdownState();
    if (!m_timeShotdown) {
        return;
    }
    m_pMonitorTime->start(1000);                           // 开始轮训，每秒轮训一次
    m_pTimeShowWidget->m_pHourRollWidget->setColor(false); // 修改时间界面透明度
    m_pTimeShowWidget->m_pMinuteRollWidget->setColor(false);
    m_pTimeShowWidget->m_pHourRollWidget->update();
    m_pTimeShowWidget->m_pMinuteRollWidget->update();
    m_pTransparentWidget->setVisible(true);                // 置时间调试界面为不可滚动
    m_pShowDownTime.clear();
    m_Hours  = m_pTimeShowWidget->m_pHourRollWidget->readValue();
    m_Minute = m_pTimeShowWidget->m_pMinuteRollWidget->readValue();
    m_pShowDownTime = QStringLiteral("%1:%2").arg(m_Hours).arg(m_Minute);
    qDebug() << "当前的设置的关机时间---->" << m_pShowDownTime;

    // 设置关机频率
    setTimeShutdownValue(true);
    setShutDownTimeValue(m_pShowDownTime);
    setFrequencyValue(m_WeekSelect);
    m_pConfirmAreaWidget->m_pConfirmButton->setEnabled(false);

    // 断开点击Combox展示下拉框的 信号 槽
    disconnect(m_pComBoxWidget, &comBoxWidget::comBoxWidgetClicked, this, &Widget::dropDownBoxShowHideSlots);
    return;
}

void Widget::canceButtonSlots()
{
    m_pMonitorTime->stop();                                 // 开始轮训，每秒轮训一次
    m_pTimeShowWidget->m_pHourRollWidget->setColor(true);   // 修改时间界面透明度
    m_pTimeShowWidget->m_pMinuteRollWidget->setColor(true);
    m_pTimeShowWidget->m_pHourRollWidget->update();
    m_pTimeShowWidget->m_pMinuteRollWidget->update();
    m_pTransparentWidget->setVisible(false);                // 置时间调试界面为可滚动
    setShutDownTimeValue(m_pShowDownTime);
    setFrequencyValue(m_WeekSelect);
    qDebug() << "当前的gsetting值" << m_WeekSelect;
    setTimeShutdownValue(false);
    m_pConfirmAreaWidget->m_pConfirmButton->setEnabled(true);

    // 重新连接点击Combox展示下拉框的 信号 槽
    connect(m_pComBoxWidget, &comBoxWidget::comBoxWidgetClicked, this, &Widget::dropDownBoxShowHideSlots);
    return;
}

void Widget::threadSlots()
{
    QTime time = QTime::currentTime();
    int timeS = time.second();
    QDateTime current_date_time = QDateTime::currentDateTime();
    m_timeShotdown = getTimedShutdownState();
    setNextShutDownTime();
    if (m_timeShotdown && current_date_time.toString("hh:mm") == m_pShowDownTime && timeS == 0) {
        QProcess p(0);
        p.startDetached("ukui-session-tools");
        p.waitForStarted();
        setWeekSelectShutdownFrequency();
    }
}
