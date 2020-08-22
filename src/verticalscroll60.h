#ifndef VERTICALSCROLL60_H
#define VERTICALSCROLL60_H

#include <QObject>
#include <QWidget>
#include <QWidget>
#include <QPropertyAnimation>
#include <QPainter>
namespace Ui {

class VerticalScroll_60;

}

class VerticalScroll_60 : public QWidget

{
    Q_OBJECT
    Q_PROPERTY(int deviation READ readDeviation WRITE setDeviation )

public:
    explicit VerticalScroll_60(int m_maxRange, QWidget *parent = 0);

    ~VerticalScroll_60();

    // set range 设置范围
    void setRange(int min, int max);

    // Get current value 获取当前值
    int readValue();

    //Currently selected value 当前选中的值
    int m_currentValue;

    void setupUi(QWidget *VerticalScroll_60);

    void retranslateUi(QWidget *VerticalScroll_60);

    void setColor(bool selectColor);

    void setCurrentValue(int value);

protected:
    void mousePressEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);

    void mouseReleaseEvent(QMouseEvent *);

    void wheelEvent(QWheelEvent *);

    void paintEvent(QPaintEvent *);

    // Drawing numbers 描绘数字
    void paintNum(QPainter &painter, int num, int deviation);

    //Bring the selected number back to the middle of the screen 使选中的数字回到屏幕中间
    void homing();

    // Mouse movement offset, default is 0 鼠标移动偏移量，默认为0
    int readDeviation();

    // Set offset 设置偏移量
    void setDeviation(int n);


signals:

    void currentValueChanged(int value);

    void deviationChange(int deviation);



private:


    Ui::VerticalScroll_60 *ui;

private:
    int m_minRange;      //最小值 // minimum value
    int m_maxRange;      //最大值 // Maximum

    bool isDragging;        //鼠标是否按下 // Muse down
    int m_deviation;        //偏移量,记录鼠标按下后移动的垂直距离  // Offset, record the vertical distance after mouse is pressed
    int m_mouseSrcPos;
    int m_numSize;
    bool m_bSelectColor = false;
    QPropertyAnimation *homingAni;
    const int interval;  //间隔大小 // Interval size
    const int devide;       //分隔数量 // Number of partitions
    QString change_NUM_to_str(int alarmHour);
};

#endif // VERTICALSCROLL60_H
