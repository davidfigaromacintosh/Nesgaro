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

	// MMC3
	u8 mmc3BankMode;
	u8 mmc3PRGmode;
	u8 mmc3CHRinversion;
	u8 mmc3IRQenable;
	u8 mmc3IRQlatch;
	u8 mmc3IRQcounter;
	u8 mmc3IRQreloadRequest;
	u8 mmc3IRQhalt;
	u8 mmc3risingEdge;

	
}