#pragma once
#include "Audio/AudioManager.h"
#include "Rendering/Renderer/Renderer.h"
#include "Input/InputHandler.h"
#include "Window/Window.h"

#include <condition_variable>
#include <mutex>

namespace Hi_Engine
{
	class Application;
	class Timer;

	class Engine
	{
	public:
		Engine(Application* anApp);
		~Engine();

		bool			Init();
		void			Shutdown();
		void			Update();
		void			Render();
		bool			IsRunning() const;

		static Timer&	GetTimer();

	private:
		bool			CreateWindow();		

		//ResourceHolder<Texture2D> m_textureHolder;	// static? in Game?
		//ResourceHolder<Shader>		m_shaderHolder;

		InputHandler	m_inputHandler;
		AudioManager	m_audioManager;
		Application*	m_application;
		// Renderer		m_renderer;
		Window			m_window;
		bool			m_isRunning;



		std::mutex				m_renderingMutex;
		std::mutex				m_mutex;
		std::condition_variable m_cv;
		// bool DataReady;
		std::atomic<bool> DataReady{ false };


		std::thread				m_renderThread;
		std::atomic<bool>		m_isRenderingComplete;		//m_isRenderThreadSynced;
		std::atomic<bool>		m_shouldQuit;		//m_isRenderThreadSynced;



		//std::mutex m_renderMutex;
		//std::condition_variable m_renderCV;




		// std::atomic<bool> isRunning{ true };
	};
}