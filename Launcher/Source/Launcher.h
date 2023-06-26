#pragma once

class Launcher
{
public:
	Launcher();
	~Launcher();
	
	bool UpdatesAvailable();
	void DownloadUpdatesAsync(std::function<void(bool)> callback);
	
	void StartGameLoop();
};