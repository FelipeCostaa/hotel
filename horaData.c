//
// Created by felipe on 21/02/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "horaData.h"

void data()
{
  time_t mytime;
  mytime = time(NULL);
  struct tm tm = *localtime(&mytime);
  printf("\nData: %d/%d/%d\t |\tHora: %d:%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
}
