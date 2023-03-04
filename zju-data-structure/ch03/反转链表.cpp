#include <iostream>
#include <string>

using namespace std;

typedef struct {
  int data;
  int next;
} Node;

int main() {
  int headAddress, len, reverse;
  int address, data, next;

  Node list[100000];

  cin >> headAddress >> len >> reverse;
  for (int i = 0; i < len; i++) {
    cin >> address >> data >> next;
    Node node;
    node.data = data;
    node.next = next;
    list[address] = node;
  }

  return 0;
}