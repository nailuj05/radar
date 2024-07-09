#include "game.h"
#include "radar.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

#define SW 800
#define SH 600

int main(int argc, char *argv[]) {
  InitWindow(SW, SH, "radar-punk");

  // State
  State state = {GREEN, SW, SH};

  // Radar
  Radar radar = {.range = 200.0f,
                 .maxAngle = DEG2RAD * 140.0f,
                 .pos = (Vector2){0.f, 0.f},
                 .angle = 0.0f,
                 .dir = 0.f,
                 .q = 2.5f,
                 .contacts = NULL};

  Contact c1 = {(Vector2){-50.f, -50.f}, 3.f, NULL};
  Contact c2 = {(Vector2){-100.f, 0.f}, 3.f, NULL};
  Contact c3 = {(Vector2){-50.f, 50.f}, 3.f, NULL};
  addContact(&radar, &c1);
  addContact(&radar, &c2);
  addContact(&radar, &c3);

  SetTargetFPS(120);

  while (!WindowShouldClose()) {
    BeginDrawing();

    // SCREEN FADE EFFECT: draw everything persistent BEFORE this and
    // everything radar related AFTER
    Color bg = {0, 0, 0, 10};
    DrawRectangle(0, 0, state.sw, state.sh, bg);

    renderRadar(&state, &radar);

    EndDrawing();
  }

  CloseWindow();

  return EXIT_SUCCESS;
}
