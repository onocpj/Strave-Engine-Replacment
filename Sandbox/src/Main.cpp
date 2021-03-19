#include "Sandbox.hpp"


using namespace Strave;
using namespace Sandbox;

int main(int argc, char* argv[])
{
	Game* Executable = new Game();
	bool executed = Executable->Execute();

	delete Executable;
	return executed;
}