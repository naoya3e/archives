using System;
using System.Linq;

class Program {
  static void Main(string[] args) {
    int n = int.Parse(Console.ReadLine());
    char[, ] s = new char[n, n];

    for (int i=0; i<n; i++) {
      string tmp = Console.ReadLine();
      for (int j=0; j<n; j++) {
        s[i, j] = tmp[j];
      }
    }

    for (int i=0; i<n; i++) {
      for (int j=n-1; j>=0; j--) {
        Console.Write(s[j, i]);
      }
      Console.WriteLine();
    }
  }
}
