#ifndef _SpriteString
#define _SpriteString
//#include <string>
#include <list>
#include <string>
#include "AzulCore.h"
class BENgineSprite;
class SpriteFont;
class SpriteString
{
public:

	using Glyph = BENgineSprite;
	using GlyphCollection = std::list<Glyph*>;
	SpriteString() = delete;
	SpriteString(const SpriteString&) = delete;
	SpriteString& operator=(const SpriteString&) = delete;
	~SpriteString() = default;



	////pre optimization that saves a whopping 4 bytes at the expense of the users sanity
	////I can implement this later.
	//enum StringOrientation { 
	//	LeftJustifiedAbsolutePosition,
	//	RightJustificationAbsolutePosition,
	//	CenteredAbsolutePosition,
	//
	//	LeftJustifiedRelativePosition,
	//	RightJustificationRelativePosition,
	//	CenteredRelativePosition
	//};



	enum Alignment
	{
		Left,
		Right,
	};

	enum AngleUnit {
		Degrees,
		Radians
	};

	enum ScaleType {
		ScaleFactor,
		ScalePixel
	};

	enum PositionType {
		Absolute,
		Relative
	};



	SpriteString(std::string fontKey, std::string message, PositionType positionType, float x, float y, Alignment messageAlignment);
	//SpriteString(std::string fontKey, std::string message, Alignment messageAlignment, PositionType positionType, float x, float y, AngleUnit angleUnit, float angle, ScaleType scaleType, float scaleWidth, float scaleHeight);



	//Pass a float value between 0 and 1 for x and y. The value passed is treated as a percentage of the window.
	//Example
	//If the window width is 200 pixels and the window height is 100, passing .5 for x and .5 for y would result
	//in the position of the sprite in pixels on the window being 100 x and 50 y.
	void SetPositionRelative(const float x, const float y);
	void TransformPositionRelative(const float x, const float y);

	void SetPositionAbsolute(const float x, const float y);
	void TransformPositionAbsolute(const float x, const float y);

	//void SetScaleFactor(float x, float y);

	//Sets the absolute pixel position of the sprite on the window.
	//void SetScalePixel(float x, float y);

	//Get the original width of the sprite
	float GetWidth() const;

	//Get the original height of the sprite
	float GetHeight() const;

	//Returns angle in radians
	//float GetAngle() const;

	//Returns the relative scale of the sprite in the x direction
	//float GetScaleX() const;

	//Returns the relative scale of the sprite in the y direction
	//float GetScaleY() const;

	//used when updating what to display
	void ChangeString(std::string newMessage);

	void SetAlignment(Alignment newAlignment);

	void Render(Camera* camera); //Camera was not included in the class diagram from class but it was in the sprite class diagram from class so I am including it.

private:
	//std::string string;
	GlyphCollection text; //The text to be displayed

	//StringOrientation orientation; //Defines the texts alignment and how position is defined by the text.

	Alignment alignment; //Defines the texts alignment

	//PositionType positionType; //Defines how the text is positioned

	//float scaleX; //The scale of the text in the x direction
	//float scaleY; //The scale of the text in the y direction

	float posX;
	float posY;

	float width;
	float height;

	float angle;

	SpriteFont* font;
};

#endif _SpriteString