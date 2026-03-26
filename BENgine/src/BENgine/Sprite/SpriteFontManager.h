//Ben La Monica
#pragma once
#ifndef _SpriteFontManager
#define _SpriteFontManager
#include <map>

class SpriteFont;

//Manages the creation, loading, retrieval, storage, and deletion of Models.
class SpriteFontManager
{
public:
	friend class SpriteFontManagerAttorney;

	// Creates a SpriteFont from the xml file at xmlPath and the texture from the tgaPath. T
	// The texture is then loaded into the TextureManager storageMap with textureKey and
	// the SpriteFont is loaded into the SpriteFontManager storageMap with spriteFontKey.
	// Parameters:
	// spriteFontKey - The key to associate with the SpriteFont in the storageMap. (Must be unique)
	// xmlPath - The file path of the .xml file to create the SpriteFont from.
	// textureKey - The key to associate with the SpriteFont's texture in the TextureManager storageMap. (Must be unique)
	// tgaPath - The file path of the .tga file to create the SpriteFont's texture from.
	static void Load(const std::string& spriteFontKey, const std::string& xmlPath, const std::string& textureKey, const std::string& tgaPath); //used for files

	//Searches the storageMap for key and returns a pointer to the SpriteFont associated with that key.
	// Parameters:
	// key - The key assoiated with the SpriteFont to search for in the storageMap.
	static SpriteFont* GetSpriteFont(const std::string& key);

private:

	SpriteFontManager();
	SpriteFontManager(const SpriteFontManager&) = delete;
	SpriteFontManager& operator=(const SpriteFontManager&) = delete;
	~SpriteFontManager() = default;
	static SpriteFontManager& Instance(); // Access reference (all public methods will be static)

	//Deletes the instance of the SpriteFontManager and all SpriteFonts stored in the storageMap. Accessed by BENgine through SpriteFontManagerAttorney.
	static void Delete(); //MUST be called by attorney and NO ONE ELSE

	void privLoad(const std::string& spriteFontKey, const std::string& xmlPath, const std::string& textureKey, const std::string& tgaPath);

	SpriteFont* privGetSpriteFont(const std::string& key);


	static SpriteFontManager* ptrInstance;

	//File location for font xml file
	const std::string defaultPath;

	///Used to override the default path used in TextureManager
	const std::string alteredTexturePath;

	//Map that SpriteFonts are loaded into and retrieved from. The key is the name the user assigns the SpriteFont, and the value is a pointer to the SpriteFont.
	std::map<std::string, SpriteFont*> storageMap;


};
#endif _SpriteFontManager