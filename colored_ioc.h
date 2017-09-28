#pragma once

#include <ostream>

#if defined(_WIN32) || defined(_WIN64)
#define NOMINMAX
#include <windows.h> // WinApi header
#endif

struct ConsoleColor
{
	int foreground, background;
	ConsoleColor(int fg, int bg) : foreground(fg), background(bg){};
};

inline std::ostream &operator<<(std::ostream &os, pharoah::ConsoleColor c_color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info))
		return os;

	SetConsoleTextAttribute(hConsole, c_color.background * 16 + c_color.foreground);
	return os;
}

#if defined(_WIN32) || defined(_WIN64)

enum ColorCode
{
	RED = 4,
	GREEN = 2,
	BLUE = 1,
	WHITE = 7,
	BLACK = 0
};

//first of pair is background color
//second of pair is foreground color
#elif defined(__linux__)

enum ColorCode
{
	FG_RED = 31,
	FG_GREEN = 32,
	FG_BLUE = 34,
	FG_DEFAULT = 39,
	BG_RED = 41,
	BG_GREEN = 42,
	BG_BLUE = 44,
	BG_DEFAULT = 49
};

//first of pair is background color
//second of pair is foreground color
std::ostream &operator<<(std::ostream &os, ConsoleColor c_color)
{
	return os << "\033[" << c_color.background << "m"
			  << "\033[" << c_color.foreground << "m";
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
	std::cout << ConsoleColor(WHITE, BLACK) << std::endl;
}
