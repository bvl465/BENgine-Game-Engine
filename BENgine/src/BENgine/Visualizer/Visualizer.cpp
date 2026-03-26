#include "Visualizer.h"
#include "../Collision/CollisionVolumeBSphere.h"
#include "../Collision/CollisionVolumeAABB.h"
#include "../Collision/CollisionVolumeOBB.h"
#include "Matrix.h"
#include "CollisionVisualizerBSphereCommand.h"
#include "CollisionVisualizerAABBCommand.h"
#include "CollisionVisualizerOBBCommand.h"
#include "Model.h"
#include "VisualizerCommandPool.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "../Asset Managers/Model Manager/ModelManager.h"
#include "../Asset Managers/Shader Manager/ShaderManager.h"
#include "../Asset Managers/Texture Manager/TextureManager.h"
#include "../Camera/CameraManager.h" //should fix this later
Visualizer* Visualizer::ptrInstance = nullptr;
Vect Visualizer::DEFAULT_COLOR = Vect(0.0f, 0.0f, 1.0f, 1.0f);
VisualizerCommandPool* Visualizer::cmdPool = nullptr;

Visualizer::Visualizer()
{
	this->WFUnitSphere = new GraphicsObject_WireframeConstantColor(ModelManager::GetModel("PModelSphere"), ShaderManager::GetShaderObject("pShaderObject_constantColor"), DEFAULT_COLOR);
	this->WFUnitBox = new GraphicsObject_WireframeConstantColor(ModelManager::GetModel("PModelBox"), ShaderManager::GetShaderObject("pShaderObject_constantColor"), DEFAULT_COLOR);
	this->cmdPool = new VisualizerCommandPool();
	cmdList = CommandList();
	ptrInstance = this;
}

void Visualizer::VisualizeAll()
{
	Instance().privVisualizeAll();
}

void Visualizer::privVisualizeAll()
{
	for (CommandList::iterator it = cmdList.begin(); it != cmdList.end(); it++) {
		(*it)->Execute();
		(*it)->Recycle();
		//could als remove the command from the list here
	}
	cmdList.clear();
}

void Visualizer::ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col)
{
	Instance().privShowBSphere(S, col);
}

void Visualizer::ShowAABB(const CollisionVolumeAABB& S, const Vect& col)
{
	Instance().privShowAABB(S, col);
}

void Visualizer::ShowAABBUsingMinMax(const Vect min, const Vect max, const Vect& col)
{
	Instance().privShowAABBUsingMinMax(min, max, col);
}

void Visualizer::ShowOBB(const CollisionVolumeOBB& S, const Vect& col)
{
	Instance().privShowOBB(S, col);
}

void Visualizer::ShowMarker(const Vect& pos, const Vect& col)
{
	Instance().privShowMarker(pos, col);
}

void Visualizer::ShowVectorFromPoint(const Vect& startingPos, const Vect& direction, const Vect& color, const float width)
{
	Instance().privShowVectorFromPoint(startingPos, direction, color, width);

}

Visualizer& Visualizer::Instance()
{
	if (ptrInstance == nullptr) {
		ptrInstance = new Visualizer();
	}
	return *ptrInstance;
}

void Visualizer::Delete()
{
	if (ptrInstance != nullptr) {
		delete ptrInstance->WFUnitSphere;
		delete ptrInstance->WFUnitBox;
		delete ptrInstance->cmdPool;
		for (CommandList::iterator it = ptrInstance->cmdList.begin(); it != ptrInstance->cmdList.end(); it++) {
			delete (*it);
		}
		ptrInstance->cmdList.clear(); // Use 'this' to refer to the instance member
		delete ptrInstance;
		ptrInstance = nullptr;
	}
}

void Visualizer::RenderBSphere(Matrix& S, const Vect& col)
{
	Instance().privRenderBSphere(S, col);
}

