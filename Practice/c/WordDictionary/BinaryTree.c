#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct word {
  char id[16];
  char def[256];
  struct word  *left;
  struct word *right;
} Word;

// 何故かadd()とdelete()でWord型のアドレスを返さないといけない
// 追加した要素のアドレスを返すと代入がおかしくなるから必ずheadを返す
// 意味不明な仕様である
void print_word(Word *p);
void print_child_node(char key[], Word *p);
Word *add   (char key[], Word *head);
Word *search(char key[], Word *head);
Word *delete(char key[], Word *head);
Word *find_min_node(Word **node);
Word *file_read(Word *head);
void file_write(Word *head);
void traverse(FILE *fp, Word *p);
void write_in(FILE *fp, Word *p);

int main() {
  char key[256];  // コマンドと読み方を格納する
  Word *head = NULL;  // 二分探索木のルートを示す

  while (1) {
    printf("調べたい単語を入力してください : ");
    scanf("%s", key);

    if (strcmp(key, "-add") == 0) {
      printf("辞書に単語を追加します.\n");
      printf("読み方は？ : ");
      scanf("%s", key);
      head = add(key, head);
    } else if (strcmp(key, "-delete") == 0) {
      printf("辞書から単語を削除します.\n");
      printf("読み方は？ : ");
      scanf("%s", key);
      head = delete(key, head);
    } else if (strcmp(key, "-quit") == 0) {
      break;
    } else if (strcmp(key, "-read") == 0) {
      head = file_read(head);
      printf("ファイルを読み込み辞書に追加しました.\n\n");
    } else if (strcmp(key, "-write") == 0) {
      file_write(head);
      printf("ファイルへ辞書を出力しました. (output.txt)\n\n");
    } else {
      head = search(key, head);
    }
  }

  return 0;
}

void print_word(Word *p) {
  printf("[%s] : %s\n", p->id, p->def);
}

// 引数のノード以下のノードを再帰的に出力する
// 探索は深さ優先探索で行う
void print_child_node(char key[], Word *p) {
  if (p != NULL) {
    print_child_node(key, p->left);
    if (strncmp(p->id, key, strlen(key)) == 0) print_word(p);
    print_child_node(key, p->right);
  }
}

Word *add(char key[], Word *head) {
  Word *new;
  Word **p;

  new = (Word *)malloc(sizeof(Word));
  if (new == NULL) {
    fprintf(stderr, "ERROR: メモリの割り当てに失敗しました.\n");
    exit(EXIT_FAILURE);
  }

  strcpy(new->id, key);
  new->left  = NULL;
  new->right = NULL;

  printf("意味は？   : ");
  scanf("%s", new->def);

  // 二分探索木が空の場合、ノードを辿らずにルートとして追加を行う
  p = &head;
  while (*p != NULL) {
    if (strcmp((*p)->id, key) == 0) {
      printf("指定した単語 %s は既に登録されています.\n\n", key);
      return head;
    }
    if (strcmp((*p)->id, key) < 0) {
      p = &(*p)->left;
    } else {
      p = &(*p)->right;
    }
  }

  *p = new;
  printf("単語 %s を追加しました.\n\n", key);
  return head;
}

Word *search(char key[], Word *head) {
  Word *target = NULL;
  Word **p;

  p = &head;
  while (*p != NULL) {
    // 完全一致検索
    // if (strcmp((*p)->id, key) == 0) target = *p;
    //
    // 前方一致検索
    // strncmp()を利用して、keyの文字列長まで比較を行う
    // 0が返ってきたときのノード以下をすべて出力すればよい
    if (strncmp((*p)->id, key, strlen(key)) == 0) {
      target = *p;
      break;
    }

    if (strcmp((*p)->id, key) < 0) {
      p = &(*p)->left;
    } else {
      p = &(*p)->right;
    }
  }

  if (target == NULL) {
    printf("指定した単語は見つかりませんでした.\n\n");
  } else {
    // 対象のノードの左側ノードは間違いなく出力対象
    // しかし、右側のノードは出力対象じゃないかもしれない
    print_child_node(key, target);
    printf("\n");  // 表示調整用
  }

  return head;
}

