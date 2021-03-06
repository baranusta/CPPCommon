#pragma once

#include <ostream>

#if defined(_WIN32) || defined(_WIN64)
#define NOMINMAX
#include <windows.h> // WinApi header
#endif

#if defined(_WIN32) || defined(_WIN64)

enum ColorCode
{
	RED = 4,
	GREEN = 2,
	BLUE = 1,
	WHITE = 7,
	BLACK = 0
};

struct ConsoleColor
{
	int foreground, background;
	ConsoleColor(int fg, int bg) : foreground(fg), background(bg){};
};

//first of pair is background color
//second of pair is foreground color
inline std::ostream &operator<<(std::ostream &os, pharoah::ConsoleColor c_color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info))
		return os;

	SetConsoleTextAttribute(hConsole, c_color.background * 16 + c_color.foreground);
	return os;
}
#elif defined(__linux__)

enum ColorCode
{

	RED = 1,
	GREEN = 2,
	BLUE = 4,
	WHITE = 9,
	BLACK = 0
};

struct ConsoleColor
{
	int foreground, background;
	ConsoleColor(int fg, int bg) : foreground(fg + 30), background(bg + 40){};
};

//first of pair is background color
//second of pair is foreground color
inline std::ostream &operator<<(std::ostream &os, ConsoleColor c_color)
{
	return os << "\033[" << c_color.background << ";" << c_color.foreground << "m";
}
#endif

template <typename T>
void print(const T &v)
{
	std::cout << v << ' ';
}

template <typename... REST>
void print(ConsoleColor color, const REST &... rest)
{
	std::cout << color;
	print(rest...);

#if defined(_WIN32) || defined(_WIN64)
	std::cout << ConsoleColor(WHITE, BLACK) << std::endl;
#elif defined(__linux__)
	std::cout << "\e[0m" << std::endl;
#endif
}
