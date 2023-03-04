#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct LNode *List;

// 链表的每个结点
struct LNode {
  // 结点上的数据
  ElementType Data;
  // 指向下一结点的指针, List 是 struct LNode *
  List Next;
};

// 初始化一个链表
List MakeEmpty();
// 返回链表长度
int Length(List L);
// 返回链表第 K 个结点指针
List FindKth(int K, List L);
// 查找链表是否存在某个值, 返回该结点指针
List Find(ElementType X, List L);
// 在第 i (i > 0) 个位置插入新结点
List Insert(ElementType X, int i, List L);
// 删除第 i (i > 0) 个结点
List Delete(int i, List L);
// 打印链表
void Print(List L);

List MakeEmpty() {
  List L = NULL; //(List)malloc(sizeof(struct LNode));
  // L = NULL;
  return L;
}

void Print(List L) {
  List tmp = L;
  int flag = 1;
  printf("  当前链表为: ");
  while (tmp) {
    printf("%d ", tmp->Data);
    tmp = tmp->Next;
    flag = 0;
  }

  if (flag) {
    printf("NULL");
  }

  printf("\n");
}

int Length(List L) {
  List p = L;
  int len = 0;
  while (p) {
    len++;
    p = p->Next;
  }

  return len;
}

List FindKth(int K, List L) {
  List p = L;
  int i = 1;
  while (p && i < K) {
    i++;
    p = p->Next;
  }

  // 找到对应结点
  if (i == K) {
    return p;
  }

  return NULL;
}

List Find(ElementType X, List L) {
  List p = L;
  while (p && p->Data != X) {
    p = p->Next;
  }

  // 找到时, p 指向这个结点
  // 没找到时, p 指向 NULL
  return p;
}

List Insert(ElementType X, int i, List L) {
  List p, s;
  // i == 1 时, 表示在头结点插入
  if (i == 1) {
    s = (List)malloc(sizeof(struct LNode));
    s->Data = X;
    s->Next = L;
    return s;
  }

  // 找到第 i 个结点前一结点
  p = FindKth(i - 1, L);
  if (!p) { // 链表没这么长
    printf("结点错误\n");
    return NULL;
  } else {
    s = (List)malloc(sizeof(struct LNode));
    s->Data = X;
    // 注意这两行不能颠倒, 要先把新的结点指向是旧的下一结点
    s->Next = p->Next;
    p->Next = s;
    return L;
  }
}

List Delete(int i, List L) {
  List p, s;
  if (i == 1) {
    s = L;
    if (L) {
      L = L->Next;
    } else {
      return NULL;
    }

    free(s);
    return L;
  }

  p = FindKth(i - 1, L);
  if (!p || !(p->Next)) {
    printf("结点错误\n");
    return NULL;
  } else {
    s = p->Next;
    p->Next = s->Next;
    free(s);
    return L;
  }
}

int main() {
  List l = MakeEmpty();
  Print(l);
  l = Insert(11, 1, l);
  l = Insert(25, 1, l);
  l = Insert(33, 2, l);
  l = Insert(77, 3, l);
  Print(l);
  printf("当前链表长度为: %d\n", Length(l));
  printf("此时链表中的第二结点的值是: %d\n", FindKth(2, l)->Data);
  printf("查找 22 是否在该链表中: ");
  if (Find(22, l)) {
    printf("是\n");
  } else {
    printf("否\n");
  }
  printf("查找 33 是否在该链表中: ");
  if (Find(33, l)) {
    printf("是\n");
  } else {
    printf("否\n");
  }

  l = Delete(1, l);
  l = Delete(3, l);
  printf("删除后\n");
  Print(l);

  return 0;
}