
#include <cstdint>
#include "XitariALE.h"
#include <allocators>
#include <mutex>
//$(SWIG_PATH)\swig.exe -c++ -csharp -D_MSC_VER -Werror -I$(SolutionDir)Source\XITARIv1LibraryDll -I$(SolutionDir)Source -I$(SolutionDir)Source\agents -I$(SolutionDir)Source\common -I$(SolutionDir)Source\controllers -I$(SolutionDir)Source\emucore -I$(SolutionDir)Source\environment -I$(SolutionDir)Source\games -I$(SolutionDir)Source\os_dependent -I$(SolutionDir)Source\zlib -namespace Xitari -outdir  $(SolutionDir)XitariLibraryCSBinding\SwigProxyClasses -dllimport Xitari.Core.CSBinding-$(CntkComponentVersion).dll xitari_cs.i
namespace {
	// work around bug in ALE.
	// see Arcade-Learning-Environment/issues/86
	std::mutex ALE_GLOBAL_LOCK;
}


XitariALE::XitariALE(const char* rom_file)
{
	std::lock_guard<std::mutex> lg(ALE_GLOBAL_LOCK);
	_ale = new ale::ALEInterface(rom_file);


}

void XitariALE::ale_fillRgbFromPalette(uint8_t* rgb, const uint8_t* obs, size_t rgb_size, size_t obs_size)
{
	assert(obs_size >= 0);
	assert(rgb_size == 3 * obs_size);

	const int r_offset = 0ul;
	const int g_offset = obs_size;
	const int b_offset = 2ul * obs_size;

	for (int index = 0ul; index < obs_size; ++index) {
		uint8_t r, g, b;
		ale::ALEInterface::getRGB(obs[index], r, g, b);

		rgb[r_offset + index] = r;
		rgb[g_offset + index] = g;
		rgb[b_offset + index] = b;
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void XitariALE::ale_gc()
{
	delete _ale;
}

// ReSharper disable once CppMemberFunctionMayBeConst
double XitariALE::ale_act(int action)
{
	assert(action >= static_cast<int>(ale::PLAYER_A_NOOP) &&
		action <= static_cast<int>(ale::PLAYER_A_DOWNLEFTFIRE));
	return _ale->act(static_cast<ale::Action>(action));
}

int XitariALE::ale_getScreenWidth() const
{
	return _ale->getScreen().width();
}

int XitariALE::ale_getScreenHeight() const
{
	return _ale->getScreen().height();
}

bool XitariALE::ale_isGameOver() const
{
	return _ale->gameOver();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void XitariALE::ale_resetGame()
{
	_ale->resetGame();
	assert(!_ale->gameOver());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void XitariALE::ale_saveState()
{
	_ale->saveState();
}

// ReSharper disable once CppMemberFunctionMayBeConst
bool XitariALE::ale_loadState()
{
	return _ale->loadState();
}

void XitariALE::ale_fillObs(uint8_t* obs, size_t obs_size) const
{
	const ale::ALEScreen& screen = _ale->getScreen();
	size_t h = screen.height();
	size_t w = screen.width();
	assert(obs_size == h * w);

	std::copy(screen.getArray().begin(), screen.getArray().end(), obs);
}

void XitariALE::ale_fillRamObs(uint8_t *ram, size_t ram_size) const
{
	const ale::ALERAM& ale_ram = _ale->getRAM();
	assert(ram_size == ale_ram.size());

	const unsigned char* ram_content = ale_ram.array();
	std::copy(ram_content, ram_content + ram_size, ram);
}

// ReSharper disable once CppMemberFunctionMayBeConst
int XitariALE::ale_numLegalActions()
{
	return static_cast<int>(_ale->getMinimalActionSet().size());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void XitariALE::ale_legalActions(int *actions,
	size_t actions_size)
{
	const std::vector<enum ale::Action>& legal_actions = _ale->getMinimalActionSet();
	assert(actions_size == legal_actions.size());
	std::copy(legal_actions.begin(), legal_actions.end(), actions);
}

int XitariALE::ale_livesRemained() const
{
	return _ale->lives();
}

int XitariALE::ale_getSnapshotLength() const
{
	return static_cast<int>(_ale->getSnapshot().size());
}

void XitariALE::ale_saveSnapshot(uint8_t* data, size_t length) const
{
	std::string result = _ale->getSnapshot();

	assert(length >= result.size() && length > 0);

	if (length < result.size())
		data = NULL;
	else
		result.copy(reinterpret_cast<char *>(data), length);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void XitariALE::ale_restoreSnapshot(const uint8_t* snapshot, size_t size)
{
	assert(size > 0);

	std::string snapshotStr(reinterpret_cast<char const *>(snapshot), size);
	_ale->restoreSnapshot(snapshotStr);
}