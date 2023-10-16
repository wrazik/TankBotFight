#include "Tank.hpp"

#include <cmath>
#include <gsl/gsl>

#include "Size.hpp"
#include "utility.hpp"

constexpr int TANK_INITIAL_ROTATION = 180;

Tank::Tank(float x, float y, const TankTextures &textures, std::unique_ptr<Engine> &&engine,
           Sound&& shot_sound, const TracesHandlerConfig &traces_handler_config,
           const std::chrono::milliseconds &shot_cooldown)
    : mPos({x, y}),
      mBody(textures.mBody),
      mTurret(TankTurretTextures{.mTurret = textures.mTurret,
                               .mShotAnimation = textures.mShot,
                               .mMissile = textures.mMissile},
             shot_cooldown, std::move(shot_sound)),
      mEngine(std::move(engine)),
      mTracesHandler(std::make_unique<TracesHandler>(textures.mTracks, mBody.get_sprite(), mPos,
                                                     traces_handler_config)) {
  set_rotation(TANK_INITIAL_ROTATION);
  mBody.get_sprite().setPosition(mPos);
  mTurret.set_position(mPos);
}

Tank::Tank(Tank &&rhs) noexcept
    : mPos(rhs.mPos),
      mCurrentSpeed(rhs.mCurrentSpeed),
      mBody(std::move(rhs.mBody)),
      mTurret(std::move(rhs.mTurret)),
      mEngine(std::move(rhs.mEngine)),
      mTracesHandler(std::make_unique<TracesHandler>(rhs.mTracesHandler->get_trace_texture(),
                                                     mBody.get_sprite(), mPos,
                                                     rhs.mTracesHandler->get_config())),
      mHealth(rhs.mHealth),
      mHealthBar(std::move(rhs.mHealthBar)) {}

Tank &Tank::operator=(Tank &&rhs) noexcept {
  if (this == &rhs) {
    return *this;
  }
  mPos = rhs.mPos;
  mCurrentSpeed = rhs.mCurrentSpeed;
  mBody = std::move(rhs.mBody);
  mTurret = std::move(rhs.mTurret);
  mEngine = std::move(rhs.mEngine);
  mTracesHandler =
      std::make_unique<TracesHandler>(rhs.mTracesHandler->get_trace_texture(), mBody.get_sprite(),
                                      mPos, rhs.mTracesHandler->get_config());
  mHealth = rhs.mHealth;
  mHealthBar = std::move(rhs.mHealthBar);
  return *this;
}

void Tank::set_gear(Gear gear) { mEngine->set_gear(gear); }

void Tank::rotate_body(Rotation r) { mBody.rotate(r); }

void Tank::rotate_turret(Rotation r) { mTurret.rotate(r); }

void Tank::set_rotation(const float angle) {
  mTurret.set_rotation(angle);
  mBody.set_rotation(angle);
}

void Tank::take_damage(unsigned int damage) {
  mHealth -= damage;
  if (mHealth < 0) {
    mHealth = 0;
  }
  mHealthBar.set_health(mHealth);
}

sf::Vector2f Tank::get_position() const { return mPos; }

sf::FloatRect Tank::get_body_rect() const { return mBody.get_sprite().getGlobalBounds(); }

void Tank::update() {
  mBody.update();
  mTurret.update();
  mEngine->update();
  update_position();
  mTracesHandler->update();
}

void Tank::update_position() {
  const auto &delta =
      mEngine->get_position_delta(gsl::narrow_cast<float>(to_radians(mBody.get_rotation())));
  const auto new_pos = mPos + delta;
  if (is_sprite_x_in_board(new_pos.x, mBody.get_sprite())) {
    mPos.x = new_pos.x;
  }
  if (is_sprite_y_in_board(new_pos.y, mBody.get_sprite())) {
    mPos.y = new_pos.y;
  }
  mBody.get_sprite().setPosition(mPos);
  mTurret.set_position(mPos);
  mHealthBar.set_position(mPos);
}

std::optional<Missle> Tank::shoot() { return mTurret.shoot(); }

float Tank::get_current_speed() const { return mEngine->get_current_speed(); }

bool Tank::is_alive() const { return mHealth > 0; }

void Tank::draw(sf::RenderWindow &window) {
  mBody.draw(window);
  mTurret.draw(window);
  draw_tracks(window);
  mHealthBar.draw(window);
}

void Tank::draw_tracks(sf::RenderWindow &window) {
  for (const auto &trace : mTracesHandler->get_traces()) {
    window.draw(trace);
  }
}
