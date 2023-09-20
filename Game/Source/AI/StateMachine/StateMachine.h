#pragma once

class State;

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void Update();
	void RegisterState(State* aState);
	void Clear();

	// Pop, push get current or update..

private:
	std::vector<State*> m_states;
	State*				m_activeState;
};