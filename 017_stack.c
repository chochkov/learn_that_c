#include <stdio.h>
#include <stdlib.h>

#define MAX_OBJECTS 10

struct Object {
  int val;
};

struct Stack {
  int index;
  struct Object objects[MAX_OBJECTS];
};

struct Stack *init()
{
  struct Stack *stack = malloc(sizeof(struct Stack));

  stack->index = 0;

  int i;
  for (i = 0; i < MAX_OBJECTS; i++) {
    struct Object obj = { .val = 0 };

    stack->objects[i] = obj;
  }

  return stack;
}

// 1 if sth was cleaned, 0 if nothing was cleaned
int clean(struct Stack *stack)
{
  if (stack) {
    free(stack);
    return 1;
  }

  return 0;
}

struct Object *pop(struct Stack *stack)
{
  struct Object *result = &stack->objects[stack->index];
  stack->index--;

  return result;
}

struct Stack *push(struct Stack *stack, struct Object *object)
{
  stack->objects[stack->index] = *object;
  stack->index++;

  return stack;
}

void print(struct Stack *stack)
{
  int i;
  for (i = 0; i <= stack->index; i++) {
    printf("%d-th value: %d\n", i, stack->objects[i].val);
  }
}

void get_command(struct Stack *stack)
{
  char input;
  int quit = 0;

  do {
    scanf("%s", &input);

    switch (input) {
      case 'l':
        print(stack);

        break;
      case 'q':
        printf("Ok, we go.\n");
        quit = 1;

        break;
      case '+':
        /* struct Object object = { .val = 37 }; */
        /* push(stack, object); */
        printf("Yes i know\n");

        break;
      case '-':
        if (stack->index != 0) {
          printf("%d\n", pop(stack)->val);
        } else {
          printf("You can't pop an empty stack.\n");
        }

        break;
      default:
        printf("You work with +, -, l to list, h for help, q for quit.\n");
    }
  } while (quit == 0);
}

int main(int argc, char *argv[])
{
  printf("We are a stack program.\n");

  struct Stack *stack = init();

  get_command(stack);

  clean(stack);

  return 0;
}
