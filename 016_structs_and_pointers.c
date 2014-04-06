/*
 * Exercise 16: http://c.learncodethehardway.org/
 *
 * Structs and pointers.
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
  char *name;
  int age;
  int height;
  int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
  struct Person *who = malloc(sizeof(struct Person));
  assert(who != NULL);

  who->name   = strdup(name);
  who->age    = age;
  who->height = height;
  who->weight = weight;

  return who;
}

void Person_destruct(struct Person *who)
{
  assert(who != NULL);

  free(who->name);
  free(who);
}

void Person_print(struct Person *who)
{
  printf("Name: %s\n", who->name);
  printf("\tAge: %d\n", who->age);
  printf("\tHeight: %d\n", who->height);
  printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
  int i;
  for (i = 0; i < argc; i++) {
    struct Person *myguy = Person_create(argv[i], i, 1, 1);
    printf("In memory: %p\n", myguy);
    Person_print(myguy);
    Person_destruct(myguy);
  }

  return 0;
}
