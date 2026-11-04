#include "moonPhase.h"

static const char *phase[8] = {
    "waxing crecent",  "at first quarter", "waxing gibbous",   "full",
    "wanning gibbous", "at last quarter",  "wanning crescent", "new"};

const char *moon_phase(int year, int month, int day) {
  int d, g, e;

  int index;

  d = day;
  if (month == 2)
    d += 31;
  else if (month > 2)
    d += 59 + (month - 3) * 30.6 + 0.5;

  g = (year - 1900) % 19;
  e = (11 * g + 29) % 30;

  if (e == 25 || e == 24)
    e++;

  index = (((e + d) * 6 + 5) % 177) / 22 & 7;

  return phase[index];
}