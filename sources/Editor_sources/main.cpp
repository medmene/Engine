#include "include/EditorWindow.h"

int main()
{
	EditorWindow::instance()->Initialize();
	EditorWindow::instance()->Update();
	return 1;
}