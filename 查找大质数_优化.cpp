#include <iostream>
#include <ctime>
using namespace std;

#define _MAX_SIZE_ 1000000

int GetPrimeNNormal(int n) //获取第n个素数 普通方法
{
	int val = 1;
	while (n)
	{
		++val;
		//判断当前数
		bool flag = false;
		for (int i = val - 1; i > 1; --i)
		{
			if (val % i == 0)
			{
				flag = true;
				break;
			}
		}
		if (flag == false)
		{
			--n;
		}
	}
	return val;
}


/*
获取第n个素数 优化  
只有在处理很大的质数时才会有优势，对于小一些的数，反而会不如普通方法，还需要再优化
对于求第25000个质数，该方法就比普通方法要快一个数量级 （分别为13000+ms    和    100000+ms）
*/
int GetPrimeN(int n)	
{
	static int TmpArr[_MAX_SIZE_] = { 0 };
	int val = 1;
	while (n)
	{
		++val;
		if (TmpArr[val] == -1)
		{
			continue;
		}
		//判断当前的数是否为质数
		bool flag = false;
		for (int i = val - 1; i > 1; --i)
		{
			if (val % i == 0)	//不是质数
			{
				flag = true;
				break;
			}
		}
		if(flag == false)  		//是质数:
		{
			for (int i = val + val; i < _MAX_SIZE_; i += val)//保存到临时数组中
			{
				TmpArr[i] = -1;
			}
			--n;
		}
	}
	return val;
}

void TestTime(int TestNum)
{
	
	//优化方法
	clock_t start, finish;
	cout << "经过优化后的方法：" << endl;
	start = clock();
	cout << "结果为：  " << GetPrimeN(TestNum) << endl;
	finish = clock();
	cout << "运行时间：" << finish - start << "/" << CLOCKS_PER_SEC << " (s) " << endl;

	cout << endl;


	//普通方法
	cout << "普通方法：" << endl;
	start = clock();
	cout << "结果为： " << GetPrimeNNormal(TestNum) << endl;
	finish = clock();
	cout << "运行时间： " << finish - start << "/" << CLOCKS_PER_SEC << "(s)" << endl;
}

int main()
{

	cout << "------------------------以下测试：求第2000个质数------------------------" << endl;
	TestTime(2000);
	cout << "~~~~~~~~~~~~~~测          试          完          毕~~~~~~~~~~~~~~" << endl << endl;

	cout << "------------------------以下测试：求第5000个质数------------------------" << endl;
	TestTime(5000);
	cout << "~~~~~~~~~~~~~~测          试          完          毕~~~~~~~~~~~~~~" << endl << endl;

	cout << "------------------------以下测试：求第25000个质数------------------------" << endl;
	TestTime(25000);
	cout << "~~~~~~~~~~~~~~测          试          完          毕~~~~~~~~~~~~~~" << endl << endl;


	return 0;
}
