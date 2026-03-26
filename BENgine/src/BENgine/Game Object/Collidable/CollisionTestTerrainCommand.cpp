#include "CollisionTestTerrainCommand.h"
#include "CollidableGroup.h"
#include "CollisionDispatchBase.h"
#include "Collidable.h"
#include "../../Math Tools/BENgineMathTools.h"
#include "../../Terrain/TerrainObject.h"
#include "../../Terrain/TerrainManager.h"
#include "../../Terrain/TerrainRectangleArea.h"
#include "../../Terrain/TRAIterator.h"	
#include "../../Scene/SceneManager.h"
#include "../../Scene/Scene.h"
#include "../../Collision/CollisionVolumeBSphere.h"
#include "../../Collision/CollisionVolumeAABB.h"


CollisionTestTerrainCommand::~CollisionTestTerrainCommand()
{
	delete pDispatch;
	delete pTerrainCellAABB;
}

CollisionTestTerrainCommand::CollisionTestTerrainCommand(CollidableGroup* g1, CollisionDispatchBase* pd) : pG1(g1), pDispatch(pd)
{
	pTerrainCellAABB = new CollisionVolumeAABB();
}

void CollisionTestTerrainCommand::Execute()
{
	TerrainObject* terrain = SceneManager::GetCurrentScene()->GetTerrainManager()->GetCurrentTerrain();
	const CollidableGroup::CollidableCollection& Collection1 = pG1->GetColliderCollection();
	
	for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
	{
		Collidable* col = (*it1);

		TerrainRectangleArea CandidateCells = TerrainRectangleArea(col, terrain);
		const CollisionVolumeBSphere& pBS1 = (*it1)->GetBSphere();
		if (CandidateCells.begin() == CandidateCells.end())
		{
			CellMinMaxVects minMax = CandidateCells.begin().GetMinMaxVects();
			pTerrainCellAABB->SetMinMax(minMax.Min, minMax.Max);
			if (BENgineMathTools::AABBToBSphereIntersect(*pTerrainCellAABB, pBS1) == false)
			{
				continue; //if the AABB of the cell does not intersect the BSphere then continue to the next cell
			}
			const CollisionVolume& cv1 = (*it1)->GetCollisionVolume();

			const CollisionVolumeAABB& cellAABB = *pTerrainCellAABB; // Cast to AABB for intersection check
			if (BENgineMathTools::Intersect(cv1, cellAABB))
			{
				pDispatch->ProcessCallbacks(*it1, nullptr);
				//No need to check the rest of the cells since we already found a collision
				break;
			}
			continue; //if there are no candidate cells then continue to the next collidable
		}
		else {
			for (TRAIterator itCell = CandidateCells.begin(); itCell != CandidateCells.end(); itCell++)
			{
				CellMinMaxVects minMax = itCell.GetMinMaxVects();
				pTerrainCellAABB->SetMinMax(minMax.Min, minMax.Max);
				if (BENgineMathTools::AABBToBSphereIntersect(*pTerrainCellAABB, pBS1) == false)
				{
					continue; //if the AABB of the cell does not intersect the BSphere then continue to the next cell
				}
				const CollisionVolume& cv1 = (*it1)->GetCollisionVolume();

				const CollisionVolumeAABB& cellAABB = *pTerrainCellAABB; // Cast to AABB for intersection check
				if (BENgineMathTools::Intersect(cv1, cellAABB))
				{
					pDispatch->ProcessCallbacks(*it1, nullptr);
					//No need to check the rest of the cells since we already found a collision
					break;
				}
			}
			CellMinMaxVects minMax = CandidateCells.end().GetMinMaxVects();
			pTerrainCellAABB->SetMinMax(minMax.Min, minMax.Max);
			if (BENgineMathTools::AABBToBSphereIntersect(*pTerrainCellAABB, pBS1) == false)
			{
				continue; //if the AABB of the cell does not intersect the BSphere then continue to the next cell
			}
			const CollisionVolume& cv1 = (*it1)->GetCollisionVolume();

			const CollisionVolumeAABB& cellAABB = *pTerrainCellAABB; // Cast to AABB for intersection check
			if (BENgineMathTools::Intersect(cv1, cellAABB))
			{
				pDispatch->ProcessCallbacks(*it1, nullptr);
				//No need to check the rest of the cells since we already found a collision
				break;
			}

		}
		
	}
}
