#pragma once

#ifndef CWORKTHREAD_H_
#define CWORKTHREAD_H_

#include <QThread>
#include <QObject>
#include <QDebug>

#include "./include/CShareMemory/CShareMemory.h"


class CWorkThread : public QThread
{
    Q_OBJECT
public:
    CWorkThread(QObject* parent, int sleep_time);
    ~CWorkThread();
    void run();
    void stopRunning();

signals:
    // send to draw
    void sendData(const double*, const int) const;

private:
    QObject* m_parent;
    int m_sleep_time;
    bool m_keep_runing;
    double* m_recv_data;
};

#endif // !CWORKTHREAD_H_



