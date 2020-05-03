#include "include/GameWindow.h"

int main()
{
	GameWindow::instance()->Initialize();
	GameWindow::instance()->Processing();
	delete GameWindow::instance();
	return 1;
}