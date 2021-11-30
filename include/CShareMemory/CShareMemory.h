#pragma once

#include<iostream>
#include<stdio.h>
#include<Windows.h>


class CShareMemory
{
private:
	uint64_t _data_length;

	// 数据共享内存区域相关变量
	int _memory_size;
	HANDLE _h_file_map;
	LPVOID _lp_data;

	HANDLE _h_sender_event;		// 用于接收消息通知
	HANDLE _h_receiver_event;	// 用于向对方发送通知

private:
	void init();
	void initHandleOfFileMapping();
	void initPointerOfShareMemory();
	void initHandleOfEvent();

public:
	CShareMemory(int data_length);
	~CShareMemory();
	
	void senderNotifyReceiver();
	void senderWait();
	void receiverNotifySender();
	void receiverWait();

	int readShareData(double*);
	int writeShareData(double[], int);
};

