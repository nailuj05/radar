#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

#define SW 800
#define SH 600

int main(int argc, char *argv[]) {
  InitWindow(SW, SH, "radar-punk");

  float angle = 0.0f;
  float maxAngle = DEG2RAD * 150.0f;
  float dir = DEG2RAD * 180.0f;
  float range = 200.0f;

  float q = 5.0f;

  Vector2 pos = {.x = SW / 2.0f, .y = SH / 2.0f};

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    Color bg = {0, 0, 0, 50};
    DrawRectangle(0, 0, SW, SH, bg);
    DrawCircle(pos.x, pos.y, 10, GREEN);

    Vector2 v = {.x = 0, .y = range};
    v = Vector2Rotate(v, angle + dir);

    DrawLineV(pos, Vector2Add(pos, v), GREEN);

    angle += q * GetFrameTime();
    if (fabs(angle) > maxAngle) {
      q = -q;
    }

    EndDrawing();
  }

  CloseWindow();

  return EXIT_SUCCESS;
}
