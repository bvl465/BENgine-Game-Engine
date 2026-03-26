//Ben La Monica
#pragma once
#ifndef _SceneNull
#define _SceneNull
#include "Scene.h"

class SceneNull : public Scene
{
public:
	SceneNull() = default;
	SceneNull(const SceneNull&) = delete;
	SceneNull& operator=(const SceneNull&) = delete;
	~SceneNull();


private:
	virtual void Initialize() override;
	virtual void SceneEnd() override;

};
#endif _SceneNull