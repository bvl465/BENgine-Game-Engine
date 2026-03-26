
#include "SpriteFont.h"
#include "../Asset Managers/Texture Manager/TextureManager.h"
#include <xmllite.h>
#include <shlwapi.h>
#include "../Asset Managers/Image Manager/ImageManager.h"

//*********************************************************
// Don't forget to add the associated libs to your project 
// Properties/Linker/Input  -> add these
//		xmllite.lib
//		shlwapi.lib
//*********************************************************

SpriteFont::SpriteFont(const std::string& xmlPath, const std::string& textureKey, const std::string& tgaPath): Name(textureKey)
{
	// <Load associated texture into TextureManager>
	TextureManager::Load(Name, (tgaPath).c_str());
	FontTexture = TextureManager::GetTexture(Name);
	// Parse associated XML file
	
	XMLtoCollection(xmlPath);
}

SpriteFont::~SpriteFont()
{
	for (auto it = fontmap.begin(); it != fontmap.end(); it++)
	{
		delete it->second; //Delete the glyph
	}
	fontmap.clear(); //Clear the map
	// to be completed
}

void SpriteFont::XMLtoCollection(std::string filename)
{
	IXmlReader* reader = nullptr;
	IStream* readStream = nullptr;
	XmlNodeType nodeType;

	CreateXmlReader(IID_PPV_ARGS(&reader), nullptr);

	SHCreateStreamOnFile(filename.c_str(), STGM_READ, &readStream);

	reader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit);
	reader->SetInput(readStream);

	const wchar_t* stringValue = nullptr;
	unsigned int stringSize = 0;

	int key = 0;	// ASCII value
	int x = 0;		// x, y position of the glyph in texture
	int y = 0;
	int w = 0;		// width and height of the gluth in texture
	int h = 0;
	//Rect* rect = new Rect(0.f, 0.f, 0.f, 0.f);

	while (S_OK == reader->Read(&nodeType))
	{
		switch (nodeType)
		{
		case XmlNodeType::XmlNodeType_Element:
		{
			reader->GetQualifiedName(&stringValue, &stringSize);

			if (wcscmp(stringValue, L"character") == 0)
			{
				//Gets ASCII value
				reader->MoveToAttributeByName(L"key", nullptr);
				reader->GetValue(&stringValue, &stringSize);
				key = _wtoi(stringValue);
				//Ignore the warning
				//C6387 'stringValue' could be '0':  this does not adhere to the specification for the function '_wtoi'. 

				
			}
			else if (wcscmp(stringValue, L"x") == 0)
			{
				ElementTextToInt(reader, x);
			}
			else if (wcscmp(stringValue, L"y") == 0)
			{
				ElementTextToInt(reader, y);
			}
			else if (wcscmp(stringValue, L"width") == 0)
			{
				ElementTextToInt(reader, w);
			}
			else if (wcscmp(stringValue, L"height") == 0)
			{
				ElementTextToInt(reader, h);
			}
			else
			{
				//Do nothing
			}
		} break;

		case XmlNodeType::XmlNodeType_EndElement:
		{
			reader->GetQualifiedName(&stringValue, &stringSize);
			assert(stringValue);

			//If we are at the end of "character", we found everything we need for this char
			if (wcscmp(stringValue, L"character") == 0)
			{
				//************************************************************************
				// You now have all the data for a character: key, x, y, w, h
				//
				// Load the associated image in the ImageManager 
				// (its name could be <font name><key> to insure uniqueness)
				//
				// Create the glyph and add it to the fontmap
				// NB: Consider moving the glyph's origin to the *upper-left* corner...
				//*************************************************************************
				
				//rect->x = (float)x;
				//rect->y = (float)y;
				//rect->width = (float)w;
				//rect->height = (float)h;
				std::string imageKey = Name + std::to_string(key);
				ImageManager::Load(imageKey, FontTexture, new Rect((float)(x), (float)(y), (float)(w), (float)(h)));
				Glyph* glyph = new BENgineSprite(imageKey);
				glyph->SetCenter(1.f, 1.f);
				fontmap.insert(std::pair<Key, Glyph*>(key, glyph));
				
				//---------------------------------------------------------------------------
				//DebugMsg::out("Font %s: creating glyph for ASCII %i\n", Name.c_str(), key);
				//---------------------------------------------------------------------------
			}

		} break;

		//Don't care about these
		case XmlNodeType::XmlNodeType_Attribute:
		case XmlNodeType::XmlNodeType_CDATA:
		case XmlNodeType::XmlNodeType_Comment:
		case XmlNodeType::XmlNodeType_DocumentType:
		case XmlNodeType::XmlNodeType_None:
		case XmlNodeType::XmlNodeType_ProcessingInstruction:
		case XmlNodeType::XmlNodeType_Text:
		case XmlNodeType::XmlNodeType_Whitespace:
		case XmlNodeType::_XmlNodeType_Last:
		default:
		{} break;
		}
	}

	//Release COM objects
	if (readStream)
	{
		readStream->Release();
	}

	if (reader)
	{
		reader->Release();
	}
	//delete rect;
}

void SpriteFont::ElementTextToInt(IXmlReader* pReader, int& out)
{
	const wchar_t* stringValue = nullptr;
	UINT stringSize = 0;
	XmlNodeType nodeType;

	while (S_OK == pReader->Read(&nodeType))
	{
		if (nodeType == XmlNodeType::XmlNodeType_Text)
		{
			pReader->GetValue(&stringValue, &stringSize);
			assert(stringValue);

			out = _wtoi(stringValue);
			break;
		}
	}
}

SpriteFont::Glyph* SpriteFont::GetGlyph(char c)
{
	int key = (int)c;
	FontMap::iterator it = fontmap.find(key);
	assert(it != fontmap.end());
	return it->second;
}


