#include <iostream>
#include <vector>

using namespace std;

int getMaxSumAndIndex(vector<int> v, int &left, int &right) {
  int pre = 0, max = 0, tempLeft;
  for (int i = 0; i < v.size(); i++) {
    // 如果当前值和上一次值相加后大于 0, 说明这个值是以 a[i] 为结尾的和为更大
    if (pre > 0) {
      pre += v.at(i);
    } else {
      pre = v.at(i);
      tempLeft = i;
    }

    if (max < pre) {
      max = pre;
      right = i;
      left = tempLeft;
    }
  }

  return max;
}

int main(int argc, char **argv) {
  int n;
  bool all_negative = true;
  bool no_positive = true;

  vector<int> v(n);
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> n;

    if (n >= 0) {
      all_negative = false;
    }

    if (n > 0) {
      no_positive = false;
    }

    v[i] = n;
  }

  if (all_negative) {
    std::cout << v.size() << std::endl;
    std::cout << 0 << " " << v.front() << " " << v.back() << std::endl;
    return 0;
  }

  if (no_positive) {
    std::cout << "0 0 0" << std::endl;
    return 0;
  }

  int left = 0, right = 0;
  int max = getMaxSumAndIndex(v, left, right);
  std::cout << max << " " << left << " " << right << std::endl;

  return 0;
}