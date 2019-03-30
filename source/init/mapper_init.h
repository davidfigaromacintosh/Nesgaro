namespace MAPPER {

	u32 mapper;
	void init();

	void setMapper(u32 mapperid);

	void writebus(u16 address, u8 value);

	// MMC1
	u8 mmc1Count;
	u8 mmc1Control;
	u8 mmc1CHRmode;
	u8 mmc1PRGmode;
	u8 mmc1Shift;
	void mmc1SetPRGBanks();
	
}