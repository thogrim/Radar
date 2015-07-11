#pragma once

enum Action{
	NONE,
	POP,
	PUSH,
	SWITCH
};

template<typename T>
class ChangeableContainer
{
public:
	virtual ~ChangeableContainer() {}
	virtual void pendChange(Action action, T* state) = 0;
};

