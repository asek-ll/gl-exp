#ifndef __KEYBOARD_INPUT_H__
#define __KEYBOARD_INPUT_H__

class KeyBoardInputController {
  bool keys_[1024];
  float keys_pressed_time_[1024];

public:
  void OnKeyDown(int key);
  void OnKeyUp(int key);
};

#endif /* end of include guard: __KEYBOARD_INPUT_H__ */
