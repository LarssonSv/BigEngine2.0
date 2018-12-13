#include "files/LogFile.h"
#include "engine/Engine.h"

int main(int argc, char* argv[])
{
	Big::Engine engine;
	if (!engine.Create())
	{
		engine.Destroy();
		return -1;
	}

	engine.Run();

	engine.Destroy();

	return 0;
}
