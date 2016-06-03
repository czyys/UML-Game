#include "Config.h"

bool Config::loadConfig(const char* source) {
	file::buffer fileData;

	// save path to the file
	this->_source = source;

	// read into the buffer if exists
	if(!file::exists(source)) {
		log::messageln("config file does not exist");
		return false;
	}
	
	// read file
	file::read(source, fileData);
	
	// parse file as json
	Json::Reader jreader;
	Json::Value  jvalue;
	
	jreader.parse((char*)&fileData.front(), (char*)&fileData.front() + fileData.size(), jvalue, false);

	// get data from file
	// game data
	this->_playerName1 = jvalue["game"]["playerName1"].asString();
	this->_playerName2 = jvalue["game"]["playerName2"].asString();

	// prepare memory to save keycodes
	this->_playerKey1.resize(5);
	this->_playerKey2.resize(5);

	// get player keys
	char* keyName[] = { "key_up", "key_right", "key_down", "key_left", "key_shot" };
	for (unsigned i = 0; i < 5; i++) {
		this->_playerKey1[i] = jvalue["player1"][keyName[i]].asInt();
		this->_playerKey2[i] = jvalue["player2"][keyName[i]].asInt();
	}
	
	return true;
};

bool Config::saveConfig() {
	Json::Value jvalue;
	Json::FastWriter jwriter;

	// if source is not defined return false
	if (this->_source == "") return false;

	// game settings
	jvalue["game"]["playerName1"] = this->_playerName1;
	jvalue["game"]["playerName2"] = this->_playerName2;

	// game keys
	char* keyName[] = { "key_up", "key_right", "key_down", "key_left", "key_shot" };
	for (unsigned i = 0; i < 5; i++) {
		jvalue["player1"][keyName[i]] = this->_playerKey1[i];
		jvalue["player2"][keyName[i]] = this->_playerKey2[i];
	}

	std::string confFile = jwriter.write(jvalue);
	file::write(this->_source, confFile.c_str(), confFile.size());

	return true;
};

std::string Config::getPlayerName(int id) {
	if (id == 0) return _playerName1;
	return _playerName2;
}

std::vector<int> Config::getPlayerKeys(int id) {
	if (id == 0) return _playerKey1;
	return _playerKey2;
}

void Config::setPlayerName(int id, const std::string &playerName){
	if (id == 0) {
		_playerName1 = playerName;
		return;
	}

	_playerName2 = playerName;
};

/**
	Set new player keys to game config
	@param: id			int          user id
			playerKeys  vector<int>  new player keys

	@note: it's very importat to pass keys in correct ordering
		   keyUp    = playerKeys[0]
		   keyRight = playerKeys[1]
		   keyDown  = playerKeys[2]
		   keyLeft  = playerKeys[3]
		   keyShot  = playerKeys[4]

	@return: void
*/
void Config::setPlayerKeys(int id, const std::vector<int> &playerKeys){
	if (id == 0) {
		_playerKey1 = playerKeys;
		return;
	}

	_playerKey2 = playerKeys;
};

std::string Config::toString(){
	std::string output;
	
	output.append("Aircraft Config\n\n[game]\n");
	output.append("Player1 name: ").append(this->_playerName1);
	output.append("\nPlayer2 name: ").append(this->_playerName2);
	output.append("\n\n[player 1]\n");
	output.append("key up: ").append(std::to_string(this->_playerKey1[0]));
	output.append("\nkey right: ").append(std::to_string(this->_playerKey1[1]));
	output.append("\nkey down: ").append(std::to_string(this->_playerKey1[2]));
	output.append("\nkey left: ").append(std::to_string(this->_playerKey1[3]));
	output.append("\nkey shot: ").append(std::to_string(this->_playerKey1[4]));
	output.append("\n\n[player 2]\n");
	output.append("key up: ").append(std::to_string(this->_playerKey2[0]));
	output.append("\nkey right: ").append(std::to_string(this->_playerKey2[1]));
	output.append("\nkey down: ").append(std::to_string(this->_playerKey2[2]));
	output.append("\nkey left: ").append(std::to_string(this->_playerKey2[3]));
	output.append("\nkey shot: ").append(std::to_string(this->_playerKey2[4]));

	return output;
};