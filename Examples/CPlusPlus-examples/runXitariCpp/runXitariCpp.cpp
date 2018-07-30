// runXitariCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ale_interface.hpp"
#include "../../../XitariLibraryCSBinding/XitariALE.h"


int main()
{
	//auto ale = new XitariALE("ms_pacman.bin");
	auto ale = new ale::ALEInterface("ms_pacman.bin");

	const auto legal_actions = ale->getLegalActionSet();
	

	// Play 100 episodes
	for (auto episode = 0; episode<100; episode++) {
		float total_reward = 0;
		while (!ale->gameOver()) {
			auto a = legal_actions[rand() % legal_actions.size()];
			// Apply the action and get the resulting reward
			float reward = ale->act(a);
			total_reward += reward;
		}
		std::cout << "Episode " << episode << " ended with score: " << total_reward << std::endl;
		ale->resetGame();
	}

	return 0;
}

