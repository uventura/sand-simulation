#include "Screen.hpp"

Screen::Screen()
{
	mConsoleApp = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(mConsoleApp);
	mDwBytesWritten = 0;
	/*
		COLOR PALLETE
	// ' ', 0x2591, 0x2592, 0x2593, 0x2588
	// '.', ',' , '-', '~', ':', ';', '=', '!', '#', '$', '@' 
	wchar_t palette[6] = {' ', 0x2591, '.', 0x2592, 0x2593, 0x2588};*/
	
	// Console Size
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	
	mWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1; // Console Row
	mHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1; // Console Col
	mElements = new wchar_t[mWidth * mHeight + 1];
	
	// TODO: Replace for memset
	for(int i = 0; i <= mWidth * mHeight; ++i)
		mElements[i] = ' ';
	mElements[mWidth * mHeight] = '\0';
}

Screen::~Screen()
{
	delete(mElements);
}

void Screen::show()
{
	mElements[mWidth * mHeight] = '\0';
	WriteConsoleOutputCharacter(mConsoleApp, mElements, mWidth * mHeight + 1, {0,0}, &mDwBytesWritten);
}

void Screen::clear()
{
	for(int i = 0; i < mWidth * mHeight; ++i)
		mElements[i] = ' ';
	mElements[mWidth * mHeight] = '\0';
}

void Screen::ortographic(console3D::vec4 vector)
{
	vector.x /= vector.w;
	vector.y /= vector.w;
	mElements[getPositionScr(vector.x, vector.y)] = 0x2588;//0x2588;
}

void Screen::setElements(std::vector<console3D::vec4> vectors)
{
	for(int i = 0; i < vectors.size(); ++i)
		if(vectors[i].x >= 0 and vectors[i].y >= 0 and
		   vectors[i].x < mWidth and vectors[i].y < mHeight)
			mElements[getPositionScr(vectors[i].x, vectors[i].y)] = 0x2588;
}
