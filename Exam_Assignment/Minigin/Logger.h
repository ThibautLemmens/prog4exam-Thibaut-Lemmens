#pragma once
#include <iostream>
#include <sstream>
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
			std::wstringstream stream{};

			HANDLE  hConsole;

			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


			switch (type)
			{
			case LogType::Info:
				SetConsoleTextAttribute(hConsole, 11);
				stream << L"[INFO]";
				break;
			case LogType::Warning:
				SetConsoleTextAttribute(hConsole, 10);
				stream << L"[WARNING]";
				break;
			case LogType::Error:
				SetConsoleTextAttribute(hConsole, 12);
				stream << L"[ERROR]";
				break;
			case LogType::Todo:
				SetConsoleTextAttribute(hConsole, 8);
				stream << L"[TODO]";
				break;
			default:
				SetConsoleTextAttribute(hConsole, 15);
				stream << L"[DEFAULT]";
			}

			//SetConsoleTextAttribute(hConsole, 15);
			std::wstring string;
			stream >> string;

			std::wcout << string << L' ' << str << L'\n';

			SetConsoleTextAttribute(hConsole, 15);
		};
	private:

	};
}

