#include "BENgineSprite.h"
#include "../BENgine.h"
#include "Image.h"
#include "../Asset Managers/Image Manager/ImageManager.h"
#include "../Asset Managers/Shader Manager/ShaderManager.h"
#include "../Asset Managers/Model Manager/ModelManager.h"
BENgineSprite::BENgineSprite(std::string imageKey) : centerX(0.f), centerY(0.f), updateWorldSetting(SpriteAutoUpdateWorldSetting::ON_RENDER)
{

	Image* image = ImageManager::GetImage(imageKey);
	Rect* rect = image->pImageRect;
	//new Rect(0.f, 0.f, (float)(image->pText->getWidth()), (float)(image->pText->getHeight()));
	ptrGOSprite = new GraphicsObject_Sprite(ModelManager::GetModel("UnitSquareXY"), ShaderManager::GetShaderObject("SpriteRender"), image, rect);
	
	offsetX = -ptrGOSprite->origPosX;
	offsetY = -ptrGOSprite->origPosY;
	//trans.set(TRANS, ptrGOSprite->origPosX * .5f * ptrGOSprite->origWidth, ptrGOSprite->origPosY * .5f * ptrGOSprite->origHeight, 0.f);
	posX = ptrGOSprite->origPosX * .5f * ptrGOSprite->origWidth;
	posY = ptrGOSprite->origPosY * .5f * ptrGOSprite->origHeight;
	//delete rect;
	UpdateWorld();

}

BENgineSprite::BENgineSprite(std::string imageKey, SpriteAutoUpdateWorldSetting spriteAutoUpdateWorldSetting) : centerX(0.f), centerY(0.f), updateWorldSetting(spriteAutoUpdateWorldSetting)
{
	Image* image = ImageManager::GetImage(imageKey);
	Rect* rect = image->pImageRect;
	ptrGOSprite = new GraphicsObject_Sprite(ModelManager::GetModel("UnitSquareXY"), ShaderManager::GetShaderObject("SpriteRender"), image, rect);
	offsetX = -ptrGOSprite->origPosX;
	offsetY = -ptrGOSprite->origPosY;
	posX = ptrGOSprite->origPosX * .5f * ptrGOSprite->origWidth;
	posY = ptrGOSprite->origPosY * .5f * ptrGOSprite->origHeight;
	
	UpdateWorld();
}

void BENgineSprite::Render(Camera* cam)
{
	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_RENDER || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER)
	{
		UpdateWorld();
	}
	ptrGOSprite->Render(cam);
}

void BENgineSprite::SetCenter(const float x, const float y)
{
	centerX = x;
	centerY = y;
	//ptrGOSprite->origPosX = x * ((ptrGOSprite->origWidth) * .5f);
	//ptrGOSprite->origPosY = y * ((ptrGOSprite->origHeight) * .5f);
	//offsetX = -ptrGOSprite->origPosX;
	//offsetY = -ptrGOSprite->origPosY;
	
	offsetX = -x * (ptrGOSprite->origWidth) * .5f;
	offsetY = -y * (ptrGOSprite->origHeight) * .5f;
	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
}

void BENgineSprite::SetPositionAbsolute(const float x, const float y)
{
	posX = x;
	posY = y;
	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
}

void BENgineSprite::SetPositionRelative(const float x, const float y)
{
	posX = BENgine::GetWidth() * x;
	posY = BENgine::GetHeight() * y;
	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
}

void BENgineSprite::RotateByRadians(const float radians)
{
	angle += radians;
	cosAngle = cosf(angle);
	sinAngle = sinf(angle);
	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
}

void BENgineSprite::RotateByDegrees(const float degrees)
{
	angle += degrees * MATH_PI_180;
	cosAngle = cosf(angle);
	sinAngle = sinf(angle);
	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
}

void BENgineSprite::SetAngleDegrees(const float degrees)
{
	angle = degrees * MATH_PI_180;
	cosAngle = cosf(angle);
	sinAngle = sinf(angle);
	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
}

void BENgineSprite::SetAngleRadians(const float radians)
{
	angle = radians;
	cosAngle = cosf(angle);
	sinAngle = sinf(angle);
	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
}

void BENgineSprite::SetScaleFactor(const float x, const float y)
{
	scaleX = x;
	scaleY = y;
	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
}

void BENgineSprite::SetScalePixel(const float x, const float y)
{
	scaleX = x / ptrGOSprite->origWidth;
	scaleY = y / ptrGOSprite->origHeight;
	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
}

float BENgineSprite::GetCenterX() const
{
	return centerX;
}

float BENgineSprite::GetCenterY() const
{
	return centerY;
}

float BENgineSprite::GetWidth() const
{
	return ptrGOSprite->origWidth;
}

