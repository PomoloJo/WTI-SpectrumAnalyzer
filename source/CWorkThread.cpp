#include "./include/CWorkThread.h"

// 在接收数据之前，在共享内存区域创建之前，就应该提前决定共享区域大小
const int MYSM_LENGTH{ 500000 };

CWorkThread::CWorkThread(QObject* parent = nullptr, int sleep_time = 0) :
    m_parent(parent),
    m_sleep_time(sleep_time),
    m_keep_runing(false),
    m_recv_data(nullptr)
{}


CWorkThread::~CWorkThread()
{
    m_keep_runing = false;
    // 下面这个貌似不需要加也可以
    if (m_recv_data != nullptr)
    {
        delete[] m_recv_data;
        m_recv_data = nullptr;
    }
}

void CWorkThread::run()
{
    m_recv_data = new double[MYSM_LENGTH];
    CShareMemory mysm(MYSM_LENGTH + 1);

    m_keep_runing = true;
    while (m_keep_runing)
    {
        mysm.receiverWait();
        int recv_data_len = mysm.readShareData(m_recv_data);
        mysm.receiverNotifySender();

        // 第二个参数是点数，告诉绘图函数要画多少个点
        emit sendData(m_recv_data, recv_data_len);
        //qDebug() << recv_data_len;
        msleep(m_sleep_time);
    }
    if (m_recv_data != nullptr)
    {
        delete[] m_recv_data;
        m_recv_data = nullptr;
    }
}

void CWorkThread::stopRunning()
{
    qDebug() << "mythread " << this << " stop";
    m_keep_runing = false;
}
