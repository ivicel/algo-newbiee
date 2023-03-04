#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int ElementType;
typedef struct LNode *List;

struct LNode {
  ElementType Data[MAXSIZE];
  int Last;
};

// 初始化一个链表
List MakeEmpty();
// 返回链表长度
int Length(List L);
// 返回链表第 K 个结点指针
ElementType FindKth(int K, List L);
// 查找链表是否存在某个值, 返回该结点指针
int Find(ElementType X, List L);
// 在第 i (i > 0) 个位置插入新结点
void Insert(ElementType X, int i, List L);
// 删除第 i (i > 0) 个结点
void Delete(int i, List L);
// 打印链表
void Print(List L);

List MakeEmpty() {
  List L;
  L = (List)malloc(sizeof(struct LNode));
  L->Last = -1;
  return L;
}

int Find(ElementType X, List L) {
  int i = 0;
  while (i <= L->Last && L->Data[i] != X) {
    i++;
  }

  if (L->Last < i) {
    return -1;
  } else {
    return i;
  }
}

void Insert(ElementType X, int i, List L) {
  int j;
  if (L->Last == MAXSIZE - 1) {
    printf(" 表满  \n");
    return;
  }

  if (i < 0 || L->Last + 1 < i) {
    printf(" 位置不合法 \n");
    return;
  }

  // 从后往前依次向后挪一个, 给 a[i] 腾出位置
  for (j = L->Last; j >= i; j--) {
    L->Data[j + 1] = L->Data[j];
  }

  // 新元素插入
  L->Data[i] = X;
  L->Last++;
}

void Delete(int i, List L) {
  int j;
  // 位置越界
  if (i < 0 || L->Last < i) {
    printf("L->Data[%d] 不存在元素\n", i);
    return;
  }

  for (j = i; j < L->Last; j++) {
    L->Data[j] = L->Data[j + 1];
  }

  L->Last--;
}

ElementType FindKth(int K, List L) {
  if (K < 0 || L->Last < K) {
    printf("L->Data[%d] 不存在元素\n", K);
    return -1;
  }

  return L->Data[K];
}

int Length(List L) { return L->Last + 1; }

// 打印链表
void Print(List L) {
  int i;
  printf("此时线性表为: ");
  for (i = 0; i < Length(L); i++) {
    printf("%d ", L->Data[i]);
  }
  printf("\n");
}

int main() {
  int i = 0;
  List L = MakeEmpty();
  Insert(11, 0, L);
  printf("在线性表 L-Data[0] 插入 11\n");
  Insert(25, 0, L);
  printf("在线性表 L-Data[0] 插入 25\n");
  Insert(33, 0, L);
  printf("在线性表 L-Data[0] 插入 33\n");
  Insert(77, 0, L);
  printf("在线性表 L-Data[0] 插入 77\n");
  Print(L);
  printf("查找值为 12 的下标是: %d\n", Find(12, L));
  printf("查找值为 3 的下标是: %d\n", Find(3, L));
  Delete(2, L);
  printf("删除下标为 2 的元素\n");
  Delete(2, L);
  printf("删除下标为 2 的元素\n");
  Print(L);

  return 0;
}