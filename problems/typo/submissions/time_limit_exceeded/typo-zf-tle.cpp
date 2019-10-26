#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<string> v(n);
  unordered_set<string> dict;

  for (auto& s : v) {
    cin >> s;
    dict.insert(s);
  }

  bool any = false;
  for (const auto& s : v) {
    bool ok = true;
    for (int i = 0; i < s.length() && ok; ++i) {
      string sub = s.substr(0, i) + s.substr(i+1, s.length());
      ok &= dict.find(sub) == dict.end();
    }
    if (!ok) {
      any = true;
      cout << s << endl;
    }
  }
  if (!any) cout << "NO TYPOS" << endl;

  return 0;
}
