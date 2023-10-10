#include "TankFactory.hpp"

#include "Random.hpp"
#include "Sound.hpp"
#include "SquareRootEngine.hpp"
#include "Tank/Tank.hpp"
#include "TextureStore.hpp"

std::unique_ptr<Tank> TankFactory::Random(TextureStore& store, const float x, const float y,
                                          const Sound& shot_sound) {
  using namespace std::string_literals;
  const sf::IntRect TRACKS_TEXTURE_RECT = {0, 0, 37, 48};
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
  auto& missile_texture = store.get_texture("bulletDark3.png");
  missile_texture.setSmooth(true);

  return std::make_unique<Tank>(x, y,
                                TankTextures{.mBody = body_texture,
                                             .mTower = tower_texture,
                                             .mShot = shot_texture,
                                             .mTracks = tracks_texture,
                                             .mMissile = missile_texture},
                                std::make_unique<SquareRootEngine>(
                                    SquareRootEngineConfig{.mStepCount = 70, .mMaxSpeed = 5.f}),
                                shot_sound,
                                TracesHandlerConfig{.mMaxTraceAge = 50, .mDecayRate = 0.1f});
}
