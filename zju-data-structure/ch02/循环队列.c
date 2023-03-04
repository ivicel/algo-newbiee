#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int ElementType;
typedef struct QNode *Queue;

struct QNode {
  ElementType Data[MAXSIZE]; // 存储队列元素
  int Front;                 // 队头
  int Rear;                  // 队尾
};

Queue CreateQueue();                  // 初始化
int IsFull(Queue S);                  // 判断队列是否已满
int IsEmpty(Queue S);                 // 判断队列是否为空
void AddQ(Queue S, ElementType item); // 入队
ElementType DeleteQ(Queue S);         // 出队

Queue CreateQueue() {
  Queue s;
  s = (Queue)malloc(sizeof(struct QNode));
  s->Front = -1;
  s->Rear = -1;
  return s;
}

int IsFull(Queue s) { return (s->Rear + 1) % MAXSIZE == s->Front; }

int IsEmpty(Queue s) { return s->Front == s->Rear; }

void AddQ(Queue s, ElementType item) {
  if (IsFull(s)) {
    printf("队列满了\n");
    return;
  }

  s->Rear = (s->Rear + 1) % MAXSIZE;
  s->Data[s->Rear] = item;
}

ElementType DeleteQ(Queue s) {
  if (IsEmpty(s)) {
    printf("队列为空\n");
    return -1;
  }

  s->Front = (s->Front + 1) % MAXSIZE;
  return s->Data[s->Front];
}

int main() {
  Queue s;
  s = CreateQueue();
  printf("5 入队\n");
  AddQ(s, 5);
  printf("7 入队\n");
  AddQ(s, 7);
  printf("66 入队\n");
  AddQ(s, 66);
  printf("%d 出队\n", DeleteQ(s));
  printf("%d 出队\n", DeleteQ(s));
  return 0;
}