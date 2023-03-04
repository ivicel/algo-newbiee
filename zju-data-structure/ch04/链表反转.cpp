#include <iomanip>
#include <iostream>

using namespace std;

#define MAX 100000

typedef struct {
  int data;
  int next;
} Element;

int main() {
  Element arr[MAX];
  int head;
  int len, K;
  int i;

  cin >> head >> len >> K;

  while (len--) {
    cin >> i;
    cin >> arr[i].data >> arr[i].next;
  }

  int newNode, oldNode, tmp;
  newNode = head;
  oldNode = arr[newNode].next;
  tmp = arr[oldNode].next;

  if (K != 1) {
    while (--K) {
      arr[oldNode].next = newNode;
      newNode = oldNode;
      oldNode = tmp;
      tmp = arr[tmp].next;
    }

    arr[head].next = oldNode;
    head = newNode;
  }
  for (int i = head; i != -1; i = arr[i].next) {
    cout << setw(5) << setfill('0') << i << " " << arr[i].data << " ";
    if (arr[i].next >= 0) {
      cout << setw(5) << setfill('0') << arr[i].next << endl;
    } else {
      cout << arr[i].next << endl;
    }
  }

  return 0;
}