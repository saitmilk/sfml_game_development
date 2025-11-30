#include <SFML/Graphics.hpp>

class Game {
public:
	Game() : mWindow(sf::VideoMode({ 1920u, 1080u }), "Air Combat"), mPlayer(40.f) {
		mWindow.setFramerateLimit(144);
		mPlayer.setPosition({ 100.f, 100.f });
		mPlayer.setFillColor(sf::Color::Magenta);
	};

	void run() {
		while (mWindow.isOpen())
		{
			processEvents();
			update();
			render();
		}
	};

private:
	void processEvents() {
		while (const std::optional event = mWindow.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				mWindow.close();
			}
		}
	};

	void update() {
	};

	void render() {
		mWindow.clear();
		mWindow.draw(mPlayer);
		mWindow.display();
	};

private:
	sf::RenderWindow mWindow;
	sf::CircleShape mPlayer;
};

int main()
{
	Game game;
	game.run();
}