#pragma once

#include<iostream>
#include<stdio.h>
#include<Windows.h>


class CShareMemory
{
private:
	uint64_t _data_length;

	// ���ݹ����ڴ�������ر���
	int _memory_size;
	HANDLE _h_file_map;
	LPVOID _lp_data;

	HANDLE _h_sender_event;		// ���ڽ�����Ϣ֪ͨ
	HANDLE _h_receiver_event;	// ������Է�����֪ͨ

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

