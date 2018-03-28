#include <iostream>
using namespace std;

int main() {
  int year;

  cout << "西暦を入力してください: ";
  cin >> year;

  if (year%4 == 0 && year%100 != 0 || year%400 == 0) {
    cout << year << "年は閏年です" << endl;
  } else {
    cout << year << "年は閏年ではありません" << endl;
  }
}
