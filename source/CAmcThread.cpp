#include "./include/CAmcThread.h"

// 貌似必须放在这里
#include "mainwindow.h"

CAmcThread::CAmcThread(QObject* parent, int sleep_time, void* p_mainwindow) :
    m_parent(parent),
    m_sleep_time(sleep_time),
    m_keep_runing(false),
    m_sm_handle(-1),
    m_sm_status(smNoError)
{
    m_mainwindow = p_mainwindow;
}


CAmcThread::~CAmcThread()
{
    m_keep_runing = false;
    terminate();
    wait();
}

void CAmcThread::run()
{
    m_keep_runing = true;
    
    // set sm200b
    setSmConfig();

    // load dll
    HINSTANCE hDllInst;
    QString dll_dir_str{ "./dlls/AMC_Dll1.dll" };
    auto dll_dir_temp = dll_dir_str.toStdWString();
    auto dll_dir_final = const_cast<wchar_t*>(dll_dir_temp.c_str());
    hDllInst = LoadLibrary(dll_dir_final);
    if (hDllInst == NULL)
    {
        qDebug() << "load dll failed!";
        return;
    }
    else
        qDebug() << "load success!";
    typedef void (*PLUSFUNC)(int RecvData[], double R, int D, double* num, double* modulation, double FX[3], double Tao[80000]);
    PLUSFUNC dll_detect_recognize = (PLUSFUNC)GetProcAddress(hDllInst, "main_detect_recognize");

    double R = 1;
    int D = 0;
    double FX[3];
    double num = 0;
    double modulation = 0;
    std::unique_ptr<double[]> Tao(new double[80000]);

    // keep running
    while (m_keep_runing)
    {
        try
        {
            double amc_freq = ((MainWindow*)m_mainwindow)->getAmcFreq() * 1e6;
            double amc_bw = ((MainWindow*)m_mainwindow)->getAmcBw() * 1e6;
            if (amc_freq == 0)
                amc_freq = 100e6;
            if (amc_bw == 0)
                amc_bw = 1e6;
            std::unique_ptr<int[]> p_recv_data = getIqData(amc_freq, amc_bw, 1);
            if (m_sm_status < 0 || m_sm_handle < 0)
            {
                throw std::runtime_error("ERROR! SM200 ERROR!");
            }
            qDebug() << "data collect done, amc_freq: " << amc_freq << "  amc_bw:" << amc_bw;
            qDebug() << "amc start...  ";
            dll_detect_recognize(p_recv_data.get(), R, D, &num, &modulation, FX, Tao.get());
            qDebug() << modulation << endl;
            emit sendResult(modulation);

            msleep(m_sleep_time);
        }
        catch (std::runtime_error& e)
        {
            qDebug() << e.what();
            stopRunning();
        }

    }
}

void CAmcThread::stopRunning()
{
    //qDebug() << "amc_thread " << this << " will stop latter";
    qDebug() << "amc_thread will stop latter";
    smCloseDevice(m_sm_handle);
    m_keep_runing = false;
}

void CAmcThread::setSmConfig()
{
    m_sm_handle = -1;
    m_sm_status = smNoError;
    // Uncomment this to open a USB SM200 device
    m_sm_status = smOpenDevice(&m_sm_handle);
    // Uncomment this to open a networked SM200 device with a default network config
    //status = smOpenNetworkedDevice(&handle, SM200_ADDR_ANY, SM200_DEFAULT_ADDR, SM200_DEFAULT_PORT);

    if (m_sm_status != smNoError)
    {
        qDebug() << "Unable to open device";
        return;
    }
}


std::unique_ptr<int[]> CAmcThread::getIqData(int freq, int bandwidth, int downfreq)
{
    // Configure the receiver for IQ acquisition
    smSetIQCenterFreq(m_sm_handle, freq); // 900MHz
    smSetIQSampleRate(m_sm_handle, downfreq); // 50 / 2 = 25MS/s IQ 
    //smSetRefLevel(handle, -20);
    smSetIQBandwidth(m_sm_handle, smTrue, bandwidth); // 25MHz of bandwidth
    smSetIQDataType(m_sm_handle, smDataType32fc);

    // Initialize the receiver with the above settings
    m_sm_status = smConfigure(m_sm_handle, smModeIQ);
    if (m_sm_status != smNoError) 
    {
        qDebug() << "Unable to configure device  " << smGetErrorString(m_sm_status);
        smCloseDevice(m_sm_handle);
        return nullptr;
    }

    // Query the receiver IQ stream characteristics
    // Should match what we set earlier
    double actualSampleRate, actualBandwidth;
    smGetIQParameters(m_sm_handle, &actualSampleRate, &actualBandwidth);

    // Allocate memory for complex sample, IQ pairs interleaved
    double bufLen = 100000;
    std::unique_ptr<float[]> iqBuf(new float[bufLen * 2]);
    //std::vector<float> iqBuf(bufLen * 2);

    // Let's acquire 1 second worth of data
    int samplesNeeded = 1 * (int)actualSampleRate;

    while (samplesNeeded > 0) 
    {
        // Notice the purge parameter is set to false, so that each time
        //  the get IQ function is called, the next contiguous block of data
        //  is returned.
        smGetIQ(m_sm_handle, iqBuf.get(), bufLen, 0, 0, 0, smFalse, 0, 0);
        // Process/store data here
        // Data is interleaved 32-bit complex values
        // Need bufLen less samples
        samplesNeeded -= bufLen;
    }

    std::unique_ptr<int[]> result_int(new int[bufLen * 2]);
    for (double idx = 0; idx < bufLen; ++idx)
    {
        result_int[idx * 2] = int(iqBuf[idx * 2] * 1e5);
        result_int[idx * 2 + 1] = int(iqBuf[idx * 2 + 1] * 1e5);
    }
    return result_int;
}
