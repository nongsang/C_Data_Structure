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
	else
		p->next = removed->next;
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

	NODE *list1 = NULL, *list2 = NULL;		// 리스트를 가리키는 NODE형 포인터를 만든다.
	NODE *p;					// 탐색을 위한 NODE형 포인터

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

// 17 ~ 34행
// 노드를 삽인하는 함수이다.
// if head의 포인터를 따라서 동적할당된 곳이 NULL이라면 새로운 NODE를 삽입한다.
// else if p의 위치가 NULL(0)이라면 가장 앞에 노드를 삽입한다.
// 새롭게 만든 노드의 next*는 가장 앞에 있던 노드를 가리키게 하고 head의 포인터를 새로운 노드를 가리키게 한다.
// else 새로운 노드를 p의 위치 다음에 노드를 삽입한다.
// 새롭게 만든 노드의 next*는 p의 next*가 가리키는 노드와 같은 것을 가리키게 한다.
// 그리고 p의 next*를 새롭게 만든 노드로 정한다.

// 36 ~ 42행
// if p가 NULL(0)이면 제일 앞의 노드를 삭제한다.
// head의 포인터를 head의 next*를 가리키고(head의 next*를 head로 바꾸고)
// removed를 free한다.
// 131행과 연관지어서 removed = list1;이 되면서 list1이 가리키고 있는 위치(첫번째 위치)를 removed도 똑같이 가리키게 한다.
// else p의 다음 노드를 삭제한다.
// p의 next*를 removed(삭제될 노드)의 next*를 가리키게 한다.
// 그리고 removed 노드 삭제

// 45 ~ 54행
// p가 NULL을 가리킬때 까지(리스트 끝까지)
// p가 가리키는 노드의 값을 출력하고 p는 다음 노드를 가리키게 한다ㅣ.

// 56 ~ 64행
// p가 가리키는 값을 출력하고 p의 다음 노드를 값으로 전달하여 재귀로 값을 출력한다.

// 66 ~ 75행
// p가 NULL을 가리킬때 까지(리스트 끝까지)
// p가 가리키는 노드의 값이 입력한 값과 같은지 비교해가면서 찾는다.

// 77 ~ 90행
// 두 리스트 중 하나라도 노드가 존재하지 않다면 반대 노드를 반환한다.
// 그게 아니라면 head1 리스트의 끝노드에 head2의 처음노드를 연결한다.

// 92 ~ 105행
// 이것은 나중에 설명

// 107 ~ 114행
// 새로운 노드를 생성한다.