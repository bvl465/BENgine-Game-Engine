#include "BENgineSpriteCollection.h"
#include <algorithm>
#include "../BENgine.h"
BENgineSpriteCollection::BENgineSpriteCollection()
{
}
BENgineSpriteCollection::~BENgineSpriteCollection()
{
	for (auto& spriteComponent : spriteComponentList)
	{
		delete spriteComponent;
	}
	spriteComponentList.clear();
}
void BENgineSpriteCollection::Render(Camera* cam)
{
	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->Render(cam);
	}
}

void BENgineSpriteCollection::SetPositionAbsolute(const float x, const float y)
{
	float xTransform = x - posX;
	float yTransform = y - posY;
	posX = x;
	posY = y;
	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->TransformPositionAbsolute(xTransform, yTransform);
	}
}

void BENgineSpriteCollection::SetPositionRelative(const float x, const float y)
{

	posX = BENgine::GetWidth() * x;
	posY = BENgine::GetHeight() * y;
	float xTransform = x - posX;
	float yTransform = y - posY;
	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->TransformPositionAbsolute(xTransform, yTransform);
	}
	
}

void BENgineSpriteCollection::AddSpriteComponent(BENgineSpriteComponent* spriteComponent)
{
	spriteComponentList.push_front(spriteComponent);
}

void BENgineSpriteCollection::RemoveSpriteComponent(BENgineSpriteComponent* spriteComponent)
{
	std::list<BENgineSpriteComponent*>::iterator it = std::find(spriteComponentList.begin(), spriteComponentList.end(), spriteComponent);
	assert(it != spriteComponentList.end());
	spriteComponentList.erase(it);
}

void BENgineSpriteCollection::RotateByRadiansUsingMatrixAboutPoint(const float radians, const Matrix& rotationAndTranslationMatrix)
{
	//Matrix temp = scale * rot * trans * rotationAndTranslationMatrix;
	//Matrix temp = Matrix(SCALE, scaleX, scaleY, 1.f) * Matrix(Vect(cosAngle, sinAngle, 0.f, 0.f), Vect(-sinAngle, cosAngle, 0.f, 0.f), Vect(0.f, 0.f, 1.f, 0.f), Vect(0.f, 0.f, 0.f, 1.f)) * Matrix(TRANS, posX, posY, 0.f) * rotationAndTranslationMatrix;
	Matrix temp = GetSRTMatrix() * rotationAndTranslationMatrix;
	posX = temp.M12();
	posY = temp.M13();

	angle += radians;
	const float cosRad = rotationAndTranslationMatrix.M0();
	const float sinRad = rotationAndTranslationMatrix.M1();
	const float prevCosAngle = cosAngle;
	cosAngle = (cosAngle * cosRad) - (sinAngle * sinRad);
	sinAngle = (sinAngle * cosRad) + (prevCosAngle * sinRad);

	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->RotateByRadiansUsingMatrixAboutPoint(radians, rotationAndTranslationMatrix);
	}
}

void BENgineSpriteCollection::UpdateWorld()
{
	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->UpdateWorld();
	}
}

void BENgineSpriteCollection::SetDataWithoutTransform(const float px, const float py, const float radians, const float sx, const float sy)
{
	posX = px;
	posY = py;
	angle = radians;
	cosAngle = cosf(angle);
	sinAngle = sinf(angle);
	scaleX = sx;
	scaleY = sy;
}



void BENgineSpriteCollection::RotateByRadians(const float radians)
{
	//angle += radians;
	//cosAngle = cosf(angle);
	//sinAngle = sinf(angle);
	//Matrix rotationMatrix = Matrix(ROT_Z, radians);
	//const Matrix rotationAndTranslationMatrix = (Matrix(TRANS, -posX, -posY, 0.f) * rotationMatrix * Matrix(TRANS, posX, posY, 0.f));

	const Matrix rotationAndTranslationMatrix = (Matrix(TRANS, -posX, -posY, 0.f) * Matrix(ROT_Z, radians) * Matrix(TRANS, posX, posY, 0.f));
	angle += radians;

	const float cosRad = rotationAndTranslationMatrix.M0();
	const float sinRad = rotationAndTranslationMatrix.M1();
	const float prevCosAngle = cosAngle;
	cosAngle = (cosAngle * cosRad) - (sinAngle * sinRad);
	sinAngle = (sinAngle * cosRad) + (prevCosAngle * sinRad);


	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->RotateByRadiansUsingMatrixAboutPoint(radians, rotationAndTranslationMatrix);
	}

}

