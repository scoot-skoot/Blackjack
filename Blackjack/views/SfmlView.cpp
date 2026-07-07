#include "SfmlView.h"

#include "../core/card.h"
#include "../core/game_engine.h"

#include <SFML/Graphics.hpp>

#include <array>
#include <optional>
#include <string>
#include <string_view>

namespace
{
	constexpr unsigned windowWidth{ 900 };
	constexpr unsigned windowHeight{ 700 };
	constexpr float cardWidth{ 80.f };
	constexpr float cardHeight{ 112.f };
	constexpr float cardSpacing{ 20.f };

	sf::Color feltColor{ 34, 100, 55 };
	sf::Color cardFaceColor{ 250, 250, 250 };
	sf::Color cardBackColor{ 30, 60, 140 };

	std::string rankLabel(Card::Rank rank)
	{
		return std::string(1, Card::rankValue[rank]);
	}

	std::string suitLabel(Card::Suit suit)
	{
		switch (suit)
		{
		case Card::suit_clubs: return "C";
		case Card::suit_diamonds: return "D";
		case Card::suit_hearts: return "H";
		case Card::suit_spades: return "S";
		default: return "?";
		}
	}

	sf::Color suitColor(Card::Suit suit)
	{
		return (suit == Card::suit_hearts || suit == Card::suit_diamonds)
			? sf::Color::Red
			: sf::Color::Black;
	}

	class Button
	{
	public:
		Button(std::string label, const sf::Font& font, sf::Vector2f position, sf::Vector2f size)
			: label_{ std::move(label) }
			, font_{ &font }
		{
			shape_.setPosition(position);
			shape_.setSize(size);
			shape_.setFillColor(sf::Color(220, 220, 220));
			shape_.setOutlineColor(sf::Color::Black);
			shape_.setOutlineThickness(2.f);

			text_.setFont(font);
			text_.setString(label_);
			text_.setCharacterSize(20);
			text_.setFillColor(sf::Color::Black);

			const sf::FloatRect textBounds = text_.getLocalBounds();
			text_.setOrigin(textBounds.left + textBounds.width / 2.f,
			                textBounds.top + textBounds.height / 2.f);
			text_.setPosition(position.x + size.x / 2.f, position.y + size.y / 2.f);
		}

		void setEnabled(bool enabled)
		{
			enabled_ = enabled;
			shape_.setFillColor(enabled ? sf::Color(220, 220, 220) : sf::Color(150, 150, 150));
		}

		bool contains(sf::Vector2f point) const
		{
			return enabled_ && shape_.getGlobalBounds().contains(point);
		}

		void draw(sf::RenderTarget& target) const
		{
			target.draw(shape_);
			target.draw(text_);
		}

	private:
		std::string label_;
		const sf::Font* font_{};
		sf::RectangleShape shape_{};
		sf::Text text_{};
		bool enabled_{ true };
	};

	class CardSprite
	{
	public:
		CardSprite(const sf::Font& font)
			: font_{ &font }
		{
			body_.setSize({ cardWidth, cardHeight });
			body_.setFillColor(cardFaceColor);
			body_.setOutlineColor(sf::Color::Black);
			body_.setOutlineThickness(2.f);

			back_.setSize({ cardWidth, cardHeight });
			back_.setFillColor(cardBackColor);
			back_.setOutlineColor(sf::Color::Black);
			back_.setOutlineThickness(2.f);
		}

		void setPosition(sf::Vector2f position)
		{
			body_.setPosition(position);
			back_.setPosition(position);
			rankText_.setPosition(position.x + 8.f, position.y + 6.f);
			suitText_.setPosition(position.x + 8.f, position.y + 36.f);
		}

		void setCard(const Card& card)
		{
			card_ = card;
			hasCard_ = true;

			rankText_.setFont(*font_);
			rankText_.setString(rankLabel(card.rank_));
			rankText_.setCharacterSize(22);
			rankText_.setStyle(sf::Text::Bold);
			rankText_.setFillColor(suitColor(card.suit_));

			suitText_.setFont(*font_);
			suitText_.setString(suitLabel(card.suit_));
			suitText_.setCharacterSize(28);
			suitText_.setFillColor(suitColor(card.suit_));
		}

		void setFaceDown(bool faceDown) { faceDown_ = faceDown; }

		void draw(sf::RenderTarget& target) const
		{
			if (faceDown_ || !hasCard_)
			{
				target.draw(back_);
				return;
			}

			target.draw(body_);
			target.draw(rankText_);
			target.draw(suitText_);
		}

	private:
		const sf::Font* font_{};
		std::optional<Card> card_{};
		bool hasCard_{ false };
		bool faceDown_{ false };
		sf::RectangleShape body_{};
		sf::RectangleShape back_{};
		sf::Text rankText_{};
		sf::Text suitText_{};
	};

	sf::Font loadFont()
	{
		sf::Font font;
		const std::array fontPaths{
			"/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
			"/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
			"C:/Windows/Fonts/arial.ttf",
		};

		for (const char* path : fontPaths)
		{
			if (font.loadFromFile(path))
			{
				return font;
			}
		}

		return font;
	}

