#pragma once
#include "GlobalWindow.h"

class GlobalWindowManager
{
public:
	GlobalWindowManager(){}
	~GlobalWindowManager();
	
	static GlobalWindowManager * instance() { return sm_instance; }

	void RegisterWindow(GlobalWindow* win);
	void RegisterWindowAndInitialize(GlobalWindow* win);
	void FreeWindows();

	int GetWindowCount() const;
	void ProcessWindows();
	
private:
	static GlobalWindowManager		  * sm_instance;
	vector<GlobalWindow*>				m_windows;
	vector<GlobalWindow*>				m_toDestroy;

	void DestroyWindow(int index);
	void DisposeWindows();
	bool isUniqInDestroy(GlobalWindow* window);
};
