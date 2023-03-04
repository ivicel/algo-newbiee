#include <cstring>
#include <iostream>

using namespace std;

#define MAX 1024

typedef struct HeapNode *Heap;

struct HeapNode {
  int *data;    // 指向存值的数组, 数组的第一个元素不存值
  int capacity; // 堆最大容量
  int size;     // 堆当前存的数据量
};

// 建空堆
Heap createHeap() {
  Heap heap = new struct HeapNode;
  heap->capacity = MAX;
  heap->size = 0;
  heap->data = new int[MAX + 1];

  return heap;
}

// 调整堆
void adjust(Heap heap) {}

void insert(Heap heap, int data) {
  int i;

  // 堆已满
  if (heap->size == heap->capacity) {
    cout << "堆已满" << endl;
    return;
  }

  heap->data[0] = data;
  heap->size++;
  for (i = heap->size; heap->data[i / 2] < data; i = i / 2) {
    heap->data[i] = heap->data[i / 2];
  }
  heap->data[i] = data;
}

// 删除根元素
int deleteElement(Heap heap) {
  int i;
  if (heap->size == 0) {
    return -1;
  }

  int max = heap->data[1];
  heap->data[1] = heap->data[heap->size];
  heap->size--;

  heap->data[0] = heap->data[1];
  for (i = 1; i * 2 <= heap->size;) {
    int tmp = i * 2;
    // 是否有右子树, 并且右子树比左子树大
    if (tmp + 1 <= heap->size && heap->data[tmp] < heap->data[tmp + 1]) {
      tmp++;
    }

    if (heap->data[tmp] < heap->data[0]) {
      break;
    }

    heap->data[i] = heap->data[tmp];
    i = tmp;
  }
  heap->data[i] = heap->data[0];

  return max;
}

// 以 root 为根做树, 向下调整
void percDown(Heap heap, int root) {
  int data = heap->data[root];
  int i;
  // 判断条件便是说明有左子树
  for (i = root; i * 2 <= heap->size;) {
    int tmp = i * 2;
    // 如果有右子树, 并且右子树比左子树大
    if (tmp + 1 <= heap->size && heap->data[tmp] < heap->data[tmp + 1]) {
      tmp++;
    }

    // 将左右子树中较大者和根比较
    if (heap->data[tmp] < data) {
      break;
    }

    heap->data[i] = heap->data[tmp];
    i = tmp;
  }

  heap->data[i] = data;
}

Heap createHeapWithAdjust(int arr[], int len) {
  Heap heap = createHeap();
  heap->size = len;
  memcpy(&heap->data[1], arr, len * sizeof(int));

  // 从最后一个子树的父结点开始往回调
  for (int i = heap->size / 2; i > 0; i--) {
    percDown(heap, i);
  }

  return heap;
}

int main() {
  cout << "使用插入建立一个最大堆(NlogN)复杂度" << endl;

  Heap heap = createHeap();
  for (int i = 1; i < 10; i++) {
    insert(heap, i);
  }

  for (int i = 1; i <= heap->size; i++) {
    cout << heap->data[i] << " ";
  }
  cout << endl;

  cout << "删除一个最大元素: " << deleteElement(heap) << endl;
  cout << "删除一个最大元素: " << deleteElement(heap) << endl;

  for (int i = 1; i <= heap->size; i++) {
    cout << heap->data[i] << " ";
  }
  cout << endl;

  cout << "=============" << endl;
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Heap heap2 = createHeapWithAdjust(arr, sizeof(arr) / sizeof(int));
  cout << "使用向下调整数组(logN)复杂度建立一个最大堆" << endl;
  for (int i = 1; i <= heap2->size; i++) {
    cout << heap2->data[i] << " ";
  }
  cout << endl;
  for (int i = 1; i <= 9; i++) {
    cout << "删除一个最大元素: " << deleteElement(heap2) << endl;
  }

  return 0;
}