#pragma once

struct State;

class GraphicsEngine {
public:
	GraphicsEngine(State&);
	~GraphicsEngine();

	void DrawFrame();

private:
	State& state;
};
