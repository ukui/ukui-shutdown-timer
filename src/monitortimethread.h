#ifndef MONITORTIMETHREAD_H
#define MONITORTIMETHREAD_H

#include <QObject>
#include <QThread>

class monitorTimeThread : public QThread
{
    Q_OBJECT
public:
    monitorTimeThread();
//    void run();                                 //线程入口函数（工作线程的主函数）
};

#endif // MONITORTIMETHREAD_H
