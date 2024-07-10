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
                 .dir = 180.f,
                 .q = 2.5f,
                 .contacts = NULL};

  Contact c1 = {(Vector2){-50.f, -50.f}, 3.f, NULL};
  Contact c2 = {(Vector2){-100.f, 0.f}, 3.f, NULL};
  Contact c3 = {(Vector2){-50.f, 50.f}, 3.f, NULL};
  addContact(&radar, &c1);
  addContact(&radar, &c2);
  addContact(&radar, &c3);

  Shader bloom = LoadShader(0, "resources/shaders/bloom.glsl");
  Shader scanlines = LoadShader(0, "resources/shaders/scanlines.glsl");
  Shader distortion = LoadShader(0, "resources/shaders/distortion.glsl");
  Shader pp = LoadShader(0, "resources/shaders/pp.glsl");

  RenderTexture2D target = LoadRenderTexture(SW, SH);

  SetTargetFPS(120);

  while (!WindowShouldClose()) {
    BeginTextureMode(target);

    // SCREEN FADE EFFECT
    Color bg = {0, 0, 0, 10};
    DrawRectangle(0, 0, state.sw, state.sh, bg);

    renderRadar(&state, &radar);

    EndTextureMode();

    BeginDrawing();

    // Post Process
    BeginShaderMode(bloom);
    DrawTextureRec(target.texture,
                   (Rectangle){0, 0, (float)target.texture.width,
                               (float)-target.texture.height},
                   (Vector2){0, 0}, WHITE);
    EndShaderMode();

    EndDrawing();
  }

  UnloadShader(bloom);
  UnloadShader(scanlines);
  UnloadShader(distortion);
  UnloadShader(pp);
  UnloadRenderTexture(target); // Unload render texture
  CloseWindow();

  return EXIT_SUCCESS;
}
