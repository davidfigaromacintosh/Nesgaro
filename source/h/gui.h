namespace GUI {

	void power() {
		MEM::power();
		CPU::power();
		PPU::power();
	}

	void reset() {
		CPU::reset();
		PPU::reset();
	}

	const char* getCurPath(const char* path) {

		static char buff[MAX_PATH] = { 0 };
		GetModuleFileNameA(NULL, buff, MAX_PATH);
		std::string::size_type pos = std::string(buff).find_last_of("\\/");
		strcpy(buff, std::string(buff).substr(0, pos).c_str());

		strcat(buff, path);
		return buff;
	}

	const char* getNesgaroTitle() {

		static char buff[MAX_PATH] = { 0 };
		strcpy(buff, "Nesgaro ");
		strcat(buff, NESGARO_VERSION);
		return buff;
	}

	const char* getNesgaroTitle(const char* str) {

		static char buff[MAX_PATH] = { 0 };
		strcpy(buff, str);
		strcat(buff, " ~ Nesgaro ");
		strcat(buff, NESGARO_VERSION);
		return buff;
	}

	const char* getFileName(const char* str, bool allowext) {

		static char buff[MAX_PATH] = { 0 };
		char tempstr[MAX_PATH] = { 0 };
		strcpy(tempstr, str);

		int ptr = strlen(tempstr);
		bool dotted = false;
		while (tempstr[ptr] != '\\' && ptr > 0) { if (!allowext && tempstr[ptr] == '.' && !dotted) { tempstr[ptr] = 0, dotted = true; } --ptr; }
		strcpy(buff, &tempstr[ptr + 1]);
		return buff;
	}

	u32 crc32() {

        return 0xffffffff;
	}

	void checkForUpdates() {

	    CURL* c;
	    CURLcode ccode;

	    if (c = curl_easy_init()) {

            curl_easy_setopt(c, CURLOPT_URL, "https://nes.figaro.ga/?ver");

            curl_easy_setopt(c, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(c, CURLOPT_SSL_VERIFYHOST, 0L);

            curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, displayUpdateMessage);
            curl_easy_perform(c);
            curl_easy_cleanup(c);
	    }

	}

	size_t displayUpdateMessage(void* str, size_t len, size_t nmem, void* usrp) {

	    size_t rsize = len * nmem;

        char dwVersion[64] = { 0 }, notifyV[256] = { 0 };

        for (int i = 0; i < rsize; i++) {

            dwVersion[i] = *(char*)(str + i);
        }

        if (!_stricmp(NESGARO_VERSION, dwVersion)) {
            MessageBoxA(NULL, "Your version of Nesgaro is up to date.", "No updates available", MB_OK | MB_SETFOREGROUND);
        }

        else {
            sprintf(notifyV, "A new version of Nesgaro is available: %s.\nWould you like to download it now?", dwVersion);
            if (MessageBoxA(NULL, notifyV, "An update is available", MB_YESNO | MB_SETFOREGROUND | MB_ICONINFORMATION) == IDYES) {
                ShellExecuteA(NULL, "open", "https://nes.figaro.ga/", NULL, NULL, SW_SHOWNORMAL);
            }
        }

		return rsize;
	}

}
