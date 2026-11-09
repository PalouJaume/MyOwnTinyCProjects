#include "pithy.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BSIZE 256

const char filename[] = PITHY_PATH;

static struct {
  char **list_base;
  int items;
} list;

void pithy_create(void) {
  FILE *fp = NULL;
  char buffer[BSIZE];
  char *r = NULL, *entry = NULL;

  fp = fopen(filename, "r");
  assert(fp != NULL && "Unable to open pithy file");

  list.list_base = (char **)malloc(sizeof(char *) * 100);
  assert(list.list_base != NULL && "Unbale to allocate memory\n");

  list.items = 0;

  while (!feof(fp)) {
    r = fgets(buffer, BSIZE, fp);
    if (r == NULL)
      break;

    entry = (char *)malloc(sizeof(char) * strlen(buffer) + 1);
    assert( entry != NULL && "Unable to allocate memory\n");

    strcpy(entry, buffer);
    list.list_base[list.items] = entry;

    if (list.items % 100 == 0) {
      list.list_base =
          (char **)realloc(list.list_base, sizeof(char *) * (list.items + 100));
      assert(list.list_base != NULL && "Unable to reallocate memory\n");
    }

    list.items++;
  }

  fclose(fp);
}

void pithy_destroy(void) {
  if (list.list_base == NULL)
    return;

  for (int i = 0; i < list.items; i++)
    free(list.list_base[i]);

  free(list.list_base);
}

char *pithy_get(void)
{
    int index = 0;

    srand((unsigned)time(NULL));

    index = rand() % (list.items - 1);

    return list.list_base[index];
}