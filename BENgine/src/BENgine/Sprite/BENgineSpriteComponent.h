#ifndef _BENgineSpriteComponent
#define _BENgineSpriteComponent

#include "AzulCore.h"
#include "./Layers/Sprite2DLayer.h"
#include <string>
class Camera;
class SpriteLayer2DCommandComponent;
class Sprite2DLayer;

class BENgineSpriteComponent
{
public:


    enum class FlipType
    {
        //Flip over local y axis
        HORIZONTAL,
    
		//Flip over local x axis
        VERTICAL
    };


    BENgineSpriteComponent();
    BENgineSpriteComponent(const BENgineSpriteComponent&) = delete;
    BENgineSpriteComponent& operator=(const BENgineSpriteComponent&) = delete;
    virtual ~BENgineSpriteComponent() = default;


	//Defined by inherited classes -------------------------------------------------------------------------------------------------
    
    virtual void Render(Camera* cam) = 0;

    virtual void SetPositionAbsolute(const float x, const float y) = 0;

    virtual void SetPositionRelative(const float x, const float y) = 0;

    virtual void SetAngleDegrees(const float degrees) = 0;

    virtual void SetAngleRadians(const float radians) = 0;

    virtual void SetScaleFactor(const float x, const float y) = 0;

    virtual void TransformPositionRelative(const float x, const float y) = 0;

    virtual void TransformPositionAbsolute(const float x, const float y) = 0;

    virtual void RotateAboutAbsolutePointRadians(const float x, const float y, const float radians) = 0;
    virtual void RotateAboutAbsolutePointDegrees(const float x, const float y, const float degrees) = 0;

    virtual void RotateAboutRelativePointRadians(float x, float y, const float radians) = 0;
    virtual void RotateAboutRelativePointDegrees(float x, float y, const float degrees) = 0;

    virtual void SetScaleRotationTranslation(const float sx, const float sy, const float rad, const float px, const float py) = 0;

    virtual void RotateByRadiansUsingMatrixAboutPoint(const float radians, const Matrix& rotationAndTranslationMatrix) = 0;

    //virtual void ScaleDistanceFromPointAndScaleByFactor(float pointX, float pointY, float sx, float sy) = 0;

    virtual void UpdateWorld() = 0;

	//virtual void ScaleSizeAndDistanceFromPointByFactor(float pointX, float pointY, float sx, float sy) = 0;

    ////Reflection methods to be implemented:
    virtual void ReflectOverLocalXAxis() = 0;
    
	virtual void ReflectOverLocalYAxis() = 0;
    
    virtual void ReflectOverNormalizedVectorFromPoint(Vect vector, float pointX, float pointY, FlipType flipType) = 0;


	virtual void RotateByRadians(const float radians) = 0;

	virtual void RotateByDegrees(const float degrees) = 0;

    //------------------------------------------------------------------------------------------------------------------------------



	//Returns the x position of the BENgineSpriteComponent in pixels on the window.
    float GetPosX() const;

	//Returns the y position of the BENgineSpriteComponent in pixels on the window.
    float GetPosY() const;

    //Returns the BENgineSpriteComponent's angle in radians
    float GetAngleRadians() const;

    //Computes then returns the BENgineSpriteComponent's angle in degrees and returns it
    float GetAngleDegrees() const;

    //Returns the scale factor of the BENgineSpriteComponent in the x direction
    float GetScaleX() const;

    //Returns the scale factor of the BENgineSpriteComponent in the y direction
    float GetScaleY() const;

	////To be used once reflection methods are implemented --------------------------------------
	float GetFlipX() const;
    
	float GetFlipY() const;
	////-----------------------------------------------------------------------------------------

	//Calculates then returns the matrix that results from multiplying the scale matrix, rotation matrix, and translation matrix of the BENgineSpriteComponent together in that order.
    Matrix GetSRTMatrix() const;

    void SetFlipX(float flip) { flipX = flip; };

    void SetFlipY(float flip) { flipY = flip; };

protected:


    //The x position of the BENgineSpriteComponent in pixels on the window.
    float posX;
	//The y position of the BENgineSpriteComponent in pixels on the window.
    float posY;

    //The relative x scale factor of the BENgineSpriteComponent.
    float scaleX;
    //The relative y scale factor of the BENgineSpriteComponent.
    float scaleY;



 
    //The angle of the BENgineSpriteComponent in radians.
    float angle;

    //cosAngle and sinAngle are used to avoid having to calculate the cosine and sine of the angle multiple times in the update world function.
    
    //The cosine of the angle of the BENgineSpriteComponent.
    float cosAngle;
    //The sine of the angle of the BENgineSpriteComponent.
    float sinAngle;


	//To be used for reflection methods --------------------------------------
    
    //The x flip of the BENgineSpriteComponent. 1 for normal, -1 for flipped.
	float flipX; 
    //The y flip of the BENgineSpriteComponent. 1 for normal, -1 for flipped.
	float flipY;
    //------------------------------------------------------------------------
};

/*
TODO:
SetScaleRotationTranslation should be overhauled. Passing whole matrices and the values to calulate them as parametersis inefficient.
Not only is it inefficent, but it can also lead to errors if the matrices and corresponding values don't match up.
*/

#endif _BENgineSpriteComponent