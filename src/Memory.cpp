//Memory.cpp
#ifndef _MEMORY_CPP
#define _MEMORY_CPP

#include "Memory.h"

void Memory::memory_rw()
{
	//data initail
	for(i = 0;i <= MEM_SIZE-1;i++)
	{
		mem[i] = i;
	}
	wait();
	while(true)
	{
		//write mode
		if(cs.read() && we.read())
		{
			mem[address.read()] = data_in.read();
		}
		//read mode
		else if(cs.read() && oe.read() && !we.read())
		{		
			data_out.write(mem[address.read()]);
		}
		wait();
		
				
	}
}

#endif
