#include <iostream>
#include <string>

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

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

namespace eengine
{
	Core::Core() :
		m_running(false),
		m_window(nullptr)
	{
		m_input = std::make_shared<Input>();
		m_mainCamera = std::make_shared<Camera>();
		m_renderContext = shared<RenderContext>(new RenderContext());
		m_audioContext = shared<AudioContext>(new AudioContext());
		m_audioContext->Initialise();
		m_physicsContext = shared<PhysicsContext>(new PhysicsContext());
	}

	Core::~Core() 
	{
		SDL_GL_DeleteContext(m_SDL_GLContext);
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

		rtn->m_SDL_GLContext = SDL_GL_CreateContext(rtn->m_window);
		if (!rtn->m_SDL_GLContext)
		{
			throw std::exception();
		}

		SDL_GL_SetSwapInterval(0);

		Debug::Log("Done!");
		// Done initialising SDL

		// Set up rendering context
		rtn->m_renderContext->Initialise(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

		// Provide input with the SDL window
		rtn->m_input->m_window = rtn->m_window;

		return rtn;
	}

	void Core::Loop(void* _userData) 
	{
		Core* self = (Core*)_userData;

		// MAIN ENGINE LOOP
		self->m_input->Update();
		self->m_environment->OnFrameStart();

		float deltaTime = self->m_environment->GetDeltaTime();

		// Update each entity
		for (shared<Entity> entity : self->m_entities)
		{
			try
			{
				entity->Tick(deltaTime);
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

		// Update physics with any changes from ticks included
		self->m_physicsContext->UpdateFixed(deltaTime);

		// Perform late update with each entity
		for (shared<Entity> entity : self->m_entities)
		{
			try
			{
				entity->LateTick(self->m_environment->GetDeltaTime());
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
				(*itr)->OnDelete();
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
	}

	void Core::Start() 
	{
		m_running = true;

		// Do a quick input update to flush out initial data
		m_input->Update();

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

	glm::vec2 Core::GetWindowDimensions() const
	{
		int width, height;
		SDL_GetWindowSize(m_window, &width, &height);
		return glm::vec2(width, height);
	}
}

