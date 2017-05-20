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

void insertFirstNode(NODE* L, const char* x)		// 첫 위치에 노드 생성하고 연결
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	strcpy(newNode->m_data, x);
	newNode->next = L->next;
	L->next = newNode;
}

void insertMiddleNode(NODE* L, NODE* p, const char* x)	// p위치 바로 뒤에 노드 생성하고 연결
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

void insertLastNode(NODE* L, const char* x)		// 맨 뒤에 노드 생성하고 연결
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

//void deleteFirstNode(NODE* L)		// 이거 안됨
//{
//	if (NULL == L->next) return;
//	else
//	{
//		free(L->next);
//		L->next = L->next->next;
//		return;
//	}
//}

void deleteFirstNode(NODE* L)		// 첫 노드 삭제
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

void deleteMiddleNode(NODE * L, NODE * p)	// 노드 p를 삭제
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

//void deleteLastNode(NODE* L)	// 이건 안된다.
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

void deleteLastNode(NODE* L)		// 마지막 노드 삭제
{
	NODE* prev, *curr;
	if (NULL == L->next) return;
	else if (NULL == L->next->next)		// 이 부분이 없으면 안된다.
	{
		free(L->next);					// 노드가 1개 있을 때는 안먹히기 때문
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
		free(curr);					// 노드가 1개라면 NULL인 부분을 삭제하려한다.
		prev->next = NULL;
	}
}

void freeList(NODE* L)		// 첫 노드부터 마지막까지 차례대로 노드 삭제
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

void printList(NODE* L)		// 처음 노드부터 끝까지 출력
{
	NODE* p = L->next;
	printf("L = ");
	while (NULL != p)
	{
		printf("%s->", p->m_data);
		p = p->next;
	}
	printf("끝\n");
}

NODE *searchNode(NODE* L, const char* x)		// 노드를 처음부터 끝까지 x와 비교
{
	NODE * p = L->next;
	while (p != NULL)
	{
		if (0 == strcmp(p->m_data, x)) return p;
		else p = p->next;
	}
	return p;
}

void Reverse(NODE* L)		// 노드를 거꾸로 연결
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

NODE* Concat(NODE* L1, NODE* L2)		// 리스트 끼리 연결
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
	printf("(1) 공백 리스트 생성하기! \n");
	printList(List1);
	getchar();

	printf("(2) 리스트에 [수] 노드 삽입하기! \n");
	insertFirstNode(List1, "수");
	printList(List1); getchar();

	printf("(3) 리스트 마지막에 [금] 노드 삽입하기! \n");
	insertLastNode(List1, "금");
	printList(List1);
	getchar();

	printf("(4) 리스트 첫 번째에 [월] 노드 삽입하기! \n");
	insertFirstNode(List1, "월");
	printList(List1);
	getchar();

	printf("(5) 리스트 공간을 해제하여 공백 리스트로 만들기! \n");
	freeList(List1);
	printList(List1);
	getchar();

	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f 초 입니다.\n", duration);
}

// void deleteLastNode(NODE* L)에서
// 노드가 없을 때, 1개 있을 때, 노드가 여러개 있을때로 나눈다.
// 노드 1개만 있을 때를 없애면 안된다.
// 노드 1개만 있을 때 prev와 curr를 이용하여 노드 삭제와 연결을 하는데
// free(curr)부분에서 이미 curr은 NULL이므로 오류가 발생한다.

// void insertMiddleNode(NODE *L, NODE *p, const char *x)
// void deleteMiddleNode(NODE *L, NODE *p)
// 이 두 함수는 p위치의 노드를 삭제하는 함수이다.
// 하지만 p위치를 알 방법이 없다.
// const int p를 사용하여 p번째 위치의 노드에서 작업하게끔 바꾸자.