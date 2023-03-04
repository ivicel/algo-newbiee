#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode {
  ElementType Data;
  BinTree Left;
  BinTree Right;
};

void PreorderTraversal(BinTree BT); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal(BinTree BT); /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);

/* 先序遍历，由裁判实现，细节不表 */
void PreorderTraversal(BinTree BT) {
  if (BT) {
    printf("%d ", BT->Data);
    PreorderTraversal(BT->Left);
    PreorderTraversal(BT->Right);
  }
}

/* 中序遍历，由裁判实现，细节不表 */
void InorderTraversal(BinTree BT) {
  if (BT) {
    InorderTraversal(BT->Left);
    printf("%d ", BT->Data);
    InorderTraversal(BT->Right);
  }
}

int main() {
  BinTree BST, MinP, MaxP, Tmp;
  ElementType X;
  int N, i;

  BST = NULL;
  scanf("%d", &N);
  for (i = 0; i < N; i++) {
    scanf("%d", &X);
    BST = Insert(BST, X);
  }
  printf("Preorder:");
  PreorderTraversal(BST);
  printf("\n");
  MinP = FindMin(BST);
  MaxP = FindMax(BST);
  scanf("%d", &N);
  for (i = 0; i < N; i++) {
    scanf("%d", &X);
    Tmp = Find(BST, X);
    if (Tmp == NULL)
      printf("%d is not found\n", X);
    else {
      printf("%d is found\n", Tmp->Data);
      if (Tmp == MinP)
        printf("%d is the smallest key\n", Tmp->Data);
      if (Tmp == MaxP)
        printf("%d is the largest key\n", Tmp->Data);
    }
  }
  scanf("%d", &N);
  for (i = 0; i < N; i++) {
    scanf("%d", &X);
    BST = Delete(BST, X);
  }
  printf("Inorder:");
  InorderTraversal(BST);
  printf("\n");

  return 0;
}
/* 你的代码将被嵌在这里 */

BinTree Insert(BinTree BST, ElementType X) {

  if (BST) {
    if (BST->Data > X) {
      BST->Left = Insert(BST->Left, X);
    } else if (BST->Data < X) {
      BST->Right = Insert(BST->Right, X);
    }
  } else {
    BST = (BinTree)malloc(sizeof(struct TNode));
    BST->Data = X;
    BST->Left = NULL;
    BST->Right = NULL;
  }

  return BST;
}

BinTree Delete(BinTree BST, ElementType X) {
  Position tmp;

  if (BST) {
    if (BST->Data > X) {
      BST->Left = Delete(BST->Left, X);
    } else if (BST->Data < X) {
      BST->Right = Delete(BST->Right, X);
    } else {
      // 如果都有左右子树
      if (BST->Left && BST->Right) {
        tmp = FindMax(BST->Left);
        BST->Data = tmp->Data;
        BST->Left = Delete(BST->Left, BST->Data);
      } else {
        tmp = BST;
        if (BST->Left) {
          BST = BST->Left;
        } else if (BST->Right) {
          BST = BST->Right;
        } else {
          BST = NULL;
        }

        free(tmp);
      }
    }
  } else {
    printf("Not Found\n");
  }

  return BST;
}

Position Find(BinTree BST, ElementType X) {
  BinTree bt;
  bt = BST;

  while (bt) {
    if (bt->Data > X) {
      bt = bt->Left;
    } else if (bt->Data < X) {
      bt = bt->Right;
    } else {
      break;
    }
  }

  return bt;
}

Position FindMin(BinTree BST) {
  BinTree bt;

  bt = BST;

  while (bt && bt->Left) {
    bt = bt->Left;
  }

  return bt;
}

Position FindMax(BinTree BST) {
  BinTree bt;

  bt = BST;
  while (bt && bt->Right) {
    bt = bt->Right;
  }

  return bt;
}