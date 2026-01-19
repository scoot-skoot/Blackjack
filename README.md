# Blackjack CLI Game

A simple command-line Blackjack game implemented in C++.  
The core mechanics allow the player to **hit** or **stand** against a dealer, following classic Blackjack rules.

---

## Overview

This project was originally inspired by a quiz, but the code has since then been refactored extensively to improve modularity and encapsulation.  
The core logic and implementation are my own, guided by the quiz prompts but with custom design choices. I plan to continue to expand the game and add features when I have time.

---

## Design

The game is organized into a few key classes:

- **Card**: Represents a playing card with rank and suit.
- **Deck**: A standard 52-card deck with shuffle and deal operations.
- **Player**: Represents a game participant (dealer or player), managing score and game decisions.
- **Settings**: Contains game constants like bust value and dealer behavior thresholds.

---

## How to Run

1. Build the project with your favorite C++ compiler (C++17 or later required).
2. Run the resulting executable.
3. Follow on-screen prompts to hit (`h`) or stand (`s`) during your turn.
4. The dealer automatically plays after you stand.
5. The game outputs whether you win or lose.

---

## Features and Limitations

- Command-line interface only, no graphics or GUI.
- Basic gameplay: player can only hit or stand.
- Dealer behavior follows typical Blackjack rules (hits until score ≥ 16).
- No betting, splitting, or doubling down.
- No handling of multiple players.

---

## Potential Improvements

- Add betting system and bankroll management.
- Support multiple players or multiplayer mode.
- Implement splitting, doubling down, and insurance.
- Improve input validation and error handling.
- Add unit tests for game logic.

---

## License

This code is free to use and modify.

---

## Acknowledgements

Inspired by the learncpp.com Blackjack quiz, with extensive refactoring and custom implementation by me.

