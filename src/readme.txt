初始memory值:
mem[0] = 0
mem[1] = 1
mem[2] = 2
.
.
.
mem[15] = 15

第一次CPU指令: 1、10、3、1
功能：把memory第一個位址的資料搬到第十個位址，搬三次
也就是

mem[10] <= mem[1]
mem[11] <= mem[2]
mem[12] <= mem[3]

 
第一次CPU指令: 13、5、2、1
功能：把memory第十三個位址的資料搬到第五個位址，搬兩次
也就是

mem[5] <= mem[13]
mem[6] <= mem[14]

最後memory的內容

mem[0] = 0
mem[1] = 1
mem[2] = 2
mem[3] = 3
mem[4] = 4
mem[5] = 13
mem[6] = 14
mem[7] = 7
mem[8] = 8
mem[9] = 9
mem[10] = 1
mem[11] = 2
mem[12] = 3
mem[13] = 13
mem[14] = 14
mem[15] = 15


 