void BENgineSpriteCollection::RotateByDegrees(const float degrees)
{
	//const float radians = degrees * MATH_PI_180;
	//angle += radians;
	//cosAngle = cosf(angle);
	//sinAngle = sinf(angle);
	//Matrix rotationMatrix = Matrix(ROT_Z, radians);
	//const Matrix rotationAndTranslationMatrix = (Matrix(TRANS, -posX, -posY, 0.f) * rotationMatrix * Matrix(TRANS, posX, posY, 0.f));


	const float radians = degrees * MATH_PI_180;
	const Matrix rotationAndTranslationMatrix = (Matrix(TRANS, -posX, -posY, 0.f) * Matrix(ROT_Z, radians) * Matrix(TRANS, posX, posY, 0.f));
	angle += radians;

	const float cosRad = rotationAndTranslationMatrix.M0();
	const float sinRad = rotationAndTranslationMatrix.M1();
	const float prevCosAngle = cosAngle;
	cosAngle = (cosAngle * cosRad) - (sinAngle * sinRad);
	sinAngle = (sinAngle * cosRad) + (prevCosAngle * sinRad);
	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->RotateByRadiansUsingMatrixAboutPoint(radians, rotationAndTranslationMatrix);
	}

}

void BENgineSpriteCollection::SetAngleDegrees(const float degrees)
{
	//const float radians = degrees * MATH_PI_180;
	//const float rotateBy = radians - angle;
	//angle = radians;
	//cosAngle = cosf(angle);
	//sinAngle = sinf(angle);
	//Matrix rotationMatrix = Matrix(ROT_Z, rotateBy);
	//const Matrix rotationAndTranslationMatrix = (Matrix(TRANS, -posX, -posY, 0.f) * rotationMatrix * Matrix(TRANS, posX, posY, 0.f));


	const float radians = degrees * MATH_PI_180;
	const float rotateBy = radians - angle;
	const Matrix rotationAndTranslationMatrix = (Matrix(TRANS, -posX, -posY, 0.f) * Matrix(ROT_Z, rotateBy) * Matrix(TRANS, posX, posY, 0.f));
	angle = radians;
	const float cosRad = rotationAndTranslationMatrix.M0();
	const float sinRad = rotationAndTranslationMatrix.M1();
	const float prevCosAngle = cosAngle;
	cosAngle = (cosAngle * cosRad) - (sinAngle * sinRad);
	sinAngle = (sinAngle * cosRad) + (prevCosAngle * sinRad);
	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->RotateByRadiansUsingMatrixAboutPoint(rotateBy, rotationAndTranslationMatrix);
	}
}

void BENgineSpriteCollection::SetAngleRadians(const float radians)
{

	//const float rotateBy = radians - angle;
	//angle = radians;
	//cosAngle = cosf(angle);
	//sinAngle = sinf(angle);
	//Matrix rotationMatrix = Matrix(ROT_Z, rotateBy);
	//const Matrix rotationAndTranslationMatrix = (Matrix(TRANS, -posX, -posY, 0.f) * rotationMatrix * Matrix(TRANS, posX, posY, 0.f));
	
	const float rotateBy = radians - angle;
	const Matrix rotationAndTranslationMatrix = (Matrix(TRANS, -posX, -posY, 0.f) * Matrix(ROT_Z, rotateBy) * Matrix(TRANS, posX, posY, 0.f));
	angle = radians;
	const float cosRad = rotationAndTranslationMatrix.M0();
	const float sinRad = rotationAndTranslationMatrix.M1();
	const float prevCosAngle = cosAngle;
	cosAngle = (cosAngle * cosRad) - (sinAngle * sinRad);
	sinAngle = (sinAngle * cosRad) + (prevCosAngle * sinRad);
	
	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->RotateByRadiansUsingMatrixAboutPoint(rotateBy, rotationAndTranslationMatrix);
	}
}

void BENgineSpriteCollection::SetScaleFactor(const float x, const float y)
{
	scaleX = x;
	scaleY = y;
	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->SetScaleFactor(x, y);
	}
}

void BENgineSpriteCollection::ReflectOverLocalXAxis()
{
	flipX *= -1.f;

	//Vect reflectionVector = Vect(flipX, 0.f, 0.f) * Matrix(Vect(cosAngle, sinAngle, 0.f, 0.f), Vect(-sinAngle, cosAngle, 0.f, 0.f), Vect(0.f, 0.f, 1.f, 0.f), Vect(0.f, 0.f, 0.f, 1.f));
	Vect reflectionVector = Vect(flipX * cosAngle, flipX * sinAngle, 0.f);

	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->ReflectOverNormalizedVectorFromPoint(reflectionVector, posX, posY, BENgineSpriteComponent::FlipType::HORIZONTAL);
	}
}

