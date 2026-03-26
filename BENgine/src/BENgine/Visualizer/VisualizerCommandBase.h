//Ben La Monica
#pragma once
#ifndef _VisualizerCommandBase
#define _VisualizerCommandBase

class VisualizerCommandBase
{
public:

	VisualizerCommandBase() = default;
	VisualizerCommandBase(const VisualizerCommandBase&) = delete;
	VisualizerCommandBase& operator=(const VisualizerCommandBase&) = delete;
	virtual ~VisualizerCommandBase() = default;

	virtual void Execute() = 0;
	virtual void Recycle() = 0; //This is the only difference between this and the CommandBase

private:

	//Nothing for now

};
#endif _VisualizerCommandBase