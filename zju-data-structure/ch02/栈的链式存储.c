#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int ElementType;
typedef struct SNode *Stack;

struct SNode {
  ElementType Data; // 存储栈元素
  Stack Next;       // 下一个元素
};

Stack CreateStack();                  // 初始化堆栈
int IsEmpty(Stack S);                 // 判断堆栈是否为空
void Push(Stack S, ElementType item); // 入栈
ElementType Pop(Stack S);             // 出栈

Stack CreateStack() {
  Stack s;
  s = (Stack)malloc(sizeof(struct SNode));
  s->Next = NULL;
  return s;
}

int IsEmpty(Stack s) { return s->Next == NULL; }

void Push(Stack s, ElementType item) {
  Stack tmp;
  tmp = (Stack)malloc(sizeof(struct SNode));
  tmp->Next = s->Next;
  tmp->Data = item;
  s->Next = tmp;
}

ElementType Pop(Stack s) {
  Stack first;
  ElementType topVal;

  if (IsEmpty(s)) {
    printf("栈为空\n");
    return -1;
  }

  first = s->Next;
  s->Next = first->Next;
  ElementType val = first->Data;
  free(first);
  return val;
}

int main() {
  Stack s;
  s = CreateStack();
  printf("5 入栈\n");
  Push(s, 5);
  printf("7 入栈\n");
  Push(s, 7);
  printf("66 入栈\n");
  Push(s, 66);
  printf("%d 出栈\n", Pop(s));
  printf("%d 出栈\n", Pop(s));
  return 0;
}