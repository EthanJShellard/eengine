#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Core.h"
#include "Entity.h"

namespace eengine
{
	void Core::TestFunction()
	{
		std::cout << "Test Function Success!!" << std::endl;
	}
	
	Core::Core() 
	{
		m_running = false;
		m_window = NULL;
	}

	Core::~Core() 
	{
		SDL_DestroyWindow(m_window);
	}

	shared<Core> Core::Initialise() 
	{
		// std::make_shared cannot access private constructor, so call it manually
		shared<Core> rtn = shared<Core>(new Core());

		rtn->m_self = rtn;

		// START SDL WINDOW TEST
		if (SDL_Init(SDL_INIT_VIDEO) < 0) 
		{
			throw std::exception();
		}

		rtn->m_window = SDL_CreateWindow("eengine",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			600, 400, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		if (!SDL_GL_CreateContext(rtn->m_window)) 
		{
			throw std::exception();
		}

		if (glewInit() != GLEW_OK)
		{
			throw std::exception();
		}
		// END SDL WINDOW TEST

		return rtn;
	}

	void Core::Start() 
	{
		m_running = true;

		while (m_running) 
		{
			// MAIN ENGINE LOOP

			// Update each entity
			for (shared<Entity> entity : m_entities) 
			{
				entity->Tick();
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
			if (m_entities.empty()) Stop();
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
		m_entities.push_back(rtn);

		return rtn;
	}
}

