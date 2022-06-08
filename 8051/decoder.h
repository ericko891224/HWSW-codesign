#ifndef	__DECODER_H
#define __DECODER_H
#include "systemc.h"
#include <stdio.h>
#include <vector>

using namespace std;

typedef enum{
    A = 0,
    B,
    C,
    D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z
}morse_library;

SC_MODULE(morse)
{
	sc_in_clk			    clk;
	sc_in<sc_uint<1> >		reset;
	sc_in<sc_uint<8> >      A_;  	// P0: input random A
	sc_in<sc_uint<8> >      B_;  	// P3: control signal to FIR
	sc_out<sc_uint<8> >     C_;  	// P2: has_reset
	sc_out<sc_uint<8> >     D_;  	// P1: 8051 forwards result to Port2
	sc_signal<bool> rst;

	SC_CTOR(morse)
	{
		// reset = true;
		SC_CTHREAD(behavior, clk.neg());
	}

    void behavior()
    {
        vector<bool> decode_input;

        while (1) {

        }
    }
}


#endif