#ifndef M_PITHY_H
#define M_PITHY_H

#ifndef PITHY_PATH
#define PITHY_PATH "pithy.txt"
#endif

void pithy_create(void);
void pithy_destroy(void);

char *pithy_get(void);

#endif /* M_PITHY_H */