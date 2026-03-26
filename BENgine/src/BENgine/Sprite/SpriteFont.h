// SpriteFont

#ifndef _SpriteFont
#define _SpriteFont

#include <string>
#include <xmllite.h>
#include <map>
#include "BENgineSprite.h"

class Texture;

//A font used for rendering text as sprites.
class SpriteFont
{

public:
	using Key = int;
	using Glyph = BENgineSprite;

private:
	
	Texture* FontTexture;
	using FontMap = std::map< Key, Glyph* >;
	FontMap fontmap;
	std::string Name;

	// Parse the XML file
	void XMLtoCollection(std::string filename);

	// Tool: Reads & converts an XML attribute into an int
	void ElementTextToInt(IXmlReader* pReader, int& out);

public:
	SpriteFont() = delete;

	SpriteFont(const std::string& xmlPath, const std::string& textureKey, const std::string& tgaPath);
	~SpriteFont();
	SpriteFont(const SpriteFont&) = delete;
	SpriteFont& operator=(const SpriteFont&) = delete;

	//Returs the sprite of the char passed in.
	//Parameters:
	//c - the char to get the sprite of.
	Glyph* GetGlyph(char c);
};

#endif _SpriteFont