//
// ノードの削除は以下の3通りが考えられる
//
//  1: 子を持たない場合
//  2: 子を1つ持つ場合
//  3: 子を2つ持つ場合
//
//  1: 削除対象のノードをそのまま削除してよい
//  2: 削除対象のノードと子のノードを入れ替えて接続し直す
//  3: 削除対象ノードの右側の子の最小のノードと置き換える
//      (削除対象のノードの左側の子の最大のノードと置き換える)
//
// ダブルポインタによる操作を行うため、親ノードからポインタを張り替える必要はない
// 探索先ポインタ *p が指すアドレスを書き換えることで親ノードからの接続を更新する
//
Word *delete(char key[], Word *head) {
  Word *target = NULL;
  Word *leftChild, *rightChild;
  Word **p;

  p = &head;
  while (*p != NULL) {
    if (strcmp((*p)->id, key) == 0) {
      target = *p;

      if ((*p)->left == NULL && (*p)->right == NULL) {
        // ノードが葉 (子を持たない)
        *p = NULL;
      } else if ((*p)->left == NULL) {
        // 左の子ノードが存在しない
        *p = (*p)->right;
      } else if ((*p)->right == NULL) {
        // 右の子ノードが存在しない
        *p = (*p)->left;
      } else {
        // 左右の子ノードが存在する
        *p = find_min_node(&target->right);
        // 削除対象ノードが持つ子を接続し直す
        (*p)->left  = target->left;
        (*p)->right = target->right;
      }

      free(target);
      printf("単語 %s を削除しました.\n\n", key);
      break;
    }

    if (strcmp((*p)->id, key) < 0) {
      p = &(*p)->left;
    } else {
      p = &(*p)->right;
    }
  }

  return head;
}

Word *find_min_node(Word **node) {
  Word *min;

  // 探索対象のノードよりも小さい値は node の左側にしか存在しない
  // 葉ノードに辿り着いた時、指し示すノードが最小であるはず
  while ((*node)->left != NULL) {
    node = &(*node)->left;
  }
  min = *node;

  // *node が右側に子ノードがある可能性
  // NULLか右側の子ノードと置き換える
  *node = (*node)->right;

  return min;
}

Word *file_read(Word *head) {
  int flag = 0;
  char filename[256];
  char pron[16];
  char definition[256];
  Word *new;
  Word **p;
  FILE *fp;

  printf("読み込むファイル名を指定してください : ");
  scanf("%s", filename);

  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "ERROR: ファイルの読み込みに失敗しました.\n");
    exit(EXIT_FAILURE);
  }

  while (fscanf(fp, "%s %s", pron, definition) != EOF) {
    p = &head;

    // 追加するノードの位置を探索する
    while (*p != NULL) {
      if (strcmp((*p)->id, pron) == 0) flag = 1;
      if (strcmp((*p)->id, pron) <  0) {
        p = &(*p)->left;
      } else {
        p = &(*p)->right;
      }
    }

    if (flag == 0) {
      new = (Word *)malloc(sizeof(Word));
      if (new == NULL) {
        fprintf(stderr, "ERROR: メモリの割り当てに失敗しました.\n");
        exit(EXIT_FAILURE);
      }

      strcpy(new->id,  pron);
      strcpy(new->def, definition);
      new->left  = NULL;
      new->right = NULL;
      *p = new;
    }
    flag = 0;
  }

  return head;
}

void file_write(Word *head) {
  FILE *fp;

  if ((fp = fopen("output.txt", "a")) == NULL) {
    fprintf(stderr, "ERROR: ファイルの読み込みに失敗しました.\n");
    exit(EXIT_FAILURE);
  }

  // 木構造をすべて深さ優先探索して、全要素にアクセスする
  traverse(fp, head);

  fclose(fp);
}

void traverse(FILE *fp, Word *p) {
  write_in(fp, p);
  if (p != NULL) {
    write_in(fp, p->left);
    write_in(fp, p->right);
  }
}

void write_in(FILE *fp, Word *p) {
  fprintf(fp, "%s %s\n", p->id, p->def);
}

