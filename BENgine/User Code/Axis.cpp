#include "Axis.h"
#include "../src/BENgine/Scene/SceneManager.h"
#include "../src/BENgine/Scene/Scene.h"
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
