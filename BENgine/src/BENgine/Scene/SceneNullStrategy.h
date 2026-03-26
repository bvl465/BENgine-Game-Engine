//Ben La Monica
#pragma once
#ifndef _SceneNullStrategy
#define _SceneNullStrategy
#include "SceneManagerStrategyBase.h"
class SceneNullStrategy : public SceneManagerStrategyBase
{
public:
	SceneNullStrategy() = default;
	SceneNullStrategy(const SceneNullStrategy&) = delete;
	SceneNullStrategy& operator=(const SceneNullStrategy&) = delete;
	~SceneNullStrategy() = default;

	virtual void Execute() override;

private:

};
#endif _SceneNullStrategy