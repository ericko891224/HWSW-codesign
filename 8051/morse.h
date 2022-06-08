#ifndef	__MORSE_H
#define __MORSE_H
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

	bool morse_encode(vector<bool> a) 
	{
		for (unsigned i=0; i<a.size(); i++) {
			if (!a[i]) {
				D_.write(1);
				wait();
			} else {
				D_.write(1);
				wait();
				wait();
			}
			D_.write(0);
			wait();
		}
		C_.write(0);
		return true;
	}

	void behavior() {
		int morse_input;
		while(1){
			// if (!B_.read()) {
				cout << "in" << endl;
			wait();
			cout<<"A: "<<A_.read()<<", B: "<<B_.read()<<", C: "<<C_.read()<<", D: "<<D_.read()<<"\n";			
			morse_input=(int)A_.read();
			switch(morse_input){
				case A:				// .-
						cout << "A" << endl;
						morse_encode({0,1});
						break;
				case B: 			// -...
						cout << "B" << endl;
						morse_encode({1, 0, 0, 0});
						break;
				case C: 			// -.-.
						morse_encode({1, 0, 1, 0});
						break;
				case D: 			// -..
						morse_encode({1, 0, 0});
						break;
				case E: 			// .
						morse_encode({0});
						break;
				case F: 			// ..-.
						morse_encode({0, 0, 1, 0});
						break;
				case G: 			// --.
						morse_encode({1, 1, 0});
						break;
				case H: 			// ....
						morse_encode({0, 0, 0, 0});
						break;
				case I: 			// ..
						morse_encode({0, 0});
						break;
				case J: 			// .---
						morse_encode({0, 1, 1, 1});
						break;
				case K: 			// -.-
						morse_encode({1, 0, 1});
						break;
				case L: 			// .-..
						morse_encode({0, 1, 0, 0});
						break;
				case M: 			// --
						morse_encode({1, 1});
						break;
				case N: 			// -.
						morse_encode({1, 0});
						break;
				case O: 			// ---
						morse_encode({1, 1, 1});
						break;
				case P: 			// .--.
						morse_encode({0, 1, 1, 0});
						break;
				case Q: 			// --.-
						morse_encode({1, 1, 0, 1});
						break;
				case R: 			// .-.
						morse_encode({0, 1, 0});
						break;
				case S: 			// ...
						morse_encode({0, 0, 0});
						break;
				case T: 			// -
						morse_encode({1});
						break;
				case U: 			// ..-
						morse_encode({0, 0, 1});
						break;
				case V: 			// ...-
						morse_encode({0, 0, 0, 1});
						break;
				case W: 			// .--
						morse_encode({0, 1, 1});
						break;
				case X: 			// -..-
						morse_encode({1, 0, 0, 1});
						break;
				case Y: 			// -.--
						morse_encode({1, 0, 1, 1});
						break;
				case Z: 			// --..
						morse_encode({1, 1, 0, 0});
						break;
				default:
						wait();
						break;
			}
			// }
		}
	}
};



#endif
