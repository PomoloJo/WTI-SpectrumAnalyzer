#pragma once

#ifndef CWORKTHREAD_H
#define CWORKTHREAD_H

#include <QThread>
#include <QObject>
#include <QDebug>


class CWorkThread : public QThread
{
    Q_OBJECT
public:
    CWorkThread(QObject* parent, int sleep_time);
    ~CWorkThread();
    void run();
    void stopRunning();

signals:
    void sendData(double*);

private:
    QObject* _parent;
    int _sleep_time;
    bool _keep_runing;
    double* _p_recv_data;

};

#endif // !CWORKTHREAD_H



