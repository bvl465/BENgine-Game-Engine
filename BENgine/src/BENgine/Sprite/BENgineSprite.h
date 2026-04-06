#ifndef _BENgineSprite
#define _BENgineSprite

#include "AzulCore.h"
#include "BENgineSpriteBase.h"
class Camera;

//Represents to determine when the sprite updates the world matrix of the GraphicsObject_Sprite*.
enum class SpriteAutoUpdateWorldSetting
{

    //World matrix of GraphicsObject is only update when a transformation is applied
    //Best for sprites that will move but not frequently.
    ON_TRANSFORM,

	//World matrix of GraphicsObject is updated every time before it is rendered.
	//Best for sprites that move frequently. Also necessary if multiple sprites use the same GraphicsObject_Sprite.
    ON_RENDER,

	//World matrix of GraphicsObject is updated every time before it is transformed and rendered.
    //Best for debugging sprites.
    ON_TRANSFORM_AND_RENDER,

	//World matrix of GraphicsObject is never automatically updated. The user must manually call UpdateWorld() to update the world matrix when using this setting.
	//Best for optimization or sprites that will never move after they are created.
	NEVER
};


class BENgineSprite : public BENgineSpriteBase
{
public:
    BENgineSprite();
    BENgineSprite(const BENgineSprite&) = delete;
    BENgineSprite& operator=(const BENgineSprite&) = delete;
    virtual ~BENgineSprite();

	//constructor to pass the image key to the sprite as a string
    BENgineSprite(std::string imageKey);

	//constructor to pass the image key to the sprite as a string and also set the SpriteAutoUpdateWorldSetting.
	//Parameters:
	//imageKey - the key of the image to use for the sprite. The image must already be loaded and stored in the ImageManager.
	//spriteAutoUpdateWorldSetting - the SpriteAutoUpdateWorldSetting to set for the sprite which determines when the sprite's world matrix is automatically updated.
    BENgineSprite(std::string imageKey, SpriteAutoUpdateWorldSetting spriteAutoUpdateWorldSetting);

    //Pass a 2D camera to have it the sprite rendered. If registered to an enabled Sprite2DLayer the layer will also call this at the appropriate time.
    //It can also be called manually whenever during the game loop although this is not recommended.
	//Parameters:
	//cam - the camera to render the sprite with. This should be a 2D camera.
    void Render(Camera* cam) override;

	//Sets the center of the sprite relative to its current size.
	//The bottom left corner is represented with (-1, -1), the top right corner is represented with (1, 1) and the center is represented with (0, 0).
    //and then updates the sprites position based on the new offset.
	//Parameters:
	//x - the x coordinate of the center of the sprite as a percentage of the sprite's size. Positive values will move the center to the right and negative values will move the center to the left.
	//y - the y coordinate of the center of the sprite as a percentage of the sprite's size. Positive values will move the center up and negative values will move the center down.
    void SetCenter(const float x, const float y) override;

    //Sets the absolute pixel position of the sprite on the window.
	//Parameters:
	//x - the x coordinate of the position to set the sprite to in pixels on the window.
	//y - the y coordinate of the position to set the sprite to in pixels on the window.
    void SetPositionAbsolute(const float x, const float y) override;

    //Pass a float value between 0 and 1 for x and y. The value passed is treated as a percentage of the window.
    //Example
    //If the window width is 200 pixels and the window height is 100, passing .5 for x and .5 for y would result
    //in the position of the sprite in pixels on the window being 100 x and 50 y.
	//Parameters:
	//x - the x coordinate of the position to set the sprite to as a percentage of the window width.
	//y - the y coordinate of the position to set the sprite to as a percentage of the window height.
    void SetPositionRelative(const float x, const float y) override;

    //Rotates sprite around centerX and centerY by radians
    //Parameters:
	//radians - The amount to rotate the sprite by in radians.
    void RotateByRadians(const float radians) override;

    //Rotates sprite around centerX and centerY by degrees (this involves a conversion to radians in the method)
	//Parameters:
	//degrees - The amount to rotate the sprite by in degrees.
    void RotateByDegrees(const float degrees) override;

    //Sets the angle of the sprite in degrees (this involves a conversion to radians in the method)
	//Parameters:
	//degrees - The angle to set the sprite to in degrees.
    void SetAngleDegrees(const float degrees) override;

    //Sets the angle of the sprite in radians
    void SetAngleRadians(const float radians) override;

    //Sets the scale factor of the sprite in the x and y direction as a percentage of the original size.
	//Parameters:
	//x - the x scale factor of the sprite as a percentage of the original size.
	//y - the y scale factor of the sprite as a percentage of the original size.
    void SetScaleFactor(const float x, const float y) override;

    //Sets the scale factor of the sprite in the x and y direction in pixels.
	//Parameters:
	//x - the number of pixels the sprite will take up on the x axis.
	//y - the number of pixels the sprite will take up on the y axis.
    void SetScalePixel(const float x, const float y) override;

    //Returns centerX
    float GetCenterX() const override;

    //Returns centerY
    float GetCenterY() const override;

    //Get the original width of the sprite
    float GetWidth() const override;

    //Get the original height of the sprite
    float GetHeight() const override;


    //Transforms the position of the sprite by an amount that is a percentage of the window size.
	//Parameters:
	//x - the amount to transform the sprite in the x direction as a percentage of the window width.
	//y - the amount to transform the sprite in the y direction as a percentage of the window height.
    void TransformPositionRelative(const float x, const float y) override;

