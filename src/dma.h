// DMA.h
#ifndef _DMA_H
#define _DMA_H

#include "systemc.h"
#define BASE_ADDR 123
SC_MODULE(DMA)
{
	//clock
	sc_in<bool> clock;
	//master port
	sc_out<sc_uint<32> > m_addr;
	sc_in<sc_uint<32> > m_datain;
	sc_out<sc_uint<32> > m_dataout;
	sc_out<bool> m_rw; //1:read 0:write 
	//slave port
	sc_in<sc_uint<32> > s_addr;
	sc_in<sc_uint<32> > s_data;
	sc_in<bool> s_rw; //1:read 0:write
	//other controll
	sc_in<bool> reset; //syncchronous active low
	sc_in<bool> clear;
	sc_out<bool> interrupt; 
	//conncet to memory
	sc_out<bool> cs; //chip select  
	sc_out<bool> we; //write enable
	sc_out<bool> oe; //output enable
	
	
	//local 
	sc_uint<32> Source_reg; //0~3
	sc_uint<32> Target_reg; //4~7
	sc_uint<32> Size_reg; //8~11
	bool Start_clear_reg; //12, 1:start 0:clear   
	sc_uint<8> control_register [13]; //save Sourece Target Size and start from CPU
	sc_uint<32> base_address;
	sc_uint<32> temp;
	sc_uint<32> count;
	int i;
	void dma();
	
	SC_CTOR(DMA) 
	{
		SC_CTHREAD(dma, clock.pos());
		reset_signal_is(reset, false);
		//watching(reset.delayed() == false);
	}
};
#endif
