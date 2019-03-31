namespace APU {
	
	unsigned int clock[] = { 1789773, 1662607 };

	void init();
	void run_frame(int elapsed);
	void output_samples(const blip_sample_t* samples, size_t count);

	void writebus(int elapsed, u16 address, u8 value = 0x00);
	u8 readbus(int elapsed, u16 address);
	void setVolume(double vol);
}