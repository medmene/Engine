#include "include/GameWindow.h"

int main()
{
	GameWindow::instance()->Initialize();
	GameWindow::instance()->Update();
	//delete GameWindow::instance();
	return 1;
}