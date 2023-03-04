#ifndef MIN_HEAP_H

#define MIN_HEAP_H

#define MAX 1024

typedef struct HeapNode *MinHeap;

struct HeapNode {
  int *data;    // 指向存值的数组, 数组的第一个元素不存值
  int capacity; // 堆最大容量
  int size;     // 堆当前存的数据量
};

/* 建空堆 */
void BuildHeap(MinHeap H);
/* 插入新元素 */
void insert(MinHeap heap, int data);
/* 删除根元素 */
int DeleteElement(MinHeap heap);
/* 以 root 为根做树, 向下调整 */
static void percDown(MinHeap heap, int root);
/* 先建立树, 再调整成最小堆 */
MinHeap createHeapWithAdjust(int arr[], int len);

#endif