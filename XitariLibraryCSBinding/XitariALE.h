#pragma once
#include <memory>
#include "../Source/ale_interface.hpp"
#include "circular_queue.h"

// explicit declare
typedef unsigned char uint8_t;

class XitariALE
{
private:
	//ale::ALEInterface* _ale;
	std::unique_ptr<ale::ALEInterface> _ale;

	CircularQueue<std::vector<float>> _h;

	std::vector<float> s;

public:
	XitariALE(const char *rom_file);

	// Converts the palette values to RGB.
	// The shape of the rgb array should be 3 x obs.shape.
	void ale_fillRgbFromPalette(std::vector<unsigned char> & rgb, std::vector<unsigned char> & obs,
		size_t rgb_size, size_t obs_size);

	// Initializes the ALE.
	//ALEInterface *ale_new(const char *rom_file);

	// Deletes the ALE pointer.
	void ale_gc();

	// Applies the action and returns the obtained reward.
	double ale_act(int action);

	// Returns the screen width.
	int ale_getScreenWidth() const;

	// Returns the screen height.
	int ale_getScreenHeight() const;

	// Indicates whether the game ended.
	// Call resetGame to restart the game.
	//
	// Returning of bool instead of int is important.
	// The bool is converted to lua bool by FFI.
	bool ale_isGameOver() const;

	// Resets the game.
	void ale_resetGame();

	// ALE save state
	void ale_saveState();

	// ALE load state
	bool ale_loadState();

	// Fills the obs with raw palette values.
	//
	// Currently, the palette values are even numbers from 0 to 255.
	// So there are only 128 distinct values.
	// void ale_fillObs(std::vector<unsigned char> &obs, size_t obs_size) const;

	// Fills the given array with the content of the RAM.
	// The obs_size should be 128.
	// void ale_fillRamObs(std::vector<unsigned char> & ram, size_t ram_size) const;

	void ale_getScreenRGB(std::vector<unsigned char> & rgb);

	// Returns a 84x84 rescaled YChannel array 
	std::vector<unsigned char> ale_getRescaledYChannelScreen();

	// Returns the 4 latest rescaled YChannel arrays
	std::vector<float> ale_getRescaledYChannelScreenHistory();

	void ale_fillRgb2yFromPalette(std::vector<unsigned char> & y, std::vector<unsigned char> & obs, size_t y_size, size_t obs_size);

	std::vector<unsigned char> ale_resizeBilinearGray(std::vector<unsigned char> & pixels, const int w, const int h, const int w2, const int h2);

	// Returns the number of legal actions
	int ale_numLegalActions();

	// Returns the valid actions for a game
	std::vector<int> ale_legalActions(size_t actions_size);

	// Returns the number of remaining lives for a game
	int ale_livesRemained() const;

	// Used by api to create a string of correct size.
	int ale_getSnapshotLength() const;

	// Save the current state into a snapshot
	// void ale_saveSnapshot(std::vector<unsigned char> & data, size_t length) const;

	// Load a particular snapshot into the emulator
	//void ale_restoreSnapshot(const std::vector<unsigned char> &snapshot,
	//	size_t size);


};



