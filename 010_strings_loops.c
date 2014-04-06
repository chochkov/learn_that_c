/*
 * Exercise 10: http://c.learncodethehardway.org/
 *
 * Looping over strings.
 */

#include <stdio.h>

int counts_of_a(char *word)
{
  int result = 0;
  int i;

  for (i = 0; word[i] != '\0'; i++) {
    switch (word[i]) {
      case 'a':
      case 'A':
        result++;
        break;
    }
  }

  return result;
}

int main(int argc, char *argv[])
{
  char *msg = "The word *%s* has %d times a or A\n";

  int i;
  for (i = 1; i < argc; i++) {
    printf(msg, argv[i], counts_of_a(argv[i]));
  }

  return 0;
}
