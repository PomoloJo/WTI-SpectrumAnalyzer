#include"CShareMemory.h"

int main()
{
	// create row data
	int length{ 500000 };
	double* arr = new double[length];

	CShareMemory myshare(500001);

#if 0
	while (true)
	{
		// 模拟数据处理规模及实际用时
		int sum{};
		for (int i = 0; i < length; ++i)
		{
			arr[i] = rand() % 100;
			sum += arr[i];
		}
		std::cout << sum << std::endl;
		Sleep(300);

		myshare.writeShareData(arr, length);
		myshare.senderNotifyReceiver();
		myshare.senderWait();
	}

#else
	clock_t t1 = clock(), td;

	while (true)
	{
		myshare.receiverWait();

		int a = myshare.readShareData(arr);

		myshare.receiverNotifySender();

		// 模拟数据处理规模及实际用时
		int sum{};
		std::cout << a << std::endl;
		for (int i = 0; i < length; ++i)
		{
			sum += arr[i];
		}
		std::cout << sum << std::endl;
		Sleep(500);
		td = clock() - t1;
		t1 = clock();
		std::cout << "time:" << td << "\n" << std::endl;
	}
#endif
	
	system("pause");

	delete[] arr;
	return 0;
}