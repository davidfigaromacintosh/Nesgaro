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

	void checkForUpdates() {
        /*
		//Tutaj jest ciekawie, bo emulator wysy³a requesta do strony "https://nes.figaro.ga/?ver" requesta i porównuje wersje. Jeœli s¹ ró¿ne, wyskoczy komunikat o updacie
		HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL; bool bResults = false; DWORD dwSize = 0, dwDownloaded = 0; char dwVersion[64] = { 0 }, notifyV[256] = { 0 };

		//Tworzymy sesjê
		hSession = WinHttpOpen(L"WinHTTP Nesgaro/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

		//Gdzie
		if (hSession) hConnect = WinHttpConnect(hSession, L"nes.figaro.ga", 443, 0);

		//Tworzymy requesta
		if (hConnect) hRequest = WinHttpOpenRequest(hConnect, L"GET", L"/?ver", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

		//Wysy³amy requesta
		if (hRequest) bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);

		//Otrzymaj odpowiedŸ
		if (bResults) bResults = WinHttpReceiveResponse(hRequest, NULL);

		//Jeœli wszystko posz³o OK
		if (bResults) {

			if (WinHttpQueryDataAvailable(hRequest, &dwSize) && WinHttpReadData(hRequest, (void*)dwVersion, dwSize, &dwDownloaded) && _stricmp(dwVersion, NESGARO_VERSION)) {

				sprintf(notifyV, "A new version of Nesgaro is available: %s.\nWould you like to download it now?", dwVersion);
				if (MessageBoxExA(NULL, notifyV, "Update", MB_YESNO | MB_ICONINFORMATION, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL)) == IDYES) {
					ShellExecuteA(NULL, "open", "https://nes.figaro.ga/", NULL, NULL, SW_SHOWNORMAL);
				}

			}

		}

		//Sprz¹tamy po sobie
		if (hSession) WinHttpCloseHandle(hSession);
		if (hConnect) WinHttpCloseHandle(hConnect);
		if (hRequest) WinHttpCloseHandle(hRequest);
        */
	}

}
