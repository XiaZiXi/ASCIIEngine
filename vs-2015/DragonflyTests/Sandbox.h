#pragma once
/// Sandbox that starts/stops up a very barebones game
/// for isolated testing
class Sandbox {
private:
	Sandbox();
	Sandbox(Sandbox const&);
	void operator=(Sandbox const&);
public:
	Sandbox &getInstance();
	void startup();
	void reset();
	void stop();
};