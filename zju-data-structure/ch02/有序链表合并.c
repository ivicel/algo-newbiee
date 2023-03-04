#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
  ElementType Data;
  PtrToNode Next;
};
typedef PtrToNode List;

List Read();        /* 细节在此不表 */
void Print(List L); /* 细节在此不表；空链表将输出NULL */

List Merge(List L1, List L2);

int main() {
  List L1, L2, L;
  L1 = Read();
  L2 = Read();
  L = Merge(L1, L2);
  Print(L);
  Print(L1);
  Print(L2);

  return 0;
}

List Read() {
  List list, t, last = NULL;
  int n;

  list = (List)malloc(sizeof(struct Node));
  list->Data = -1;
  list->Next = NULL;

  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    t = (List)malloc(sizeof(struct Node));
    scanf("%d", &t->Data);
    t->Next = NULL;
    if (last) {
      last->Next = t;
    } else {
      list->Next = t;
    }
    last = t;
  }

  return list;
}

void Print(List L) {
  List t = L->Next;
  int first = 1;
  while (t != NULL) {
    if (first) {
      first = 0;
    } else {
      printf(" ");
    }

    printf("%d", t->Data);
    t = t->Next;
  }

  if (first) {
    printf("NULL");
  }

  printf("\n");
}

/* 你的代码将被嵌在这里 */
List Merge(List L1, List L2) {
  List p1 = L1->Next, p2 = L2->Next, tail, t1, t2;
  List newList;

  newList = (List)malloc(sizeof(struct Node));
  newList->Data = -1;
  newList->Next = NULL;
  tail = newList->Next;

  while (p1 && p2) {
    if (p1->Data > p2->Data) {
      if (tail == NULL) {
        tail = p2;
        newList->Next = tail;
      } else {
        tail->Next = p2;
        tail = p2;
      }
      p2 = p2->Next;
    } else if (p1->Data < p2->Data) {
      if (tail == NULL) {
        tail = p1;
        newList->Next = tail;
      } else {
        tail->Next = p1;
        tail = p1;
      }
      p1 = p1->Next;
    } else if (p1->Data == p2->Data) {
      if (tail == NULL) {
        tail = p1;
        p1 = p1->Next;
        newList->Next = tail;

        tail->Next = p2;
        tail = p2;
        p2 = p2->Next;
      } else {
        tail->Next = p1;
        p1 = p1->Next;

        tail->Next->Next = p2;
        tail = p2;
        p2 = p2->Next;
      }
    }
  }

  while (p1) {
    tail->Next = p1;
    tail = p1;
    p1 = p1->Next;
  }

  while (p2) {
    tail->Next = p2;
    tail = p2;
    p2 = p2->Next;
  }

  L1->Next = NULL;
  L2->Next = NULL;

  return newList;
}