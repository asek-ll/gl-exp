#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include "field-model.hpp"

class GameState {
  FieldModel field_model_;

public:
  inline FieldModel &field_model() { return field_model_; }
  void Update(float dt);
};

#endif /* end of include guard: __GAME_STATE_H__ */
