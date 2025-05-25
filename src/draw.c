#include "origin.h"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Polygon BuildPolygon(int vertices) {
  Polygon poly = {
      .size = vertices,
      .pos = (SDL_FPoint){250, 250},
  };

  SDL_Vertex *points = malloc(sizeof(SDL_Vertex) * vertices);
  SDL_Vertex top, left, right;

  top.position = (SDL_FPoint){250, 150};
  top.color = (SDL_FColor){.0f, 1.0f, .0f, 0.f};

  left.position = (SDL_FPoint){150, 350};
  left.color = (SDL_FColor){1.0f, .0f, .0f, 0.f};

  right.position = (SDL_FPoint){350, 350};
  right.color = (SDL_FColor){.0f, .0f, 1.0f, 0.f};

  // Loook if SDL draws vertices in counter clockwise for normals.
  points[0] = top;
  points[1] = left;
  points[2] = right;
  poly.vertices = points;

  return poly;
}

SDL_FPoint VRotate(float theta, SDL_FPoint vec2) {
  float vec_p_x = (vec2.x * cosf(theta)) - (vec2.y * sinf(theta));
  float vec_p_y = (vec2.x * sinf(theta)) + (vec2.y * cosf(theta));
  SDL_FPoint vec_p = {vec_p_x, vec_p_y};
  return vec_p;
}

void RotatePolygon(Polygon *obj, float theta) {
  for (int i = 1; i < obj->size; i++) {
    SDL_FPoint v = obj->vertices[i].position;
    SDL_FPoint vp = VRotate(theta, v);
    obj->vertices[i].position = vp;
  }
}

void UpdatePolygon(Polygon *obj, float theta) {
  // Rotation
  RotatePolygon(obj, theta);
  // Translation
};

void DrawApp(AppState *app, Polygon obj, float theta) {
  UpdatePolygon(&obj, theta);

  SDL_RenderGeometry(app->rndr, NULL, obj.vertices, obj.size, NULL, 0);
}
