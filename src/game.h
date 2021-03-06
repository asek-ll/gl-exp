#ifndef __GAME_H__
#define __GAME_H__

#include "field.h"
#include "shape.h"

class Game {
    Field field;
    Shape currentShape, nextShape;
    float lastMoveTime = 0.0;
public:
    bool Keys[1024];

    void Init();
    void Render(float dt);
    void Update(float dt);
};

#endif /* __GAME_H__ */
