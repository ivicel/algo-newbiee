#include <iostream>

using namespace std;

class Node;

class Tree {

public:
  Node *root;

public:
  // 插入数据
  void insert(int data);
  // 左左旋转
  Node *llRotate(Node *node);
  // 右右旋转
  Node *rrRotate(Node *aNode);
  // 左右旋转
  Node *lrRotate(Node *aNode);
  // 右左旋转
  Node *rlRotate(Node *aNode);

private:
  Node *insert(int data, Node *node);
};

class Node {
public:
  int data;
  Node *left;
  Node *right;

  // 结点的高度
  int height;

  Node(int val) : data(val) {}
};

int getHeight(Node *node) { return node == nullptr ? 0 : node->height; }

int getMax(Node *node) {
  if (node == nullptr) {
    return 0;
  }

  int i = node->left == nullptr ? 0 : node->left->height;
  int j = node->right == nullptr ? 0 : node->right->height;

  return i > j ? i : j;
}

void Tree::insert(int data) {
  // 插入到叶子结点
  root = insert(data, root);

  // 判断是否需要旋转
}

Node *Tree::insert(int data, Node *node) {
  if (node == nullptr) {
    node = new Node(data);
    node->height = 0;
    node->left = nullptr;
    node->right = nullptr;
  }

  if (node->data > data) { // 往左子树插入
    node->left = insert(data, node->left);
    // 判断结点高度差,
    if (getHeight(node->left) - getHeight(node->right) == 2) {
      if (node->left->data > data) { // 左左
        node = llRotate(node);
      } else { // 左右
        node = lrRotate(node);
      }
    }

  } else if (node->data < data) { // 往右子树插入
    node->right = insert(data, node->right);
  }

  // 重新计算结点高度
  node->height = getMax(node) + 1;

  cout << "结点: " << node->data << ", 高度: " << node->height << endl;

  return node;
}

/**
          A                          B
        /                          /   \
       B                          C     A
      /
     C
*/
Node *Tree::llRotate(Node *aNode) {
  Node *bNode;

  bNode = aNode->left;
  // B 的右子树要跑到 A 的左边
  aNode->left = bNode->right;
  // A 现在成为 B 的新右子树了
  bNode->right = aNode;
  // 重新计算这 A, B 两个结点的高度
  aNode->height = getMax(aNode) + 1;
  bNode->height = getMax(bNode) + 1;

  // 指向 A 的结点, 现在要指向 B
  // pointToBroken -> B
  return bNode;
}

/**
      A                          B
        \                      /   \
         B                    A     C
          \
           C
*/
Node *Tree::rrRotate(Node *aNode) {

  Node *newParentNode = aNode->right;
  // B 的左子树要跑到 A 的右边
  aNode->right = newParentNode->left;
  // A 现在成为 B 的左子树了
  newParentNode->left = aNode;
  // 指向 A 的现在变成指向 B 了
  return newParentNode;
}

/**
          A                          C
        /                          /   \
       B                          B     A
        \
         C
*/
Node *Tree::lrRotate(Node *aNode) {
  Node *bNode, *cNode;
  bNode = aNode->left;
  cNode = bNode->right;

  bNode->right = cNode->left;
  aNode->left = cNode->right;
  cNode->left = bNode;
  cNode->right = aNode;

  return cNode;
}

/**
          A                        C
            \                     /   \
             B                   A     B
            /
           C
*/
Node *Tree::rlRotate(Node *aNode) {
  Node *bNode, *cNode;
  bNode = aNode->right;
  cNode = bNode->left;

  aNode->right = cNode->left;
  bNode->left = cNode->right;
  cNode->left = aNode;
  cNode->right = bNode;

  return cNode;
}

// 前序遍历
void preorder(Node *node) {
  if (node != nullptr) {
    cout << "[" << node->data << ", " << node->height << "] ";
    preorder(node->left);
    preorder(node->right);
  }
}

/*
                     5
                /       \
               3         7
             /  \	    /    \
            1    4    6     8
             \               \
              2               9

5 3 1 2 4 7 6 8 9
        */
Tree buildTree() {
  Tree bt;
  bt.insert(5);
  bt.insert(3);
  bt.insert(7);
  bt.insert(2);
  bt.insert(1);
  bt.insert(4);
  // bt.insert(6);
  // bt.insert(8);
  // bt.insert(9);

  return bt;
}

int main() {
  Tree bt = buildTree();
  preorder(bt.root);

  return 0;
}