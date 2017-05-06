#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101	// �ִ� ��� ����
struct
{
	double m_coef;		// ���
	int m_expon;		// ����
} terms[MAX_TERMS] = { {8,3},{7,1},{1,0},{10,3},{3,2},{1,0} };
int avail = 6;	// ������ ������ ��ġ

char Compare(int a, int b)	// ������ ���ϱ� ���� �Լ�
{
	if (a > b) return '>';
	else if (a == b) return '=';
	else return '<';
}

void Attach(double coef, int expon)	// ����� ������ �ٿ��� ���ο� ���� �����.
{
	if (avail > MAX_TERMS)
	{
		fprintf(stderr, "���� ������ �ʹ� ����\n");
		exit(1);
	}
	terms[avail].m_coef = coef;	// ������ ��ġ�� ��� �κп� ���ο� ��� ����
	terms[avail++].m_expon = expon;	// ������ ��ġ�� ���� �κп� ���ο� ���� ������ ���� ��ġ�� �̵�
}

void poly_add2(int As, int Ae, int Bs, int Be, int *Cs, int *Ce)
{
	double tempcoef;
	*Cs = avail;		// ������� ���� ��ġ�� avail
	while (As <= Ae && Bs <= Be)
	{
		switch (Compare(terms[As].m_expon, terms[Bs].m_expon))	// ������ �˻�
		{
		case '>':		// ù��° ���� ������ ũ�ٸ�
			Attach(terms[As].m_coef, terms[As].m_expon);	// ù��° ���� ����� ������ �����Ѵ�.
			++As;					// �׸��� ���� ��ġ�� �̵�
			break;
		case '=':		// ������ ���ٸ�
			tempcoef = terms[As].m_coef + terms[Bs].m_coef;	// �ӽ� ������ ����� ���� ����
			if (tempcoef)	// ���� �����ϸ�
				Attach(tempcoef, terms[As].m_expon);	// �ӽ� ������ ����� ���� �����Ѵ�.
			// ���� �������� ������(�� ���� ����� ���Ͽ� 0�� ������) �������� �ʴ´�.
			++As;
			++Bs;
			break;
		case '<':		// �ι�° ���� ������ ũ��
			Attach(terms[Bs].m_coef, terms[Bs].m_expon);	// �ι�° ���� ����� ������ �����Ѵ�.
			++Bs;
			break;
		}
	}
	// ���� ��� ���׽��� ������ ���� ������(���� ��� ù��° ���׽��� x^2, �ι�° ���׽��� x + a�� x^2���길 �ϰ� �����ٸ�)
	for (; As <= Ae; ++As)			// ���� ù��° ���׽� ���θ� �״�� ���ο� ������ ����
		Attach(terms[As].m_coef, terms[As].m_expon);
	for (; Bs <= Be; ++Bs)			// ���� �ι�° ���׽� ���θ� �״�� ���ο� ������ ����
		Attach(terms[Bs].m_coef, terms[Bs].m_expon);
	*Ce = avail - 1;	// avail���� ���� �ͼ� ������� ���� �迭�� ��ġ�� ����Ű�Ƿ� ���� ��ȿ�� �迭�� ���� ������ ������ avail - 1 ��ġ�� ����Ų��.
}

int main()
{
	int Cs, Ce;
	poly_add2(0, 2, 3, 5, &Cs, &Ce);
}