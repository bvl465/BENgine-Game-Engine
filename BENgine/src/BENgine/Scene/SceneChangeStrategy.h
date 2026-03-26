//Ben La Monica
#pragma once
#ifndef _SceneChangeStrategy
#define _SceneChangeStrategy
#include "SceneManagerStrategyBase.h"
class Scene;
class SceneChangeStrategy : public SceneManagerStrategyBase
{
public:
	SceneChangeStrategy() = default;
	SceneChangeStrategy(const SceneChangeStrategy&) = delete;
	SceneChangeStrategy& operator=(const SceneChangeStrategy&) = delete;
	~SceneChangeStrategy() = default;
	void SetNextScene(Scene* s);


	virtual void Execute() override;

private:
	Scene* scene = nullptr;
};
#endif _SceneChangeStrategy