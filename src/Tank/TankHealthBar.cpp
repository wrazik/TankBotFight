#include "TankHealthBar.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

#include "Files.hpp"

constexpr float HEALTHBAR_Y_OFFSET = -50.f;
constexpr unsigned int HEALTHBAR_FONT_SIZE = 10;

TankHealthBar::TankHealthBar(unsigned int total_health)
    : mTotalHealth(total_health), mHealth(total_health) {
  mFont.loadFromFile(files::asset_path() + "DejaVuSans.ttf");
  setup_text();
  update_string();
}

void TankHealthBar::set_position(const sf::Vector2f& pos) {
  mText.setPosition(pos.x, pos.y + HEALTHBAR_Y_OFFSET);
}

void TankHealthBar::set_health(unsigned int health) {
  mHealth = health;
  update_string();
}

void TankHealthBar::draw(sf::RenderWindow& window) { window.draw(mText); }

void TankHealthBar::setup_text() {
  mText.setFont(mFont);
  mText.setCharacterSize(HEALTHBAR_FONT_SIZE);
  mText.setFillColor(sf::Color::Black);
}

void TankHealthBar::update_string() {
  mText.setString(std::to_string(mHealth) + " / " + std::to_string(mTotalHealth));
  sf::FloatRect textRect = mText.getLocalBounds();
  mText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
}
