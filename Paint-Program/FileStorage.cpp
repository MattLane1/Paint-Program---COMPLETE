/********************************************************************/
//@Class CFileStorage.cpp
//@Purpose This class is used to save and load image files
/*
	@class CFileStorage.cpp
	@purpose This class is used for saving and loading image files. 

I am not the sole author of this code. The function SaveFile as well as it's reliant GetFile Pointer were modified by myself for my needs, but the core of the code
was taken from http://www.cplusplus.com/forum/beginner/25138/, its original location is unknown, as the author there said it was a snippet they found. 

However, I did write everything else in this program
*/

#include "stdafx.h"
#include "FileStorage.h"
#include <fstream>
#include <iostream>
#include <vector>

CFileStorage::CFileStorage()
{
}


CFileStorage::~CFileStorage()
{
}

/*Get a pointer to the file where we will write the bitmap header and information*/
inline int GetFilePointer(HANDLE FileHandle) {
	return SetFilePointer(FileHandle, 0, 0, FILE_CURRENT);
}

/*This function opens the file explorer dialog, so the user can select a file to load, or save*/
CString CFileStorage::OpenExplorer(bool loading)
{
	//Open the file dialog. In load mode, load is true. In save mode, it is false
	CFileDialog dlg(loading, L"bmp", L"*.bmp", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("", this));

	//Display the dialog as a modal dialog (do nothing else until the dialog is delt with, then continue)
	dlg.DoModal();

	return dlg.GetPathName();
}

/*Save the image from the window to the bmp file. */
bool CFileStorage::SaveFile(CDC* dC, CRect clientRect)
{
	//Open the explorer dialog in save mode
	CString filename = OpenExplorer(false);

	bool Success = 0;
	HDC SurfDC = NULL;
	HBITMAP OffscrBmp = NULL;
	HDC OffscrDC = NULL;
	LPBITMAPINFO lpbi = NULL;
	LPVOID lpvBits = NULL;
	HANDLE BmpFile = INVALID_HANDLE_VALUE;
	BITMAPFILEHEADER bmfh;

	//Set up the rect for the size of the window, so we know where to copy from and to, as well as how big to make the bitmap file
	RECT wndRect;
	GetClientRect(WindowFromDC(dC->GetSafeHdc()), &wndRect);
	int width = (wndRect.right - wndRect.left);
	int height = (wndRect.bottom - wndRect.top);

	//Create a DC in memory, the size of the area we are copying from (the client area),then copy the image from the window to this memory DC
	HDC hDc = CreateCompatibleDC(dC->GetSafeHdc());
	HBITMAP hBmp = CreateCompatibleBitmap(GetDC(0), width, height);
	SelectObject(hDc, hBmp);
	BitBlt(hDc, 0, 0, width, height, GetDC(WindowFromDC(dC->GetSafeHdc())), 0, 0, SRCCOPY);
	DeleteObject(hBmp);
	HDC bitmapDC = hDc;

	//Create an off screen bitmap to hold the image for us
	if ((OffscrBmp = CreateCompatibleBitmap(bitmapDC, width, height)) == NULL)
		return 0;
	if ((OffscrDC = CreateCompatibleDC(bitmapDC)) == NULL)
		return 0;
	HBITMAP OldBmp = (HBITMAP)SelectObject(OffscrDC, OffscrBmp);

	//Blit the image from the window to this offscreen bitmap we created above
	BitBlt(OffscrDC, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);
	if ((lpbi = (LPBITMAPINFO)(new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)])) == NULL)
		return 0;
	ZeroMemory(&lpbi->bmiHeader, sizeof(BITMAPINFOHEADER));
	lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	SelectObject(OffscrDC, OldBmp);

	//Get the information about the bitmap, bits, resolution etc.
	GetDIBits(OffscrDC, OffscrBmp, 0, height, NULL, lpbi, DIB_RGB_COLORS); 
	lpvBits = new char[lpbi->bmiHeader.biSizeImage];
	GetDIBits(OffscrDC, OffscrBmp, 0, height, lpvBits, lpbi, DIB_RGB_COLORS); 

	//Create the physical file in the designated location with the users given name
	if ((BmpFile = CreateFile(filename,
		GENERIC_WRITE,
		0, NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL)) == INVALID_HANDLE_VALUE)
		return 0;
	DWORD Written;
	bmfh.bfType = 19778;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;

	//Write to the empty file we created, the information in the image
	if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
		return 0;
	if (Written < sizeof(bmfh))
		return 0;
	if (!WriteFile(BmpFile, &lpbi->bmiHeader, sizeof(BITMAPINFOHEADER), &Written, NULL))
		return 0;
	if (Written < sizeof(BITMAPINFOHEADER))
		return 0;
	int PalEntries;
	if (lpbi->bmiHeader.biCompression == BI_BITFIELDS)
		PalEntries = 3;
	else PalEntries = (lpbi->bmiHeader.biBitCount <= 8) ?
		(int)(1 << lpbi->bmiHeader.biBitCount) : 0;
	if (lpbi->bmiHeader.biClrUsed)
		PalEntries = lpbi->bmiHeader.biClrUsed;
	if (PalEntries) {
		if (!WriteFile(BmpFile, &lpbi->bmiColors, PalEntries * sizeof(RGBQUAD), &Written, NULL))
			return 0;
		if (Written < PalEntries * sizeof(RGBQUAD))
			return 0;
	}
	bmfh.bfOffBits = GetFilePointer(BmpFile);
	if (!WriteFile(BmpFile, lpvBits, lpbi->bmiHeader.biSizeImage, &Written, NULL))
		return 0;
	if (Written < lpbi->bmiHeader.biSizeImage)
		return 0;
	bmfh.bfSize = GetFilePointer(BmpFile);
	SetFilePointer(BmpFile, 0, 0, FILE_BEGIN);
	if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
		return 0;
	if (Written < sizeof(bmfh))
		return 0;

	CloseHandle(BmpFile);
	
	//SUCCESS we have saved the file!
	return true;
}

/* This function loads bmp images into the window */
bool CFileStorage::LoadFile(CDC* dC)
{
	//Get a handle to the client from the DC passed to us by mainframe
	HDC hDC = dC->GetSafeHdc();
	BITMAP bm;

	//Open the explorer dialog in load mode
	CString imagePath = OpenExplorer(true);

	//Load the image into the HANDLE object, then create a DC that is compatible with our screen
	HANDLE hBmp = LoadImage(NULL, imagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HDC dcmem = CreateCompatibleDC(NULL);

	//Join the objects together
	SelectObject(dcmem, hBmp);
	GetObject(hBmp, sizeof(bm), &bm);

	//Draw the image on the screen
	BitBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight, dcmem, 0, 0, SRCCOPY);
	
	//Clean up
	DeleteDC(dcmem);

	//SUCCESS we have loaded the image into the window
	return true;
}

