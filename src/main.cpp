#include "dma.h"
#include "Memory.h"

int sc_main(int argc, char* argv[]){

	
	sc_signal<sc_uint<32> > master_datain;
	sc_signal<sc_uint<32> > master_dataout;
	sc_signal<sc_uint<32> > master_addr;
	sc_signal<sc_uint<32> > slave_datain;
	sc_signal<sc_uint<32> > slave_addr;
	sc_signal<bool> master_rw;
	sc_signal<bool> slave_rw;
	sc_signal<bool> interrupt;
	sc_signal<bool> reset;
	sc_signal<bool> clear;
	
	sc_signal<bool> cs;
	sc_signal<bool> we;
	sc_signal<bool> oe;
	
	sc_time t(10, SC_NS);
	sc_clock clock("clock", t);
   // sc_time t1(0.1, SC_NS);
	int i;
	DMA x("DMA");
	x.m_datain(master_datain);
	x.m_dataout(master_dataout);
	x.m_addr(master_addr);
	x.m_rw(master_rw);
	x.s_data(slave_datain);
	x.s_addr(slave_addr);
	x.s_rw(slave_rw);
	x.interrupt(interrupt);
	x.clock(clock);
	x.reset(reset);
	x.clear(clear);
	x.cs(cs);
	x.we(we);
	x.oe(oe);

	sc_trace_file *out = sc_create_vcd_trace_file("RESULT");
	sc_trace(out, clock, "clock");
	sc_trace(out, master_datain, "master_datain");
	sc_trace(out, slave_datain, "slave_datain");
	sc_trace(out, master_addr, "master_addr");
	sc_trace(out, slave_addr, "slave_addr");
	sc_trace(out, slave_rw, "slave_rw");
	sc_trace(out, interrupt, "interrupt");
	sc_trace(out, reset, "reset");
	sc_trace(out, x.Source_reg, "SOURCE");
	sc_trace(out, x.Target_reg, "TARGET");
	sc_trace(out, x.Size_reg, "SIZE");
	sc_trace(out, x.Start_clear_reg, "START_CLEAR");
	sc_trace(out, x.control_register[0], "CONTROL_REG_0");
	sc_trace(out, x.control_register[1], "CONTROL_REG_1");
	sc_trace(out, x.control_register[2], "CONTROL_REG_2");
	sc_trace(out, x.control_register[3], "CONTROL_REG_3");
	sc_trace(out, x.control_register[4], "CONTROL_REG_4");
	sc_trace(out, x.control_register[5], "CONTROL_REG_5");
	sc_trace(out, x.control_register[6], "CONTROL_REG_6");
	sc_trace(out, x.control_register[7], "CONTROL_REG_7");
	sc_trace(out, x.control_register[8], "CONTROL_REG_8");
	sc_trace(out, x.control_register[9], "CONTROL_REG_9");
	sc_trace(out, x.control_register[10], "CONTROL_REG_10");
	sc_trace(out, x.control_register[11], "CONTROL_REG_11");
	sc_trace(out, x.control_register[12], "CONTROL_REG_12");
	sc_trace(out, x.base_address, "DMA_BASE_addr");
	sc_trace(out, x.m_dataout, "master_data_out");
	sc_trace(out, x.m_addr, "master_addr");
	sc_trace(out, x.m_rw, "master_rw");
	sc_trace(out, x.s_data, "slave_data");
	sc_trace(out, x.s_addr, "slave_addr");
	sc_trace(out, x.s_rw, "slave_rw");
	sc_trace(out, x.clear, "clear");
	sc_trace(out, x.interrupt, "x_interrupt");
	// sc_trace(out, x.cs,"x_cs");
	// sc_trace(out, x.we,"x_we");
	// sc_trace(out, x.oe,"x_oe");

	//sc_signal<sc_uint<DATA_WIDTH> > mem_addr;
	//sc_signal<sc_uint<ADDR_WIDTH> > mem_datain;
	//sc_signal<sc_uint<ADDR_WIDTH> > mem_dataout;
	// sc_signal<bool> mem_cs;
	// sc_signal<bool> mem_we;
	// sc_signal<bool> mem_oe;
	
	Memory m("Memory");
	m.clock(clock);
	m.reset(reset);
	m.address(master_addr);
	m.data_in(master_dataout);
	m.data_out(master_datain);
	m.cs(cs);
	m.we(we);
	m.oe(oe);
	// sc_trace(out, m.cs,"m_cs");
	// sc_trace(out, m.we,"m_we");
	// sc_trace(out, m.oe,"m_oe");
	sc_trace(out, cs,"cs");
	sc_trace(out, we,"we");
	sc_trace(out, oe,"oe");
	/*
	string mmm = "m.mem_";
	int i = 0;
	string mmn = to_string(i);
	strcat(mmm,mmn);
	for (i = 0; i <= MEM_SIZE-1;i++)
	{
		sc_trace(out, m.mem[i], mmm);
	}
	*/
	sc_trace(out, m.data_in, "m_datain");
	sc_trace(out, m.data_out, "m_dataout");
	sc_trace(out, m.address, "m_address");
	sc_trace(out, m.mem[0], "m_mem_0");
	sc_trace(out, m.mem[1], "m_mem_1");
	sc_trace(out, m.mem[2], "m_mem_2");
	sc_trace(out, m.mem[3], "m_mem_3");
	sc_trace(out, m.mem[4], "m_mem_4");
	sc_trace(out, m.mem[5], "m_mem_5");
	sc_trace(out, m.mem[6], "m_mem_6");
	sc_trace(out, m.mem[7], "m_mem_7");
	sc_trace(out, m.mem[8], "m_mem_8");
	sc_trace(out, m.mem[9], "m_mem_9");
	sc_trace(out, m.mem[10], "m_mem_10");
	sc_trace(out, m.mem[11], "m_mem_11");
	sc_trace(out, m.mem[12], "m_mem_12");
	sc_trace(out, m.mem[13], "m_mem_13");
	sc_trace(out, m.mem[14], "m_mem_14");
	sc_trace(out, m.mem[15], "m_mem_15");	

// reset active low
	sc_start(0, SC_NS);
	reset.write(0);
	sc_start(t);
	reset.write(1);
	if(interrupt.read() ==1){
		clear.write(1); //clear
	}
	sc_start(t);

	//clear.write(0);
// 1st access data with size 3 from m.mem[1] to mem[10]
	slave_rw.write(0); //write to DMA
	sc_start(t);
	slave_addr.write(1);//source
	sc_start(t);
	slave_addr.write(10);//target
	sc_start(t);
	slave_datain.write(3);//size
	sc_start(t);
	slave_datain.write(1);//start
	sc_start(t);
	slave_rw.write(1); //stop write
	clear.write(0);
	
//	while(interrupt.read() ==0){
		sc_start(t);
//	}
	for(i =0;i<=100;i++){
		sc_start(t);
		if(interrupt.read() ==1){
			clear.write(1); //clear
			break;
		}
	}
	
	
	for(i =0;i<=5;i++){
		sc_start(t);
		
	}
// 2nd access data with size 2 from m.mem[13] to tar_mem[5]
	slave_rw.write(0); //write to DMA
	sc_start(t);
	slave_addr.write(13);//source
	sc_start(t);
	slave_addr.write(5);//target
	sc_start(t);
	slave_datain.write(2);//size
	sc_start(t);
	slave_datain.write(1);//start
	sc_start(t);
	slave_rw.write(1); //stop write
	clear.write(0); //clear

//	while(interrupt.read() ==0){
		sc_start(t);
//	}	
	for(i =0;i<=100;i++){
		sc_start(t);
		if(interrupt.read() ==1){
			clear.write(1); //clear
			break;
		}
	}

	sc_close_vcd_trace_file(out);
	return(0);

}



