/**
 * mazeconf.h
 * @author yuta seya
 * @date 2019 3.13
*/

#ifndef MAZECONF_H
#define MAZECONF_H

#include <stdint.h>

typedef enum {
  Front = 0,
  Left,
  Rear,
  Right,
}Action;

typedef enum {
  North = 0,
  West,
  South,
  East,
}Direction;

#endif // MAZECONF_H