float BENgineSprite::GetHeight() const
{
	return ptrGOSprite->origHeight;
}



void BENgineSprite::TransformPositionRelative(const float x, const float y)
{
	posX += x * BENgine::GetWidth();
	posY += y * BENgine::GetHeight();
	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}

}

void BENgineSprite::TransformPositionAbsolute(const float x, const float y)
{
	posX += x;
	posY += y;
	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
}      

void BENgineSprite::RotateAboutAbsolutePointRadians(const float x, const float y, const float radians)
{
	const float cosRad = cosf(radians);
	const float sinRad = sinf(radians);
	
	//Matrix temp = GetSRTMatrix() * (Matrix(TRANS, -x, -y, 0.f) * Matrix(ROT_Z, radians) * Matrix(TRANS, x, y, 0.f));
	const Matrix temp = GetSRTMatrix() * (Matrix(TRANS, -x, -y, 0.f) * Matrix(Vect(cosRad, sinRad, 0.f, 0.f), Vect(-sinRad, cosRad, 0.f, 0.f), Vect(0.f, 0.f, 1.f, 0.f), Vect(0.f, 0.f, 0.f, 1.f)) * Matrix(TRANS, x, y, 0.f));
	posX = temp.M12();
	posY = temp.M13();
	angle += radians;
	//cosAngle = cosf(angle);
	//sinAngle = sinf(angle);

	const float prevCosAngle = cosAngle;
	cosAngle = (cosAngle * cosRad) - (sinAngle * sinRad);
	sinAngle = (sinAngle * cosRad) + (prevCosAngle * sinRad);

	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
}

void BENgineSprite::RotateAboutAbsolutePointDegrees(const float x, const float y, const float degrees)
{
	const float radians = degrees * MATH_PI_180;
	
	const float cosRad = cosf(radians);
	const float sinRad = sinf(radians);

	//Matrix temp = GetSRTMatrix() * (Matrix(TRANS, -x, -y, 0.f) * Matrix(ROT_Z, radians) * Matrix(TRANS, x, y, 0.f));
	const Matrix temp = GetSRTMatrix() * (Matrix(TRANS, -x, -y, 0.f) * Matrix(Vect(cosRad, sinRad, 0.f, 0.f), Vect(-sinRad, cosRad, 0.f, 0.f), Vect(0.f, 0.f, 1.f, 0.f), Vect(0.f, 0.f, 0.f, 1.f)) * Matrix(TRANS, x, y, 0.f));
	posX = temp.M12();
	posY = temp.M13();
	angle += radians;

	const float prevCosAngle = cosAngle;
	cosAngle = (cosAngle * cosRad) - (sinAngle * sinRad);
	sinAngle = (sinAngle * cosRad) + (prevCosAngle * sinRad);

	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
}

void BENgineSprite::RotateAboutRelativePointRadians(float x, float y, const float radians)
{
	x *= BENgine::GetWidth();
	y *= BENgine::GetHeight();
	
	const float cosRad = cosf(radians);
	const float sinRad = sinf(radians);

	//Matrix temp = GetSRTMatrix() * (Matrix(TRANS, -x, -y, 0.f) * Matrix(ROT_Z, radians) * Matrix(TRANS, x, y, 0.f));
	const Matrix temp = GetSRTMatrix() * (Matrix(TRANS, -x, -y, 0.f) * Matrix(Vect(cosRad, sinRad, 0.f, 0.f), Vect(-sinRad, cosRad, 0.f, 0.f), Vect(0.f, 0.f, 1.f, 0.f), Vect(0.f, 0.f, 0.f, 1.f)) * Matrix(TRANS, x, y, 0.f));
	posX = temp.M12();
	posY = temp.M13();
	angle += radians;
	//cosAngle = cosf(angle);
	//sinAngle = sinf(angle);

	const float prevCosAngle = cosAngle;
	cosAngle = (cosAngle * cosRad) - (sinAngle * sinRad);
	sinAngle = (sinAngle * cosRad) + (prevCosAngle * sinRad);

	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
}

