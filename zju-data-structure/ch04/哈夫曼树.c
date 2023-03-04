#include <stdio.h>
#include <stdlib.h>
#include "最小堆.h"

typedef struct HTNode *HuffmanTree;

struct HTNode {      /* 哈夫曼树结点定义 */
  int Weight;        /* 结点权重值 */
  HuffmanTree Left;  /* 左结点 */
  HuffmanTree Right; /* 右结点 */
};

HuffmanTree Huffman(MinHeap H) {
  int i, N;
  HuffmanTree T;

/* 将 H-> Data[] 按权值 Weight 调整为最小堆 */
  BuildHeap(H);
  N = H->size;
  for (i = 1; i < N; i++) {
    T = (HuffmanTree)malloc(sizeof(struct HTNode));
T->Left =DeleteElement(MinHeap heap)
  }
}