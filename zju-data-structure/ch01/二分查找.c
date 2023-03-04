#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0

typedef int ElementType;

typedef int Position;
typedef struct LNode *List;

struct LNode {
  ElementType Data[MAXSIZE];
  Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch(List L, ElementType X);

int main() {
  List L;
  ElementType X;
  Position P;

  L = ReadInput();
  scanf("%d", &X);
  P = BinarySearch(L, X);
  printf("%d\n", P);

  return 0;
}

List ReadInput() {
  List list;
  int n;

  list = (List)malloc(sizeof(struct LNode));
  list->Last = -1;

  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &list->Data[i]);
    list->Last++;
  }

  return list;
}

/* 你的代码将被嵌在这里 */
Position BinarySearch(List L, ElementType X) {
  int mid, first = 0, last = L->Last;

  if (last == -1) {
    return NotFound;
  }

  while (first <= last) {
    mid = first + (last - first) / 2;
    if (L->Data[mid] > X) {
      last = mid - 1;
    } else if (L->Data[mid] < X) {
      first = mid + 1;
    } else {
      return mid + 1;
    }
  }

  return NotFound;
}