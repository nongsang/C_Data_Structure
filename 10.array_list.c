#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LIST_SIZE 100

typedef struct			// 배열로 이루어진 list
{
	int list[MAX_LIST_SIZE];
	int length;
} ArrayList;

void error(const char *massage)		// 에러 검출용 함수
{
	fprintf(stderr, "%s\n", massage);
	exit(1);
}

void Init(ArrayList *L)		// 초기화
{
	L->length = 0;
}

int Is_Empty(const ArrayList *L)	// 비어있는지 확인하는 함수
{
	return L->length == 0;
}

int Is_Full(const ArrayList *L)		// 배열이 다 차있는지 확인하는 함수
{
	return L->length == MAX_LIST_SIZE;
}

void Display(const ArrayList *L)	// 화면에 출력
{
	int i;
	for (i = 0; i < L->length; ++i)
		printf("%d\n", L->list[i]);
}

void Add(ArrayList *L, const int position, const int item)		// position위치에 item을 넣는다
{
	if (!Is_Full(L) && (position >= 0) && (position <= L->length))
	{
		int i;
		for (i = (L->length - 1); i >= position; --i)	// 처음은 i값이 -1이므로 for문 스킵
			L->list[i + 1] = L->list[i];
		L->list[position] = item;
		++L->length;
	}
}

int Delete(ArrayList *L, int position)		// position위치에 있는 값을 삭제
{
	int i;
	int item;

	if (position < 0 || position >= L->length)	// 위치가 유효하지 않다면
		error("위치 오류");

	item = L->list[position];		// 백업

	for (i = position; i < (L->length - 1); ++i)
		L->list[i] = L->list[i + 1];	// 뒤에 있는 값을 앞으로 밀기
	--L->length;
	return item;		// 삭제된 값을 return
}

int main()
{
	clock_t start, finish;
	double duration;

	ArrayList list;
	ArrayList *plist = (ArrayList*)malloc(sizeof(ArrayList));

	Init(&list);
	Init(plist);

	start = clock();

	Add(&list, 0, 10);
	Add(&list, 0, 20);
	Add(&list, 0, 30);
	Display(&list);

	Add(plist, 0, 10);
	Add(plist, 0, 20);
	Add(plist, 0, 30);
	Display(plist);

	finish = clock();

	free(plist);
	plist = NULL;

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f 초 입니다.\n", duration);
}

// 41 ~ 51행
// position위치에 item을 넣는다.
//
// 43행
// 리스트에 자리가 남아있고, position이 0이상이고, position이 허용범위 내라면 item을 생성한다.
//
// 46, 47행
// L->length - 1은 배열의 위치를 나타낸다.
// 따라서 뒤에서부터 앞으로 진행하며 앞에 있는 값을 뒤로 한칸씩 복사저장하는 방식이다.
// 맨 앞에서 값을 넣으면 i값이 -1이며, position이 0이므로 for문은 생략하여 값을 추가한다.
// 끝에 값을 넣으면 i값과 position의 값이 같기에 for문을 1번만 실행하여 끝값을 한칸 뒤로 보내고 값을 삽입한다.
// 맨 뒤에 값을 넣으면 i값은 position의 값보다 작으므로 for문은 생략하고 값을 추가한다.

// 53 ~ 67행
// 배열의 위치가 유효한지를 먼저 검사한다.
// item은 삭제를 명한 위치의 값을 백업한 변수이다.
// position부터 length - 1의 위치까지 뒤로가면서 뒤에 있는 값을 앞으로 한칸씩 땡겨서 복사저장하는 방식이다.

// 74행
// 정적으로 리스트를 생성하였다.

// 75행
// 동적으로 리스트를 생성하였다.

// 94 ~ 95행
// 동적으로 생성한 리스트를 해제한다.