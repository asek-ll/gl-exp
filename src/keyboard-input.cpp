#include "keyboard-input.hpp"

void KeyBoardInputController::OnKeyDown(int key) {
  if (key >= 0 && key < 1024) {
    keys_[key] = true;
    keys_pressed_time_[key] = 0;
  }
}

void KeyBoardInputController::OnKeyUp(int key) {
  if (key >= 0 && key < 1024) {
    keys_[key] = false;
  }
}
