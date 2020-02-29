#include "include/GameWindow.h"

int main()
{
	GameWindow::instance()->Initialize();
	GameWindow::instance()->Update();
	return 1;
}