#include "stdafx.h"
#include "GraphicsSettings.h"
GraphicsSettings::GraphicsSettings()
{
	this->title = "DEFAULT";
	this->resolution = VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->Vertical_sync = false;
	this->FrameRateLimit = 120;
	this->Context_Settings.antialiasingLevel = 0;
	this->VideoModes = VideoMode::getFullscreenModes();
}


void GraphicsSettings::saveToFile(const string path)
{
	ofstream ofs(path);
	if (ofs.is_open())
	{
		ofs << this->title;
		ofs << this->resolution.width << " " << this->resolution.height;
		ofs << this->fullscreen;
		ofs << this->FrameRateLimit;
		ofs << Vertical_sync;
		ofs << this->Context_Settings.antialiasingLevel;
	}
	else
	{
		throw "Error";
		ofs.close();
	}
	ofs.close();
}
bool GraphicsSettings::LoadFromFile(const string path)
{
	ifstream ifs(path);
	if (ifs.is_open())
	{
		getline(ifs, this->title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> this->fullscreen;
		ifs >> this->FrameRateLimit;
		ifs >> this->Vertical_sync;
		ifs >> this->Context_Settings.antialiasingLevel;
		return true;
	}
	else
	{
		throw "Error";
		ifs.close();
		return false;
	}
	ifs.close();
}