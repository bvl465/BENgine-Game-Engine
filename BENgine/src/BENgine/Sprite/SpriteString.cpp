//#include "Glyph.h"
#include "SpriteFontManager.h"
#include "SpriteString.h"
#include "BENgineSprite.h"
#include "SpriteFont.h"
#include "../BENgine.h"
SpriteString::SpriteString(std::string fontKey, std::string message, PositionType positionType, float x, float y, Alignment messageAlignment) : posX(x), posY(y), alignment(messageAlignment)
{
	angle = 0.f;

	font = SpriteFontManager::GetSpriteFont(fontKey); //Get the font from the manager
	if (positionType == PositionType::Relative)
	{
		posX = BENgine::GetWidth() * x;
		posY = BENgine::GetHeight() * y;
	}
	else if (positionType == PositionType::Absolute)
	{
		posX = x;
		posY = y;
	}
	float nextX = posX;
	float nextY = posY;

	int messageLength = message.length();

	Glyph* glyph;
	for (int i = 0; i < messageLength; i++)
	{
		glyph = font->GetGlyph(message.at(i));
		glyph->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
		text.push_back(glyph);
		nextX += glyph->GetWidth(); // add cell width for left alignment

		// we must update the next position ourselves
	}
	width = nextX - posX; // set the width of the string

	if (text.size() > 0) {
		height = text.front()->GetHeight();
	}
	else {
		height = 0.f;
	}
	
	
	//if (alignment == Alignment::Left) {
	//
	//	for (int i = 0; i < messageLength; i++)
	//	{
	//		glyph = font->GetGlyph(message.at(i));
	//		glyph->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
	//		text.push_front(glyph);
	//		nextX += glyph->GetWidth(); // add cell width for left alignment
	//
	//		// we must update the next position ourselves
	//	}
	//	width = nextX - posX; // set the width of the string
	//
	//	if (text.size() > 0) {
	//		height = text.front()->GetHeight();
	//	}
	//	else {
	//		height = 0.f;
	//	}
	//}
	//else{
	//	messageLength -= 1;
	//	for (int i = messageLength; i >= 0; i--) //start from the end of the string when using right alignment
	//	{
	//		glyph = font->GetGlyph(message.at(i));
	//		nextX -= glyph->GetWidth();
	//		glyph->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
	//		text.push_front(glyph);
	//	}
	//	width = posX - nextX; // set the width of the string
	//
	//	if (text.size() > 0) {
	//		height = text.front()->GetHeight();
	//	}
	//	else {
	//		height = 0.f;
	//	}
	//}
	// 
	//else if (alignment == Right) {
	//	messageLength -= 1;
	//	for (int i = messageLength; i >= 0; i--) //start from the end of the string when using right alignment
	//	{
	//		glyph = font->GetGlyph(message.at(i));
	//		nextX -= glyph->GetWidth();
	//		glyph->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
	//		text.push_front(glyph);
	//	}
	//	width = posX - nextX; // set the width of the string
	//	height = text.front()->GetHeight();
	//}
	//else {
	//	//to make this compile because I will be making a centered alignment later
	//	height = 0.f;
	//	width = 0.f;
	//}
}


void SpriteString::SetPositionRelative(const float x, const float y)
{
	//posX = BENgine::GetWidth() * x;
	//posY = BENgine::GetHeight() * y;
	//float nextX = posX;
	//float nextY = posY;
	//int textLength = text.size();
	//auto it = text.begin(); // Use an iterator to access elements
	////Maybe use vector math instead. To do so I would just 
	////subtract the current position from the new position
	////then add that vector to the current position of each glyph.
	////The current math only works when the sprite isn't rotated.
	////The nextX will only be equal to the current glyphs width
	////IF it is perfectly aligned with the x axis.
	//
	//
	//if (alignment == Alignment::Left) {
	//    for (int i = 0; i < textLength; i++)
	//    {
	//        (*it)->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
	//        nextX += (*it)->GetWidth(); // add cell width for left alignment
	//        ++it; // Move to the next glyph
	//    }
	//}
	//else if (alignment == Right) {
	//    textLength -= 1;
	//    it = text.end(); // Start from the end of the list
	//    for (int i = textLength; i >= 0; i--) //start from the end of the string when using right alignment
	//    {
	//        --it;
	//        nextX -= (*it)->GetWidth();
	//        (*it)->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
	//    }
	//}

	const float transX = (BENgine::GetWidth() * x) - posX;
	const float transY = (BENgine::GetHeight() * y) - posY;
	GlyphCollection::iterator it;
	for (it = text.begin(); it != text.end(); it++) {
		(*it)->TransformPositionAbsolute(transX, transY);
	}
	posX = BENgine::GetWidth() * x;
	posY = BENgine::GetHeight() * y;
}

