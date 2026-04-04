#include "WorldPlane.h"
#include "../src/BENgine/Asset Managers/Shader Manager/ShaderManager.h"
#include "../src/BENgine/Asset Managers/Texture Manager/TextureManager.h"
#include "../src/BENgine/Asset Managers/Model Manager/ModelManager.h"
#include "../src/BENgine/Camera/CameraManager.h"
#include "../src/BENgine/Scene/SceneManager.h"
#include "../src/BENgine/Scene/Scene.h"
WorldPlane::WorldPlane()
{
	pGObj_WorldPlane = new GraphicsObject_TextureFlat(ModelManager::GetModel("pModelPlane"), ShaderManager::GetShaderObject("pShaderObject_texture"), TextureManager::GetTexture("pTextPlane"));
	Matrix world;
	world = Matrix(IDENTITY);
	pGObj_WorldPlane->SetWorld(world);
	Drawable::SubmitDrawRegistration();

}

WorldPlane::~WorldPlane()
{
	Drawable::SubmitDrawDeregistration();
	delete pGObj_WorldPlane;

}


void WorldPlane::Draw()
{
	pGObj_WorldPlane->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}
