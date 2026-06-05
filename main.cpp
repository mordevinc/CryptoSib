#ifdef _WIN32
	#include "src/menu/menu.h"
#else
	#include "crossPlatform/menu/crossMenu.h"
#endif

int main() {
	setConsoleEncoding();
	#ifdef _WIN32
	showMenu();
	#else
	crosspShowMenu();
	#endif
	showMenu();
	return 0;
}