void SpriteString::TransformPositionRelative(const float x, const float y)
{
	GlyphCollection::iterator it;
	for (it = text.begin(); it != text.end(); it++) {
		(*it)->TransformPositionRelative(x, y);
	}
	posX += x * BENgine::GetWidth();
	posY += y * BENgine::GetHeight();
}


void SpriteString::SetPositionAbsolute(const float x, const float y)
{

	////Maybe use vector math instead. To do so I would just 
	////subtract the current position from the new position
	////then add that vector to the current position of each glyph.
	////The current math only works when the sprite isn't rotated.
	////The nextX will only be equal to the current glyphs width
	////IF it is perfectly aligned with the x axis.
	//posX = x;
	//posY = y;
	//
	//
	//float nextX = posX;
	//float nextY = posY;
	//int textLength = text.size();
	//auto it = text.begin(); // Use an iterator to access elements
	//
	//if (alignment == Alignment::Left) {
	//	for (int i = 0; i < textLength; i++)
	//	{
	//		(*it)->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
	//		nextX += (*it)->GetWidth(); // add cell width for left alignment
	//		++it; // Move to the next glyph
	//	}
	//}
	//else if (alignment == Right) {
	//	textLength -= 1;
	//	it = text.end(); // Start from the end of the list
	//	for (int i = textLength; i >= 0; i--) //start from the end of the string when using right alignment
	//	{
	//		--it;
	//		nextX -= (*it)->GetWidth();
	//		(*it)->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
	//	}
	//}


	//maybe just have float x and float y not be const and just do x -= posX and y -= posY and then replace transX and transY with x and y respectively
	const float transX = x - posX;
	const float transY = y - posY;
	GlyphCollection::iterator it;
	for (it = text.begin(); it != text.end(); it++) {
		(*it)->TransformPositionAbsolute(transX, transY);
	}
	posX = x;
	posY = y;

}

void SpriteString::TransformPositionAbsolute(const float x, const float y)
{
	GlyphCollection::iterator it;
	for (it = text.begin(); it != text.end(); it++) {
		(*it)->TransformPositionAbsolute(x, y);
	}
	posX += x;
	posY += y;
}

void SpriteString::ChangeString(std::string newMessage)
{

	float nextX = posX;
	float nextY = posY;

	int messageLength = newMessage.length();
	text.clear(); // Clear the current text before changing the string
	Glyph* glyph;

	for (int i = 0; i < messageLength; i++)
	{
		glyph = font->GetGlyph(newMessage.at(i));
		glyph->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
		text.push_back(glyph);
		nextX += glyph->GetWidth(); // add cell width for left alignment

		// we must update the next position ourselves
	}
	width = nextX - posX; // set the width of the string

	//if (alignment == Alignment::Left) {
	//
	//	for (int i = 0; i < messageLength; i++)
	//	{
	//		glyph = font->GetGlyph(newMessage.at(i));
	//		glyph->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
	//		text.push_front(glyph);
	//		nextX += glyph->GetWidth(); // add cell width for left alignment
	//
	//		// we must update the next position ourselves
	//	}
	//	width = nextX - posX; // set the width of the string
	//}
	//else if (alignment == Right) {
	//	messageLength -= 1;
	//	for (int i = messageLength; i >= 0; i--) //start from the end of the string when using right alignment
	//	{
	//		glyph = font->GetGlyph(newMessage.at(i));
	//		nextX -= glyph->GetWidth();
	//		glyph->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
	//		text.push_front(glyph);
	//	}
	//	width = posX - nextX; // set the width of the string
	//}

}

