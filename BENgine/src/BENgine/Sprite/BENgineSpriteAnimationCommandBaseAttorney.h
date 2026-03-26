//Ben La Monica
#pragma once
#ifndef _BENgineSpriteAnimationCommandBaseAttorney
#define _BENgineSpriteAnimationCommandBaseAttorney

#include "BENgineSpriteAnimationCommandBase.h"

class BENgineSpriteAnimationCommandBaseAttorney
{
public:
	class Timer
	{
		friend class BENgineSpriteAnimationTimer;
	private:
		static void TriggerExecute(BENgineSpriteAnimationCommandBase* cmd) { cmd->TriggerExecute(); }
		static void SetTimelineStorageEntryRef(BENgineSpriteAnimationCommandBase* cmd, BENgineSpriteAnimationTimer::TimeLineMapStorageEntryRef entryRef) { cmd->SetTimelineStorageEntryRef(entryRef); }
		static void SetPendingStorageEntryRef(BENgineSpriteAnimationCommandBase* cmd, BENgineSpriteAnimationTimer::PendingTimerListStorageEntryRef entryRef) { cmd->SetPendingStorageEntryRef(entryRef); }
	};
};
#endif _BENgineSpriteAnimationCommandBaseAttorney