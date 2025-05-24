#pragma once

namespace Hi_Engine
{
	// TODO; potentially create an implementation that can be reset?

	template <typename Tag>
	class IDGenerator
	{
	public:
		template <typename T>
		[[nodiscard]] static std::size_t GetID();

	private:
		inline static std::size_t s_counter = 0;
	};

	template <typename Tag>
	template <typename T>
	static std::size_t IDGenerator<Tag>::GetID()
	{
		static const std::size_t id = s_counter++;
		return id;
	}
}
