#include "TankHealthBar.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

#include "Files.hpp"
#include "utility.hpp"

constexpr auto HEALTH_BAR_SIZE_WIDTH = 55.0f;
constexpr auto HEALTH_BAR_SIZE_HEIGHT = 18.0f;
constexpr float HEALTHBAR_Y_OFFSET = -50.f;
constexpr unsigned int HEALTHBAR_FONT_SIZE = 10;

TankHealthBar::TankHealthBar(unsigned int total_health)
    : mTotalHealth(total_health), mHealth(total_health) {
  mFont.loadFromFile(files::asset_path() + "DejaVuSans.ttf");
  setup_text();
  setup_bar();
  update_string();
  update_health_size();
}

void TankHealthBar::set_position(const sf::Vector2f& pos) {
  auto new_pos = sf::Vector2f(pos.x, pos.y + HEALTHBAR_Y_OFFSET);
  mText.setPosition(new_pos);
  mBarShape.setPosition(new_pos);
  mHealthShape.setPosition(new_pos);
}

void TankHealthBar::set_health(unsigned int health) {
  mHealth = health;
  update_string();
  update_health_size();
}

void TankHealthBar::draw(sf::RenderWindow& window) {
  window.draw(mHealthShape);
  window.draw(mBarShape);
  window.draw(mText);
}

void TankHealthBar::setup_text() {
  mText.setFont(mFont);
  mText.setCharacterSize(HEALTHBAR_FONT_SIZE);
  mText.setFillColor(sf::Color::Black);
}

void TankHealthBar::setup_bar() {
  mBarShape.setSize({HEALTH_BAR_SIZE_WIDTH, HEALTH_BAR_SIZE_HEIGHT});
  mBarShape.setOrigin(get_center_of_rect(mBarShape.getLocalBounds()));
  mBarShape.setOutlineColor(sf::Color::Black);
  mBarShape.setOutlineThickness(1.0f);
  mBarShape.setFillColor(sf::Color::Transparent);
  mHealthShape.setFillColor(sf::Color::Red);
}

void TankHealthBar::update_string() {
  mText.setString(std::to_string(mHealth) + " / " + std::to_string(mTotalHealth));
  mText.setOrigin(get_center_of_rect(mText.getLocalBounds()));
}

void TankHealthBar::update_health_size() {
  auto health_width = HEALTH_BAR_SIZE_WIDTH * (mHealth / static_cast<float>(mTotalHealth));
  mHealthShape.setSize({health_width, HEALTH_BAR_SIZE_HEIGHT});
  auto health_center = get_center_of_rect(mHealthShape.getLocalBounds());
  auto origin_offset = (HEALTH_BAR_SIZE_WIDTH - health_width) / 2.f;
  mHealthShape.setOrigin(health_center.x + origin_offset, health_center.y);
}
