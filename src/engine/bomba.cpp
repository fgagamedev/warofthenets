#include "bomba.h"
#include "SDL2/SDL.h"
#include "texturemanager.h"
#include "render.h"
#include <iostream>
#include <math.h>


std::string Bomba::path = "resources/img/bomb.png";

int Bomba::custoAtualizacao = 0;

Bomba::Bomba(int raioDestruicao, int x, int y):Image(path,x,y)
{
	numFrames = 5;
	currentFrame = 1;

	this->raioDestruicao = 6 * pow( (2 + 1), (raioDestruicao - 1) );

	//animate();

	tempInicial = SDL_GetTicks();

	inAnimate = true;

}

void
Bomba::animate()
{
	//int intervalo = 1000;
	//currentFrame = 1;

}

void
Bomba::update()
{
	int intervalo = 100;

	int delta= SDL_GetTicks() - tempInicial;

	if(delta >= intervalo)
	{
		std::cout<<"entrou aqui"<<std::endl;
		currentFrame++;
		tempInicial = SDL_GetTicks();
	}

	
	if(currentFrame == 5)
		inAnimate = false;

	/*int temp = SDL_GetTicks() - tempInicial;

	if(temp > 1500)
		inAnimate = false;*/
}

bool 
Bomba::isAnimating()
{
	return inAnimate;
}

void
Bomba::draw()
{

	TextureManager::Instance()->drawFrame(imageId, (Uint32)position.getX(),(Uint32)position.getY(),width/5,
	 height, currentRow, currentFrame,Render::getInstance()->getRenderer(), 0 );
}

int
Bomba::getCustoAtualizacao()
{
	return Bomba::custoAtualizacao;
}

void 
Bomba::setCustoAtualizacao(int _custoAtualizacao)
{
	Bomba::custoAtualizacao = _custoAtualizacao;
}

void 
Bomba::explode(map<Hexagon*, vector<Hexagon*>>  grafoHexagon, Hexagon *hex)
{
	mapaVisitado.clear();
	vetorDestruicao.clear();

	while(!filaVisitar.empty())
	{
		filaVisitar.pop();
	}

	mapaVisitado[hex] = true;
	filaVisitar.push(hex);

	explodeRecursivo(grafoHexagon, 0);
}

 
void 
Bomba::explodeRecursivo(map<Hexagon*, vector<Hexagon*>> grafoHexagon, int num)
{
	if(num > (raioDestruicao) || filaVisitar.empty())
		return;

	//std::cout << "\n\n num: " << num << std::endl;

	Hexagon *hex = filaVisitar.front();
	filaVisitar.pop();

	if(hex->haveObject())
		vetorDestruicao.push_back(hex);

	
	std::vector<Hexagon *> adjacentes = grafoHexagon[hex];

	//std::cout << "adjacentes: " << adjacentes.size() << std::endl;
	
	for (unsigned int i = 0; i < adjacentes.size(); ++i)
	{
		//std::cout << "i: " << i << std::endl;
		if(mapaVisitado.find(adjacentes[i]) == mapaVisitado.end())
		{
			//std::cout << "i no if: " << i << std::endl;

			filaVisitar.push(adjacentes[i]);
			mapaVisitado[adjacentes[i]] = true;
		}
	}

	explodeRecursivo(grafoHexagon, num + 1);
}

std::vector<Hexagon *> 
Bomba::getVetorDestruicao()
{
	return vetorDestruicao;
}