void BENgineSprite::RotateAboutRelativePointDegrees(float x, float y, const float degrees)
{
	x *= BENgine::GetWidth();
	y *= BENgine::GetHeight();
	const float radians = degrees * MATH_PI_180;
	
	const float cosRad = cosf(radians);
	const float sinRad = sinf(radians);

	//Matrix temp = GetSRTMatrix() * (Matrix(TRANS, -x, -y, 0.f) * Matrix(ROT_Z, radians) * Matrix(TRANS, x, y, 0.f));
	const Matrix temp = GetSRTMatrix() * (Matrix(TRANS, -x, -y, 0.f) * Matrix(Vect(cosRad, sinRad, 0.f, 0.f), Vect(-sinRad, cosRad, 0.f, 0.f), Vect(0.f, 0.f, 1.f, 0.f), Vect(0.f, 0.f, 0.f, 1.f)) * Matrix(TRANS, x, y, 0.f));
	posX = temp.M12();
	posY = temp.M13();
	angle += radians;
	//cosAngle = cosf(angle);
	//sinAngle = sinf(angle);

	const float prevCosAngle = cosAngle;
	cosAngle = (cosAngle * cosRad) - (sinAngle * sinRad);
	sinAngle = (sinAngle * cosRad) + (prevCosAngle * sinRad);

	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
}

void BENgineSprite::SetScaleRotationTranslation(const float sx, const float sy, const float rad, const float px, const float py)
{
	scaleX = sx;
	scaleY = sy;
	angle = rad;
	cosAngle = cosf(angle);
	sinAngle = sinf(angle);
	posX = px;
	posY = py;
	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
}

void BENgineSprite::RotateByRadiansUsingMatrixAboutPoint(const float radians, const Matrix& rotationAndTranslationMatrix)
{
	const Matrix temp = GetSRTMatrix() * rotationAndTranslationMatrix;
	posX = temp.M12();
	posY = temp.M13();
	//trans.set(TRANS, posX, posY, 0.f);
	angle += radians;
	//rot.set(ROT_Z, angle);
	const float cosRad = rotationAndTranslationMatrix.M0();
	const float sinRad = rotationAndTranslationMatrix.M1();
	const float prevCosAngle = cosAngle;

	cosAngle = (cosAngle * cosRad) - (sinAngle * sinRad);
	sinAngle = (sinAngle * cosRad) + (prevCosAngle * sinRad);
	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}


}

void BENgineSprite::UpdateWorld()
{
	Matrix world = Matrix(TRANS, offsetX, offsetY, 0.f) * Matrix(SCALE, scaleX * flipY, scaleY * flipX, 1.f) * Matrix(Vect(cosAngle, sinAngle, 0.f, 0.f), Vect(-sinAngle, cosAngle, 0.f, 0.f), Vect(0.f, 0.f, 1.f, 0.f), Vect(0.f, 0.f, 0.f, 1.f)) * Matrix(TRANS, posX, posY, 0.f);
	//Matrix world = Matrix(TRANS, offsetX, offsetY, 0.f) * Matrix(SCALE, scaleX, scaleY, 1.f) * Matrix(Vect(cosAngle, sinAngle, 0.f, 0.f), Vect(-sinAngle, cosAngle, 0.f, 0.f), Vect(0.f, 0.f, 1.f, 0.f), Vect(0.f, 0.f, 0.f, 1.f)) * Matrix(TRANS, posX, posY, 0.f);
	//Matrix world = offset * scale * rot * trans;
	
	ptrGOSprite->SetWorld(world);
}

void BENgineSprite::SetAutoUpdateWorldSetting(SpriteAutoUpdateWorldSetting setting)
{
	updateWorldSetting = setting;
}

void BENgineSprite::ReflectOverLocalXAxis()
{
	flipX *= -1.f;
	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
}

void BENgineSprite::ReflectOverLocalYAxis()
{
	flipY *= -1.f;
	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
}

void BENgineSprite::ReflectOverNormalizedVectorFromPoint(const Vect& vector, float pointX, float pointY, FlipType flipType)
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

	const Vect posToPoint =  (Vect(pointX, pointY, 0.f) - Vect(posX, posY, 0.f));
	const Vect projection = (posToPoint.dot(vector)) * vector;
	const Vect reflectedPosToPoint = posToPoint - projection - projection;
	posX = reflectedPosToPoint.X() + pointX;
	posY = reflectedPosToPoint.Y() + pointY;

	const Vect projectionAngle = (angleVector.dot(vector)) * vector;
	const Vect reflectedAngleVector = angleVector - projectionAngle - projectionAngle;
	cosAngle = reflectedAngleVector.X();
	sinAngle = reflectedAngleVector.Y();

	//VERY IMPORTANT IT IS ATAN2
	angle = atan2f(sinAngle, cosAngle);


	if (updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM || updateWorldSetting == SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER) {
		UpdateWorld();
	}
	
}

BENgineSprite::BENgineSprite() : centerX(0.f), centerY(0.f), offsetX(0.f), offsetY(0.f), ptrGOSprite(nullptr), updateWorldSetting(SpriteAutoUpdateWorldSetting::ON_TRANSFORM_AND_RENDER)
{

}

BENgineSprite::~BENgineSprite()
{
	if (ptrGOSprite != nullptr) {
		delete ptrGOSprite;
	}
}