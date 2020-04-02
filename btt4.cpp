
#include <stdio.h>
#include<Windows.h>

#pragma warning(disable:4996)

static long num_steps = 100000;
double  pi;
double step = 1.0 / (double)num_steps;
double Sumt = 0.0;
int n;

// Giap Ngoc Hieu 20173112

DWORD WINAPI Func(LPVOID p) {
	//truyen vao tham so k la so du khi chia 1 so cho n
	int* k = (int*)p;
	double x, sum = 0.0;
	int i;

	//tinh tong cua day gom cac so chia n du k
	for (i = *k; i < num_steps; i += n) {
		x = (i + 0.5) * step;
		sum += 4.0 / (1.0 + x * x);

	}
	
	// tinh tong cac hThreads[i]
	Sumt += sum;

	return 0;
}

int main()
{
	//tao ra mang 8 phan tu
	int params[8];
	HANDLE hThreads[8];

	//nhap vao so hThread;
	while (1) {
		printf(" nhap vao n=8 hoac n=4 \n");
		scanf("%d", &n);
		if (n == 8 || n == 4)
			break;
	}

	//ham khoi tao ra cac thread
	for (int i = 0; i < n; i++)
	{
		params[i] = i;
		hThreads[i] = CreateThread(0, 0, Func, &params[i], 0, 0);
	}
	//ham doi cho cac luong thuc thi xong het
	WaitForMultipleObjects(n, hThreads, TRUE, INFINITE);

	//tinh pi
	pi = step * Sumt;
	printf("Pi = %f\n", pi);
}
