# archives

> Projects are archived for reference.

アーカイブして良いような「前このコード書いたな」ってときに探すだけのリポジトリ.  
競技プログラミングとかPythonの練習用の残骸のコードとか.

## To archive git repository

```sh
git remote add $repo git@github.com:naoya3e/$repo.git
git fetch $repo
git checkout -b $repo $repo/master
git filter-branch -f --tree-filter "mkdir -p $repo && git mv -k {,.[\!.],..[\!.]}* $repo/"
git checkout master
git merge --allow-unrelated-histories --no-edit $repo
```

`git filter-branch`がこの処理のキモ.  

`mkdir`によって作成するディレクトリを階層構造にしても大丈夫.  
そのときは`git mv`の移動先も対応させることを忘れないように.  

## References

- [Githubさん,ごめんなさい！複数リポジトリを一つにまとめる方法](https://qiita.com/awakia/items/6233eeac21fb895fa58d)
- [How do you move all files (including hidden) from one directory to another?](https://unix.stackexchange.com/questions/6393/how-do-you-move-all-files-including-hidden-from-one-directory-to-another)
