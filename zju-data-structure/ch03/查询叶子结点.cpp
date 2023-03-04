#include <iostream>
#include <queue>

using namespace std;

#define Node int
#define MAX 10
#define Null -1

struct Tree {
  Node left;
  Node right;
} tree[MAX];

Node buildTree() {
  Node root = Null;
  char left, right;
  int n;
  int arr[MAX];
  for (int i = 0; i < MAX; i++) {
    arr[i] = 0;
  }

  cin >> n;
  if (n > 0) {
    for (int i = 0; i < n; i++) {
      struct Tree t;
      cin >> left >> right;

      if (left == '-') {
        t.left = Null;
      } else {
        t.left = left - '0';
        arr[t.left] = -1;
      }

      if (right == '-') {
        t.right = Null;
      } else {
        t.right = right - '0';
        arr[t.right] = -1;
      }

      tree[i] = t;
    }
  }

  for (int i = 0; i < MAX; i++) {
    if (arr[i] == 0) {
      root = i;
      break;
    }
  }

  return root;
}

void findLeaves(Node root) {
  queue<Node> v;
  bool first = true;
  Node node = root;

  v.push(node);
  while (!v.empty()) {
    bool flag = true;
    node = v.front();

    if (tree[node].left != Null) {
      v.push(tree[node].left);
      flag = false;
    }

    if (tree[node].right != Null) {
      v.push(tree[node].right);
      flag = false;
    }

    if (flag) {
      if (first) {
        first = false;
      } else {
        cout << " ";
      }
      cout << node;
    }

    v.pop();
  }

  cout << endl;
}

int main() {
  Node root = buildTree();
  findLeaves(root);

  return 0;
}