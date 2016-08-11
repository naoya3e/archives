import java.util.Scanner;

public class LeapYear {
  public static void main (String[] args) {
    System.out.println("西暦を入力してください");

    Scanner scan = new Scanner(System.in);

    int year = scan.nextInt();

    if (year%4 == 0 && year%100 != 0 || year%400 == 0) {
      System.out.println(year + "年は閏年です");
    } else {
      System.out.println(year + "年は閏年ではありません");
    }
  }
}
