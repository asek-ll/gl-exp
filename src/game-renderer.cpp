#include "game-renderer.hpp"

#include "field-renderer.hpp"
#include "game-state.hpp"

GameRenderer::GameRenderer(GameState &state)
    : state_(state), field_renderer_(FieldRenderer(state.field_model())) {}

void GameRenderer::Render(float dt) {
  glClearColor(0.1f, 0.1f, 0.1f, 0.5f);
  glClear(GL_COLOR_BUFFER_BIT);

  field_renderer_.Render(dt);
}

void GameRenderer::Reload() { field_renderer_.Reload(); }
