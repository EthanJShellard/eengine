#include <unordered_map>

#include <SDL2/SDL_keycode.h>
#include <glm/glm.hpp>

#include "NonCopyable.h"
#include "eengine_defines.h"

namespace eengine 
{
	// struct to encapsulate keycodes
	enum class KeyCode
	{
		// Numerals
		zero  = SDLK_0,
		one   = SDLK_1,
		two   = SDLK_2,
		three = SDLK_3,
		four  = SDLK_4,
		five  = SDLK_5,
		six   = SDLK_6,
		seven = SDLK_7,
		eight = SDLK_8,
		nine  = SDLK_9,
		// Symbols
		ampersand         = SDLK_AMPERSAND,
		asterix           = SDLK_ASTERISK,
		at                = SDLK_AT,
		caret             = SDLK_CARET,
		colon             = SDLK_COLON,
		dollar            = SDLK_DOLLAR,
		exclaimation      = SDLK_EXCLAIM,
		greater           = SDLK_GREATER,
		less              = SDLK_LESS,
		hash              = SDLK_HASH,
		percent           = SDLK_PERCENT,
		plus              = SDLK_PLUS,
		minus             = SDLK_MINUS,
		equals            = SDLK_EQUALS,
		question          = SDLK_QUESTION,
		double_quote      = SDLK_QUOTEDBL,
		apostrophe        = SDLK_QUOTE,
		underscore        = SDLK_UNDERSCORE,
		comma             = SDLK_COMMA,
		backslash         = SDLK_BACKSLASH,
		slash             = SDLK_SLASH,
		semicolon         = SDLK_SEMICOLON,
		left_bracket      = SDLK_LEFTBRACKET,
		right_bracket     = SDLK_RIGHTBRACKET,
		left_parenthesis  = SDLK_LEFTPAREN,
		right_parenthesis = SDLK_RIGHTPAREN,
		period            = SDLK_PERIOD,
		// Letters
		a = SDLK_a,
		b = SDLK_b,
		c = SDLK_c,
		d = SDLK_d,
		e = SDLK_e,
		f = SDLK_f,
		g = SDLK_g,
		h = SDLK_h,
		i = SDLK_i,
		j = SDLK_j,
		k = SDLK_k,
		l = SDLK_l,
		m = SDLK_m,
		n = SDLK_n,
		o = SDLK_o,
		p = SDLK_p,
		q = SDLK_q,
		r = SDLK_r,
		s = SDLK_s,
		t = SDLK_t,
		u = SDLK_u,
		v = SDLK_v,
		w = SDLK_w,
		x = SDLK_x,
		y = SDLK_y,
		z = SDLK_z,
		// Function keys
		F1  = SDLK_F1,
		F2  = SDLK_F2,
		F3  = SDLK_F3,
		F4  = SDLK_F4,
		F5  = SDLK_F5,
		F6  = SDLK_F6,
		F7  = SDLK_F7,
		F8  = SDLK_F8,
		F9  = SDLK_F9,
		F10 = SDLK_F10,
		F11 = SDLK_F11,
		F12 = SDLK_F12,
		F13 = SDLK_F13,
		F14 = SDLK_F14,
		F15 = SDLK_F15,
		F16 = SDLK_F16,
		F17 = SDLK_F17,
		F18 = SDLK_F18,
		F19 = SDLK_F19,
		F20 = SDLK_F20,
		F21 = SDLK_F21,
		F22 = SDLK_F22,
		F23 = SDLK_F23,
		F24 = SDLK_F24,
		// Audio control
		audio_mute     = SDLK_AUDIOMUTE,
		audio_next     = SDLK_AUDIONEXT,
		audio_previous = SDLK_AUDIOPREV,
		audio_play     = SDLK_AUDIOPLAY,
		audio_stop     = SDLK_AUDIOSTOP,
		volume_down    = SDLK_VOLUMEDOWN,
		volume_up      = SDLK_VOLUMEUP,
		// Keypad
		keypad_0       = SDLK_KP_0,
		keypad_1       = SDLK_KP_1,
		keypad_2       = SDLK_KP_2,
		keypad_3       = SDLK_KP_3,
		keypad_4       = SDLK_KP_4,
		keypad_5       = SDLK_KP_5,
		keypad_6       = SDLK_KP_6,
		keypad_7       = SDLK_KP_7,
		keypad_8       = SDLK_KP_8,
		keypad_9       = SDLK_KP_9,
		keypad_slash   = SDLK_KP_DIVIDE,
		keypad_equals  = SDLK_KP_EQUALS,
		keypad_plus    = SDLK_KP_PLUS,
		keypad_minus   = SDLK_KP_MINUS,
		keypad_asterix = SDLK_KP_MULTIPLY,
		keypad_enter   = SDLK_KP_ENTER,
		keypad_period  = SDLK_KP_PERIOD,
		// Modifier keys
		left_alt    = SDLK_LALT,
		left_ctrl   = SDLK_LCTRL,
		left_shift  = SDLK_LSHIFT,
		right_alt   = SDLK_RALT,
		right_ctrl  = SDLK_RCTRL,
		right_shift = SDLK_RSHIFT,
		// Arrow keys
		up    = SDLK_UP,
		right = SDLK_RIGHT,
		down  = SDLK_DOWN,
		left  = SDLK_LEFT,
		// Other keys
		backspace    = SDLK_BACKSPACE,
		capslock     = SDLK_CAPSLOCK,
		numlock      = SDLK_NUMLOCKCLEAR,
		scrolllock   = SDLK_SCROLLLOCK,
		del          = SDLK_DELETE,
		escape       = SDLK_ESCAPE,
		home         = SDLK_HOME,
		insert       = SDLK_INSERT,
		page_up      = SDLK_PAGEUP,
		page_down    = SDLK_PAGEDOWN,
		pause        = SDLK_PAUSE,
		print_screen = SDLK_PRINTSCREEN,
		enter        = SDLK_RETURN,
		space        = SDLK_SPACE,
		tab          = SDLK_TAB
	};

