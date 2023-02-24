#include "field-model.hpp"

#include "iostream"

void FieldModel::Update(float dt) {
  std::cout << "field" << std::endl;
  for (int j = 0; j < H; j++) {
    for (int i = 0; i < W; i++) {
      std::cout << data[j * W + i] << " ";
    }
    std::cout << std::endl;
  }
}
