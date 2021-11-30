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
	// 解除文件映射
	if (_lp_data != nullptr)
	{
		UnmapViewOfFile(_lp_data);
		_lp_data = nullptr;
	}
	// 关闭内存映射文件对象句柄
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

	// 创建共享文件句柄 
	_h_file_map = CreateFileMapping
	(
		INVALID_HANDLE_VALUE,	// 物理文件句柄
		NULL,					// 默认安全级别
		PAGE_READWRITE,			// 可读可写
		0,						// 高位文件大小
		share_data_size,		// 低位文件大小
		LPCWSTR("ShareMemory")	// 共享内存名称
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

	// 映射缓存区视图 , 得到指向共享内存的指针
	_lp_data = MapViewOfFile
	(
		_h_file_map,            // 共享内存的句柄
		FILE_MAP_ALL_ACCESS,	// 可读写许可
		0,
		0,
		share_data_size
	);
}

// sender和receiver不是指消息的发送接收方，是指数据的发送和接收方
void CShareMemory::initHandleOfEvent()
{
	_h_sender_event = CreateEvent
	(
		NULL,						// 事件对象的安全属性
		false,						// 事件对象触发状态的重置方式，true手动重置，false自动重置
		true,						// 初始状态时触发状态
		LPCWSTR("SenderEvent")		// 创建有名的事件对象，用于进程间的共享
	);

	_h_receiver_event = CreateEvent
	(
		NULL,						// 事件对象的安全属性
		false,						// 事件对象触发状态的重置方式，true手动重置，false自动重置
		true,						// 初始状态时触发状态
		LPCWSTR("ReceiverEvent")	// 创建有名的事件对象，用于进程间的共享
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
