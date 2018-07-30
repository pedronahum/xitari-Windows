

#include <cstdint>
#include "XitariALE.h"
#include <mutex>
#include "Control.hxx"
#include "supported/BeamRider.hpp"

//$(SWIG_PATH)\swig.exe -c++ -csharp -D_MSC_VER -Werror -I$(SolutionDir)Source\XITARIv1LibraryDll -I$(SolutionDir)Source -I$(SolutionDir)Source\agents -I$(SolutionDir)Source\common -I$(SolutionDir)Source\controllers -I$(SolutionDir)Source\emucore -I$(SolutionDir)Source\environment -I$(SolutionDir)Source\games -I$(SolutionDir)Source\os_dependent -I$(SolutionDir)Source\zlib -namespace Xitari -outdir  $(SolutionDir)XitariLibraryCSBinding\SwigProxyClasses -dllimport Xitari.Core.CSBinding-$(CntkComponentVersion).dll xitari_cs.i
namespace {
	// workaround taken from https://github.com/facebookresearch/ELF/blob/master/atari/atari_game.h
	// work around bug in ALE.
	// see Arcade-Learning-Environment/issues/86
	std::mutex ale_global_lock;
}


XitariALE::XitariALE(const char* rom_file)
{
	std::lock_guard<std::mutex> lg(ale_global_lock);
	_ale.reset(new ale::ALEInterface(rom_file));

}

void XitariALE::ale_fillRgbFromPalette(std::vector<unsigned char> & rgb, std::vector<unsigned char> & obs, size_t rgb_size, size_t obs_size)
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

void XitariALE::ale_fillRgb2yFromPalette(std::vector<unsigned char> & y, std::vector<unsigned char> & obs, size_t y_size, size_t obs_size)
{
	assert(obs_size >= 0);
	
	int counter = 0;
	for (size_t index = 0; index < obs_size; ++index) {
		uint8_t r, g, b;
		ale::ALEInterface::getRGB(obs[index], r, g, b);

		y[counter++] = static_cast<unsigned char>(round(0.299 * r + 0.587 * g + 0.114 * b));
		
	}
}

void XitariALE::ale_getScreenRGB(std::vector<unsigned char> & rgb)
{
	const int w = _ale->getScreen().width();
	const int h = _ale->getScreen().height();
	const size_t screen_size = w * h;
	auto ale_screen_data = _ale->getScreen().getArray2();
	const size_t obs_size = _ale->getScreen().arraySize();
	XitariALE::ale_fillRgbFromPalette(rgb, ale_screen_data, screen_size, obs_size);
}

std::vector<unsigned char> XitariALE::ale_getRescaledYChannelScreen()
{
	const int w = _ale->getScreen().width();
	const int h = _ale->getScreen().height();
	const size_t screen_size = w * h;
	auto ale_screen_data = _ale->getScreen().getArray2();
	std::vector<unsigned char> yp(static_cast<int>(round(w*h)));
	//const size_t obs_size = _ale->getScreen().arraySize();
	//uint8_t y[84 * 84];
	//uint8_t *yp = y;
	
	XitariALE::ale_fillRgb2yFromPalette(yp, ale_screen_data, screen_size, w*h);
	auto rescaled_y_channel = XitariALE::ale_resizeBilinearGray(yp, w,h, 84, 84);
	return rescaled_y_channel;

}

std::vector<unsigned char> XitariALE::ale_resizeBilinearGray(std::vector<unsigned char> & pixels, const int w,const int h,const int w2, const int h2)
{
	
	std::vector<uint8_t> temp(w2*h2);
	int A, B, C, D, x, y, gray;
	const float x_ratio = ((float)(w - 1)) / w2;
	const float y_ratio = ((float)(h - 1)) / h2;
	float ya, yb;
	int offset = 0;
	for (int i = 0; i<h2; i++) {
		for (int j = 0; j<w2; j++) {
			x = static_cast<int>(x_ratio * j);
			y = static_cast<int>(y_ratio * i);
			float x_diff = (x_ratio * j) - x;
			float y_diff = (y_ratio * i) - y;
			int index = y * w + x;

			// range is 0 to 255 thus bitwise AND with 0xff
			A = pixels[index] & 0xff;
			B = pixels[index + 1] & 0xff;
			C = pixels[index + w] & 0xff;
			D = pixels[index + w + 1] & 0xff;

			// Y = A(1-w)(1-h) + B(w)(1-h) + C(h)(1-w) + Dwh
			gray = static_cast<uint8_t>(round(A * (1 - x_diff) * (1 - y_diff) + B * (x_diff) * (1 - y_diff) +
				C * (y_diff) * (1 - x_diff) + D * (x_diff * y_diff)));

			temp[offset++] = gray;
		}
	}
	return temp;

}

// ReSharper disable once CppMemberFunctionMayBeConst
void XitariALE::ale_gc()
{
	//delete _ale;
	_ale.reset(nullptr);
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

/*
void XitariALE::ale_fillObs(std::vector<unsigned char> & obs, size_t obs_size) const
{
	const ale::ALEScreen& screen = _ale->getScreen();
	size_t h = screen.height();
	size_t w = screen.width();
	assert(obs_size == h * w);

	std::copy(screen.getArray2().begin(), screen.getArray2().end(), obs);
}
*/

/*
void XitariALE::ale_fillRamObs(std::vector<unsigned char> & ram, size_t ram_size) const
{
	const ale::ALERAM& ale_ram = _ale->getRAM();
	assert(ram_size == ale_ram.size());

	const unsigned char* ram_content = ale_ram.array();
	std::copy(ram_content, ram_content + ram_size, ram);
}
*/
// ReSharper disable once CppMemberFunctionMayBeConst
int XitariALE::ale_numLegalActions()
{
	return static_cast<int>(_ale->getMinimalActionSet().size());
}

// ReSharper disable once CppMemberFunctionMayBeConst
std::vector<int> XitariALE::ale_legalActions(size_t actions_size)
{
	int* actions = static_cast<int *>(malloc(sizeof(int) * actions_size));
	const std::vector<enum ale::Action>& legal_actions = _ale->getMinimalActionSet();
	assert(actions_size == legal_actions.size());
	std::copy(legal_actions.begin(), legal_actions.end(), actions);
	std::vector<int> dataVec;
	dataVec.insert(dataVec.end(), &actions[0], &actions[actions_size]);
	return dataVec;
}

int XitariALE::ale_livesRemained() const
{
	return _ale->lives();
}

int XitariALE::ale_getSnapshotLength() const
{

	return static_cast<int>(_ale->getSnapshot().size());
}
/*
void XitariALE::ale_saveSnapshot(std::vector<unsigned char> & data, size_t length) const
{
	std::string result = _ale->getSnapshot();

	assert(length >= result.size() && length > 0);

	if (length < result.size())
		data = NULL;
	else
		result.copy(reinterpret_cast<char *>(data), length);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void XitariALE::ale_restoreSnapshot(const std::vector<unsigned char> & snapshot, size_t size)
{
	assert(size > 0);

	std::string snapshotStr(reinterpret_cast<char const *>(snapshot), size);
	_ale->restoreSnapshot(snapshotStr);
}
*/