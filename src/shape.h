#ifndef __SHAPE_H__
#define __SHAPE_H__

enum ShapeType {L, J, O, I, T, S, Z};

const int rotationsCount[] = {
  4, 4, 1, 2, 4, 2, 2
};

const bool shapes[][16] = {
{   0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
},
{   0, 0, 0, 0,
    0, 0, 1, 0,
    1, 1, 1, 0,
    0, 0, 0, 0
},
{   0, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0
},
{   0, 0, 0, 0,
    1, 1, 1, 0,
    1, 0, 0, 0,
    0, 0, 0, 0
}
};

const bool jShapes[][16] = {
{   0, 0, 1, 0,
    0, 0, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
},
{   0, 0, 0, 0,
    1, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0
},
{   0, 1, 1, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
},
{   0, 0, 0, 0,
    0, 1, 0, 0,
    0, 1, 1, 1,
    0, 0, 0, 0
}
};

const bool oShapes[][16] = {
{   0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
}
};

class Shape {
ShapeType Type;
    int type;
    int rotation;
public:
    bool const *Data;
    int X;
    int Y;


    Shape(): type(0), rotation(0), Data(shapes[0]) {}
    Shape(int _type, int _rotation): type(_type), rotation(_rotation), Data(shapes[_rotation]) {}


    Shape Rotate() {
      Shape newShape(0, (rotation+1)%4);

      newShape.X = X;
      newShape.Y = Y;

      return newShape;
    }
};

#endif /* __SHAPE_H__ */
