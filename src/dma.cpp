//DMA.cpp
#include "dma.h"

void DMA::dma()
{
	//initail and reset 
	Source_reg = 0;
	Target_reg = 0;
	Size_reg = 0;
	Start_clear_reg = 0;
	temp = 0;
	count = 0;
	base_address = BASE_ADDR;
	
	// i = 0
	//output port reset 
	m_addr.write(0);
	m_dataout.write(0);
	interrupt.write(1);
	cs.write(0);
	oe.write(0);
	we.write(0);
	for (i = 0; i <= 12;i++) //reset control_registers
	{
		control_register[i] = 0;
	}
	wait();
	
	while(true)
	{
		i = 0;
		
		if(Start_clear_reg == 0 && interrupt.read() == 0) //CLEAR and wait CPU
		{
			if(s_rw.read() == 0) //CPU write 
			{
				//wait();
				temp = s_addr.read(); //Souce Addr
				control_register[i] = temp.range(31,24);
				i++;
				control_register[i] = temp.range(23,16);
				i++;
				control_register[i] = temp.range(15,8);
				i++;
				control_register[i] = temp.range(7,0);
				i++;
				wait();
				temp = s_addr.read(); //Target Addr
				control_register[i] = temp.range(31,24);
				i++;
				control_register[i] = temp.range(23,16);
				i++;
				control_register[i] = temp.range(15,8);
				i++;
				control_register[i] = temp.range(7,0);
				i++;
				wait();
				temp = s_data.read(); //Size
				control_register[i] = temp.range(31,24);
				i++;
				control_register[i] = temp.range(23,16);
				i++;
				control_register[i] = temp.range(15,8);
				i++;
				control_register[i] = temp.range(7,0);
				i++;
				wait();
				temp = s_data.read(); //START
				control_register[i] = temp.range(7,0);
				i = 0;
				//wait();
			}
			else // no CPU write
			{
				Source_reg.range(31,24) = control_register[i];
				i++;
				Source_reg.range(23,16) = control_register[i];
				i++;
				Source_reg.range(15,8) = control_register[i];
				i++;
				Source_reg.range(7,0) = control_register[i];
				i++;
				wait();
				Target_reg.range(31,24) = control_register[i];
				i++;
				Target_reg.range(23,16) = control_register[i];
				i++;
				Target_reg.range(15,8) = control_register[i];
				i++;
				Target_reg.range(7,0) = control_register[i];
				i++;
				wait();
				Size_reg.range(31,24) = control_register[i];
				i++;
				Size_reg.range(23,16) = control_register[i];
				i++;
				Size_reg.range(15,8) = control_register[i];
				i++;
				Size_reg.range(7,0) = control_register[i];
				i++;
				wait();
				temp = control_register[i];
				Start_clear_reg = temp[0];
				i = 0;
				if(interrupt.read() == 1 && Start_clear_reg == 0) //
				{
					interrupt.write(0);
					wait();
				}
				else
				{
					wait();
				}
			}
		}
		else //START  
		{
			wait();
			i = 0;
			while(Size_reg != 0)
			{
				cs.write(1);
				oe.write(1);
				we.write(0);
				m_rw.write(1); // DMA read 
				m_addr.write(Source_reg + i);
				
				wait();
				wait();
				temp = m_datain.read();
				m_dataout.write(temp);

				m_addr.write(Target_reg + i);
				oe.write(0);
				we.write(1);
				m_rw.write(0); // DMA write 
				
				//m_dataout.write(temp);
				Size_reg -= 1;
				i++;
				wait();
				wait();

			}
			cs.write(0);
			oe.write(0);
			we.write(0);
			if (clear == 0)
			{	
				interrupt.write(1);
			}
			else 
			{
				interrupt.write(0);			
			}
			if(clear.read()==1){
				control_register[12]=0;
				Start_clear_reg = 0;
			}
		}
		wait();
	}
}
