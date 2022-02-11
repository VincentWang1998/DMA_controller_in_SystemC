//Memory.h
#ifndef _MEMORY_H
#define _MEMORY_H

#include "systemc.h"

#define DATA_WIDTH 32
#define ADDR_WIDTH 32
//#define RAM_DEPTH 1 << ADDR_WIDTH
#define MEM_SIZE 16
SC_MODULE(Memory)
{
	sc_in<bool> clock;
	sc_in<sc_uint<DATA_WIDTH> > address;
	sc_in<sc_uint<ADDR_WIDTH> > data_in;
	sc_out<sc_uint<DATA_WIDTH> > data_out;
	sc_in<bool> cs; //chip select  
	sc_in<bool> we; //write enable
	sc_in<bool> oe; //output enable
	sc_in<bool> reset; //syncchronous active low
	
	sc_uint<DATA_WIDTH> mem[MEM_SIZE]; //RAM_DEPTH to big
	
	int i;
	
	void memory_rw();
	
	SC_CTOR(Memory)
	{
		SC_CTHREAD(memory_rw, clock.pos());
		reset_signal_is(reset, false); //systemc 2.2.3
		//watching(reset.delayed() == false); //when reset=0 reset
	}
};

#endif