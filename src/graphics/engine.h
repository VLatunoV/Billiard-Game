#pragma once

struct State;

class GraphicsEngine {
public:
	GraphicsEngine(State&);
	~GraphicsEngine();

	void drawFrame();

private:
	State& state;
};