    //Transforms the position of the sprite by an absolute pixel amount.
	//Parameters:
	//x - the amount to transform the sprite in the x direction in pixels.
	//y - the amount to transform the sprite in the y direction in pixels.
    void TransformPositionAbsolute(const float x, const float y) override;

    //Rotates the sprite around a point that is defined in absolute pixel coordinates by radians.
	//Parameters:
	//x - the x coordinate of the point to rotate around in pixels on the window.
	//y - the y coordinate of the point to rotate around in pixels on the window.
	//radians - the amount to rotate the sprite by in radians.
    void RotateAboutAbsolutePointRadians(const float x, const float y, const float radians) override;

    //Rotates the sprite around a point that is defined in absolute pixel coordinates by degrees (this involves a conversion to radians in the method).
    //Parameters:
    //x - the x coordinate of the point to rotate around in pixels on the window.
    //y - the y coordinate of the point to rotate around in pixels on the window.
    //degrees - the amount to rotate the sprite by in degrees.
    void RotateAboutAbsolutePointDegrees(const float x, const float y, const float degrees) override;

    //Rotates the sprite around a point that is defined as a percentage of the window size by radians.
	//Parameters:
    //x - the x coordinate of the point to rotate about as a percentage of the window width.
	//y - the y coordinate of the point to rotate about as a percentage of the window height.
	//radians - the amount to rotate the sprite by in radians.
    void RotateAboutRelativePointRadians(float x, float y, const float radians) override;

    //Rotates the sprite around a point that is defined as a percentage of the window size by degrees (this involves a conversion to radians in the method).
	//Parameters:
	//x - the x coordinate of the point to rotate about as a percentage of the window width.
	//y - the y coordinate of the point to rotate about as a percentage of the window height.
	//degrees - the amount to rotate the sprite by in degrees.
    void RotateAboutRelativePointDegrees(float x, float y, const float degrees) override;

    //Sets the scale, rotation, and translation of the sprite.
	//Parameters:
	//sx - the x scale factor of the sprite as a percentage of the original size of the sprite.
	//sy - the y scale factor of the sprite as a percentage of the original size of the sprite.
	//rad - the angle to rotate the sprite in radians.
	//px - the x coordinate of the position to translate the sprite to in pixels on the window.
	//py - the y coordinate of the position to translate the sprite to in pixels on the window.
    void SetScaleRotationTranslation(const float sx, const float sy, const float rad, const float px, const float py) override;

	//Rotation about a point can be done using an affine transformation matrix that has the rotation and translation already in it.
	//The matrix is used to save on calculations if you need to rotate about a point multiple times with the same rotation and translation.
	//Parameters:
	//radians - the amount to rotate the sprite by in radians.
	//rotationAndTranslationMatrix - a matrix that has the rotation and translation for the rotation about a point already in it.
    void RotateByRadiansUsingMatrixAboutPoint(const float radians, const Matrix& rotationAndTranslationMatrix) override;

    //Updates the world matrix of the graphics object.
    void UpdateWorld() override;

	//Sets when the sprite updates the GraphicsObject_Sprite*'s world matrix.
    //This can be set to update when the sprite is transformed, when it is rendered, both, or never.
    //The default is to update on both transform and render.
	//Parameters:
	//setting - the SpriteAutoUpdateWorldSetting to set the sprite to.
	void SetAutoUpdateWorldSetting(SpriteAutoUpdateWorldSetting setting);


    //------------------------------------------------------------------------------------------------------------------------------------------------
    //Work in progress reflection methods
    //Translation and scaling works but the rotation gets messed up after reflection when used by a sprite collection. It works fine on a single sprite.
    //The world matrix set up is the following:
    //Matrix world = Matrix(TRANS, offsetX, offsetY, 0.f) * Matrix(SCALE, scaleX * flipY, scaleY * flipX, 1.f) * Matrix(Vect(cosAngle, sinAngle, 0.f, 0.f), Vect(-sinAngle, cosAngle, 0.f, 0.f), Vect(0.f, 0.f, 1.f, 0.f), Vect(0.f, 0.f, 0.f, 1.f)) * Matrix(TRANS, posX, posY, 0.f);
    // 
    // 
    virtual void ReflectOverLocalXAxis() override;
    
    virtual void ReflectOverLocalYAxis() override;
    
    virtual void ReflectOverNormalizedVectorFromPoint(const Vect& vector, float pointX, float pointY, BENgineSpriteComponent::FlipType flipType) override;
    //-------------------------------------------------------------------------------------------------------------------------------------------------


protected:


    GraphicsObject_Sprite* ptrGOSprite;

    //Representation of the center of the sprite:
	//                  (0,1)
	// (1,-1)  ___________ ___________ (1,1)
    //        |           |           |
	//		  |           |           |
	//		  |           |           |
    //        |           |           |
	// (-1,0) |___________|___________| (1,0)
    //        |           |           |
    //		  |           |           |
    //		  |           |           |
    //        |           |           |
	//(-1,-1) |___________|___________| (1,-1)
    //                  (0,-1)
    
    //x coordinate of the center of the sprite
	float centerX; 
	//y coordinate of the center of the sprite
	float centerY; 

    // The x offset of the sprite in pixels.This is used to offset the world matrix by the sprites center point.
    float offsetX;
    //The y offset of the sprite in pixels. This is used to offset the world matrix by the sprites center point.
    float offsetY; 

	//Used to determine when the sprite updates the world matrix of the GraphicsObject_Sprite*.
    SpriteAutoUpdateWorldSetting updateWorldSetting;
    
};

#endif _BENgineSprite