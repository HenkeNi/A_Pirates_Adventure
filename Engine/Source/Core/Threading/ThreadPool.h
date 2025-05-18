#pragma once
#include "../Service/IService.h"

// todo: memory allocator

namespace Hi_Engine
{
	using Task = std::function<void()>;

	struct Worker
	{
		std::thread m_thread;
		// std::atomic<bool> m_isWorking;
	};

	class ThreadPool : public IService
	{
	public:
		ThreadPool(std::size_t numThreads = std::thread::hardware_concurrency());
		~ThreadPool();

		ThreadPool(const ThreadPool&) = delete;
		ThreadPool& operator=(const ThreadPool&) = delete;

		ThreadPool(ThreadPool&&) = default;
		ThreadPool& operator=(ThreadPool&&) = default;

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
