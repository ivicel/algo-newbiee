#include <iostream>

using namespace std;

class Node {
public:
  int data;
  Node *left;
  Node *right;
  int height;

  Node(int data) {
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 0;
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
      if (getHeight(node->left) - getHeight(node->right) == 2) {
        if (node->left->data > data) { // ll rotate
          node = llRotate(node);
        } else { // lr rotate
          node = lrRotate(node);
        }
      }
    } else if (node->data < data) {
      node->right = insert(node->right, data);
      if (getHeight(node->right) - getHeight(node->left) == 2) {
        if (node->right->data > data) { // rl rotate
          node = rlRotate(node);
        } else { // rr rotate
          node = rrRotate(node);
        }
      }
    }

    node->height = getMax(node->left, node->right) + 1;

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
    bNode->right = node;

    node->height = getMax(node->left, node->right) + 1;

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

    node->height = getMax(node->left, node->right) + 1;
    bNode->height = getMax(bNode->left, bNode->right) + 1;

    return cNode;
  }

  Node *rrRotate(Node *node) {
    Node *bNode;
    bNode = node->right;
    node->right = bNode->left;
    bNode->left = node;

    node->height = getMax(node->left, node->right) + 1;

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

    node->height = getMax(node->left, node->right) + 1;
    bNode->height = getMax(bNode->left, bNode->right) + 1;

    return cNode;
  }
};

void preorderTravel(Node *root) {
  if (root != nullptr) {
    cout << root->data << " ";
    preorderTravel(root->left);
    preorderTravel(root->right);
  }
}

int main() {
  int n, s;
  Tree *tr = new Tree;

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> s;
    tr->insert(s);
  }

  cout << tr->root->data << endl;

  //   preorderTravel(tr->root);

  return 0;
}