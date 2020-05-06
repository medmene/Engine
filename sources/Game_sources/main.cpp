#include "include/GameWindow.h"

#undef main
int main()
{
	GameWindow::instance()->Initialize();
	GameWindow::instance()->Processing();
	delete GameWindow::instance();
	return 1;
}