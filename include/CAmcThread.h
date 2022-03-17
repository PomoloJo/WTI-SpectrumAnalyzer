#pragma once

#ifndef CAMCTHREAD_H_
#define CAMCTHREAD_H_

#include <QThread>
#include <QObject>
#include <QDebug>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#include <memory>
#include <vector>
#include "sm_api.h"

//#include "./include/CShareMemory/CShareMemory.h"

// 这个地方的设计很有问题，有时间优化一下线程类，解耦合
// 以后要改成接入式的，不能通过修改源码的方式增加功能
class CAmcThread : public QThread
{
    Q_OBJECT
public:
    CAmcThread(QObject* parent = nullptr, int sleep_time = 0, void* p_mainwindow = nullptr);
    ~CAmcThread();
    void run();
    void stopRunning();

    void setSmConfig();
    std::unique_ptr<int[]> getIqData(int freq, int bandwidth, int downfreq);

signals:
    void sendResult(const int) const;

private:
    QObject* m_parent;
    int m_sleep_time;
    bool m_keep_runing;

    int m_sm_handle;
    SmStatus m_sm_status;

    void* m_mainwindow;
};

#endif // CAMCTHREAD_H_