void Visualizer::privRenderBSphere(Matrix& S, const Vect& col)
{
	this->WFUnitSphere->SetColor(col);
	this->WFUnitSphere->SetWorld(S);
	this->WFUnitSphere->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void Visualizer::ReturnBSphereCommand(CollisionVisualizerBSphereCommand* cmd)
{
	Instance().privReturnBSphereCommand(cmd);
}

void Visualizer::privReturnBSphereCommand(CollisionVisualizerBSphereCommand* cmd)
{
	this->cmdPool->ReturnBSphereCommand(static_cast<CollisionVisualizerBSphereCommand*>(cmd));
}

void Visualizer::privShowBSphere(const CollisionVolumeBSphere& S, const Vect& col)
{
	CollisionVisualizerBSphereCommand* cmd = cmdPool->GetBSphereCommand();

	cmd->Initialize(col, S.GetCenter(), S.GetRadius());

	cmdList.push_back(cmd);
}

void Visualizer::RenderAABB(Matrix& aabb, const Vect& col)
{
	Instance().privRenderAABB(aabb, col);
}

void Visualizer::privRenderAABB(Matrix& aabb, const Vect& col)
{
	this->WFUnitBox->SetColor(col);
	this->WFUnitBox->SetWorld(aabb);
	this->WFUnitBox->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void Visualizer::ReturnAABBCommand(CollisionVisualizerAABBCommand* cmd)
{
	Instance().privReturnAABBCommand(cmd);
}

void Visualizer::privReturnAABBCommand(CollisionVisualizerAABBCommand* cmd)
{
	this->cmdPool->ReturnAABBCommand(static_cast<CollisionVisualizerAABBCommand*>(cmd));
}

void Visualizer::privShowAABB(const CollisionVolumeAABB& aabb, const Vect& col)
{
	CollisionVisualizerAABBCommand* cmd = cmdPool->GetAABBCommand();

	cmd->Initialize(col, aabb.GetCornerMin(), aabb.GetCornerMax());

	cmdList.push_back(cmd);
}

void Visualizer::privShowAABBUsingMinMax(const Vect min, const Vect max, const Vect& col)
{
	CollisionVisualizerAABBCommand* cmd = cmdPool->GetAABBCommand();

	cmd->Initialize(col, min, max);

	cmdList.push_back(cmd);
}

void Visualizer::RenderOBB(Matrix& obb, const Vect& col)
{
	Instance().privRenderOBB(obb, col);
}

void Visualizer::privRenderOBB(Matrix& obb, const Vect& col)
{
	this->WFUnitBox->SetColor(col);
	this->WFUnitBox->SetWorld(obb);
	this->WFUnitBox->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void Visualizer::ReturnOBBCommand(CollisionVisualizerOBBCommand* cmd)
{
	Instance().privReturnOBBCommand(cmd);
}

void Visualizer::privReturnOBBCommand(CollisionVisualizerOBBCommand* cmd)
{
	cmdPool->ReturnOBBCommand(static_cast<CollisionVisualizerOBBCommand*>(cmd));
}

void Visualizer::privShowOBB(const CollisionVolumeOBB& obb, const Vect& col)
{
	CollisionVisualizerOBBCommand* cmd = cmdPool->GetOBBCommand();
	cmd->Initialize(obb.GetWorld(), col, obb.GetCornerMin(), obb.GetCornerMax());
	cmdList.push_back(cmd);
}

void Visualizer::privShowVectorFromPoint(const Vect& startingPos, const Vect& direction, const Vect& color, const float width)
{
	CollisionVisualizerOBBCommand* cmd = cmdPool->GetOBBCommand();
	const Vect endPoint = startingPos + direction;
	const float scale = direction.mag();
	const Vect center = (startingPos + direction);
	Matrix world = Matrix(SCALE, width, width, scale) * Matrix(ROT_ORIENT, direction, Vect(0.f, 1.f, 0.f)) * Matrix(TRANS, center);
	cmd->Initialize(world, color, Vect(1.f, 1.f, 1.f), Vect(-1.f, -1.f, -1.f)); // Set the corner min and max to -1, -1, -1 and 1, 1, 1 for a unit box
	cmdList.push_back(cmd);
	//CollisionVisualizerOBBCommand* cmd = cmdPool->GetOBBCommand();
	
}

void Visualizer::privShowMarker(const Vect& pos, const Vect& col)
{
	Visualizer::ShowAABBUsingMinMax(Vect(pos.X() - .25f, pos.Y() - .25f, pos.Z() - .25f), Vect(pos.X() + .25f, pos.Y() + .25f, pos.Z() + .25f), col);
}

