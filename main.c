#include <stdio.h>


int pc = 0;  // Program counter

#define NUM_REGS 4
int regs[ NUM_REGS ];


int instrNum = 0;
int reg1    =0;
int reg2    = 0;
int reg3    =0;
int imm      =0;

// FOr now, use pre-assembled version of the program
int prog[] = {0x1064, 0x11C8, 0x2201, 0x0000};
int epilog_prog[] = {0x3020};
int * full_program = 0xdeadbeef;
int running = 1;
/*

0 = halt
1 = loadi
2 = add
3 = movrr

Decoding 0x1064:

0x  1            0           64
    ^ instr      ^ register  ^ imm value
bits 15-12 = 1
bits 11- 8 = register number
bits  7- 0 = immediate value


movrr  r0 r2

128   64   32   16   8   4  2   1
0     1    0    0    0   0  0   0 
0     0    0    0    0   0  0   0
0     0    0    0    0   0  0   1
???
*/
void decode( int instr)
{ 

  instrNum =  (instr & 0xF000) >>  12;
  reg1     = (instr & 0xF00 ) >>  8;
  reg2     = (instr & 0xF0  ) >>  4;
  reg3     = (instr & 0xF   );
  imm      = (instr & 0xFF  );
}

int fetch()
{
  return full_program[pc++];

}
void eval()
{
  switch (instrNum)
  {
    case 0:
      printf ("halt\n");
      running = 0;
      break;
    case 1:
      printf("loadi r%d #%d\n",reg1, imm);
      regs[reg1] = imm;
      break;
    case 2:
      printf("add r%d r%d r%d\n",reg1,reg2,reg3);
      regs[reg1] = regs[reg2] + regs[reg3];
      break;
    case 3:
      printf("movrr r%d r%d\n", reg1, reg2);
      int temp = regs[reg2];
      regs[reg2] = regs[reg1];
      regs[reg1] = temp;
  }
}

void run()
{
  while(running)
  {

    int instr = fetch();
    decode(instr);
    eval();
  }


}


void fixup()
{

  full_program = malloc(5 * sizeof(int));
  memcpy(full_program,prog, 4 * sizeof(int));
  memcpy(full_program+3,epilog_prog,1* sizeof(int));
  

  for (int i = 0; i < 4; i++)
  {
    printf("hey %x \n",full_program[i]);
  }

}
int main()
{ 
  fixup();
  run();
  printf("%d\n",regs[reg1] );
  printf("%d\n",regs[reg2] );
  printf("%d\n",regs[reg3] );
  return 0;


}

/* Main loop does:
 * *Fetch the next instruction
 * *Decode instruction into it's consituent parts
 * *Execute the decoded instruction
*/








