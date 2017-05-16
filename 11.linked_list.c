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
	else
		p->next = removed->next;
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

	NODE *list1 = NULL, *list2 = NULL;		// ����Ʈ�� ����Ű�� NODE�� �����͸� �����.
	NODE *p;					// Ž���� ���� NODE�� ������

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

// 17 ~ 34��
// ��带 �����ϴ� �Լ��̴�.
// if head�� �����͸� ���� �����Ҵ�� ���� NULL�̶�� ���ο� NODE�� �����Ѵ�.
// else if p�� ��ġ�� NULL(0)�̶�� ���� �տ� ��带 �����Ѵ�.
// ���Ӱ� ���� ����� next*�� ���� �տ� �ִ� ��带 ����Ű�� �ϰ� head�� �����͸� ���ο� ��带 ����Ű�� �Ѵ�.
// else ���ο� ��带 p�� ��ġ ������ ��带 �����Ѵ�.
// ���Ӱ� ���� ����� next*�� p�� next*�� ����Ű�� ���� ���� ���� ����Ű�� �Ѵ�.
// �׸��� p�� next*�� ���Ӱ� ���� ���� ���Ѵ�.

// 36 ~ 42��
// if p�� NULL(0)�̸� ���� ���� ��带 �����Ѵ�.
// head�� �����͸� head�� next*�� ����Ű��(head�� next*�� head�� �ٲٰ�)
// removed�� free�Ѵ�.
// 131��� ������� removed = list1;�� �Ǹ鼭 list1�� ����Ű�� �ִ� ��ġ(ù��° ��ġ)�� removed�� �Ȱ��� ����Ű�� �Ѵ�.
// else p�� ���� ��带 �����Ѵ�.
// p�� next*�� removed(������ ���)�� next*�� ����Ű�� �Ѵ�.
// �׸��� removed ��� ����

// 45 ~ 54��
// p�� NULL�� ����ų�� ����(����Ʈ ������)
// p�� ����Ű�� ����� ���� ����ϰ� p�� ���� ��带 ����Ű�� �Ѵ٤�.

// 56 ~ 64��
// p�� ����Ű�� ���� ����ϰ� p�� ���� ��带 ������ �����Ͽ� ��ͷ� ���� ����Ѵ�.

// 66 ~ 75��
// p�� NULL�� ����ų�� ����(����Ʈ ������)
// p�� ����Ű�� ����� ���� �Է��� ���� ������ ���ذ��鼭 ã�´�.

// 77 ~ 90��
// �� ����Ʈ �� �ϳ��� ��尡 �������� �ʴٸ� �ݴ� ��带 ��ȯ�Ѵ�.
// �װ� �ƴ϶�� head1 ����Ʈ�� ����忡 head2�� ó����带 �����Ѵ�.

// 92 ~ 105��
// �̰��� ���߿� ����

// 107 ~ 114��
// ���ο� ��带 �����Ѵ�.