#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include "field-model.hpp"
#include <memory>

enum class Status { PLAYING = 0, FINISHED = 1, PAUSED = 2 };

class GameState {
public:
  inline std::shared_ptr<FieldModel> field_model() { return field_model_; }
  void Update(float dt);

  GameState() : field_model_(std::make_shared<FieldModel>()) {}

private:
  std::shared_ptr<FieldModel> field_model_;
  size_t score;
  Status status;
};

#endif /* end of include guard: __GAME_STATE_H__ */
