#include <iostream>

#include "views/ConsoleView.h"
#ifdef BLACKJACK_HAS_SFML
#include "views/SfmlView.h"
#endif

#include "core/game_engine.h"

#include <cstring>

namespace
{
	void printUsage(const char* programName)
	{
		std::cout << "Usage: " << programName << " [--console | --sfml]\n"
		          << "  --console  Run the text-based game (default)\n"
		          << "  --sfml     Run the graphical SFML UI\n";
	}
}

int main(int argc, char* argv[])
{
	bool useSfml{ false };

	for (int i = 1; i < argc; ++i)
	{
		if (std::strcmp(argv[i], "--sfml") == 0)
		{
			useSfml = true;
		}
		else if (std::strcmp(argv[i], "--console") == 0)
		{
			useSfml = false;
		}
		else if (std::strcmp(argv[i], "--help") == 0 || std::strcmp(argv[i], "-h") == 0)
		{
			printUsage(argv[0]);
			return 0;
		}
		else
		{
			std::cerr << "Unknown argument: " << argv[i] << '\n';
			printUsage(argv[0]);
			return 1;
		}
	}

	GameEngine engine{};

	if (useSfml)
	{
#ifdef BLACKJACK_HAS_SFML
		return SfmlView::run(engine);
#else
		std::cerr << "SFML UI was not built. Reconfigure with BLACKJACK_BUILD_SFML=ON.\n";
		return 1;
#endif
	}

	return ConsoleView::run(engine);
}
