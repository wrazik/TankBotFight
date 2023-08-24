#pragma once

enum class GameState {
        Playing,
        GameOver,
};

class Game {
        public:
        Game();

        void run();

        private:
        void process_events();
        void update();
        void render();

        sf::RenderWindow mWindow;
        GameState mState = GameState::Playing;
        sf::Font mFont;
        sf::Text mText;
};

