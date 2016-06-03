#pragma once
#include "oxygine-framework.h"
#include "json/json.h"
#include <string>

using namespace oxygine;

class Config {
private:
	std::string      _playerName1;
	std::string      _playerName2;
	std::vector<int> _playerKey1;
	std::vector<int> _playerKey2;

	const char* _source;

	Config() {};

public:
	static Config& getInstance(){
		static Config instance; // Guaranteed to be destroyed.
							    // Instantiated on first use.
		return instance;
	}
	Config(Config const&) = delete;
	void operator=(Config const&) = delete;
	
	bool saveConfig();
	bool loadConfig(const char* source);
	std::string getPlayerName(int id);
	std::vector<int> getPlayerKeys(int id);
	void setPlayerName(int id, const std::string &playerName);
	void setPlayerKeys(int id, const std::vector<int> &playerKeys);
	std::string toString();
};