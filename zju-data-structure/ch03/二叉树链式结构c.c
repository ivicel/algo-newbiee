#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode_ *BinTree;
typedef struct TreeNode_ {
  int data;
  BinTree left;
  BinTree right;
} TreeNode;

// 创建二叉树
BinTree CreateBinTree();
// 判断树是否为空
bool IsEmpty(BinTree);
// 递归先序遍历
void PreOrderTraversalWithRecurse(BinTree);
// 递归中序遍历
void InOrderTraversalWithRecurse(BinTree);
// 递归后序遍历
void PostOrderTraversalWithRecurse(BinTree);

// 循环先序遍历
void PreOrderTraversalWithCirculation(BinTree);
// 循环中序遍历
void InOrderTraversalWithCirculation(BinTree);
// 循环后序遍历
void PostOrderTraversalWithCirculation(BinTree);
// 单栈循环后序遍历
void PostOrderTraversalWithCirculationWithOneStack(BinTree);

typedef struct SNode *Stack;
struct SNode {
  BinTree Data;
  Stack Next;
};

Stack CreateStack();       // 初始化栈
bool IsEmptyStack(Stack);  // 判断栈是否为
void Push(Stack, BinTree); // 入栈
BinTree Pop(Stack);        // 出栈
BinTree Peek(Stack);       // 检查栈顶但不弹出

void release(BinTree bt) {
  if (bt) {
    release(bt->left);
    release(bt->right);
    free(bt);
  }
}

int main() {
  BinTree bt = CreateBinTree();
  printf("递归先序遍历: ");
  PreOrderTraversalWithRecurse(bt);
  printf("\n递归中序遍历: ");
  InOrderTraversalWithRecurse(bt);
  printf("\n递归后序遍历: ");
  PostOrderTraversalWithRecurse(bt);
  printf("\n\n");

  printf("循环先序遍历: ");
  PreOrderTraversalWithCirculation(bt);
  printf("\n循环中序遍历: ");
  InOrderTraversalWithCirculation(bt);
  printf("\n循环后序遍历: ");
  PostOrderTraversalWithCirculation(bt);
  printf("\n单栈循环后序遍历: ");
  PostOrderTraversalWithCirculationWithOneStack(bt);

  release(bt);

  return 0;
}

BinTree Insert(int data) {
  BinTree bt;
  bt = (BinTree)malloc(sizeof(TreeNode));
  bt->data = data;
  bt->left = NULL;
  bt->right = NULL;
  return bt;
}

/*
                1
          2           3
       4     5     6      7
     8   9
*/
BinTree CreateBinTree() {
  BinTree bt;
  bt = Insert(1);
  bt->left = Insert(2);
  bt->right = Insert(3);
  bt->left->left = Insert(4);
  bt->left->right = Insert(5);
  bt->right->left = Insert(6);
  bt->right->right = Insert(7);
  bt->left->left->left = Insert(8);
  bt->left->left->right = Insert(9);

  return bt;
}

// 判断树是否为空
bool IsEmpty(BinTree bt) { return bt == NULL; }

// 递归先序遍历
void PreOrderTraversalWithRecurse(BinTree bt) {
  if (!IsEmpty(bt)) {
    printf("%d ", bt->data);
    PreOrderTraversalWithRecurse(bt->left);
    PreOrderTraversalWithRecurse(bt->right);
  }
}
// 递归中序遍历
void InOrderTraversalWithRecurse(BinTree bt) {
  if (!IsEmpty(bt)) {
    InOrderTraversalWithRecurse(bt->left);
    printf("%d ", bt->data);
    InOrderTraversalWithRecurse(bt->right);
  }
}
// 递归后序遍历
void PostOrderTraversalWithRecurse(BinTree bt) {
  if (!IsEmpty(bt)) {
    PostOrderTraversalWithRecurse(bt->left);
    PostOrderTraversalWithRecurse(bt->right);
    printf("%d ", bt->data);
  }
}

// 循环先序遍历
void PreOrderTraversalWithCirculation(BinTree bt) {
  BinTree t;
  Stack s;

  if (!IsEmpty(bt)) {
    s = CreateStack();
    t = bt;
    Push(s, t);
    while (!IsEmptyStack(s)) {
      t = Pop(s);
      printf("%d ", t->data);

      if (t->right) {
        Push(s, t->right);
      }

      if (t->left) {
        Push(s, t->left);
      }
    }
  }
}

// 循环中序遍历
void InOrderTraversalWithCirculation(BinTree bt) {
  Stack s;
  BinTree t = bt;

  s = CreateStack();
  while (t || !IsEmptyStack(s)) {

    while (t) {
      Push(s, t);
      t = t->left;
    }

    if (!IsEmptyStack(s)) {
      t = Pop(s);
      printf("%d ", t->data);
      t = t->right;
    }
  }
}
// 循环后序遍历
void PostOrderTraversalWithCirculation(BinTree bt) {
  Stack s, s2;
  BinTree t = bt;
  if (!t) {
    return;
  }

  s = CreateStack();
  s2 = CreateStack();

  while (t || !IsEmptyStack(s)) {
    while (t) {
      Push(s, t);
      Push(s2, t);
      t = t->right;
    }

    if (!IsEmptyStack(s)) {
      t = Pop(s);
      // Push(s2, t);
      t = t->left;
    }
  }

  while (!IsEmptyStack(s2)) {
    t = Pop(s2);
    printf("%d ", t->data);
  }
}

void PostOrderTraversalWithCirculationWithOneStack(BinTree bt) {
  BinTree t = bt, last = NULL;
  Stack s = CreateStack();

  while (t || !IsEmptyStack(s)) {
    // 遍历左边
    while (t) {
      Push(s, t);
      t = t->left;
    }

    if (!IsEmptyStack(s)) {
      t = Pop(s);

      if (t->right == NULL || last == t->right) {
        printf("%d ", t->data);
        last = t;
        t = NULL;
      } else {
        Push(s, t);
        t = t->right;
      }
    }
  }
}

// 初始化栈
Stack CreateStack() {
  Stack s;
  s = (Stack)malloc(sizeof(struct SNode));
  s->Data = NULL;
  s->Next = NULL;

  return s;
}

// 判断栈是否为
bool IsEmptyStack(Stack s) { return s->Next == NULL; }

// 入栈
void Push(Stack s, BinTree bt) {
  Stack s1;
  s1 = (Stack)malloc(sizeof(struct SNode));
  s1->Data = bt;
  s1->Next = s->Next;

  s->Next = s1;
}

// 出栈
BinTree Pop(Stack s) {
  BinTree bt;

  bt = s->Next->Data;
  s->Next = s->Next->Next;

  return bt;
}

BinTree Peek(Stack s) { return s->Next->Data; }