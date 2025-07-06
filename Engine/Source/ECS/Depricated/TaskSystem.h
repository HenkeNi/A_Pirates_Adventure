#pragma once

// Thread pool

// namespace HiEngine_ECS

class TaskSystem
{
public:
	
	void RegisterTask();
	void ExecuteTasks(const std::function<void()>& task); // static? takes in Components&...? or arche types?

private:

	// vector of function ptrs? 



	// update tasks
	// event tasks
};