	/// @brief Simple information on the state of a key, including whether it's currently down and the last time it was updated.
	struct KeyState 
	{
		KeyState(bool _down, uint64_t _updateID) :
			down(_down)
		{
			if (_down) 
			{
				lastUpdatePressed = _updateID;
			}
			else 
			{
				lastUpdateReleased = _updateID;
			}
		}

		bool down = false;
		// The last update in which this key was pressed down
		uint64_t lastUpdatePressed = 0;
		uint64_t lastUpdateReleased = 0;
	};

	/// @brief Class which encapsulates input handling for the keyboard and mouse.
	class Input : private NonCopyable
	{
		friend class Core;

	private:
		glm::vec2 m_mousePos;
		glm::vec2 m_mouseDelta;
		glm::vec2 m_mouseScroll;
		bool m_mouse1Pressed;
		bool m_mouse2Pressed;
		bool m_mouse3Pressed;
		bool m_quit;
		float m_mouseSensitivity;
		uint64_t m_updateCount;

		std::unordered_map<int, KeyState> m_keys;

		SDL_Window* m_window;

		// Update the input state. Should be called at the beginning of a frame/update.
		void Update();
	public:
		
		Input();

		/// @brief Get whether a key is being pressed.
		/// @param _key The key to check.
		/// @return Whether or not _key is currently being pressed.
		bool GetKey(KeyCode _key) const;

		/// @brief Get whether a key was pressed this update.
		/// @param _key The key to check.
		/// @return Whether or not the key was pressed this update.
		bool GetKeyDown(KeyCode _key) const;
	
		/// @brief Get whether a key was released this update.
		/// @param _key The key to check.
		/// @return Whether or not the key was released this update.
		bool GetKeyUp(KeyCode _key) const;
		
		/// @brief Get the movement of the mouse since the last update.
		/// @return A vector containing the horizontal and vertical movement of the mouse.
		glm::vec2 GetMouseDelta() const;

		/// @brief Get the movement of the mouse scrollwheel since the last update.
		/// @return A vector containing the horizontal and vertical movement of the mousewheel.
		glm::vec2 GetMouseWheelScroll() const;

		/// @brief Check whether the the process has received a quit signal.
		/// @return Whether or not the process has been told to quit.
		bool GetHasQuit() const;

		/// @brief Get the current mouse sensitivity.
		/// @return The current mouse sensitivity.
		float GetMouseSensitivity() const;

		/// @brief Set a new mouse sensitivity.
		/// @param _newSens The new mouse sensitivity.
		void SetMouseSensitivity(float _newSens);

		/// @brief Check whether mouse 1 (usually the left mouse button) is currently pressed.
		/// @return Whether or not mouse 1 is pressed.
		bool Mouse1Down() const;

		/// @brief Check whether mouse 2 (usually the right mouse button) is currently pressed.
		/// @return Whether or not mouse 2 is pressed.
		bool Mouse2Down() const;

		/// @brief Check whether mouse 3 (usually the middle mouse button) is currently pressed.
		/// @return Whether or not mouse 3 is pressed.
		bool Mouse3Down() const;

		/// @brief Reset the mouse cursor position to the centre of window.
		void ResetMousePosition();

		/// @brief Set whether or not the window should grab input, not allowing the mouse to exit the window.
		/// @param _lock Which input grab mode should be set.
		void SetInputGrab(bool _lock);

		/// @brief Get whether the window is set to grab input.
		/// @return Whether or not the window will grab input.
		bool GetInputGrab() const;

		/// @brief Set whether or not we should use relative mouse delta inputs.
		/// @param _relativeMouseMode The new relative mouse mode.
		void SetRelativeMouseMode(bool _relativeMouseMode) const;
	};
}