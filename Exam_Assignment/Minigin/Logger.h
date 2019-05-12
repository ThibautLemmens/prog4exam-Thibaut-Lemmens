#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include "Singleton.h"
#include <assert.h> 

namespace dae
{
	enum class LogType
	{
		Default = 0x00,
		Error = 0x01,
		Warning = 0x02,
		Info = 0x03,
		Todo = 0x04
	};

	class Logger
	{
	public:

		static void LogWarning(const std::wstring& wstr) { Log(LogType::Warning, wstr); };
		static void LogError(const std::wstring& wstr) { Log(LogType::Error, wstr); };
		static void LogInfo(const std::wstring& wstr) { Log(LogType::Info, wstr); };
		static void LogDefault(const std::wstring& wstr) { Log(LogType::Default, wstr); };
		static void LogTodo(const std::wstring& wstr) { Log(LogType::Todo, wstr); };

		static void Log(LogType type, const std::wstring& str)
		{
			std::wstringstream stream;

			HANDLE  hConsole;

			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


			switch (type)
			{
			case LogType::Info:
				SetConsoleTextAttribute(hConsole, 1);
				stream << L"[INFO]    ";
				break;
			case LogType::Warning:
				SetConsoleTextAttribute(hConsole, 2);
				stream << L"[WARNING] ";
				break;
			case LogType::Error:
				SetConsoleTextAttribute(hConsole, 3);
				stream << L"[ERROR]   ";
				SetConsoleTextAttribute(hConsole, 15);
				stream << str;
				//assert(true);
				break;
			case LogType::Todo:
				SetConsoleTextAttribute(hConsole, 4);
				stream << L"[TODO]   ";
				break;
			default:
				SetConsoleTextAttribute(hConsole, 15);
				stream << L"[DEFAULT]   ";
			}

			SetConsoleTextAttribute(hConsole, 15);
			stream << str;
		};
	private:

	};
}

