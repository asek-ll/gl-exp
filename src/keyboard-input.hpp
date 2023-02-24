#ifndef __KEYBOARD_INPUT_H__
#define __KEYBOARD_INPUT_H__

class KeyBoardInputController {
  bool keys_[1024];


public:
  void Update(float dt);
  void OnKeyDown(int key);
  void OnKeyUp(int key);
};

void KeyBoardInputController::OnKeyDown(int key) {
  if (key < 1024) {
    keys_[key] = true;
  }

}


#endif /* end of include guard: __KEYBOARD_INPUT_H__ */
