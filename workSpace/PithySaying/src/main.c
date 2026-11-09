#include "main.h"

#include "pithy.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  pithy_create();

  printf("%s", pithy_get());

  pithy_destroy();

  return 0;
}