#include "game.hpp"

const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
    : mWindow(sf::VideoMode({ 1920u, 1080u }), "Air Combat")
    , mTexture("media/textures/Eagle.png")
    , mPlayer(mTexture)
    , mIsMovingUp(false)
    , mIsMovingDown(false)
    , mIsMovingLeft(false)
    , mIsMovingRight(false) {
    mPlayer.setPosition({ 100.f, 100.f });
    };

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
};

void Game::processEvents() {
    while (const std::optional event = mWindow.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            mWindow.close();
        } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            const auto key = keyPressed->scancode;
            const auto key1 = keyPressed->code;
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                mWindow.close();
            } else {
                handlePlayerInput(keyPressed->code, true);
            }
        } else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            handlePlayerInput(keyReleased->code, false);
        }
    }
};

void Game::update(sf::Time deltaTime) {
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp) {
        movement.y -= PlayerSpeed;
    }
    if (mIsMovingDown) {
        movement.y += PlayerSpeed;
    }
    if (mIsMovingLeft) {
        movement.x -= PlayerSpeed;
    }
    if (mIsMovingRight) {
        movement.x += PlayerSpeed;
    }
    mPlayer.move(movement * deltaTime.asSeconds());
};

void Game::render() {
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
};

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Key::W) {
        mIsMovingUp = isPressed;
    } else if (key == sf::Keyboard::Key::S) {
        mIsMovingDown = isPressed;
    } else if (key == sf::Keyboard::Key::A) {
        mIsMovingLeft = isPressed;
    } else if (key == sf::Keyboard::Key::D) {
        mIsMovingRight = isPressed;
    }
}
