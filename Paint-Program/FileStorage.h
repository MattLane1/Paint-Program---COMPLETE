#pragma once
class CFileStorage
{
public:
	CFileStorage();
	~CFileStorage();
	CString OpenExplorer(bool loading);
	bool SaveFile(CDC* dC, CRect);
	bool LoadFile(CDC* dC);

};

