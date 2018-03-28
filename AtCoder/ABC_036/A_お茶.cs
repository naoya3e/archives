using System;

class Program {
  static void Main(string[] args) {
    var input = Console.ReadLine().Split(' ');
    var a = int.Parse(input[0]);
    var b = int.Parse(input[1]);

    Console.WriteLine((b/a) + (b%a == 0 ? 0 : 1));
  }
}
