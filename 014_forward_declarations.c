/*
 * Exercise 14: http://c.learncodethehardway.org/
 *
 * Forward declarations.
 */

#include <stdio.h>

int is_a(char ch);

int is_a(char ch)
{
  return ch == 'g' || ch == 'i';
}

int main(int argc, char *argv[])
{
  int i;
  for (i = 0; i < argc; i++) {
    if (is_a(argv[i][0])) {
      printf("It does start with g or i!\n");
    } else {
      printf("Um... no, it doesnt.\n");
    }
  }

  return 0;
}
