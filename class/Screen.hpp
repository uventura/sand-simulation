#pragma once

#include "mainHeader.hpp"

#define UNICODE
#include <Windows.h>

class Screen
{
private:
	inline unsigned int getPositionScr(unsigned int x, unsigned int y)
	{return mWidth * (mHeight - y - 1) + x;};
	
	HANDLE mConsoleApp;
	DWORD mDwBytesWritten;
	
public:
	int mWidth, mHeight;
	wchar_t* mElements;
	
	// The width and height is given by de console size.
	Screen();
	~Screen();
	
	void show();
	void clear();
	
	void setElements(std::vector<console3D::vec4> vectors);
	void ortographic(console3D::vec4 vector);
};
