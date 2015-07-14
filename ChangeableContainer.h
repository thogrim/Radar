#pragma once

template<typename T>
class ChangeableContainer
{
public:
	virtual ~ChangeableContainer() {}
	virtual void pop()=0;
	virtual void push(T* state)=0;
	virtual void change(T* state)=0;
};

