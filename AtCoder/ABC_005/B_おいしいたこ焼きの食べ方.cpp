#include <iostream>
using namespace std;

int main() {
  int N;
  cin >> N;

  int min = 101;
  int t;

  for (int i=0; i<N; i++) {
    cin >> t;
    if (t < min) min = t;
  }

  cout << min << endl;

  return 0;
}
