/* Copyright (C) 2022, 2023 Petr Antos, AP-ware servis (mixworx.net) antos.petr@gmail.com - ALL RIGHTS RESERVED */

void cmd_version(Core *core)
{
    println("  VMEX 0.30-230408a (c)2022 mixworx.net");
    println("");
}

#ifdef MONITOR

//considering to use a-z memories for ranges from-to

//r - registers
//.a=8000-8300
//m.a - print memory range a
//w.a - input memory range a
//.b=9000-9030
//m.b - print memory range b
//w.b - input memory range b

void cmd_help(Core *core)
{
    println("  ? - help");
    println("  q - quit");
    println("  v - version");
    println("  t - tests");
    println("  g - go");
    println("  r - registers");
    println("  m - read memory");
    println("  .M - read memory with CRC");
    println("  .w - write memory");
    println("  .W - write memory with CRC");
    println("  .d - disassembly");
    println("  .D - ASLIX disassembly");
    println("  .a - assembly");
    println("  .A - ASLIX assembly");
    
    println("");
}

void cmd_registers(Core *core)
{
    println("  0-zero   1-ra     2-sp     3-gp");
    print("  ");
    print(itoh(core->regs[0], 8)); print(" ");
    print(itoh(core->regs[1], 8)); print(" ");
    print(itoh(core->regs[2], 8)); print(" ");
    print(itoh(core->regs[3], 8)); println(" ");
    
    println("  4-tp     5-t0     6-t1     7-t2");
    print("  ");
    print(itoh(core->regs[4], 8)); print(" ");
    print(itoh(core->regs[5], 8)); print(" ");
    print(itoh(core->regs[6], 8)); print(" ");
    print(itoh(core->regs[7], 8)); println(" ");

    println("  8-s0     9-s1     A-a0     B-a1");
    print("  ");
    print(itoh(core->regs[8], 8)); print(" ");
    print(itoh(core->regs[9], 8)); print(" ");
    print(itoh(core->regs[10], 8)); print(" ");
    print(itoh(core->regs[11], 8)); println(" ");
    
    println("  C-a2     D-a3     E-a4     F-a5");
    print("  ");
    print(itoh(core->regs[12], 8)); print(" ");
    print(itoh(core->regs[13], 8)); print(" ");
    print(itoh(core->regs[14], 8)); print(" ");
    print(itoh(core->regs[15], 8)); println(" ");
}

void cmd_memory(Core *core, int from, int words)
{
    int i,j;
    int word=0;
    for(i=0; i<(words/4)+1; i++)
    {
        print("W ");
        for(j=0; j<4; j++)
        {
            if (word==words) break;
            print(itoh(core->data[from+4*i+j], 8)); print(" ");
            word++;
        }
        println("CC");
    }
}

void cmd_go(Core *core)
{
    
    TU8 testprog[] =
    {
        0x11, 0xAA, 0x00, 0x01, // addi r10 r0 5
        0x11, 0xBB, 0x00, 0x0B, // addi r11 r0 5
        0x11, 0xCC, 0x00, 0x0C, // addi r12 r0 5
        0x11, 0xDD, 0x00, 0x0D, // addi r13 r0 5
        
        0x51, 0xD0, 0x00, 0x00, // wb r13 r0 0
        0x11, 0xDD, 0x00, 0x01, // addi r13 r13 1
        0x51, 0xD0, 0x00, 0x01, // wb r13 r0 1
        0x42, 0x00, 0x00, 0x00, // ecall
        0x48, 0x00, 0x00, 0x00, // ebreak                
    };

    int result = vmex(testprog, sizeof(testprog));
    
    println("");
    print("  exit code: "); println(itoh(result,2));
}

#endif

