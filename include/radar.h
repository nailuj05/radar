#ifndef RADAR_H
#define RADAR_H
#include "game.h"
#include <raylib.h>

typedef struct contact {
  Vector2 pos;
  float size;
  struct contact *next;
} Contact;

typedef struct radar {
  // Public
  float range;
  float maxAngle;
  Vector2 pos;

  // Internal
  float angle;
  float dir;
  float q;

  Contact *contacts;
} Radar;

void renderRadar(State *state, Radar *radar);

Vector2 globalToLocal(Radar *radar, Vector2 screenPos, Vector2 pos);

void addContact(Radar *radar, Contact *c);

#endif
