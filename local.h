#ifndef __LOCAL_H__
#define __LOCAL_H__



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h> // for EBSY
#include <unistd.h>
#include <time.h>
#define INPUT_FILE "./input.txt"
struct kids
{
  int kid_id;
  int hasball;
int balldropcnt;
};

#endif