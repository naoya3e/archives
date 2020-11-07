use proconio::input;

fn main() {
  input! {
    s: String,
    mut t: String
  }

  t.pop();

  if s == t {
    println!("Yes");
  } else {
    println!("No");
  }
}
