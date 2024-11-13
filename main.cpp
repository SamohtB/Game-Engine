#include "AppWindow.h"


int main()
{
	try
	{
		AppWindow app;

		while (app.isRun()) {}
	}
	catch (...)
	{
		return -1;
	}

	return 0;
}