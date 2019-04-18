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
		strcpy_s(buff, sizeof(buff), std::string(buff).substr(0, pos).c_str());

		strcat_s(buff, sizeof(buff), path);
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

}