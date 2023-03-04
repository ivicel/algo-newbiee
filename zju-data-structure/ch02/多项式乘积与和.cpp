#include <iostream>
#include <vector>

using namespace std;

struct Element {
  int px;  // 系数
  int ex;  // 指数
};

// 输出结果
void Print(vector<Element> &v) {
  bool first = true;
  for (auto i = v.begin(); i != v.end(); i++) {
    if (first) {
      first = false;
    } else {
      cout << " ";
    }
    cout << i->px << " " << i->ex;
  }

  if (first) {
    cout << "0 0";
  }

  cout << endl;
}

vector<Element> calculateSum(const vector<Element> &v1,
                             const vector<Element> &v2) {
  vector<Element> ret;
  size_t i = 0, j = 0;
  while (i < v1.size() && j < v2.size()) {
    if (v1[i].ex > v2[j].ex) {
      ret.push_back(v1[i]);
      i++;
    } else if (v1[i].ex < v2[j].ex) {
      ret.push_back(v2[j]);
      j++;
    } else {
      Element e;
      e.ex = v1[i].ex;
      e.px = v1[i].px + v2[j].px;
      if (e.px != 0) {
        ret.push_back(e);
      }
      j++;
      i++;
    }
  }

  while (i < v1.size()) {
    ret.push_back(v1[i]);
    i++;
  }
  while (j < v2.size()) {
    ret.push_back(v2[j]);
    j++;
  }

  return ret;
}

vector<Element> calculateMulti(const vector<Element> &v1,
                               const vector<Element> &v2) {
  vector<Element> ret;
  for (auto iter1 : v1) {
    vector<Element> tmp;
    for (auto iter2 : v2) {
      Element t;
      t.px = iter1.px * iter2.px;
      t.ex = iter1.ex + iter2.ex;
      tmp.push_back(t);
    }

    if (!ret.empty()) {
      ret = calculateSum(ret, tmp);
    } else {
      ret = tmp;
    }
  }

  return ret;
}

vector<Element> read() {
  int n;
  vector<Element> v;

  cin >> n;
  bool skip = true;
  for (int i = 0; i < n * 2; i++) {
    int t;
    if (i % 2 == 0) {
      Element e;
      cin >> e.px;
      // cout << "======= " << e.px << endl;
      if (e.px != 0) {
        v.push_back(e);
        skip = false;
      } else {
        skip = true;
      }
    } else {
      if (skip) {
        cin >> t;
      } else {
        cin >> v.back().ex;
      }
    }
  }

  return v;
}

int main() {
  vector<Element> v1 = read();
  vector<Element> v2 = read();

  vector<Element> ret1 = calculateMulti(v1, v2);
  vector<Element> ret2 = calculateSum(v1, v2);
  Print(ret1);
  Print(ret2);

  return 0;
}