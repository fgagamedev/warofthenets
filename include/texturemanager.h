#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <string>
#include "SDL2/SDL.h"
#include "text.h"

using namespace std;

class TextureManager{

public:

	static TextureManager* Instance();

	bool loadImage(string, string, SDL_Renderer*);
	void addText(Text *);

	void draw(string, int, int, SDL_Renderer*, SDL_RendererFlip=SDL_FLIP_NONE);
	void drawFrame(string, int, int,int, int, int, int, SDL_Renderer *, double, SDL_RendererFlip=SDL_FLIP_NONE);

	SDL_Texture* getTexture(string);
	void clearTextureMap();
    void clearFromTextureMap(string imageId);

private:
	
	TextureManager(){};

	map<std::string, SDL_Texture*>	textureMap;
	map<std::string, int> textureCount;
	static TextureManager* instance;

};


#endif
