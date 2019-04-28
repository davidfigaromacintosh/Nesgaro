namespace APU {

	unsigned int clock[] = { 1789773, 1662607, 1773448 };

	void init();
	void reset(b tvreg);
	void setClockRate(long);
	void run_frame(int elapsed);
	void output_samples(const blip_sample_t* samples, size_t count);
	cpu_time_t irqBefore();
	cpu_time_t earliest_irq_before(cpu_time_t end_time);
	void irq_changed(void*);

	void writebus(int elapsed, u16 address, u8 value = 0x00);
	u8 readbus(int elapsed, u16 address);
	void setVolume(double vol);
}
