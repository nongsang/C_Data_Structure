#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	clock_t start, finish;
	double duration;
	start = clock();

	// ������ �ڵ�

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f �� �Դϴ�.\n", duration);
}

// ��� �ڷᱸ���� 'C���� ���� Ǯ�� �� �ڷᱸ��', 'C�� �� �ڷᱸ����'�� �������� �ڵ��Ѵ�.

// �˰����� �ð��� �����ϴ� �ڵ��.
// ������ ���� ����� �����̹Ƿ� �� ����صε���