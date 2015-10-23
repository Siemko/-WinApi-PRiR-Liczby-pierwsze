#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <process.h>

int main(void); //main thread
void __cdecl child(void * Args); //child thread
bool ifPrime(int num); //check if num is a prime number
HANDLE  hRunMutex; //keep running mutext

int main() //thread number one
{
	int Tnum = 1;
	hRunMutex = CreateMutex(NULL, TRUE, NULL);
	for (int i = 0; i < 50; i++)
	{
		if (ifPrime(i))
		{
			std::cout << i << " ";
		}
	}
	HANDLE hCThread = (HANDLE)_beginthread(child, 0, &Tnum);
	DWORD waiting = WaitForSingleObject(hCThread, 30000);
	if (waiting == WAIT_OBJECT_0)
	{
		std::cout << "OK";
	}
	else if (waiting == WAIT_TIMEOUT)
	{
		std::cout << "ZA KROTKO";
	}
	_getch();
	return 0;
}

void __cdecl child(void * Args)
{
	for (int i = 50; i < 100; i++)
	{
		if (ifPrime(i))
		{
			std::cout << i << " ";
		}
	}
	_endthread();
}

bool ifPrime(int num)
{
	int d;
	bool prime;
	prime = true;
	d = 2;
	while (d*d <= num && prime)
	{
		if (num%d == 0)
			prime = false;
		d++;
	}
	return prime;
}