#include "BENgineSpriteComponent.h"

BENgineSpriteComponent::BENgineSpriteComponent() : angle(0.f), posX(0.f), posY(0.f), scaleX(1.f), scaleY(1.f), cosAngle(1.f), sinAngle(0.f), flipX(1.f), flipY(1.f)
{
}

//BENgineSpriteComponent::BENgineSpriteComponent() : angle(0.f), posX(0.f), posY(0.f), scaleX(1.f), scaleY(1.f), cosAngle(1.f), sinAngle(0.f)
//{
//}

Matrix BENgineSpriteComponent::GetSRTMatrix() const
{
	//Matrix srt = Matrix(SCALE, scaleX, scaleY, 1.f) * Matrix(Vect(cosAngle, sinAngle, 0.f, 0.f), Vect(-sinAngle, cosAngle, 0.f, 0.f), Vect(0.f, 0.f, 1.f, 0.f), Vect(0.f, 0.f, 0.f, 1.f)) * Matrix(TRANS, posX, posY, 0.f);
	Matrix srt = Matrix(SCALE, scaleX * flipY, scaleY * flipX, 1.f) * Matrix(Vect(cosAngle, sinAngle, 0.f, 0.f), Vect(-sinAngle, cosAngle, 0.f, 0.f), Vect(0.f, 0.f, 1.f, 0.f), Vect(0.f, 0.f, 0.f, 1.f)) * Matrix(TRANS, posX, posY, 0.f);
	return srt;
}

// NOW INLINE FUNCTIONS

//float BENgineSpriteComponent::GetPosX() const
//{
//	return posX;
//}
//
//float BENgineSpriteComponent::GetPosY() const
//{
//	return posY;
//}
//
//float BENgineSpriteComponent::GetAngleRadians() const
//{
//	return angle;
//}
//
//float BENgineSpriteComponent::GetAngleDegrees() const
//{
//	return angle * MATH_180_PI;
//}
//
//float BENgineSpriteComponent::GetScaleX() const
//{
//	return scaleX;
//}
//
//float BENgineSpriteComponent::GetScaleY() const
//{
//	return scaleY;
//}
//
//float BENgineSpriteComponent::GetFlipX() const
//{
//	return flipX;
//}
//
//float BENgineSpriteComponent::GetFlipY() const
//{
//	return flipY;
//}

