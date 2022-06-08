#ifndef	__MORSE_H
#define __MORSE_H
#include "systemc.h"
#include <stdio.h>


SC_MODULE(morse)
{
	sc_in_clk			    clk;
	sc_in<sc_uint<1> >		reset;
	sc_in<sc_uint<8> >      A;  	// P0: input random A
	sc_in<sc_uint<8> >      B;  	// P3: control signal to FIR
	sc_out<sc_uint<8> >     C;  	// P2: has_reset
	sc_out<sc_uint<8> >     D;  	// P1: 8051 forwards result to Port2
	sc_signal<bool> rst;

	SC_CTOR(morse)
	{
		reset = true;
		SC_CTHREAD(behavior, clk.neg());
	}
	void behavior() {
		C.write(0);
		while(1) {
			wait();
		}
	}
};

#endif
