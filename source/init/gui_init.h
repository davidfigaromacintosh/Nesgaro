#undef main
#define _NESGARO main

namespace GUI {

	//static char buff[MAX_PATH];

	const char* getCurPath(const char* path);
	const char* getNesgaroTitle();
	const char* getNesgaroTitle(const char* str);
	const char* getFileName(const char* str);

}