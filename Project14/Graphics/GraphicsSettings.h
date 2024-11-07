#ifndef GRAPHICSSETTINGS
#define GRAPHICSSETTINGS
#include "..//stdafx.h"
class GraphicsSettings
{
public:
	string title;
	bool fullscreen;
	unsigned FrameRateLimit;
	bool Vertical_sync;
	ContextSettings Context_Settings;
	VideoMode resolution;
	vector<VideoMode> VideoModes;

	GraphicsSettings();
	void saveToFile(const string path);
	bool LoadFromFile(const string path);
};
#endif // !GraphicsSettings
