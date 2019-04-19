#undef main
#define _NESGARO main

namespace GUI {

	struct string {
        char* ptr;
        size_t len;
	};

	const char* getCurPath(const char* path);
	const char* getNesgaroTitle();
	const char* getNesgaroTitle(const char* str);
	const char* getFileName(const char* str, bool allowext);

	void checkForUpdates();
    size_t displayUpdateMessage(void*, size_t, size_t, void*);
	void power();
	void reset();
}
