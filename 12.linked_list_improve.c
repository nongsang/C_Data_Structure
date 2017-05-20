#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct NODE
{
	char m_data[10];
	struct NODE* next;
} NODE;

NODE* createList()
{
	NODE* L = (NODE*)malloc(sizeof(NODE));
	L->next = NULL;
	return L;
}

void insertFirstNode(NODE* L, const char* x)		// ù ��ġ�� ��� �����ϰ� ����
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	strcpy(newNode->m_data, x);
	newNode->next = L->next;
	L->next = newNode;
}

void insertMiddleNode(NODE* L, NODE* p, const char* x)	// p��ġ �ٷ� �ڿ� ��� �����ϰ� ����
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	strcpy(newNode->m_data, x);
	if (NULL == L->next)
	{
		newNode->next = NULL;
		L = newNode;
	}
	else if (NULL == p)
	{
		L->next = newNode;
	}
	else
	{
		newNode->next = p->next;
		p->next = newNode;
	}
}

void insertLastNode(NODE* L, const char* x)		// �� �ڿ� ��� �����ϰ� ����
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	NODE* p;
	strcpy(newNode->m_data, x);
	newNode->next = NULL;
	if (NULL == L->next)
	{
		L->next = newNode;
		return;
	}
	p = L;
	while (NULL != p->next)
		p = p->next;
	p->next = newNode;
}

//void deleteFirstNode(NODE* L)		// �̰� �ȵ�
//{
//	if (NULL == L->next) return;
//	else
//	{
//		free(L->next);
//		L->next = L->next->next;
//		return;
//	}
//}

void deleteFirstNode(NODE* L)		// ù ��� ����
{
	/*NODE* prev, *curr;
	if (NULL == L->next) return;
	else
	{
		prev = L->next;
		curr = L->next->next;
		free(prev);
		L->next = curr;
		return;
	}*/

	NODE* p;
	if (L->next == NULL) return;
	else
	{
		p = L->next;
		L->next = L->next->next;
		free(p);
		p = NULL;
	}
	
}

void deleteMiddleNode(NODE * L, NODE * p)	// ��� p�� ����
{
	NODE *prev;
	if (NULL == L->next) return;
	else if (NULL == L->next->next)
	{
		free(L->next);
		L->next = NULL;
		return;
	}
	else if (NULL == p) return;
	else
	{
		prev = L->next;
		while (prev->next != p)
			prev = prev->next;
		prev->next = p->next;
		free(p);
	}
}

//void deleteLastNode(NODE* L)	// �̰� �ȵȴ�.
//{
//	NODE* p;
//	if (NULL == L->next) return;
//	else if (NULL == L->next->next)
//	{
//		free(L->next);
//		L->next = NULL;
//		return;
//	}
//	else
//	{
//		p = L->next;
//		while (NULL != p->next)
//			p = p->next;
//		free(p);
//		p = NULL;
//		printf("%s", p->m_data);
//	}
//}

void deleteLastNode(NODE* L)		// ������ ��� ����
{
	NODE* prev, *curr;
	if (NULL == L->next) return;
	else if (NULL == L->next->next)		// �� �κ��� ������ �ȵȴ�.
	{
		free(L->next);					// ��尡 1�� ���� ���� �ȸ����� ����
		L->next = NULL;
		return;
	}
	else
	{
		prev = L->next;
		curr = L->next->next;
		while (NULL != curr->next)
		{
			prev = curr;
			curr = curr->next;
		}
		free(curr);					// ��尡 1����� NULL�� �κ��� �����Ϸ��Ѵ�.
		prev->next = NULL;
	}
}

void freeList(NODE* L)		// ù ������ ���������� ���ʴ�� ��� ����
{
	NODE* p;
	while (NULL != L->next)
	{
		p = L->next;
		L->next = L->next->next;
		free(p);
		p = NULL;
	}
}

void printList(NODE* L)		// ó�� ������ ������ ���
{
	NODE* p = L->next;
	printf("L = ");
	while (NULL != p)
	{
		printf("%s->", p->m_data);
		p = p->next;
	}
	printf("��\n");
}

NODE *searchNode(NODE* L, const char* x)		// ��带 ó������ ������ x�� ��
{
	NODE * p = L->next;
	while (p != NULL)
	{
		if (0 == strcmp(p->m_data, x)) return p;
		else p = p->next;
	}
	return p;
}

void Reverse(NODE* L)		// ��带 �Ųٷ� ����
{
	NODE *p, *q, *r;

	p = L->next;
	q = NULL;
	r = NULL;
	while (NULL != p)
	{
		r = q;
		q = p;
		p = p->next;
		q->next = r;
	}
	L->next = q;
}

NODE* Concat(NODE* L1, NODE* L2)		// ����Ʈ ���� ����
{
	NODE* p;
	if (NULL == L1) return L2;
	else if (NULL == L2) return L1;
	else
	{
		p = L1;
		while (NULL != p->next)
			p = p->next;
		p->next = L2;
		return L1;
	}
}

int main()
{
	clock_t start, finish;
	double duration;

	start = clock();

	NODE* List1 = createList();
	printf("(1) ���� ����Ʈ �����ϱ�! \n");
	printList(List1);
	getchar();

	printf("(2) ����Ʈ�� [��] ��� �����ϱ�! \n");
	insertFirstNode(List1, "��");
	printList(List1); getchar();

	printf("(3) ����Ʈ �������� [��] ��� �����ϱ�! \n");
	insertLastNode(List1, "��");
	printList(List1);
	getchar();

	printf("(4) ����Ʈ ù ��°�� [��] ��� �����ϱ�! \n");
	insertFirstNode(List1, "��");
	printList(List1);
	getchar();

	printf("(5) ����Ʈ ������ �����Ͽ� ���� ����Ʈ�� �����! \n");
	freeList(List1);
	printList(List1);
	getchar();

	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f �� �Դϴ�.\n", duration);
}

// void deleteLastNode(NODE* L)����
// ��尡 ���� ��, 1�� ���� ��, ��尡 ������ �������� ������.
// ��� 1���� ���� ���� ���ָ� �ȵȴ�.
// ��� 1���� ���� �� prev�� curr�� �̿��Ͽ� ��� ������ ������ �ϴµ�
// free(curr)�κп��� �̹� curr�� NULL�̹Ƿ� ������ �߻��Ѵ�.

// void insertMiddleNode(NODE *L, NODE *p, const char *x)
// void deleteMiddleNode(NODE *L, NODE *p)
// �� �� �Լ��� p��ġ�� ��带 �����ϴ� �Լ��̴�.
// ������ p��ġ�� �� ����� ����.
// const int p�� ����Ͽ� p��° ��ġ�� ��忡�� �۾��ϰԲ� �ٲ���.