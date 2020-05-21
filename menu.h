#pragma once
using namespace std;
#define TOP 3
#define LEFT 20
enum Color
{
	Black,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Brown,
	LightGray,
	DarkGray,
	LightBlue,
	LightGreen,
	LightCyan,
	LightRed,
	LightMagenta,
	Yellow,
	White
};
struct Player
{
	char nick[100];
	int score;
};
void Gotorc(short r, short c) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, { c,r });
}
void Shrift(int s = 18)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
	wcscpy_s(fontInfo.FaceName, L"Lucida Console");
	fontInfo.dwFontSize.Y = s;
	SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
}
void Paint(unsigned short Back, unsigned short Forg) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	unsigned short c = ((Back & 0x0F) << 4) + (Forg & 0x0F);
	SetConsoleTextAttribute(handle, c);
}
