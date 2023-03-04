#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  int n, max, cur, pre;

  std::cin >> n;
  std::cin >> pre;
  max = pre;

  for (int i = 1; i < n; i++) {
    std::cin >> cur;
    // 如果当前值和上一次值相加后大于 0, 说明这个值是以 a[i] 为结尾的和为更大
    if (pre > 0) {
      pre += cur;
    } else {
      pre = cur;
    }

    if (max < pre) {
      max = pre;
    }
  }

  std::cout << max << std::endl;

  return 0;
}