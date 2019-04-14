namespace MAPPER {

	u32 mapper;
	void init();

	void setMapper(u32 mapperid);

	void writebus(u16 address, u8 value);


	//Mapper 1
	namespace MMC1 {
		u8 count;
		u8 control;
		u8 CHRmode;
		u8 PRGmode;
		u8 shift;
		void setPRGBanks();
	}

	//Mapper 4
	namespace MMC3 {
		u8 bankMode;
		u8 PRGmode;
		u8 CHRinversion;
		u8 IRQenable;
		u8 IRQlatch;
		u8 IRQcounter;
		u8 IRQreloadRequest;
		u8 IRQhalt;
		u8 risingEdge;
	}
	
	//Mapper 178
	namespace EDU178 {
		u8 bankMode;
	}

	
}