//Ben La Monica
#include "SpriteFontManager.h"
#include "SpriteFont.h"

SpriteFontManager* SpriteFontManager::ptrInstance = nullptr;

SpriteFontManager::SpriteFontManager() : defaultPath("../Assets/Fonts/"), alteredTexturePath("../Fonts/")
{
	
}


void SpriteFontManager::Load(const std::string& spriteFontKey, const std::string& xmlPath, const std::string& textureKey, const std::string& tgaPath)
{
	Instance().privLoad(spriteFontKey, xmlPath, textureKey, tgaPath);
}

SpriteFont* SpriteFontManager::GetSpriteFont(const std::string& key)
{
	return Instance().privGetSpriteFont(key);
}

void SpriteFontManager::Delete()
{
	//Check if it is nullptr because there may be an instance where the user never uses a sprite font so this wouldn't be created
	//THAT BEING SAID... When the program stops running this is always called regardless as of 1/13/2025
	if (ptrInstance != nullptr) {
		std::map< std::string, SpriteFont*>::iterator itEnd = ptrInstance->storageMap.end();
		for (std::map< std::string, SpriteFont*>::iterator it = ptrInstance->storageMap.begin(); it != itEnd; ++it) {
			delete it->second;
		}
		//I use clear here instead of calling erase while iterating through because a map is set up as a red black tree and 
		// every time you erase the tree rebalances. I would HOPE the implementation of erase is more efficient than that
		// but I have yet to check.
		//     /\   /\
		//    |  | |  |      Wake up, Ben...
		//     \ --- /       The Matrix has you...
		//    / | _ | \      Don't follow the white rabbit...
		//    \(= X =)/      Knock, knock, Ben.
		//     '~~~~~'
		//     / L_ \`\
		//   (\`~._)(_/
		//    (..)_; )_
		//    '--' `---'
		
		ptrInstance->storageMap.clear();
		delete ptrInstance;
		ptrInstance = nullptr;
	}
}

void SpriteFontManager::privLoad(const std::string& spriteFontKey, const std::string& xmlPath, const std::string& textureKey, const std::string& tgaPath)
{
	std::map< std::string, SpriteFont*>::iterator it = storageMap.find(spriteFontKey);
	if (it != storageMap.end()) {
		//Using the same key multiple times throw an error
		throw std::invalid_argument("Key " + spriteFontKey + " is already used to define a SpriteFont.");
	}
	else {
		//Creates a SpriteFont and adds its pointer to the map with the specified key
		storageMap[spriteFontKey] = new SpriteFont((defaultPath + xmlPath).c_str(), textureKey, (alteredTexturePath + tgaPath).c_str()); //SpriteFont.h doesn't have any constructors with a std::string for its parameters.
	}
}


SpriteFontManager& SpriteFontManager::Instance()
{
	//part of singleton set up
	if (ptrInstance == nullptr) {
		ptrInstance = new SpriteFontManager();
	}
	return *ptrInstance;
}


SpriteFont* SpriteFontManager::privGetSpriteFont(const std::string& key) //returns a s
{
	std::map< std::string, SpriteFont*>::iterator it = storageMap.find(key);
	if (it == storageMap.end()) {
		//Key not in the storageMap
		throw std::invalid_argument("Key " + key + " could not be found.");
	}
	else {
		return it->second; //returns the SpriteFont
	}
}
