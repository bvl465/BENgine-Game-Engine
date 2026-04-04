#include "Axis.h"
#include "../src/BENgine/Scene/SceneManager.h"
#include "../src/BENgine/Scene/Scene.h"
#include "../src/BENgine/Asset Managers/Shader Manager/ShaderManager.h"
#include "../src/BENgine/Asset Managers/Texture Manager/TextureManager.h"
#include "../src/BENgine/Asset Managers/Model Manager/ModelManager.h"
#include "../src/BENgine/Camera/CameraManager.h"
#include "../src/BENgine/BENgine.h"
Axis::Axis()
{
	pGObj_Axis = new GraphicsObject_ColorNoTexture(ModelManager::GetModel("pModelAxis"), ShaderManager::GetShaderObject("pShaderObject_colorNoTexture"));
	Matrix world;

	// Axis and Plane
	world = Matrix(IDENTITY);
	pGObj_Axis->SetWorld(world);
	//SceneManager::GetCurrentScene()->Register((Drawable*)this);
	Drawable::SubmitDrawRegistration();
}

Axis::~Axis()
{
	//SceneManager::GetCurrentScene()->Deregister((Drawable*)this);
	Drawable::SubmitDrawDeregistration();
	delete pGObj_Axis;
}


void Axis::Draw()
{
	pGObj_Axis->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}
