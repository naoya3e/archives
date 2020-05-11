use proconio::input;
use std::cmp::{max,min};

fn main() {
  input! {
    a: i32,
    b: i32,
    c: i32,
    k: i32
  }

  println!("{}", min(a, k) - max(0, k-a-b));
}
