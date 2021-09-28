#include "TracesHandler.hpp"
#include "utility.hpp"
constexpr int tracesCount = 1;

TracesHandler::TracesHandler(sf::Texture& texture, const sf::Vector2f& pos) : mTracks(texture), mStartingPosition(pos) {}

void TracesHandler::update(const sf::Vector2f& move) {
    sf::Sprite sprite(mTracks);
    auto rect = sprite.getTextureRect();
    sprite.setTextureRect({rect.top, rect.left, rect.width, hypot(move)});
    sprite.setRotation(get_angle(move));
    mTraces.push_back(sprite);
}

const std::deque<sf::Sprite>& TracesHandler::getTraces() { return mTraces; }
