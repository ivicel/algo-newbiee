#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int ElementType;
typedef struct SNode *Stack;

struct SNode {
  ElementType Data[MAXSIZE]; // 存储栈元素
  int Top;                   // 指栈顶, 栈为空时为 -1
};

Stack CreateStack();                  // 初始化堆栈
int IsFull(Stack S);                  // 判断堆栈是否已满
int IsEmpty(Stack S);                 // 判断堆栈是否为空
void Push(Stack S, ElementType item); // 入栈
ElementType Pop(Stack S);             // 出栈

Stack CreateStack() {
  Stack s;
  s = (Stack)malloc(sizeof(struct SNode));
  s->Top = -1;
  return s;
}

int IsFull(Stack s) { return s->Top == MAXSIZE - 1; }

int IsEmpty(Stack s) { return s->Top == -1; }

void Push(Stack s, ElementType item) {
  if (IsFull(s)) {
    printf("栈满了\n");
    return;
  }

  s->Top++;
  s->Data[s->Top] = item;
}

ElementType Pop(Stack s) {
  if (IsEmpty(s)) {
    printf("栈为空\n");
    return -1;
  }

  ElementType val = s->Data[s->Top];
  s->Top--;
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