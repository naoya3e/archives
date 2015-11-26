#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _word {
   char id[16];
   char def[256];
   struct _word *next;
} Word;

void print_word(Word *p);
Word *add   (char key[], Word *head);
Word *search(char key[], Word *head);
Word *delete(char key[], Word *head);

int main() {
  char key[256];
  Word *p;
  Word *head = NULL;

  while (1) {
    printf("調べたい単語を入力してください.\n");
    scanf("%s", key);
    if (strcmp(key, "-add") == 0) {
      printf("辞書に単語を追加します.\n");
      printf("読み方は？ ");
      scanf("%s", key);
      head = add(key, head);
    } else if (strcmp(key, "-delete") == 0) {
      printf("辞書から単語を削除します.\n");
      printf("読み方は？ ");
      scanf("%s", key);
      head = delete(key, head);
    } else if (strcmp(key, "-quit") == 0) {
      break;
    } else {
      p = search(key, head);
      if (p == NULL) {
        printf("指定した単語は見つかりませんでした.\n");
      } else {
        print_word(p);
      }
    }
  }

  return 0;
}

void print_word(Word *p) {
  printf("[%s]\n%s\n", p->id, p->def);
}

Word *add   (char key[], Word *head) {
  Word *new;
  new = (Word *)malloc(sizeof(Word));

  strcpy(new->id, key);

  if (search(new->id, head) != NULL) {
    printf("単語名が重複しています.\n");
    return head;
  }

  printf("意味は？ ");
  scanf("%s", new->def);

  // 単方向リストの先頭へ追加処理を行う
  // 末尾じゃないから線形探索してNULLを指すようにしなくてよい
  new->next = head;
  head = new;

  printf("単語 %s を追加しました.\n", new->id);

  return head;
}

Word *search(char key[], Word *head) {
  Word *p;

  for (p=head; p!=NULL; p=p->next) {
    if (strcmp(p->id, key) == 0) return p;
  }

  return NULL;
}

Word *delete(char key[], Word *head) {
  Word **p;
  Word  *q;

  for (p=&head; p!=NULL; p=&(*p)->next) {
    if (strcmp((*p)->id, key) == 0) {
      q = *p;
      *p = (*p)->next;
      free(q);
      printf("単語 %s を削除しました.\n", key);
      return head;
    }
  }

  printf("指定した単語は見つかりませんでした.\n");
  return NULL;
}

