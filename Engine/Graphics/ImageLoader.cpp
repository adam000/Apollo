#include "ImageLoader.h"
#include "Utilities/ResourceManager.h"

namespace Graphics
{

namespace ImageLoader
{

SDL_Surface* Zip(SDL_Surface* colour, SDL_Surface* alpha)
{
	assert(colour->w == alpha->w);
	assert(colour->h == alpha->h);
	SDL_Surface* sfc = SDL_CreateRGBSurface(SDL_SWSURFACE, colour->w, colour->h, 32,
	                                        0x000000FF,
	                                        0x0000FF00,
	                                        0x00FF0000,
	                                        0xFF000000);
	const char* cpixels = static_cast<const char*>(colour->pixels);
	const char* apixels = static_cast<const char*>(alpha->pixels);
	char* dpixels = static_cast<char*>(sfc->pixels);
	int pixcount = colour->w * colour->h;
	for (int i = 0; i < pixcount; ++i)
	{
		uint8_t cR, cG, cB, aR, dead;
		uint32_t res;
		SDL_GetRGBA(*(uint32_t*)cpixels, colour->format, &cR, &cG, &cB, &dead);
		SDL_GetRGBA(*(uint32_t*)apixels, alpha->format, &aR, &dead, &dead, &dead);
		res = SDL_MapRGBA(sfc->format, cR, cG, cB, aR);
		memcpy(dpixels, &res, sfc->format->BytesPerPixel);
		cpixels += colour->format->BytesPerPixel;
		apixels += alpha->format->BytesPerPixel;
		dpixels += sfc->format->BytesPerPixel;
	}
	return sfc;
}

SDL_Surface* LoadImage ( const std::string& path )
{
	SDL_RWops* rwops = ResourceManager::OpenFile(path);
	if (!rwops)
		return NULL;
	SDL_Surface* surface = IMG_LoadTyped_RW(rwops, 1, const_cast<char*>("PNG"));
	return surface;
}

GLuint CreateTexture ( SDL_Surface* surface, bool autofree, bool rectangle )
{
	GLuint texID;
	glGenTextures(1, &texID);
	GLenum target = rectangle ? GL_TEXTURE_RECTANGLE_ARB : GL_TEXTURE_2D;
	glBindTexture(target, texID);
	bool mipmaps = !rectangle && strstr((const char*)glGetString(GL_EXTENSIONS), "GL_SGIS_generate_mipmap");
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, mipmaps ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (mipmaps)
		glTexParameteri(target, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
	if (surface->format->BytesPerPixel == 3)
	{
		GLenum format = (surface->format->Rmask) != 0xFF ? GL_BGR_EXT : GL_RGB;
		glTexImage2D(target, 0, GL_RGB,
					 surface->w, surface->h, 0,
					 format, GL_UNSIGNED_BYTE, surface->pixels);
	}
	else
	{
		GLenum format = (surface->format->Rmask) != 0xFF ? GL_BGRA_EXT : GL_RGBA;
		glTexImage2D(target, 0, GL_RGBA,
					 surface->w, surface->h, 0,
					 format, GL_UNSIGNED_BYTE, surface->pixels);
	}
	if (autofree)
		SDL_FreeSurface(surface);
	return texID;
}

}

}
