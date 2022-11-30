#include "assert.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

extern const char* password;

bool checkPassword(char* input) {
  const char* p = password;
  const char* i = input;
  while (*i && *p) {
    if (*i != *p) {
      return false;
    }
    i++;
    p++;
  }

  return *i == *p;
}

bool checkPasswordConstant(char* input) {
  const char* p = password;
  const char* i = input;

  int same = 1;

  while (*i && *p) {
    same &= (*i == *p);
    i++;
    p++;
  }

  return same & (*i == *p);
}

uint64_t timeInput(char* input, int iterations) {
  uint64_t before = __rdtsc();
  for (int i = 0; i < iterations; i++) {
    checkPassword(input);
  }
  uint64_t after = __rdtsc();

  return after - before;
}

int iterations = 100;
const char* alphabet = "0123456789abcdefghijklkmnopqrstuvwxyz-";

// Given a buffer with some characters in it, set the letter at
// index to all the letters in the alphabet, and collect the runtimes.
void testLetters(char* buffer, size_t index, uint64_t* times) {
  size_t alphalen = strlen(alphabet);
  assert(buffer[index + 1] == '\0');
  for (size_t alphaIndex = 0; alphaIndex < alphalen; alphaIndex++) {
    buffer[index] = alphabet[alphaIndex];
    times[alphaIndex] = timeInput(buffer, iterations);
  }
}

bool guessLetter(char* buffer, size_t index) {
  size_t alphalen = strlen(alphabet);
  uint64_t times[alphalen];
  testLetters(buffer, index, times);
  uint64_t max = 0;
  int maxIndex = -1;
  for (int i = 0; i < alphalen; i++) {
    if (times[i] > max) {
      maxIndex = i;
      max = times[i];
    }
  }

  buffer[index] = alphabet[maxIndex];
  printf("Guessing letter %zu is %c making current buffer %s\n", index,
         alphabet[maxIndex], buffer);

  return checkPassword(buffer);
}

void guessPassword() {
  char buffer[100] = {0};
  for (int i = 0; i < 99; i++) {
    if (guessLetter(buffer, i)) {
      printf("Found password %s\n", buffer);
      return;
    }
  }
  printf("Didn't find password\n");
}

int main(int argc, char** argv) {
  if (argc > 1) {
    iterations = atoi(argv[1]);
  }

  guessPassword();
}
