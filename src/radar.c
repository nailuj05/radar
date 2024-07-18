#include "radar.h"
#include <raylib.h>
#include <raymath.h>

void renderRadar(State *state, Radar *radar) {
  //  DrawCircle(state->sw / 2.0f, state->sh / 2.0f, 10, state->mainColor);

  Vector2 screenPos = {state->sw / 2.0f, state->sh / 2.0f};
  Vector2 v =
      Vector2Rotate((Vector2){.x = 0.0f, .y = radar->range}, radar->angle);
  Vector2 vt = vLocal2Radar(vGlobal2Local(radar, v), screenPos);

  DrawLineV(screenPos, vt, state->mainColor);

  radar->angle += radar->q * GetFrameTime();
  if (fabs(radar->angle) > radar->maxAngle) {
    radar->q = -radar->q;
  }

  Contact *c = radar->contacts;
  while (c) {
    Vector2 t = pGlobal2Local(radar, (Vector2)c->pos);
    float a = Vector2Angle(t, v) * RAD2DEG - 180.f;
    // printf("t:(%f|%f) v:(%f|%f)\n", t.x, t.y, v.x, v.y);

    if (fabs(a) < 10 && Vector2LengthSqr(t) <= radar->range * radar->range) {
      DrawCircleV(vLocal2Radar(t, screenPos), c->size, state->mainColor);
    }
    c = c->next;
  }
}

Vector2 pGlobal2Local(Radar *radar, Vector2 pos) {
  pos = Vector2Subtract(pos, radar->pos);
  pos = Vector2Rotate(pos, -radar->dir * DEG2RAD);
  return pos;
}

Vector2 vGlobal2Local(Radar *radar, Vector2 vec) {
  return Vector2Rotate(vec, -radar->dir * DEG2RAD);
}

Vector2 vLocal2Radar(Vector2 vec, Vector2 screenPos) {
  return Vector2Add(vec, screenPos);
}

void addContact(Radar *radar, Contact *contact) {
  if (!radar->contacts) {
    radar->contacts = contact;
  } else {
    Contact *c = radar->contacts;
    while (c->next)
      c = c->next;
    c->next = contact;
  }
}
