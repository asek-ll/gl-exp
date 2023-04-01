#include "field-model.hpp"

#include "iostream"

void FieldModel::Update(float dt) {
  since_last_update_ += dt;
  if (since_last_update_ < 0.1) {
    return;
  }
  since_last_update_ = 0;
  if (shape_setuped_) {
    ClearShape(shape_);
    if (IsValidShape(shape_, shape_.X, shape_.Y + 1)) {
      shape_.Y += 1;
      WithShape(shape_);
    } else {
      WithShape(shape_);
      shape_setuped_ = SetupShape();
    }
    triggerChange();
  }
}

bool FieldModel::SetupShape() {
  shape_.Random();

  int min_y = 16;
  int min_x = 16;
  int max_x = 0;
  for (int i = 0; i < 16; ++i) {
    int x = i % 4;
    int y = i / 4;

    if (shape_.Data[i]) {
      if (y < min_y) {
        min_y = y;
      }
      if (x < min_x) {
        min_x = x;
      }
      if (x > max_x) {
        max_x = x;
      }
    }
  }
  shape_.X = (W - (max_x - min_x + 1)) / 2 - min_x;
  shape_.Y = -min_y;
  if (IsValidShape(shape_, shape_.X, shape_.Y)) {
    WithShape(shape_);
    triggerChange();
    return true;
  }

  return false;
}

bool FieldModel::IsValidShape(Shape &shape, int shapeX, int shapeY) {

  for (int i = 0; i < 16; ++i) {
    int x = shapeX + i % 4;
    int y = H - (shapeY + i / 4) - 1;

    if (shape.Data[i]) {
      if (x < 0 || y < 0) {
        return false;
      }
      if (x >= (int)W || y >= (int)H || data[y * W + x] != 0) {
        return false;
      }
    }
  }
  return true;
}

void FieldModel::SetData(std::size_t x, std::size_t y, int color) {
  data[y * W + x] = color;
}

void FieldModel::FreezeShape(Shape &shape) {

  for (size_t i = 0; i < 16; ++i) {
    int x = shape.X + i % 4;
    int y = H - (shape.Y + i / 4) - 1;

    if (shape.Data[i]) {

      SetData(x, y, shape.Color);
    }
  }

  size_t dest = 0;
  for (int i = dest; i < H; ++i) {
    bool isComplete = true;
    for (size_t j = 0; j < W; ++j) {
      if (!data[i * W + j]) {
        isComplete = false;
        break;
      }
    }
    if (dest != i) {
      std::copy(&data[i * W], &data[i * W + W], &data[dest * W]);
    }
    if (!isComplete) {
      dest++;
    }
  }
}

void FieldModel::WithShape(Shape &shape) {

  for (int i = 0; i < 16; ++i) {
    int x = shape.X + i % 4;
    int y = H - (shape.Y + i / 4) - 1;

    if (shape.Data[i]) {
      SetData(x, y, shape.Color);
    }
  }
}

void FieldModel::ClearShape(Shape &shape) {

  for (int i = 0; i < 16; ++i) {
    int x = shape.X + i % 4;
    int y = H - (shape.Y + i / 4) - 1;

    if (shape.Data[i]) {
      SetData(x, y, 0);
    }
  }
}
