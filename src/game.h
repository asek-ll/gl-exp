#ifndef __GAME_H__
#define __GAME_H__

#include "field.h"
#include "shape.h"

class Game {
  Field field;
  Shape currentShape, nextShape;
  float lastMoveTime = 0.0;
  bool isKeyPressed(int key, float time, float cd, float cds);

public:
  bool Keys[1024];
  float KeyPressedSince[1024];
  float KeyProcessedAt[1024];

  void Init();
  void Render(float dt);
  void Update(float dt);
};

#endif /* __GAME_H__ */
