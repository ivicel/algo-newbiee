#include <iostream>

using namespace std;

typedef int ElementType;

typedef struct Node_ *Tree;
typedef Tree Position;
typedef struct Node_ {
  ElementType data;
  Tree left;
  Tree right;
} Node;

Tree insert(ElementType i, Tree bt) {
  if (bt == nullptr) {
    bt = new Node;
    bt->data = i;
    bt->left = nullptr;
    bt->right = nullptr;
  } else if (bt->data > i) {
    bt->left = insert(i, bt->left);
  } else if (bt->data < i) {
    bt->right = insert(i, bt->right);
  }

  return bt;
}

// 前序遍历
void preorder(Tree bt) {
  if (bt != nullptr) {
    cout << bt->data << " ";
    preorder(bt->left);
    preorder(bt->right);
  }
}

// 查找最小
Position findMin(Tree bt) {
  Position ret = nullptr;
  Tree t = bt;
  while (t != nullptr) {
    if (t->left == nullptr) {
      ret = t;
    }

    t = t->left;
  }

  return ret;
}

// 查找最大
Position findMax(Tree bt) {
  Position ret = nullptr;
  Tree t = bt;

  while (t != nullptr) {
    if (t->right == nullptr) {
      ret = t;
    }

    t = t->right;
  }

  return ret;
}

// 查找某个值
Tree find(ElementType i, const Tree bt) {
  Tree t = bt;

  if (t == nullptr) {
    return nullptr;
  }

  if (t->data > i) {
    return find(i, t->left);
  } else if (t->data < i) {
    return find(i, t->right);
  } else {
    return t;
  }
}

// 查找某个值, 循环方式
Tree findIter(ElementType i, const Tree bt) {
  Tree t = bt;

  while (t != nullptr) {
    if (i < t->data) {
      t = t->left;
    } else if (i > t->data) {
      t = t->right;
    } else {
      break;
    }
  }

  return t;
}

Tree deleteElement(ElementType i, Tree bt) {
  if (bt != nullptr) {
    if (bt->data > i) {
      bt->left = deleteElement(i, bt->left);
    } else if (bt->data < i) {
      bt->right = deleteElement(i, bt->right);
    } else {

      if (bt->left != nullptr && bt->right != nullptr) { // 如果左右子树都存在
        // 以要删除的结点为根, 找到其右子树的最小结点,
        // 即是最左结点, 该结点可能有右子树但肯定没有左子树
        Position tmp = findMin(bt->right);
        // 把这个结点的值复制到删除的结点
        bt->data = tmp->data;
        // 删除掉这个结点
        deleteElement(tmp->data, tmp);
      } else { // 有一个或者没有子结点
        Position tmp = bt;
        if (bt->left == nullptr) {
          bt = bt->right;
        } else if (bt->right == nullptr) {
          bt = bt->left;
        }

        delete tmp;
      }
    }
  }

  return bt;
}

// 删除结点
// Tree deleteElement(ElementType i, Tree bt) {
//   Tree ret = bt, lastPtr = nullptr, ptr, right, lastPtr2 = nullptr;
//   while (ret != nullptr) {
//     if (ret->data > i) {
//       ret = ret->left;
//     } else if (ret->data < i) {
//       ret = ret->right;
//     } else {
//       // 1. 如果是叶子结点, 直接删除
//       if (ret->left == nullptr && ret->right == nullptr) {
//         // 删除的是根结点时
//         if (lastPtr == nullptr) {
//           bt = nullptr;
//         } else {
//           lastPtr = nullptr;
//         }
//         break;
//       }

//       /*
//       2. 如果这个结点只有左子树, 或者只有右子树, 那么删除除这个结点后,
//        子结点填到父结点
//       */
//       if (ret->left != nullptr && ret->right == nullptr) {
//         if (lastPtr == nullptr) {
//           bt = ret->left;
//         } else if (lastPtr->data > ret->data) {
//           lastPtr->left = ret->left;
//         } else {
//           lastPtr->right = ret->left;
//         }

//         ret->left = nullptr;
//         break;
//       }

//       if (ret->right != nullptr && ret->left == nullptr) {
//         if (lastPtr == nullptr) {
//           bt = ret->right;
//         } else if (lastPtr->data > ret->data) {
//           lastPtr->left = ret->right;
//         } else {
//           lastPtr->left = ret->right;
//         }

//         ret->right = nullptr;

//         break;
//       }

//       /**
//       3. 如果左右子结点都有值, 那么可以 1) 在左子树找最小值, 即是最左子结点,
// 那么这结点最多只有右子树, 此时把这个结点填补到删除的结点位置,
// 剩下的按有右子树来处理

// 2) 在右子树找最大值, 即是最右子结点,
// 那么这结点最多只有左子树, 此时把这个结点填补到删除的结点位置,
// 剩下的按有左子树来处理
//       */
//       // 找到最左结点
//       ptr = ret;
//       while (ptr->left != nullptr) {
//         lastPtr2 = ptr;
//         ptr = ptr->left;
//       }

//       // 按有右子树的方式处理
// lastPtr2->left = ptr->right;
//         if (lastPtr == nullptr) {
//           bt = ret->right;
//         } else if (lastPtr->data > ret->data) {
//           lastPtr->left = ret->right;
//         } else {
//           lastPtr->left = ret->right;
//         }
//     }

//     lastPtr = ret;
//   }

//   // 如果删除的是

//   return ret;
// }

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
  Tree bt = nullptr;
  bt = insert(5, bt);
  bt = insert(3, bt);
  bt = insert(7, bt);
  bt = insert(1, bt);
  bt = insert(4, bt);
  bt = insert(6, bt);
  bt = insert(8, bt);
  bt = insert(2, bt);
  bt = insert(9, bt);

  return bt;
}

int main() {
  Tree bt = buildTree();
  preorder(bt);
  cout << endl;

  cout << "最小值: " << findMin(bt) << endl;
  cout << "最大值: " << findMax(bt) << endl;
  cout << "递归方法查找结点为 3 的, 其左结点为: " << find(3, bt)->left->data
       << endl;
  cout << "循环方法查找结点为 3 的, 其左结点为: " << findIter(3, bt)->left->data
       << endl;

  return 0;
}