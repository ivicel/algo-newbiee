#include <iostream>

using namespace std;

class Node {
public:
  int data;
  Node *left;
  Node *right;
  int height;
  bool flag; // 是否被遍历过

  Node(int data) {
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 0;
    this->flag = false;
  }
};

class Tree {
public:
  Node *root;

  void insert(int data) { root = insert(root, data); }

private:
  Node *insert(Node *node, int data) {
    if (node == nullptr) {
      node = new Node(data);
    }

    if (node->data > data) {
      node->left = insert(node->left, data);
      //   if (getHeight(node->left) - getHeight(node->left) == 2) {
      //     if (node->left->data > data) { // ll rotate
      //       node = llRotate(node);
      //     } else { // lr rotate
      //       node = lrRotate(node);
      //     }
      //   }
    } else if (node->data < data) {
      node->right = insert(node->right, data);
      //   if (getHeight(node->right) - getHeight(node->left) == 2) {
      //     if (node->right->data > data) { // rl rotate
      //       node = rlRotate(node);
      //     } else { // rr rotate
      //       node = rrRotate(node);
      //     }
      //   }
    }

    // node->height = getMax(node->left, node->right) + 1;

    return node;
  }

  int getMax(Node *n1, Node *n2) {
    int l = n1 == nullptr ? 0 : n1->height;
    int r = n2 == nullptr ? 0 : n2->height;
    return l > r ? l : r;
  }

  int getHeight(Node *node) { return node == nullptr ? 0 : node->height; }

  Node *llRotate(Node *node) {
    Node *bNode;
    bNode = node->left;
    node->left = bNode->right;
    bNode->right = node->left;
    return bNode;
  }

  Node *lrRotate(Node *node) {
    Node *bNode, *cNode;
    bNode = node->left;
    cNode = bNode->right;

    node->left = cNode->right;
    cNode->right = node;
    bNode->right = cNode->left;
    cNode->left = bNode;

    return cNode;
  }

  Node *rrRotate(Node *node) {
    Node *bNode;
    bNode = node->right;
    node->right = bNode->left;
    bNode->left = node->left;
    return bNode;
  }

  Node *rlRotate(Node *node) {
    Node *bNode, *cNode;
    bNode = node->right;
    cNode = bNode->left;

    node->right = cNode->left;
    cNode->left = node;

    bNode->left = cNode->right;
    cNode->right = bNode;

    return cNode;
  }
};

Tree *buildTree(int n) {
  int i;
  Tree *tr = new Tree;

  while (n--) {
    cin >> i;
    tr->insert(i);
  }

  return tr;
}

// 使用前序遍历来判断两棵树是否同一棵搜索二叉树
bool preorderTravel(Node *root1, Node *root2) {
  if (root1 != nullptr && root2 != nullptr) {
    if (root1->data != root2->data) {
      return false;
    }

    return preorderTravel(root1->left, root2->left) &&
           preorderTravel(root1->right, root2->right);
  }

  return root1 == nullptr && root2 == nullptr;
}

void judge(Tree *tr1, Tree *tr2) {
  if (preorderTravel(tr1->root, tr2->root)) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
}

// 方法一: 构建两棵树来比较
// int main() {
//   while (true) {
//     int n, s;

//     cin >> n;
//     if (n == 0) {
//       break;
//     }
//     cin >> s;
//     Tree *tr = buildTree(n);

//     for (int i = 0; i < s; i++) {
//       Tree *tr2 = buildTree(n);
//       judge(tr, tr2);
//     }
//   }

//   return 0;
// }

void judge2(Tree *tr, int n) {
  int data[n];

  for (int i = 0; i < n; i++) {
    cin >> data[i];
  }

  for (int i = 0; i < n; i++) {
    Node *node = tr->root;
    while (node != nullptr) {
      if (node->data > data[i]) {
        if (!node->flag) {
          cout << "No" << endl;
          return;
        }
        node = node->left;
      } else if (node->data < data[i]) {
        if (!node->flag) {
          cout << "No" << endl;
          return;
        }
        node = node->right;
      } else {
        node->flag = true;
        break;
      }
    }
  }

  cout << "Yes" << endl;
}

void clearFlag(Node *node) {
  if (node != nullptr) {
    node->flag = false;
    clearFlag(node->left);
    clearFlag(node->right);
  }
}

// 方法二: 构建一棵树和另一个序列直接比较
// 则变成, 在树中查找该值, 如果某个点是未访问过并且不等于该值,
// 那么这序列构成的树并不相等
int main() {
  while (true) {
    int n, s;

    cin >> n;
    if (n == 0) {
      break;
    }
    cin >> s;
    Tree *tr = buildTree(n);
    for (int i = 0; i < s; i++) {
      clearFlag(tr->root);
      judge2(tr, n);
    }
  }

  return 0;
}