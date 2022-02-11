# ESL Project1 - DMA_controller_in_SystemC - vincent08tw
###### tags: `ESL` `SystemC`

## Outline

## Project Description
Develop a Direct Memory Access Controller (DMA/DMAC) in SystemC.

* Specification
	* The DMA behavior is illustrated as:
	
```
1. The DMA has:
	i. Two (2) 32-bit bus ports: 32-bit address field, 32-bit data field,
		and a 1-bit r/w pin. One port is a master port, and the other is a
		slave port.
	ii. One (1) 1-bit interrupt output pin.
	iii. One (1) 1-bit reset input pin.
	iv. One static address register to store its base address.
2. There are also four (4) control registers in the DMA:
	i. SOURCE: 32-bit, the starting source address, at 0x0
	ii. TARGET: 32-bit, the starting target address, at 0x4
	iii. SIZE: 32-bit, the data size, at 0x8
	iv. START/CLEAR: 1-bit, the start and clear signal, at 0xC
3. Implement the DMA module with a SC_CTHREAD process and it:
	i. reads from the slave port the control data, i.e. source address,
		target address, size and start. These data are stored into control
		registers, respectively.
	ii. Once a
	iii. START/CLEAR = 1 value (0xC = 1) is received and stored,
		start moving data from the source address to the target address,
		until the SIZE is reached.
	iv. When the data movement is completed, first pull the interrupt
		signal (interrupt) to high and wait for the interrupt clear
		control (START/CLEAR, 0X0C = 0). Only after the CLEAR
		arrives then the DMA resets the interrupt to low and resume to
		the original state.
	v. The reset pin (reset) is synchronous and active low. At reset
		all 4 control registers are set to 0 and interrupt signal is pull
		to low.
```

## Project directory hierachy
```
DMA_controller_in_SystemC/
    +-- src/
    |   +-- dma
    |   +-- dma.cpp
    |   +--	dma.h
    |   +--	dma.o
    |   +--	main.cpp
    |   +--	makefile
    |   +--	Memory.cpp
    |   +--	Memory.h
    |   +--	Memory.o
    |   +--	readme.txt
    |   +--	RESULT.vcd
    +-- img/
	|   +--	behavior_of_DMA.PNG
	|
	README.md
```























