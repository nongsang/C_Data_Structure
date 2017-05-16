#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct NODE
{
	int m_data;
	struct NODE* next;
} NODE;

void Error(char * msg)				// ���� �߻�
{
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

void Insert(NODE** phead, NODE* p, NODE* new_node)	// ��� ����
{
	if (NULL == *phead)
	{
		new_node->next = NULL;
		*phead = new_node;
	}
	else if (NULL == p)
	{
		new_node->next = *phead;
		*phead = new_node;
	}
	else
	{
		new_node->next = p->next;
		p->next = new_node;
	}
}

void Remove(NODE** phead, NODE *p, NODE* removed)	// ��� ����
{
	if (NULL == p)
		*phead = (*phead)->next;
	else p->next = removed->next;
	free(removed);
}

void Display(NODE* head)		// ���� ���
{
	NODE* p = head;
	while (NULL != p)
	{
		printf("%d->", p->m_data);
		p = p->next;
	}
	printf("��\n");
}

void Display_Recur(NODE* head)	// ��͸� �̿��� ���
{
	NODE *p = head;
	if (NULL != p)
	{
		printf("%d->", p->m_data);
		Display_Recur(p->next);
	}
}

NODE* Search(NODE* head, int x)	// ��� �˻�
{
	NODE* p = head;
	while (NULL != p)
	{
		if (x == p->m_data) return p;
		p = p->next;
	}
	return p;
}

NODE* Concat(NODE* head1, NODE* head2)		// ����Ʈ ���� ����
{
	NODE* p;
	if (NULL == head1) return head2;
	else if (NULL == head2) return head1;
	else
	{
		p = head1;
		while (NULL != p->next)
			p = p->next;
		p->next = head2;
		return head1;
	}
}

NODE* Reverse(NODE* head)		// ����Ʈ�� �������� ����
{
	NODE *p, *q, *r;
	p = head;
	q = NULL;
	while (NULL != p)
	{
		r = q;
		q = p;
		p = p->next;
		q->next = r;
	}
	return q;
}

NODE* Create_Node(int data, NODE* next)		// ��� ����
{
	NODE* new_node = (NODE*)malloc(sizeof(NODE));
	if (NULL == new_node) Error("�޸� �Ҵ� ����");
	new_node->m_data = data;
	new_node->next = next;
	return new_node;
}

int main()
{
	clock_t start, finish;
	double duration;

	NODE *list1 = NULL, *list2 = NULL;
	NODE *p;

	start = clock();

	Insert(&list1, NULL, Create_Node(10, NULL));
	Insert(&list1, NULL, Create_Node(20, NULL));
	Insert(&list1, NULL, Create_Node(30, NULL));
	Display(list1);

	Remove(&list1, NULL, list1);
	Display(list1);

	Insert(&list2, NULL, Create_Node(60, NULL));
	Insert(&list2, NULL, Create_Node(70, NULL));
	Insert(&list2, NULL, Create_Node(80, NULL));
	Display(list2);

	list1 = Concat(list1, list2);
	Display(list1);

	list1 = Reverse(list1);
	Display(list1);

	p = Search(list1, 20);
	printf("Ž������ : %d\n", p->m_data);

	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f �� �Դϴ�.\n", duration);
}