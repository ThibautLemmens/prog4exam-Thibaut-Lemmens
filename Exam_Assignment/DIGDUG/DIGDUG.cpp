// DIGDUG.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Minigin.h"
//#include "MiniginPCH.h"
#pragma comment(lib,"xinput.lib")
#include "Logger.h"
using namespace dae;

int main()
{
	dae::Minigin engine;
	engine.Run();

	Logger::LogInfo(L"Test");
	Logger::LogDefault(L"Test");
	Logger::LogError(L"Test");
	Logger::LogWarning(L"Test");
	Logger::LogTodo(L"Test");
}