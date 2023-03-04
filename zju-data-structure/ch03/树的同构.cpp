#include <iostream>
#include <string>

using namespace std;

#define MAX 10
#define Node int
#define Null -1

struct Tree {
  char data;
  Node left;
  Node right;
} T1[MAX], T2[MAX];

// 读输入, 构建树
Node buildTree(Tree t[]) {
  int n;
  char data, left, right;
  // 根结点在数组中的下标
  Node root = Null;

  for (int i = 0; i < MAX; i++) {
    struct Tree node;
    node.data = 0;
    node.left = Null;
    node.right = Null;
    t[i] = node;
  }

  // 读入该树有多少个结点
  cin >> n;
  if (n != 0) {
    int tmp[n];
    for (int i = 0; i < n; i++) {
      tmp[i] = 0;
    }

    for (int i = 0; i < n; i++) {
      cin >> data >> left >> right;
      t[i].data = data;
      if (left == '-') {
        t[i].left = Null;
      } else {
        t[i].left = left - '0';
        tmp[t[i].left] = -1;
      }

      if (right == '-') {
        t[i].right = Null;
      } else {
        t[i].right = right - '0';
        tmp[t[i].right] = -1;
      }
    }

    // 查找根结点
    for (int i = 0; i < n; i++) {
      if (tmp[i] == 0) {
        root = i;
        break;
      }
    }
  }

  return root;
}

bool isomorphism(Node root1, Node root2) {

  if (root1 == Null && root2 == Null) {
    return true;
  } else if ((root1 == Null && root2 != Null) ||
             (root1 != Null && root2 == Null)) {
    return false;
  } else if (T1[root1].data != T2[root2].data) {
    return false;
  } else if (T1[root1].left != Null && T2[root2].left != Null &&
             T1[T1[root1].left].data == T2[T2[root2].left].data) {

    return isomorphism(T1[root1].left, T2[root2].left) &&
           isomorphism(T1[root1].right, T2[root2].right);
  } else {
    return isomorphism(T1[root1].left, T2[root2].right) &&
           isomorphism(T1[root1].right, T2[root2].left);
  }
}

int main() {
  Node root1 = buildTree(T1);
  Node root2 = buildTree(T2);

  if (isomorphism(root1, root2)) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }

  return 0;
}