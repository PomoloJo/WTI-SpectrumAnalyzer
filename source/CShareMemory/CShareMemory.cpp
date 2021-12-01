#include "CShareMemory.h"

CShareMemory::CShareMemory(int memory_size) :
	_memory_size(memory_size),
	_data_length(0),
	_h_file_map(INVALID_HANDLE_VALUE),
	_lp_data(nullptr),
	_h_sender_event(INVALID_HANDLE_VALUE),
	_h_receiver_event(INVALID_HANDLE_VALUE)
{
	try
	{
		init();
	}
	catch (const std::exception& e) 
	{
		std::cout << e.what() << std::endl;
		throw;
	}
}

CShareMemory::~CShareMemory()
{
	// ����ļ�ӳ��
	if (_lp_data != nullptr)
	{
		UnmapViewOfFile(_lp_data);
		_lp_data = nullptr;
	}
	// �ر��ڴ�ӳ���ļ�������
	if (_h_file_map != INVALID_HANDLE_VALUE)
	{
		CloseHandle(_h_file_map);
		_h_file_map = INVALID_HANDLE_VALUE;
	}
}

void CShareMemory::init()
{
	initHandleOfFileMapping();
	initPointerOfShareMemory();
	initHandleOfEvent();
}

void CShareMemory::initHandleOfFileMapping()
{
	int share_data_size = sizeof(uint64_t) + sizeof(double) * _memory_size;

	// ���������ļ���� 
	_h_file_map = CreateFileMapping
	(
		INVALID_HANDLE_VALUE,	// �����ļ����
		NULL,					// Ĭ�ϰ�ȫ����
		PAGE_READWRITE,			// �ɶ���д
		0,						// ��λ�ļ���С
		share_data_size,		// ��λ�ļ���С
		LPCWSTR("ShareMemory")	// �����ڴ�����
	);
}

void CShareMemory::initPointerOfShareMemory()
{
	int share_data_size = sizeof(uint64_t) + sizeof(double) * _memory_size;

	if (_h_file_map == INVALID_HANDLE_VALUE)
	{
		printf("share memory create fail\n");
		return;
	}

	// ӳ�仺������ͼ , �õ�ָ�����ڴ��ָ��
	_lp_data = MapViewOfFile
	(
		_h_file_map,            // �����ڴ�ľ��
		FILE_MAP_ALL_ACCESS,	// �ɶ�д���
		0,
		0,
		share_data_size
	);
}

// sender��receiver����ָ��Ϣ�ķ��ͽ��շ�����ָ���ݵķ��ͺͽ��շ�
void CShareMemory::initHandleOfEvent()
{
	_h_sender_event = CreateEvent
	(
		NULL,						// �¼�����İ�ȫ����
		false,						// �¼����󴥷�״̬�����÷�ʽ��true�ֶ����ã�false�Զ�����
		true,						// ��ʼ״̬ʱ����״̬
		LPCWSTR("SenderEvent")		// �����������¼��������ڽ��̼�Ĺ���
	);

	_h_receiver_event = CreateEvent
	(
		NULL,						// �¼�����İ�ȫ����
		false,						// �¼����󴥷�״̬�����÷�ʽ��true�ֶ����ã�false�Զ�����
		true,						// ��ʼ״̬ʱ����״̬
		LPCWSTR("ReceiverEvent")	// �����������¼��������ڽ��̼�Ĺ���
	);
}

void CShareMemory::senderNotifyReceiver()
{
	SetEvent(_h_receiver_event);
}

void CShareMemory::senderWait()
{
	WaitForSingleObject(_h_sender_event, INFINITE);
}

void CShareMemory::receiverNotifySender()
{
	SetEvent(_h_sender_event);
}

void CShareMemory::receiverWait()
{
	WaitForSingleObject(_h_receiver_event, INFINITE);
}

int CShareMemory::readShareData(double* read_data)
{
	if (_lp_data == nullptr)
	{
		printf("map memory fail\n");
		return -1;
	}
	_data_length = ((uint64_t*)_lp_data)[0];
	double* pData = (double*)_lp_data + 1;
	memcpy(read_data, pData, sizeof(double) * _data_length);
	return _data_length;
}

int CShareMemory::writeShareData(double row_data[], int data_length)
{
	if (_lp_data == nullptr)
	{
		printf("map memory fail\n");
		return -1;
	}
	_data_length = data_length;
	((uint64_t*)_lp_data)[0] = data_length;
	double* pData = (double*)_lp_data + 1;
	memcpy(pData, row_data, sizeof(double) * data_length);
	//printf("share memory create success and write data\n");
	return 0;
}
