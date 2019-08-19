#include "MiniginPCH.h"
#pragma comment(lib,"xinput.lib")

// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#include <SDL.h>
#define SDL_MAIN_HANDLED
#include "Minigin.h"
#undef main

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[]) {
#pragma warning( pop )

	dae::Minigin engine;
	engine.Run();


	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
    return 0;
}

