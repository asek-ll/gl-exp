#ifndef __FIELD_MODEL_H__
#define __FIELD_MODEL_H__

#include <cstddef>
#include <functional>
#include <vector>

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

private:
  int data[FieldModel::W * FieldModel::H] = {0};
  std::vector<FieldListener> listeners;
};

#endif /* end of include guard: __FIELD_MODEL_H__FIELD-MODEL_H */
