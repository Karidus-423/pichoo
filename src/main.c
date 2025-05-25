#include "origin.h"
#include <SDL3/SDL_render.h>
#include <stdio.h>

void RunApp(AppState *app) {

  Polygon triangle = BuildPolygon(3);

  float theta = 0.0;
  float rate = 0.0;

  // Drawig should be in syc with monitor frame rate.
  while (app->running == true) {
    HandleEvents(app);

    SDL_SetRenderDrawColor(app->rndr, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(app->rndr);

    SDL_SetRenderTarget(app->rndr, NULL);
    DrawApp(app, triangle, theta);

    theta += rate;
    if (theta > 360.0) {
      rate = -0.00001;
    }
    if (theta <= 0.0f) {
      rate = 0.00001;
    }

    SDL_RenderPresent(app->rndr);
  }
}

int main(int argc, char *argv[]) {
  AppState app = {
      .title = "Pichoo",
      .width = 500,
      .height = 500,
  };

  if (!InitApp(&app)) {
    SDL_Quit();
    return 1;
  }

  if (app.running == true) {
    RunApp(&app);
  }

  DenitApp(&app);
  SDL_Quit();
  return 0;
}
