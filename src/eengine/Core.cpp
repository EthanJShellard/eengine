#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <rend/rend.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "Core.h"
#include "Entity.h"
#include "Input.h"
#include "Debug.h"
#include "Environment.h"
#include "Camera.h"
#include "Resources.h"
#include "RenderContext.h"
#include "AudioContext.h"
#include "PhysicsContext.h"

#define DEFAULT_WINDOW_WIDTH 1200
#define DEFAULT_WINDOW_HEIGHT 800

namespace eengine
{
	Core::Core() 
	{
		m_running = false;
		m_window = NULL;

		m_input = std::make_shared<Input>();
		m_mainCamera = std::make_shared<Camera>();
		m_renderContext = shared<RenderContext>(new RenderContext());
		m_audioContext = shared<AudioContext>(new AudioContext());
		m_audioContext->Initialise();
		m_physicsContext = shared<PhysicsContext>(new PhysicsContext());
		m_physicsContext->m_maxSubSteps = 5;
	}

	Core::~Core() 
	{
		SDL_GL_DeleteContext(SDL_GL_GetCurrentContext());
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	shared<Core> Core::Initialise(const char* _projectWorkingDirectory)
	{
		// std::make_shared cannot access private constructor, so call it manually.
		shared<Core> rtn = shared<Core>(new Core());

		// Store self reference.
		rtn->m_self = rtn;
		rtn->m_environment = shared<Environment>(new Environment());

		// Set up project working directory path.
#if WIN32
		std::string pwd = std::string(_projectWorkingDirectory);
		pwd = pwd.substr(0, pwd.find_last_of('\\'));
		rtn->m_environment->m_projectWorkingDirectory = pwd;
#elif __EMSCRIPTEN__
		rtn->m_environment->m_projectWorkingDirectory = ".";
#endif

		// Create Resources object with this working directory.
		rtn->m_resources = shared<Resources>(new Resources(rtn->m_environment->GetProjectWorkingDirectory()));
		rtn->m_resources->m_self = rtn->m_resources;

		// Initialise SDL
		Debug::Log("Initialising SDL Video...");

		if (SDL_Init(SDL_INIT_VIDEO) < 0) 
		{
			throw std::exception();
		}

		Debug::Log("Done!");
		Debug::Log("Initiailising SDL Window...");

		rtn->m_window = SDL_CreateWindow("eengine",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		if (!SDL_GL_CreateContext(rtn->m_window))
		{
			throw std::exception();
		}

		Debug::Log("Done!");
		// Done initialising SDL

		// Set up rendering context
		rtn->m_renderContext->Initialise(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

		return rtn;
	}

	void Core::Loop(void* _userData) 
	{
		Core* self = (Core*)_userData;

		// MAIN ENGINE LOOP
		self->m_input->Update();
		self->m_environment->OnFrameStart();

		// Update each entity
		for (shared<Entity> entity : self->m_entities)
		{
			try
			{
				entity->Tick();
			}
			catch (std::runtime_error e)
			{
				Debug::Log(e.what());
				entity->Destroy();
			}
			catch (std::exception e)
			{
				Debug::Log(e.what());
				entity->Destroy();
			}
			catch (...)
			{
				Debug::Log("Caught unknown exception!");
				entity->Destroy();
			}
		}

		// Update physics with any changes from entities components included
		self->m_physicsContext->UpdateFixed(self->m_environment->GetDeltaTime());

		// Update main renderer view matrix using maincamera
		self->m_renderContext->SetMainViewMatrix(glm::inverse(self->m_mainCamera->m_transform->GetModelMatrix()));

		// Clear the main render surface
		self->m_renderContext->ClearAll();

		// Draw all that need drawing
		auto drawItr = self->m_entities.begin();
		while (drawItr != self->m_entities.end())
		{
			(*drawItr)->Display(self->m_renderContext);
			drawItr++;
		}

		// Swap buffers to display rendered content
		SDL_GL_SwapWindow(self->m_window);

		// Clean up destroyed entities
		auto itr = self->m_entities.begin();
		while (itr != self->m_entities.end())
		{
			if ((*itr)->IsDestroyed())
			{
				itr = self->m_entities.erase(itr);
			}
			else
			{
				itr++;
			}
		}
		// Only here for testing while we don't have a real engine loop.
		if (self->m_input->GetHasQuit())
		{
			self->Stop();
		}

		//std::string str = "deltaTime: ";
		//str.append( std::to_string(m_environment->GetDeltaTime()));
		//Debug::Log(str);
	}

	void Core::Start() 
	{
		m_running = true;

#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop_arg(Loop, (void*)this, 0, 1);
#else
		while (m_running)
		{
			Loop((void*)this);
		}
#endif
		
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
}

