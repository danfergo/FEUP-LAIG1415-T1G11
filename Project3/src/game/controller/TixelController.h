#pragma once
#include "CGFapplication.h"

#include "../../scenegraph/parser/ANFparser.h"
#include "../../scenegraph/Interface.h"
#include "../../game/view/Board.h"
#include "MatchController.h"

typedef struct ScenePlayingData {
	Scene * scene;
	Board * board;
} ScenePlayingData;

class TixelController: public CGFapplication
{
private:
	int mode;
	MatchController * matchController;
	enum TixelState {ChoosingMode,ChoosingScenario,Playing};
	ScenePlayingData scenes[2];
	Scene *menuMode, *menuScenario;
	TixelState currentState;
	Interface * intrface;
public:
	TixelController(void);
	void init(int argc, char* argv[]);
	void selectButton(int id);
	~TixelController(void);
};

