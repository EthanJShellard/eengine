#include <GL/glew.h>

namespace eengine 
{
	class Texture 
	{
		GLuint m_id;
		//Create an openGL texture from raw data
		static GLuint CreateTexture(unsigned char* _data, int _width, int _height);
		//Load in texture date from the specified file and return a pointer to the first character of the raw data
		static unsigned char* LoadTextureData(const char* _file, int* _width, int* _height);

		Texture(const char* _path);
		~Texture();
	};
}