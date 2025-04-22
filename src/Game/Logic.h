#pragma once
#include <memory>

class GameLogic {
public:
	GameLogic();
	~GameLogic();

	class GameObject* GetBoard();

private:
	std::unique_ptr<class BilliardBoard> billiardBoard;
};
