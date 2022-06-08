#include <systemc.h>
//#include <conio.h>
#define clockcycle      10   //10ns=100MHz
#define clockcycle_800  1.25 //1.25ns=800MHz
#include "top.h"


int sc_main(int argc, char *argv[])
{

    char *filename;
	bool dolog;

	if (argc<2) {
	    printf("Usage:8051_iss filename imagename\n");
	    return(1);
	}
	if (argc<3) {
	    printf("Usage:8051_iss filename imagename\n");
	    return(1);
	}
	filename=argv[1];
        sc_clock                clk("CLOCK",clockcycle,SC_NS,0.5,1,SC_NS);
		sc_clock                clk_800("CLOCK_800",clockcycle_800, SC_NS,0.5,1,SC_NS);
        sc_signal<sc_uint<1> >  reset;
        sc_signal<sc_uint<1> >  poff;
		
        top top("top");
        top.clk(clk);
		top.clk_800(clk_800);
        top.reset(reset);
        top.poff(poff);
		

        if (!top.core->loadrom(filename)) {
            printf("%s file not found\n",filename);
            return(1);
        }
		filename=argv[2];
		{
			FILE *FR;
			unsigned char s;
			int i;
			FR=fopen(filename,"rb");
			if (FR==NULL) {printf("%s file not found\n",filename);return(1);}
			for(i=0;i<8*8;i++)
			{
				s=fgetc(FR);
				top.xrambig->mem[(0x3000)+i]=s;
			}
			fclose (FR);
		}


        ///////////////////////////////////Start Test
        sc_start(100,SC_NS);	

		sc_trace_file* Tf;
		Tf = sc_create_vcd_trace_file("waveform");
		sc_trace(Tf, clk_800, "clk_800");
		sc_trace(Tf, clk, "clk");

		sc_trace(Tf, top.port0o, "port0o");
		sc_trace(Tf, top.port3o, "port3o");
		sc_trace(Tf, top.port2i, "port2i");
		sc_trace(Tf, top.port1i, "port1i");
		


		sc_start(10000, SC_NS);
			
		sc_close_vcd_trace_file(Tf);

        return(0);
}
