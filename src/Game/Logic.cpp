#include "Logic.h"
#include "Object/Board.h"

GameLogic::GameLogic()
	: billiardBoard{std::make_unique<BilliardBoard>()}
{}

GameLogic::~GameLogic() = default;

GameObject* GameLogic::GetBoard() {
	return billiardBoard.get();
}
