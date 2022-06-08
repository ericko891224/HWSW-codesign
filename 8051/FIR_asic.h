#ifndef	__ASIC_H
#define __ASIC_H
#include "systemc.h"
#include <stdio.h>


SC_MODULE(FIR_asic)
{
	sc_in_clk			    clk;
	sc_in<sc_uint<1> >		reset;
	sc_in<sc_uint<8> >      A;  	// P0: input random A
	sc_in<sc_uint<8> >      B;  	// P3: control signal to FIR
	sc_out<sc_uint<8> >     C;  	// P2: has_reset
	sc_out<sc_uint<8> >     D;  	// P1: 8051 forwards result to Port2
	sc_signal<bool> rst;

	SC_CTOR(FIR_asic)
	{
		/*
		rst = true;
		SC_CTHREAD(FIR_1, clk.neg());
		SC_CTHREAD(FIR_N, clk.neg());
		*/
		SC_CTHREAD(behavior, clk.neg());
	}
	void behavior() {
		const int FIR_LEN = 9;
		const int c[FIR_LEN] = {0, 0, 1, 2, 3, 4, 5, 6, 7};
		int i[FIR_LEN-1] = {0};
		C.write(0);
		while(1) {
			wait();
			//cout << A.read() << ", " << B.read() << ", " << C.read() << ", " << D.read() << endl;
			//getchar();
			if(B.read() == 1){
				//printf("in\n");
				D.write( 
					c[0] * A.read() + 
					c[1] * i[0] +
					c[2] * i[1] +
					c[3] * i[2] +
					c[4] * i[3] +
					c[5] * i[4] +
					c[6] * i[5]
				);

				i[6] = i[5];
				i[5] = i[4];
				i[4] = i[3];
				i[3] = i[2];
				i[2] = i[1];
				i[1] = i[0];
				i[0] = A.read();
		
				C.write(1);
			}
			else{
				C.write(0);
			}
		}
	}

/*	
	// 1 cycle 
	void FIR_1() {
		if (rst)
		{
			C.write(0x00);
			D.write(0x00);
			rst = false;
		}
		
		const int FIR_LEN = 9;
		const int c[FIR_LEN] = {0, 0, 1, 2, 3, 4, 5, 6, 7};
		sc_uint<8> a[FIR_LEN];
		
		sc_uint<8> index = 0;
		sc_uint<8> sum = 0;
		
		
		//  TODO: 
		//    Design Your one-cycle FIR.
		
	}
	
	/* N cycle 
	void FIR_N() {
		if (rst)
		{
			C.write(0x00);
			D.write(0x00);
			rst = false;
		}
		const int FIR_LEN = 9;
		const int c[FIR_LEN] = {0, 0, 1, 2, 3, 4, 5, 6, 7};
		
		sc_uint<8> index = 0;
		sc_uint<8> sum = 0;

		C.write(0);
		while(1){
			wait();
			
			//  TODO: 
			//	Design Your N-cycle FIR.
			
		}
	}
*/
};

#endif
