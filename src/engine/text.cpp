#include "text.h"

Text::Text(string value, int size, int style)
{
	this->value = value;
	this->size = size;
	this->style = style;

	if(!TTF_WasInit())
	{
		TTF_Init();
		atexit(TTF_Quit);
	}
}

Text::~Text()
{
	if(this->font != NULL)
		TTF_CloseFont(this->font);
	if(this->text != NULL)
		SDL_DestroyTexture(this->text);
}

void 
Text::setFont(string fontPath)
{
	this->fontPath = fontPath;
	if(this->font != NULL)
		TTF_CloseFont(this->font);

	this->font = TTF_OpenFont(this->fontPath.c_str(), this->size);
	if(this->font == NULL)
	{
		//errorlog
		return;
	}
	
	this->setStyle(this->style);
}

void 
Text::setStyle(int style)
{
	this->style = style;
	if(this->font != NULL)
		TTF_SetFontStyle(this->font, this->style);
}

SDL_Texture * 
Text::generateTexture(SDL_Renderer * render, SDL_Color foregroundColor, SDL_Color backgroundColor, int mode)
{
	if(this->font == NULL)
	{
		return NULL;
		//errorlog
	}

	if(this->text != NULL)
		SDL_DestroyTexture(this->text);

	this->foregroundColor = foregroundColor;
	this->backgroundColor = backgroundColor;
	this->text = NULL;

	SDL_Surface * textSurface = this->generateSurfaceText(mode);
	if(textSurface == NULL)
	{
		return NULL;
		//errorlog
	}
	
	this->text = SDL_CreateTextureFromSurface(render, textSurface);
	SDL_FreeSurface(textSurface);
	
	if(this->text == NULL)
	{
		//errorlog
	}

	return this->text;
}

SDL_Surface *
Text::generateSurfaceText(int mode)
{
	this->mode = mode;

	switch(this->mode)
	{
		case TTF_SHADED:
			return TTF_RenderUTF8_Shaded(this->font, this->value.c_str(), 
												this->foregroundColor, 
												this->backgroundColor);
		case TTF_BLENDED:
			return TTF_RenderUTF8_Blended(this->font, this->value.c_str(), this->foregroundColor);
		default:
			return TTF_RenderUTF8_Solid(this->font, this->value.c_str(), this->foregroundColor);
	}
}

SDL_Texture *
Text::getTexture()
{
	return this->text;	
}

