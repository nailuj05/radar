#include "radar.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

void renderRadar(State *state, Radar *radar) {
  //  DrawCircle(state->sw / 2.0f, state->sh / 2.0f, 10, state->mainColor);

  Vector2 screenPos = {state->sw / 2.0f, state->sh / 2.0f};
  Vector2 v =
      Vector2Rotate((Vector2){.x = 0.0f, .y = radar->range}, radar->angle);
  Vector2 vt = Vector2Rotate(v, DEG2RAD * 180.f);

  DrawLineV(screenPos, Vector2Add(screenPos, vt), state->mainColor);

  radar->angle += radar->q * GetFrameTime();
  if (fabs(radar->angle) > radar->maxAngle) {
    radar->q = -radar->q;
  }

  Contact *c = radar->contacts;
  while (c) {
    Vector2 t = globalToLocal(radar, screenPos, (Vector2)c->pos);
    float a = Vector2Angle(t, v) * RAD2DEG;
    printf("%f\n", a);

    if (a < 5 && a > -5) {
      DrawCircleV(t, c->size, state->mainColor);
    }
    c = c->next;
  }
}

Vector2 globalToLocal(Radar *radar, Vector2 screenPos, Vector2 pos) {
  pos = Vector2Subtract(pos, radar->pos);
  pos = Vector2Rotate(pos, -radar->dir);
  pos = Vector2Add(pos, screenPos);
  return pos;
}

void addContact(Radar *radar, Contact *contact) {
  if (!radar->contacts) {
    radar->contacts = contact;
    return;
  }
  Contact *c = radar->contacts;
  while (c->next)
    c = c->next;
  c->next = contact;
}
