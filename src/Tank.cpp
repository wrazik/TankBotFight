#include "Tank.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <tuple>

#include "Engine.hpp"
#include "Size.hpp"
#include "TextureStore.hpp"
#include "utility.hpp"

TankPart::TankPart(sf::Texture &texture) {
  mSprite.setTexture(texture);
  const auto [width, height] = texture.getSize();
  mSprite.setOrigin(width / 2.f, height / 2.f);
}

void TankPart::rotate(const Rotation r) { mRotation = r; }

void TankPart::set_rotation(const int angle) { mSprite.setRotation(angle); }

float TankPart::get_rotation() const { return mSprite.getRotation(); }

sf::Sprite &TankPart::get_sprite() { return mSprite; }

void TankPart::update() {
  switch (mRotation) {
    case Rotation::Clockwise:
      mSprite.rotate(10);
      break;
    case Rotation::Counterclockwise:
      mSprite.rotate(-10);
      break;
    case Rotation::None:
      break;
  }
}

void TankPart::draw(sf::RenderWindow &window, const float x, const float y) {
  mSprite.setPosition(x, y);
  window.draw(mSprite);
}

Tank::Tank(float x, float y, sf::Texture &body, sf::Texture &tower, sf::Texture &shot,
           sf::Texture &tracks, std::unique_ptr<Engine> &&engine)
    : mPos({x, y}),
      mBody(body),
      mTower(tower),
      mShot(shot),
      mTracks(tracks),
      mEngine(std::move(engine)) {
  mTower.set_rotation(180);
  mShot.set_rotation(180);
}

Tank::Tank(const Tank &rhs)
    : mPos(rhs.mPos),
      mBody(rhs.mBody),
      mTower(rhs.mTower),
      mShot(rhs.mShot),
      mTracks(rhs.mTracks),
      mEngine(rhs.mEngine->copy()) {}

Tank &Tank::operator=(const Tank &rhs) {
  if (this == &rhs) {
    return *this;
  }
  mPos = rhs.mPos;
  mCurrentSpeed = rhs.mCurrentSpeed;
  mShotStart = rhs.mShotStart;
  mDrawShot = rhs.mDrawShot;
  mBody = rhs.mBody;
  mTower = rhs.mTower;
  mShot = rhs.mShot;
  mTracks = rhs.mTracks;
  mEngine = rhs.mEngine->copy();
  return *this;
}

void Tank::set_gear(Gear gear) { mEngine->set_gear(gear); }

void Tank::rotate_body(Rotation r) {
  mBody.rotate(r);
  mTracks.rotate(r);
}

void Tank::rotate_tower(Rotation r) {
  mTower.rotate(r);
  mShot.rotate(r);
}

void Tank::set_rotation(const int angle) {
  mTower.set_rotation(angle);
  mBody.set_rotation(angle);
  mShot.set_rotation(angle);
  mTracks.set_rotation(angle);
}

sf::Vector2f Tank::get_position() { return mPos; }

void Tank::update() {
  update_track_animations();

  mBody.update();
  mTower.update();
  mShot.update();
  mEngine->update();

  update_position();
  update_shot();
}

void Tank::update_track_animations() {
  auto add_new_animation = [this](const sf::IntRect &texture_rect) {
    mTracksAnimations.emplace_back(std::make_tuple(mPos, mBody.get_rotation(), texture_rect));
  };

  const auto &[x, y, width, height] = mTracks.get_sprite().getTextureRect();
  const float distance = hypot(mEngine->get_position_delta(to_radians(mBody.get_rotation())));
  if (mTracksAnimations.empty()) {
    add_new_animation(sf::Rect{x, y, width, static_cast<int>(distance)});
    return;
  }
  const auto &[newestPos, newestAngle, newestRect] = mTracksAnimations.back();
  if (mBody.get_rotation() != newestAngle) {
    add_new_animation(sf::Rect{x, y, width, static_cast<int>(distance)});
  } else if (newestRect.height + distance > height) {
    std::get<2>(mTracksAnimations.back()) = sf::Rect{x, y, width, height};
    add_new_animation(sf::Rect{x, y, width, static_cast<int>(distance) % height});
  } else {
    // update existing texture height
    // update animation starting position

  }
}

