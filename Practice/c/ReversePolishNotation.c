#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define N 100

int stack[N];
int top = 0;

void push(int n) {
  if (top < N) stack[top++] = n;
}

int pop() {
  return (top > 0)? stack[--top]: 0;
}

int split(char *in, const char *delimiter, char **out) {
  int counter = 0;
  char *token;

  while (1) {
    token = strtok((counter == 0)? in: NULL, delimiter);
    if (token == NULL) break;
    out[counter] = token;
    counter++;
  }

  return counter;
}

int rpn(char *assign) {
  int i, n;
  char *exp[N];

  n = split(assign, " \n", exp);
  for (i=0; i<n; i++) {
    if (isdigit(*(exp[i]))) {
      push(atoi(exp[i]));
    } else {
      switch (*(exp[i])) {
        case '+':
          push(pop()+pop());
          break;
        case '-':
          push(pop()-pop());
          break;
        case '*':
          push(pop()*pop());
          break;
        case '/':
          push(pop()/pop());
          break;
        case '%':
          push(pop()%pop());
          break;
        default:
          fprintf(stderr, "ERROR: 式に解釈できない記号が含まれています\n");
          exit(EXIT_FAILURE);
      }
    }
  }
  return pop();
}

int main() {
  char assign[N];

  printf("逆ポーランド記法で式を入力してください：");
  fgets(assign, N, stdin);

  printf("Answer is %d\n", rpn(assign));

  return 0;
}

