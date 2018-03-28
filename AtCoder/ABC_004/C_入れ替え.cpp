#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  int card[] = {1, 2, 3, 4, 5, 6};

  cin >> n;
  n = n%30;

  for (int i=0; i<n; i++) {
    swap(card[i%5], card[i%5+1]);
  }

  for (int i=0; i<6; i++) {
    cout << card[i];
  }
  cout << endl;
}