void Tank::update_position() {
  mPos += mEngine->get_position_delta(to_radians(mBody.get_rotation()));
}

void Tank::update_shot() {
  auto now = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - mShotStart);
  if (elapsed > shotAnimationDuration) {
    mDrawShot = false;
  }
}

float Tank::get_current_speed() { return mEngine->get_current_speed(); }

void Tank::shot() {
  mShotStart = std::chrono::system_clock::now();
  mDrawShot = true;
}

float Tank::get_tower_rotation() const { return mTower.get_rotation(); }

void Tank::draw(sf::RenderWindow &window) {
  // sf::Vector2f positionDelta{};
  // for (int i = 1; i < mPositionSnapshots.size(); i++) {
  //   positionDelta += abs(mPositionSnapshots[i - 1].first - mPos);
  //   // direction change
  //   if (mPositionSnapshots[i - 1].second != mPositionSnapshots[i].second) {
  //     positionDelta = abs(mPositionSnapshots[i - 1].first - mPos);
  //   }
  //   mTracks.setRotation(angle);
  //   // window.draw(mTracks);
  // }
  mBody.draw(window, mPos.x, mPos.y);
  mTower.draw(window, mPos.x, mPos.y);
  if (mDrawShot) {
    draw_shot(window);
  }
  draw_tracks(window);
}

void Tank::draw_shot(sf::RenderWindow &window) {
  auto getShotAnimationPosition = [x = mPos.x, y = mPos.y](float towerRotation) {
    return sf::Vector2f{
        x + shotAnimationDistance * static_cast<float>(cos(to_radians(towerRotation - 90))),
        y + shotAnimationDistance * static_cast<float>(sin(to_radians(towerRotation - 90)))};
  };
  auto shotAnimationPosition = getShotAnimationPosition(mTower.get_rotation());
  mShot.draw(window, shotAnimationPosition.x, shotAnimationPosition.y);
}

void Tank::draw_tracks(sf::RenderWindow &window) {
  // auto getTracksAnimations = [this]() {
  //   std::tuple<sf::Vector2f, float, sf::Rect<int>> posAngleRect{};
  //   std::vector<std::tuple<sf::Vector2f, float, sf::Rect<int>>> tracksAnimations{};
  //   auto start = this->mPositionSnapshots.begin();
  //   while (start != this->mPositionSnapshots.end()) {
  //     const auto end = std::adjacent_find(
  //         start, this->mPositionSnapshots.end(),
  //         [](const auto &lhs, const auto &rhs) { return lhs.second != rhs.second; });
  //     auto &[startPos, startAngle] = *start;
  //     const float distance = hypot(startPos - end->first);
  //     const auto &[x, y, width, height] = this->mTracks.get_sprite().getTextureRect();
  //     for (int i = 0; i < distance / height; ++i) {
  //       // dodajemy elementy ale przesuwamy pozycje
  //       tracksAnimations.emplace_back(
  //           std::make_tuple(startPos, start->second, sf::Rect{x, y, width, height}));
  //       startPos = get_pos(startPos, height, startAngle);
  //     }
  //     tracksAnimations.emplace_back(std::make_tuple(
  //         startPos, startAngle, sf::Rect{x, y, width, static_cast<int>(distance) % height}));

  //     start = end;
  //   }

  //   return std::vector{posAngleRect};
  // };
  for (const auto &[pos, angle, rect] : mTracksAnimations) {
    mTracks.set_rotation(angle);
    mTracks.get_sprite().setTextureRect(rect);
    mTracks.draw(window, pos.x, pos.y);
  }
}
