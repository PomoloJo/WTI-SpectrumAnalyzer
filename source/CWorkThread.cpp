#include "./include/CWorkThread.h"

CWorkThread::CWorkThread(QObject* parent = nullptr, int sleep_time = 0) :
    _parent(parent),
    _sleep_time(sleep_time),
    _keep_runing(false)
{
    _p_recv_data = new double[10000];
}


CWorkThread::~CWorkThread()
{
    _keep_runing = false;
    delete[] _p_recv_data;
    _p_recv_data = nullptr;
}

void CWorkThread::run()
{
    _keep_runing = true;
    while (_keep_runing)
    {
        for (int i = 0; i < 10000; i++)
        {
            _p_recv_data[i] = rand();
        }
        emit sendData(_p_recv_data);
        qDebug() << "sended data";
        sleep(_sleep_time);
    }
}

void CWorkThread::stopRunning()
{
    qDebug() << "mythread " << this << " stop";
    _keep_runing = false;
}
