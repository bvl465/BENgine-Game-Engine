#pragma once
#ifndef _BENgineSpriteCollection
#define _BENgineSpriteCollection

#include "AzulCore.h"
#include "BENgineSpriteBase.h"
#include <list>
#include "BENgineSpriteComponent.h"
class Camera;


class BENgineSpriteCollection : public BENgineSpriteComponent
{
public:
    BENgineSpriteCollection();
    BENgineSpriteCollection(const BENgineSpriteCollection&) = delete;
    BENgineSpriteCollection& operator=(const BENgineSpriteCollection&) = delete;
    ~BENgineSpriteCollection();

    void Render(Camera* cam) override;

    //Sets the absolute pixel position of the sprite on the window.
    void SetPositionAbsolute(const float x, const float y) override;

    //Pass a float value between 0 and 1 for x and y. The value passed is treated as a percentage of the window.
    //Example
    //If the window width is 200 pixels and the window height is 100, passing .5 for x and .5 for y would result
    //in the position of the sprite in pixels on the window being 100 x and 50 y.
    void SetPositionRelative(const float x, const float y) override;

    void RotateByRadians(const float radians) override;

    void RotateByDegrees(const float degrees) override;

    void SetAngleDegrees(const float degrees) override;

    void SetAngleRadians(const float radians) override;

    void SetScaleFactor(const float x, const float y) override;

    
    //Reflect

    virtual void ReflectOverLocalXAxis() override;
    
    virtual void ReflectOverLocalYAxis() override;
    
    virtual void ReflectOverNormalizedVectorFromPoint(Vect vector, float pointX, float pointY, FlipType flipType) override;



	//void ScaleSizeAndDistanceFromPointByFactor(float pointX, float pointY, float sx, float sy) override;
    
    //void ScaleCollectionByFactor(float scale);

    void TransformPositionRelative(const float x, const float y) override;

    void TransformPositionAbsolute(const float x, const float y) override;

    void RotateAboutAbsolutePointRadians(const float x, const float y, const float radians) override;
    void RotateAboutAbsolutePointDegrees(const float x, const float y, const float degrees) override;

    void RotateAboutRelativePointRadians(float x, float y, const float radians) override;
    void RotateAboutRelativePointDegrees(float x, float y, const float degrees) override;

    void SetScaleRotationTranslation(const float sx, const float sy, const float rad, const float px, const float py) override;



	void AddSpriteComponent(BENgineSpriteComponent* spriteComponent);

	void RemoveSpriteComponent(BENgineSpriteComponent* spriteComponent);


    void RotateByRadiansUsingMatrixAboutPoint(const float radians, const Matrix& rotationAndTranslationMatrix) override;

    void UpdateWorld() override;

    void SetDataWithoutTransform(const float px, const float py, const float radians, const float sx, const float sy);

private:

    //Maybe having all these matrices ins't as efficient as doing the math to calculate them in the update world function.
    //This does help with debugging though.
	std::list<BENgineSpriteComponent*> spriteComponentList; ///<The list of BENgineSpriteComponent pointers in this sprite collection.

    //Matrix trans;
    //Matrix rot;
    //Matrix scale;
    

};

#endif _BENgineSpriteCollection