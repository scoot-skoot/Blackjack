# Blackjack

A simple Blackjack game implemented in C++ with a headless game engine and two UI options: a console view and an SFML graphical view.

---

## Overview

The game lets you **hit** or **stand** against a dealer following classic Blackjack rules. Game logic is separated from presentation so the same engine powers both the text and graphical interfaces.

---

## Design

```
Blackjack/
├── core/              # Card, Deck, Hand, GameEngine, Settings (no I/O)
├── views/
│   ├── ConsoleView    # Text-based UI
│   └── SfmlView       # Graphical SFML UI
└── main.cpp           # Selects view via command-line flag
```

- **Card**: Playing card with rank and suit.
- **Deck**: Standard 52-card deck with shuffle and deal.
- **Hand**: Tracks dealt cards with soft-ace scoring.
- **GameEngine**: Headless game state machine (`hit`, `stand`, `newRound`).
- **ConsoleView / SfmlView**: Read engine state and send player actions.

---

## How to Run

### CMake (cross-platform)

```bash
cmake -B build -S . -DBLACKJACK_BUILD_SFML=ON
cmake --build build
```

Console (default):

```bash
./build/Blackjack
./build/Blackjack --console
```

Graphical SFML UI:

```bash
./build/Blackjack --sfml
```

On Linux, install SFML first: `sudo apt install libsfml-dev`

### Visual Studio (Windows)

1. Install SFML via [vcpkg](https://vcpkg.io): `vcpkg install sfml`
2. Open `Blackjack.sln` and link SFML in project settings.
3. Run with `--console` or `--sfml` as program arguments.

---

## Features

- Hit / stand gameplay with dealer auto-play (hits below 16).
- Soft ace scoring (ace counts as 11 or 1).
- Console view with input validation.
- SFML view with card rendering, dealer hole card, Hit/Stand/New Round buttons.

## Limitations

- No betting, splitting, doubling down, or insurance.
- Single player only.
- SFML cards are drawn programmatically (no image assets).

---

## License

This code is free to use and modify.

---

## Acknowledgements

Inspired by the learncpp.com Blackjack quiz, with extensive refactoring and custom implementation.
