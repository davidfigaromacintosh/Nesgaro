namespace GUI {

	char* getCurPath(const char* path) {

		GetModuleFileNameA(NULL, buff, MAX_PATH);
		std::string::size_type pos = std::string(buff).find_last_of("\\/");
		strcpy_s(buff, sizeof(buff), std::string(buff).substr(0, pos).c_str());

		strcat_s(buff, sizeof(buff), path);
		return buff;
	}

}