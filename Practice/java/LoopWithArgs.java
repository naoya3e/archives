public class LoopWithArgs {
  public static void main (String[] args) {
    try {
      int n = Integer.parseInt(args[0]);

      for (int i=0; i<n; i++) {
        System.out.println("Hello, world!  " + (i+1));
      }
    } catch (ArrayIndexOutOfBoundsException e) {
      System.out.println("コマンドライン引数を指定して実行してください");
    }
  }
}
