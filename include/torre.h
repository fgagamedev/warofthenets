#ifndef TORRE_H
#define TORRE_H

#include <string>
#include "image.h"

class Torre : public Image{

public:

	Torre(int tipoTorre, int numLevelTower = 1, int x=0, int y=0, std::string path = "resources/img/tower.png");
	virtual void update();
	virtual void draw();
	
	static int getCustoAtualizacao();
	static void setCustoAtualizacao(int _custoAtualizacao);

	void incActualColumn();
	virtual int getInformacao();
	int spyOnTower(int levelSpy);

	bool playSound();

	bool isAliada();

	static int ALIADA ;
	static int INIMIGA ;

protected:

	int numFrames;
	int numLevels;

private:

	int actualRow;
	int numInformacao;
	int numLevelTower;
	std::string constructSound;
	static int custoAtualizacao;

	int tipoTorre;

	

};

#endif
