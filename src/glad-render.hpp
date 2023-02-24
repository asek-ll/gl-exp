#ifndef __GLAD_RENDER_H__
#define __GLAD_RENDER_H__

template <typename G> class GladWindow {
public:
  void Render(G game);
};

class KeyboardInput {
private:
  float keys[1024];

public:
  void Press(int key);
  void Release(int key);
};

#endif /* end of include guard: __GLAD_RENDER_H__ */
