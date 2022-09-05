#ifndef __SHAPE_H__
#define __SHAPE_H__
#include <cstdlib>

enum ShapeType { L, J, O, I, T, S, Z };

const int rotationsCount[] = {4, 4, 1, 2, 4, 2, 2};

const int shapeIndex[] = {0, 4, 8, 9, 11, 15, 17};

const bool shapes[][16] = {{0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
                           {0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                           {0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
                           {0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
                           {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                           {0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                           {0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                           {1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0}};

class Shape {
  ShapeType Type;
  int type;
  int rotation;

public:
  bool const *Data;
  int X;
  int Y;
  int Color;

  Shape() { Random(); }

  Shape(int _type, int _rotation, int _color)
      : type(_type), rotation(_rotation),
        Data(shapes[shapeIndex[_type] + _rotation]), Color(_color) {}

  void Random() {
    type = rand() % 7;
    rotation = rand() % rotationsCount[type];
    Data = shapes[shapeIndex[type] + rotation];
    Color = rand() % 80 + 20;
  }

  Shape Rotate() {
    Shape newShape(type, (rotation + 1) % rotationsCount[type], Color);

    newShape.X = X;
    newShape.Y = Y;

    return newShape;
  }
};

#endif /* __SHAPE_H__ */
