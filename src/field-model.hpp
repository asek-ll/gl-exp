#ifndef __FIELD_MODEL_H__
#define __FIELD_MODEL_H__

#include <cstddef>
#include <functional>
#include <vector>

#include "shape.hpp"

using FieldListener = std::function<void()>;

class FieldModel {
public:
  static const std::size_t W = 10;
  static const std::size_t H = 18;

  inline void OnChange(FieldListener listener) {
    listeners.push_back(listener);
  }
  inline int GetData(std::size_t x, std::size_t y) {
    return data[y * FieldModel::W + x];
  }

  void Update(float dt);
  FieldModel() { shape_setuped_ = SetupShape(); }

private:
  int data[FieldModel::W * FieldModel::H] = {0};
  std::vector<FieldListener> listeners;
  float since_last_update_;
  Shape shape_;
  bool shape_setuped_;

  void SetData(std::size_t x, std::size_t y, int color);
  bool IsValidShape(Shape &shape, int x, int y);
  void FreezeShape(Shape &shape);
  void WithShape(Shape &shape);
  void ClearShape(Shape &shape);
  bool SetupShape();

  inline void triggerChange() {
    for (auto &listener : listeners) {
      listener();
    }
  }
};

#endif /* end of include guard: __FIELD_MODEL_H_ */
