#include "TankFactory.hpp"

#include "Random.hpp"
#include "SquareRootEngine.hpp"

Tank TankFactory::Random(TextureStore& store, float x, float y, Sound& shot_sound) {
  using namespace std::string_literals;
  const sf::IntRect TRACKS_TEXTURE_RECT = {0, 0, 37, 48};
  constexpr int STEP_COUNT = 70;
  constexpr float MAX_SPEED = 5.f;
  auto& body_texture = store.get_texture(one_of("tankBody_red.png"s, "tankBody_dark.png"s,
                                                "tankBody_blue.png"s, "tankBody_green.png"s));
  body_texture.setSmooth(true);
  auto& tower_texture =
      store.get_texture(one_of("tankDark_barrel2_outline.png", "tankRed_barrel2_outline.png",
                               "tankGreen_barrel2_outline.png", "tankBlue_barrel2_outline.png"));
  tower_texture.setSmooth(true);
  auto& shot_texture = store.get_texture("shotOrange.png");
  shot_texture.setSmooth(true);
  auto& tracks_texture = store.get_texture("tracksSmall.png", TRACKS_TEXTURE_RECT);
  tracks_texture.setSmooth(true);
  tracks_texture.setRepeated(true);
  return Tank(x, y, body_texture, tower_texture, shot_texture, tracks_texture,
              std::make_unique<SquareRootEngine>(STEP_COUNT, MAX_SPEED),
              TracesHandlerConfig{.mMaxTraceAge = 50, .mDecayRate = 0.1f});
}
