#include "Pch.h"
#include "ThreadPool.h"

namespace Hi_Engine
{
	ThreadPool::ThreadPool(std::size_t numThreads)
		: m_isActive{ true }
	{
		assert(numThreads > 0 && "[ThreadPool::ThreadPool] - To few threads!");

		for (std::size_t i = 0; i < numThreads; ++i)
		{
			m_workers.emplace_back(std::thread([this]() { RunTask(); }));
		}
	}

	ThreadPool::~ThreadPool()
	{
		{
			std::unique_lock<std::mutex> lock(m_queueMutex);
			m_isActive = false;

			m_cv.notify_all();
		}

		for (auto& worker : m_workers)
		{
			if (worker.m_thread.joinable())
				worker.m_thread.join();
		}
	}

	void ThreadPool::AddTask(const Task& task)
	{
		std::lock_guard<std::mutex> queue_lock{ m_queueMutex };

		m_taskQueue.push(std::move(task));
		m_cv.notify_one();
	}

	void ThreadPool::AddTask(Task&& task)
	{
		std::lock_guard<std::mutex> queue_lock{ m_queueMutex };

		m_taskQueue.push(std::move(task));
		m_cv.notify_one();
	}

	void ThreadPool::RunTask()
	{
		while (true)
		{
			std::unique_lock<std::mutex> lock(m_queueMutex);
			m_cv.wait(lock, [this]() { return !m_isActive || !m_taskQueue.empty(); });

			if (!m_isActive && m_taskQueue.empty()) {
				return; 
			}

			auto task = std::move(m_taskQueue.front());
			m_taskQueue.pop();

			lock.unlock();
			task();
		}
	}
}