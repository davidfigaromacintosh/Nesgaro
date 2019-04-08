namespace APU {
	
	const int samplerate = 88200;
	Nes_Apu apu;
	Blip_Buffer buff;
	Sound_Queue* soundQueue;

	const int out_size = 2048;
	blip_sample_t output[out_size];

	void init() {
		soundQueue = new Sound_Queue();
		soundQueue->init(samplerate);

		buff.sample_rate(samplerate);
		buff.clock_rate(clock[tvregion]);
		apu.output(&buff);
		apu.dmc_reader(MEM::dmc_read);
	}

	cpu_time_t irqBefore() {
			return apu.earliest_irq();
	}

	cpu_time_t earliest_irq_before(cpu_time_t end_time)
	{
		if (!CPU::getI())
		{
			cpu_time_t irq_time = apu.earliest_irq();
			if (irq_time < end_time)
				end_time = irq_time;
		}
		return end_time;
	}

	void writebus(int elapsed, u16 address, u8 value) {
		apu.write_register(elapsed, address, ((address == 0x4000 || address == 0x4004) && tvregion == DENDY) ? (((value & 0b01000000) << 1) | ((value & 0b10000000) >> 1) | value & 0b00111111) : value);
	}

	u8 readbus(int elapsed, u16 address) {
		return apu.read_status(elapsed);
	}

	void setVolume(double vol) {
		apu.volume(vol);
		
	}

	void output_samples(const blip_sample_t* samples, size_t count) {
		soundQueue->write(samples, count);
	}


	void run_frame(int elapsed) {
		
		apu.end_frame(elapsed);
		buff.end_frame(elapsed);

		if (buff.samples_avail() >= out_size)
		{
			size_t count = buff.read_samples(output, out_size);
			output_samples(output, count);
		}

	}

}
