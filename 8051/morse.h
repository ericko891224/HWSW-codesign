#ifndef	__MORSE_H
#define __MORSE_H
#include "systemc.h"
#include <stdio.h>

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
		morse_library morse_input;
		morse_input=A;
		switch(morse_input){
			case A:				// .-
					break;
			case B: 			// -...
					break;
			case C: 			// -.-.
					break;
			case D: 			// -..
					break;
			case E: 			// .
					break;
			case F: 			// ..-.
					break;
			case G: 			// --.
					break;
			case H: 			// ....
					break;
			case I: 			// ..
					break;
			case J: 			// .---
					break;
			case K: 			// -.-
					break;
			case L: 			// .-..
					break;
			case M: 			// --
					break;
			case N: 			// -.
					break;
			case O: 			// ---
					break;
			case P: 			// .--.
					break;
			case Q: 			// --.-
					break;
			case R: 			// .-.
					break;
			case S: 			// ...
					break;
			case T: 			// -
					break;
			case U: 			// ..-
					break;
			case V: 			// ...-
					break;
			case W: 			// .--
					break;
			case X: 			// -..-
					break;
			case Y: 			// -.--
					break;
			case Z: 			// --..
					break;
			default:;
		}
	}
};

#endif
