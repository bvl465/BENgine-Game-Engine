#include "SceneChangeStrategy.h"
#include "SceneManagerAttorney.h"
#include "Scene.h"
void SceneChangeStrategy::SetNextScene(Scene* s)
{
	scene = s;
}

void SceneChangeStrategy::Execute()
{
	assert(scene != nullptr);
	SceneManagerAttorney::SceneStrategy::ChangeScene(scene);
}
