//Ben La Monica
#pragma once
#ifndef _SceneManagerStrategyBase
#define _SceneManagerStrategyBase

class SceneManagerStrategyBase
{
public:

	SceneManagerStrategyBase() = default;
	SceneManagerStrategyBase(const SceneManagerStrategyBase&) = delete;
	SceneManagerStrategyBase& operator=(const SceneManagerStrategyBase&) = delete;
	~SceneManagerStrategyBase() = default;

	virtual void Execute() = 0;

private:

	//Nothing for now

};
#endif _SceneManagerStrategyBase