void BENgineSpriteCollection::ReflectOverLocalYAxis()
{
	flipY *= -1.f;

	
	//Vect reflectionVector = Vect(0.f, flipY, 0.f) * Matrix(Vect(cosAngle, sinAngle, 0.f, 0.f), Vect(-sinAngle, cosAngle, 0.f, 0.f), Vect(0.f, 0.f, 1.f, 0.f), Vect(0.f, 0.f, 0.f, 1.f));
	Vect reflectionVector = Vect (flipY * -sinAngle, flipY * cosAngle, 0.f);

	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->ReflectOverNormalizedVectorFromPoint(reflectionVector, posX, posY, BENgineSpriteComponent::FlipType::VERTICAL);
	}
}

void BENgineSpriteCollection::ReflectOverNormalizedVectorFromPoint(const Vect& vector, float pointX, float pointY, FlipType flipType)
{

	Vect angleVector;
	if (flipType == FlipType::HORIZONTAL)
	{
		flipX *= -1.f;

		//VERY IMPORTANT
		angleVector = Vect(-cosAngle, -sinAngle, 0.f);
	}
	else
	{
		flipY *= -1.f;

		//VERY IMPORTANT
		angleVector = Vect(cosAngle, sinAngle, 0.f);
	}

	const Vect posToPoint = (Vect(pointX, pointY, 0.f) - Vect(posX, posY, 0.f));
	const Vect projection = (posToPoint.dot(vector)) * vector;
	const Vect reflectedPosToPoint = posToPoint - projection - projection;
	posX = reflectedPosToPoint.X() + pointX;
	posY = reflectedPosToPoint.Y() + pointY;

	//Vect angleVector = Vect(cosAngle, sinAngle, 0.f);
	const Vect projectionAngle = (angleVector.dot(vector)) * vector;
	const Vect reflectedAngleVector = angleVector - projectionAngle - projectionAngle;
	cosAngle = reflectedAngleVector.X();
	sinAngle = reflectedAngleVector.Y();
	angle = atan2f(sinAngle, cosAngle);
	//angle = asinf(sinAngle);

	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->ReflectOverNormalizedVectorFromPoint(vector, pointX, pointY, flipType);
	}
}

void BENgineSpriteCollection::TransformPositionRelative(const float x, const float y)
{
	posX = BENgine::GetWidth() * x;
	posY = BENgine::GetHeight() * y;
	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->TransformPositionAbsolute(x, y);
	}
}

void BENgineSpriteCollection::TransformPositionAbsolute(const float x, const float y)
{
	posX += x;
	posY += y;
	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->TransformPositionAbsolute(x, y);
	}
}

void BENgineSpriteCollection::RotateAboutAbsolutePointRadians(const float x, const float y, const float radians)
{

	const Matrix rotationAndTranslationMatrix = (Matrix(TRANS, -x, -y, 0.f) * Matrix(ROT_Z, radians) * Matrix(TRANS, x, y, 0.f));
	//Matrix temp = scale * rot * trans * rotationAndTranslationMatrix
	//Matrix temp = Matrix(SCALE, scaleX, scaleY, 1.f) * Matrix(Vect(cosAngle, sinAngle, 0.f, 0.f), Vect(-sinAngle, cosAngle, 0.f, 0.f), Vect(0.f, 0.f, 1.f, 0.f), Vect(0.f, 0.f, 0.f, 1.f)) * Matrix(TRANS, posX, posY, 0.f) * rotationAndTranslationMatrix;
	const Matrix temp = GetSRTMatrix() * rotationAndTranslationMatrix;
	posX = temp.M12();
	posY = temp.M13();
	angle += radians;
	const float cosRad = rotationAndTranslationMatrix.M0();
	const float sinRad = rotationAndTranslationMatrix.M1();
	const float prevCosAngle = cosAngle;

	cosAngle = (cosAngle * cosRad) - (sinAngle * sinRad);
	sinAngle = (sinAngle * cosRad) + (prevCosAngle * sinRad);
	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->RotateByRadiansUsingMatrixAboutPoint(radians, rotationAndTranslationMatrix);
	}

}