	void layoutHand(const Hand& hand, bool hideFirstCard, float centerX, float y,
	                std::vector<CardSprite>& sprites, const sf::Font& font)
	{
		const float totalWidth = static_cast<float>(hand.cards.size()) * cardWidth
			+ static_cast<float>(hand.cards.size() > 0 ? hand.cards.size() - 1 : 0) * cardSpacing;
		float startX = centerX - totalWidth / 2.f;

		sprites.clear();
		sprites.reserve(hand.cards.size());

		for (std::size_t i = 0; i < hand.cards.size(); ++i)
		{
			CardSprite sprite{ font };
			sprite.setCard(hand.cards[i]);
			sprite.setFaceDown(hideFirstCard && i == 0);
			sprite.setPosition({ startX + static_cast<float>(i) * (cardWidth + cardSpacing), y });
			sprites.push_back(sprite);
		}
	}

	std::string scoreText(const Hand& hand, bool hideFirstCard)
	{
		if (hideFirstCard && !hand.cards.empty())
		{
			Hand visible{};
			for (std::size_t i = 1; i < hand.cards.size(); ++i)
			{
				visible.addCard(hand.cards[i]);
			}

			if (hand.cards.size() == 1)
			{
				return "Score: ?";
			}

			return "Score: " + std::to_string(visible.score()) + "+?";
		}

		return "Score: " + std::to_string(hand.score());
	}
}

int SfmlView::run(GameEngine& engine)
{
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Blackjack");
	window.setFramerateLimit(60);

	const sf::Font font = loadFont();
	if (font.getInfo().family.empty())
	{
		return 1;
	}

	sf::Text title;
	title.setFont(font);
	title.setString("Blackjack");
	title.setCharacterSize(36);
	title.setFillColor(sf::Color::White);
	title.setPosition(20.f, 20.f);

	sf::Text dealerLabel;
	dealerLabel.setFont(font);
	dealerLabel.setString("Dealer");
	dealerLabel.setCharacterSize(24);
	dealerLabel.setFillColor(sf::Color::White);
	dealerLabel.setPosition(40.f, 90.f);

	sf::Text playerLabel;
	playerLabel.setFont(font);
	playerLabel.setString("Player");
	playerLabel.setCharacterSize(24);
	playerLabel.setFillColor(sf::Color::White);
	playerLabel.setPosition(40.f, 300.f);

	sf::Text dealerScoreText;
	dealerScoreText.setFont(font);
	dealerScoreText.setCharacterSize(20);
	dealerScoreText.setFillColor(sf::Color::White);
	dealerScoreText.setPosition(40.f, 120.f);

	sf::Text playerScoreText;
	playerScoreText.setFont(font);
	playerScoreText.setCharacterSize(20);
	playerScoreText.setFillColor(sf::Color::White);
	playerScoreText.setPosition(40.f, 330.f);

	sf::Text statusText;
	statusText.setFont(font);
	statusText.setCharacterSize(28);
	statusText.setFillColor(sf::Color::Yellow);
	statusText.setPosition(300.f, 560.f);

	Button hitButton{ "Hit", font, { 250.f, 600.f }, { 120.f, 50.f } };
	Button standButton{ "Stand", font, { 400.f, 600.f }, { 120.f, 50.f } };
	Button newRoundButton{ "New Round", font, { 550.f, 600.f }, { 140.f, 50.f } };

	std::vector<CardSprite> dealerSprites;
	std::vector<CardSprite> playerSprites;

	auto refreshUi = [&]()
	{
		const GameState& state = engine.state();
		const bool hideDealerHole = state.phase == Phase::PlayerTurn;

		layoutHand(state.dealerHand, hideDealerHole, windowWidth / 2.f, 150.f, dealerSprites, font);
		layoutHand(state.playerHand, false, windowWidth / 2.f, 380.f, playerSprites, font);

		dealerScoreText.setString(scoreText(state.dealerHand, hideDealerHole));
		playerScoreText.setString(scoreText(state.playerHand, false));

		const bool playerTurn = state.phase == Phase::PlayerTurn;
		const bool finished = state.phase == Phase::Finished;

		hitButton.setEnabled(playerTurn);
		standButton.setEnabled(playerTurn);
		newRoundButton.setEnabled(finished);

		if (finished)
		{
			if (state.dealerHand.isBust())
			{
				statusText.setString(*state.playerWon ? "Dealer busts - You Win!" : "You Lose!");
			}
			else
			{
				statusText.setString(*state.playerWon ? "You Win!" : "You Lose!");
			}
		}
		else if (playerTurn)
		{
			statusText.setString("Your turn - Hit or Stand");
		}
		else
		{
			statusText.setString("Dealer's turn...");
		}
	};

	engine.newRound();
	refreshUi();

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed
				&& event.mouseButton.button == sf::Mouse::Left)
			{
				const sf::Vector2f click{
					static_cast<float>(event.mouseButton.x),
					static_cast<float>(event.mouseButton.y)
				};

				if (hitButton.contains(click))
				{
					engine.hit();
					refreshUi();
				}
				else if (standButton.contains(click))
				{
					engine.stand();
					refreshUi();
				}
				else if (newRoundButton.contains(click))
				{
					engine.newRound();
					refreshUi();
				}
			}
		}

		window.clear(feltColor);
		window.draw(title);
		window.draw(dealerLabel);
		window.draw(playerLabel);
		window.draw(dealerScoreText);
		window.draw(playerScoreText);
		window.draw(statusText);

		for (const CardSprite& sprite : dealerSprites)
		{
			sprite.draw(window);
		}

		for (const CardSprite& sprite : playerSprites)
		{
			sprite.draw(window);
		}

		hitButton.draw(window);
		standButton.draw(window);
		newRoundButton.draw(window);
		window.display();
	}

	return 0;
}