void SpriteString::SetAlignment(Alignment newAlignment)
{
	alignment = newAlignment;
	//if (alignment != newAlignment) {
	//	alignment = newAlignment;
	//	float nextX = posX;
	//	float nextY = posY;
	//	int textLength = text.size();
	//	auto it = text.begin();
	//	switch (alignment) {
	//	case Alignment::Left:
	//
	//		for (int i = 0; i < textLength; i++)
	//		{
	//			(*it)->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
	//			nextX += (*it)->GetWidth(); // add cell width for left alignment
	//			++it; // Move to the next glyph
	//
	//		}
	//		break;
	//	case Alignment::Right:
	//		it = text.end(); // Start from the end of the list
	//		textLength -= 1;
	//		for (int i = textLength; i >= 0; i--) //start from the end of the string when using right alignment
	//		{
	//			--it;
	//			nextX -= (*it)->GetWidth();
	//			(*it)->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
	//		}
	//		break;
	//	//case Alignment::Center:
	//	//
	//	//	break;
	//	}
	//}
}

void SpriteString::Render(Camera* camera)
{

	float nextX = posX;
	float nextY = posY;
	int textLength = text.size();
	auto it = text.begin();

	switch (alignment) {
	case Alignment::Right:

		for (int i = 0; i < textLength; i++)
		{
			(*it)->SetPositionAbsolute(nextX - width, nextY); // set the position of the glyph
			(*it)->Render(camera);
			nextX += (*it)->GetWidth(); // add cell width for left alignment
			++it; // Move to the next glyph

		}
		break;
	case Alignment::Left:
		//it = text.end(); // Start from the end of the list
		for (int i = 0; i < textLength; i++)
		{
			(*it)->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
			(*it)->Render(camera);
			nextX += (*it)->GetWidth(); // add cell width for left alignment
			++it; // Move to the next glyph

		}
		break;
		//case Alignment::Center:
		//
		//	break;
	}


	//switch (alignment) {
	//case Alignment::Right:
	//
	//	for (int i = 0; i < textLength; i++)
	//	{
	//		(*it)->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
	//		(*it)->Render(camera);
	//		nextX += (*it)->GetWidth(); // add cell width for left alignment
	//		++it; // Move to the next glyph
	//
	//	}
	//	break;
	//case Alignment::Left:
	//	//it = text.end(); // Start from the end of the list
	//	textLength -= 1;
	//	for (int i = textLength; i >= 0; i--) //start from the end of the string when using right alignment
	//	{
	//		
	//		nextX -= (*it)->GetWidth();
	//		(*it)->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
	//		(*it)->Render(camera);
	//		++it;
	//	}
	//	break;
	//	//case Alignment::Center:
	//	//
	//	//	break;
	//}


	//Glyph* glyph;
	//float nextX = posX;
	//float nextY = posY;
	//text.
	//int stringLen = string.length();
	//if (alignment == Alignment::Left) {
	//	GlyphCollection::iterator it;
	//	for (it = text.begin(); it != text.end(); it++) {
	//		(*it)->SetPositionAbsolute(nextX, nextY);
	//		nextX += (*it)->GetWidth();
	//		(*it)->Render(camera); //call draw on all the glyphs in the list of glyphs
	//	}
	//	//for (int i = 0; i < stringLen; i++)
	//	//{
	//	//	glyph = font->GetGlyph(string.at(i));
	//	//	glyph->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
	//	//	glyph->Render(camera);
	//	//	nextX += glyph->GetWidth(); // add cell width for left alignment
	//	//
	//	//	// we must update the next position ourselves
	//	//}
	//	width = nextX - posX; // set the width of the string
	//	height = text.front()->GetHeight();
	//}
	//else {
	//
	//	stringLen -= 1;
	//	for (int i = stringLen; i >= 0; i--) //start from the end of the string when using right alignment
	//	{
	//		glyph = font->GetGlyph(string.at(i));
	//		nextX -= glyph->GetWidth();
	//		glyph->Render(camera);
	//		glyph->SetPositionAbsolute(nextX, nextY); // set the position of the glyph
	//		text.push_front(glyph);
	//	}
	//	width = posX - nextX; // set the width of the string
	//	height = text.front()->GetHeight();
	//}
	//GlyphCollection::iterator it;
	//for (it = text.begin(); it != text.end(); it++) {
	//	(*it)->Render(camera); //call draw on all the glyphs in the list of glyphs
	//}
}



float SpriteString::GetWidth() const
{
	return width;
}

float SpriteString::GetHeight() const
{
	return height;
}
