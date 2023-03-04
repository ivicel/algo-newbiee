#include <iostream>
#include <stdio.h>

using namespace std;

template <typename T> class Stack {

public:
  T data;
  Stack *next;

  Stack<T>() {
    this->data = nullptr;
    this->next = nullptr;
  }

  bool isEmpty() { return this->next == nullptr; }

  void push(T t) {
    Stack<T> *s = new Stack<T>;
    s->data = t;
    s->next = this->next;
    this->next = s;
  }

  T pop() {
    if (isEmpty()) {
      return nullptr;
    }

    Stack<T> *s = this->next;
    this->next = s->next;
    T t = s->data;

    delete s;
    return t;
  }
};

template <typename T> class BinTree {

public:
  T data;
  BinTree<T> *left;
  BinTree<T> *right;

  BinTree() {
    left = nullptr;
    right = nullptr;
  }
};

BinTree<int> *CreateBinTree();

// 递归先序遍历
template <class T> void PreOrderTraversalWithRecurse(BinTree<T> *);
// 递归中序遍历
template <class T> void InOrderTraversalWithRecurse(BinTree<T> *);
// 递归后序遍历
template <class T> void PostOrderTraversalWithRecurse(BinTree<T> *);

// 循环先序遍历
template <class T> void PreOrderTraversalWithCirculation(BinTree<T> *);
// 循环中序遍历
template <class T> void InOrderTraversalWithCirculation(BinTree<T> *);
// 循环后序遍历
template <class T> void PostOrderTraversalWithCirculation(BinTree<T> *);
template <class T>
void PostOrderTraversalWithCirculationSingleStack(BinTree<T> *);

template <typename T> int getTreeHeight(BinTree<T> *);

template <typename T> int getLeavesCount(BinTree<T> *);

int main() {
  BinTree<int> *bt = CreateBinTree();
  cout << "递归先序遍历: ";
  PreOrderTraversalWithRecurse(bt);
  cout << "\n递归中序遍历: ";
  InOrderTraversalWithRecurse(bt);
  cout << "\n递归后序遍历: ";
  PostOrderTraversalWithRecurse(bt);

  cout << "\n\n循环先序遍历: ";
  PreOrderTraversalWithCirculation(bt);
  cout << "\n循环中序遍历: ";
  InOrderTraversalWithCirculation(bt);
  cout << "\n循环后序遍历: ";
  PostOrderTraversalWithCirculation(bt);
  cout << "\n单栈循环后序遍历: ";
  PostOrderTraversalWithCirculationSingleStack(bt);
  cout << "\n树的高度: " << getTreeHeight(bt);
  cout << "\n树的叶子结点数: " << getLeavesCount(bt);

  cout << "\n";

  // delete bt;

  return 0;
}

template <class T> BinTree<T> *Insert(T data) {
  BinTree<T> *bt = new BinTree<T>;
  bt->data = data;
  bt->left = nullptr;
  bt->right = nullptr;
  return bt;
}

/*
                1
          2           3
       4     5     6      7
     8   9
  10
*/
BinTree<int> *CreateBinTree() {
  BinTree<int> *bt = new BinTree<int>;
  bt->data = 1;
  bt->left = Insert<int>(2);
  bt->right = Insert<int>(3);

  bt->left->left = Insert<int>(4);
  bt->left->right = Insert<int>(5);

  bt->right->left = Insert<int>(6);
  bt->right->right = Insert<int>(7);

  bt->left->left->left = Insert<int>(8);
  bt->left->left->right = Insert<int>(9);

  bt->left->left->left->left = Insert<int>(10);

  return bt;
}

// 递归先序遍历
template <class T> void PreOrderTraversalWithRecurse(BinTree<T> *bt) {
  if (bt == nullptr) {
    return;
  }

  cout << bt->data << " ";
  PreOrderTraversalWithRecurse(bt->left);
  PreOrderTraversalWithRecurse(bt->right);
}
// 递归中序遍历
template <class T> void InOrderTraversalWithRecurse(BinTree<T> *bt) {
  if (bt == nullptr) {
    return;
  }

  InOrderTraversalWithRecurse(bt->left);
  cout << bt->data << " ";
  InOrderTraversalWithRecurse(bt->right);
}
// 递归后序遍历
template <class T> void PostOrderTraversalWithRecurse(BinTree<T> *bt) {
  if (bt == nullptr) {
    return;
  }

  PostOrderTraversalWithRecurse(bt->left);
  PostOrderTraversalWithRecurse(bt->right);
  cout << bt->data << " ";
}

// 循环先序遍历
template <class T> void PreOrderTraversalWithCirculation(BinTree<T> *bt) {
  Stack<BinTree<T> *> s;
  while (bt != nullptr || !s.isEmpty()) {
    while (bt != nullptr) {
      cout << bt->data << " ";
      s.push(bt);
      bt = bt->left;
    }

    if (!s.isEmpty()) {
      bt = s.pop();
      bt = bt->right;
    }
  }
}

// 循环中序遍历
template <class T> void InOrderTraversalWithCirculation(BinTree<T> *bt) {
  Stack<BinTree<T> *> s;
  BinTree<T> *t = bt;

  while (t != nullptr || !s.isEmpty()) {
    while (t != nullptr) {
      s.push(t);
      t = t->left;
    }

    if (!s.isEmpty()) {
      t = s.pop();
      cout << t->data << " ";
      t = t->right;
    }
  }
}

// 循环后序遍历, 左右根
template <class T> void PostOrderTraversalWithCirculation(BinTree<T> *bt) {
  Stack<BinTree<T> *> s1;
  Stack<BinTree<T> *> s2;
  BinTree<T> *t = bt;

  while (t != nullptr || !s1.isEmpty()) {
    while (t != nullptr) {
      s1.push(t);
      s2.push(t);
      t = t->right;
    }

    if (!s1.isEmpty()) {
      t = s1.pop();
      t = t->left;
    }
  }

  while (!s2.isEmpty()) {
    t = s2.pop();
    cout << t->data << " ";
  }
}

// 后序遍历, 使用循环, 单栈
template <class T>
void PostOrderTraversalWithCirculationSingleStack(BinTree<T> *bt) {
  Stack<BinTree<T> *> s;
  BinTree<T> *t = bt, *pre = nullptr;

  while (t != nullptr || !s.isEmpty()) {
    while (t != nullptr) {
      s.push(t);
      t = t->left;
    }

    if (!s.isEmpty()) {
      t = s.pop();
      // 如果这个结点没有右结点,
      // 如果这个结点有右结点, 那么这个是个父结点, 此时我们要记录下这个父结点
      if (t->right == nullptr || t->right == pre) {
        cout << t->data << " ";
        pre = t;
        t = nullptr;
      } else {
        s.push(t);
        t = t->right;
      }
    }
  }
}

template <typename T> int getTreeHeight(BinTree<T> *bt) {
  int lh = 0, rh = 0;

  if (bt != nullptr) {
    lh += getTreeHeight(bt->left) + 1;
    rh += getTreeHeight(bt->right) + 1;
    return lh > rh ? lh : rh;
  }

  return 0;
}

template <typename T> int getLeavesCount(BinTree<T> *bt) {
  int count = 0;
  BinTree<T> *t = bt;

  if (t != nullptr) {
    if (t->left == nullptr && t->right == nullptr) {
      count++;
    }

    count += getLeavesCount(t->left);
    count += getLeavesCount(t->right);
  }

  return count;
}