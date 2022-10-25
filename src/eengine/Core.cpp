#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Core.h"
#include "Entity.h"
#include "Input.h"
#include "Debug.h"
#include "Environment.h"
#include "Camera.h"

namespace eengine
{
	Core::Core() 
	{
		m_running = false;
		m_window = NULL;

		m_input = std::make_shared<Input>();
		m_mainCamera = std::make_shared<Camera>();
	}

	Core::~Core() 
	{
		SDL_DestroyWindow(m_window);
	}

	shared<Core> Core::Initialise(const char* _arg0) 
	{
		// std::make_shared cannot access private constructor, so call it manually
		shared<Core> rtn = shared<Core>(new Core());
		// Store self reference
		rtn->m_self = rtn;
		rtn->m_environment = shared<Environment>(new Environment());
		// Set up project working directory path
		std::string pwd = std::string(_arg0);
		pwd = pwd.substr(0, pwd.find_last_of('\\'));
		rtn->m_environment->m_projectWorkingDirectory = pwd;

		Debug::Log("Initialising SDL Video...");

		if (SDL_Init(SDL_INIT_VIDEO) < 0) 
		{
			throw std::exception();
		}

		Debug::Log("Done!");
		Debug::Log("Initiailising SDL Window...");

		rtn->m_window = SDL_CreateWindow("eengine",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			600, 400, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		if (!SDL_GL_CreateContext(rtn->m_window)) 
		{
			throw std::exception();
		}

		Debug::Log("Done!");
		Debug::Log("Initialising GLEW...");

		if (glewInit() != GLEW_OK)
		{
			throw std::exception();
		}

		Debug::Log("Done!");

		return rtn;
	}

	void Core::Start() 
	{
		m_running = true;

		while (m_running) 
		{
			// MAIN ENGINE LOOP
			m_input->Update();
			m_environment->OnFrameStart();

			// Update each entity
			for (shared<Entity> entity : m_entities) 
			{
				entity->Tick();
			}

			// Draw all that need drawing
			auto drawItr = m_entities.begin();
			while (drawItr != m_entities.end()) 
			{
				(*drawItr)->Display();
				drawItr++;
			}

			// Clean up destroyed entities
			auto itr = m_entities.begin();
			while (itr != m_entities.end()) 
			{
				if ((*itr)->IsDestroyed()) 
				{
					itr = m_entities.erase(itr);
				}
				else 
				{
					itr++;
				}
			}
			// Only here for testing while we don't have a real engine loop.
			if (m_input->GetHasQuit()) 
			{
				Stop();
			}

			std::string str = "deltaTime: ";
			str.append( std::to_string(m_environment->GetDeltaTime()));
			Debug::Log(str);
		}
	}

	void Core::Stop() 
	{
		m_running = false;
	}

	shared<Entity> Core::AddEntity() 
	{
		shared<Entity> rtn = shared<Entity>(new Entity());

		rtn->m_core = m_self;
		rtn->m_self = rtn;
		rtn->m_transform = rtn->AddComponent<Transform>();
		m_entities.push_back(rtn);

		return rtn;
	}

	shared<Environment> Core::GetEnvironment()
	{
		return m_environment;
	}

	shared<Camera> Core::GetMainCamera() 
	{
		return m_mainCamera;
	}
}

