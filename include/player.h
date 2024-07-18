#ifndef PLAYER_H
#define PLAYER_H
#include <radar.h>

typedef struct player {
  Vector2 pos;
  float dir;
  float speed;
  float angSpeed;
  int hp;
  int fuel;
} Player;

// void steerShip(Player *player, Radar *radar);

#endif