void BENgineSpriteCollection::RotateAboutAbsolutePointDegrees(const float x, const float y, const float degrees)
{

	const float radians = degrees * MATH_PI_180;
	const Matrix rotationAndTranslationMatrix = (Matrix(TRANS, -x, -y, 0.f) * Matrix(ROT_Z, radians) * Matrix(TRANS, x, y, 0.f));
	//Matrix temp = scale * rot * trans * rotationAndTranslationMatrix;
	//Matrix temp = Matrix(SCALE, scaleX, scaleY, 1.f) * Matrix(Vect(cosAngle, sinAngle, 0.f, 0.f), Vect(-sinAngle, cosAngle, 0.f, 0.f), Vect(0.f, 0.f, 1.f, 0.f), Vect(0.f, 0.f, 0.f, 1.f)) * Matrix(TRANS, posX, posY, 0.f) * rotationAndTranslationMatrix;
	const Matrix temp = GetSRTMatrix() * rotationAndTranslationMatrix;
	posX = temp.M12();
	posY = temp.M13();
	angle += radians;
	const float cosRad = rotationAndTranslationMatrix.M0();
	const float sinRad = rotationAndTranslationMatrix.M1();
	const float prevCosAngle = cosAngle;

	cosAngle = (cosAngle * cosRad) - (sinAngle * sinRad);
	sinAngle = (sinAngle * cosRad) + (prevCosAngle * sinRad);
	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->RotateByRadiansUsingMatrixAboutPoint(radians, rotationAndTranslationMatrix);
	}



}

void BENgineSpriteCollection::RotateAboutRelativePointRadians(float x, float y, const float radians)
{
	x *= BENgine::GetWidth();
	y *= BENgine::GetHeight();
	const Matrix rotationAndTranslationMatrix = (Matrix(TRANS, -x, -y, 0.f) * Matrix(ROT_Z, radians) * Matrix(TRANS, x, y, 0.f));
	//Matrix temp = scale * rot * trans * rotationAndTranslationMatrix;
	//Matrix temp = Matrix(SCALE, scaleX, scaleY, 1.f) * Matrix(Vect(cosAngle, sinAngle, 0.f, 0.f), Vect(-sinAngle, cosAngle, 0.f, 0.f), Vect(0.f, 0.f, 1.f, 0.f), Vect(0.f, 0.f, 0.f, 1.f)) * Matrix(TRANS, posX, posY, 0.f) * rotationAndTranslationMatrix;
	const Matrix temp = GetSRTMatrix() * rotationAndTranslationMatrix;
	posX = temp.M12();
	posY = temp.M13();
	//trans.set(TRANS, posX, posY, 0.f);
	angle += radians;
	const float cosRad = rotationAndTranslationMatrix.M0();
	const float sinRad = rotationAndTranslationMatrix.M1();
	const float prevCosAngle = cosAngle;

	cosAngle = (cosAngle * cosRad) - (sinAngle * sinRad);
	sinAngle = (sinAngle * cosRad) + (prevCosAngle * sinRad);
	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->RotateByRadiansUsingMatrixAboutPoint(radians, rotationAndTranslationMatrix);
	}

}

void BENgineSpriteCollection::RotateAboutRelativePointDegrees(float x, float y, const float degrees)
{
	x *= BENgine::GetWidth();
	y *= BENgine::GetHeight();
	const float radians = degrees * MATH_PI_180;
	const Matrix rotationAndTranslationMatrix = (Matrix(TRANS, -x, -y, 0.f) * Matrix(ROT_Z, radians) * Matrix(TRANS, x, y, 0.f));
	//Matrix temp = scale * rot * trans * rotationAndTranslationMatrix;
	//Matrix temp = Matrix(SCALE, scaleX, scaleY, 1.f) * Matrix(Vect(cosAngle, sinAngle, 0.f, 0.f), Vect(-sinAngle, cosAngle, 0.f, 0.f), Vect(0.f, 0.f, 1.f, 0.f), Vect(0.f, 0.f, 0.f, 1.f)) * Matrix(TRANS, posX, posY, 0.f) * rotationAndTranslationMatrix;
	const Matrix temp = GetSRTMatrix() * rotationAndTranslationMatrix;
	posX = temp.M12();
	posY = temp.M13();
	angle += radians;
	const float cosRad = rotationAndTranslationMatrix.M0();
	const float sinRad = rotationAndTranslationMatrix.M1();
	const float prevCosAngle = cosAngle;

	cosAngle = (cosAngle * cosRad) - (sinAngle * sinRad);
	sinAngle = (sinAngle * cosRad) + (prevCosAngle * sinRad);
	for (auto& spriteComponent : spriteComponentList)
	{
		spriteComponent->RotateByRadiansUsingMatrixAboutPoint(radians, rotationAndTranslationMatrix);
	}
}

void BENgineSpriteCollection::SetScaleRotationTranslation(const float sx, const float sy, const float rad, const float px, const float py)
{
	scaleX = sx;
	scaleY = sy;
	angle = rad;
	cosAngle = cosf(angle);
	sinAngle = sinf(angle);
	posX = px;
	posY = py;
}
