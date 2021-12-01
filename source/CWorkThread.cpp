#include "./include/CWorkThread.h"

CWorkThread::CWorkThread(QObject* parent = nullptr, int sleep_time = 0) :
    _parent(parent),
    _sleep_time(sleep_time),
    _keep_runing(false)
{

}


CWorkThread::~CWorkThread()
{
    _keep_runing = false;
}

void CWorkThread::run()
{
    _keep_runing = true;
    while (_keep_runing)
    {
        sleep(_sleep_time);
    }
}

void CWorkThread::stop()
{
    qDebug() << "mythread " << this << " stop";
    _keep_runing = false;
}
