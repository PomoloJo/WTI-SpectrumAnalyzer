#include "./include/CWorkThread.h"

// �ڽ�������֮ǰ���ڹ����ڴ����򴴽�֮ǰ����Ӧ����ǰ�������������С
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
    // �������ò�Ʋ���Ҫ��Ҳ����
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

        // �ڶ��������ǵ��������߻�ͼ����Ҫ�����ٸ���
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
