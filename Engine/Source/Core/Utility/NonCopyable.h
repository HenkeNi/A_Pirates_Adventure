#pragma once

	namespace Hi_Engine
	{
		class NonCopyable
		{
		protected:
			NonCopyable() = default;
			~NonCopyable() = default;

			NonCopyable(const NonCopyable&) = delete;
			NonCopyable& operator=(const NonCopyable&) = delete;

			//NonCopyable(NonCopyable&&) = default;
			//NonCopyable& operator=(NonCopyable&&) = default;
		};
	}
