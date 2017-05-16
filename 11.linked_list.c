#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct NODE
{
	int m_data;
	struct NODE* next;
} NODE;

void Error(char * msg)				// 에러 발생
{
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

void Insert(NODE** phead, NODE* p, NODE* new_node)	// 노드 삽입
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

void Remove(NODE** phead, NODE *p, NODE* removed)	// 노드 삭제
{
	if (NULL == p)
		*phead = (*phead)->next;
	else p->next = removed->next;
	free(removed);
}

void Display(NODE* head)		// 노드들 출력
{
	NODE* p = head;
	while (NULL != p)
	{
		printf("%d->", p->m_data);
		p = p->next;
	}
	printf("끝\n");
}

void Display_Recur(NODE* head)	// 재귀를 이용한 출력
{
	NODE *p = head;
	if (NULL != p)
	{
		printf("%d->", p->m_data);
		Display_Recur(p->next);
	}
}

NODE* Search(NODE* head, int x)	// 노드 검색
{
	NODE* p = head;
	while (NULL != p)
	{
		if (x == p->m_data) return p;
		p = p->next;
	}
	return p;
}

NODE* Concat(NODE* head1, NODE* head2)		// 리스트 끼리 연결
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

NODE* Reverse(NODE* head)		// 리스트를 역순으로 설정
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

NODE* Create_Node(int data, NODE* next)		// 노드 생성
{
	NODE* new_node = (NODE*)malloc(sizeof(NODE));
	if (NULL == new_node) Error("메모리 할당 에러");
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
	printf("탐색성공 : %d\n", p->m_data);

	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f 초 입니다.\n", duration);
}