#pragma once
#include "../IService.h"

// todo: memory allocator

namespace Hi_Engine
{
	using Task = std::function<void()>;

	struct Worker
	{
		std::thread m_thread;
		// std::atomic<bool> m_isWorking;
	};
	
	class TaskService : public IService
	{
	public:
		TaskService(std::size_t numThreads = std::thread::hardware_concurrency());
		~TaskService();

		TaskService(const TaskService&) = delete;
		TaskService& operator=(const TaskService&) = delete;

		TaskService(TaskService&&) = default;
		TaskService& operator=(TaskService&&) = default;

		void AddTask(const Task& task);
		void AddTask(Task&& task);

	private:
		void RunTask();

		std::vector<Worker> m_workers;
		std::queue<Task> m_taskQueue;

		std::mutex m_queueMutex;
		std::condition_variable m_cv;

		std::atomic_bool m_isActive;
	};
}
