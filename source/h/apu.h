namespace APU {
	
	const int samplerate = 88200;
	Nes_Apu apu;
	Blip_Buffer buff;
	Sound_Queue* soundQueue;

	const int out_size = 4096;
	blip_sample_t output[out_size];

	void init() {
		soundQueue = new Sound_Queue();
		soundQueue->init(samplerate);

		buff.sample_rate(samplerate);
		buff.clock_rate(1789773);

		apu.output(&buff);
		apu.dmc_reader(MEM::dmc_read);

	}

	void writebus(int elapsed, u16 address, u8 value) {
		apu.write_register(elapsed, address, value);
	}

	u8 readbus(int elapsed, u16 address) {
		return apu.read_status(elapsed);
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
