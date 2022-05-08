`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03.04.2022 21:48:02
// Design Name: 
// Module Name: modules
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module AND_GATE(I0, I1, O);
    input wire I0;
    input wire I1;
    
    output wire O;
    
    assign O = I0 & I1;

endmodule

module OR_GATE(I0, I1, O);
    input wire I0;
    input wire I1;
    
    output wire O;
    
    assign O = I0 | I1;
    
endmodule

module NOT_GATE(I, O);
    input wire I;
    
    output wire O;
    
    assign O = ~I;

endmodule

module XOR_GATE(I0, I1, O);

    input wire I0;
    input wire I1;
    
    output wire O;
    
    assign O = (~I0 & I1) | (I0 & ~I1);

endmodule

module NAND_GATE(I0, I1, O);
    
    input wire I0;
    input wire I1;
    
    output wire O;
    
    assign O = ~(I0 & I1);

endmodule

module MULTIPLEXER81(I0, I1, I2, I3, I4, I5, I6, I7, S2, S1, S0, O);
    
    input wire I0, I1, I2, I3, I4, I5, I6, I7, S2, S1, S0;
    output wire O;
    
    assign O = ((~S2 & ~S1 & ~S0 & I0) | (~S2 & ~S1 & S0 & I1) | (~S2 & S1 & ~S0 & I2) | (~S2 & S1 & S0 & I3) | (S2 & ~S1 & ~S0 & I4) | (S2 & ~S1 & S0 & I5) | (S2 & S1 & ~S0 & I6) | (S2 & S1 & S0 & I7)); 

endmodule

module DECODER38(S2, S1, S0, O0, O1 ,O2, O3, O4, O5, O6, O7);

    input wire S2, S1, S0;
    
    output wire O0, O1, O2, O3, O4, O5, O6, O7;
    
    assign O0 = ~S2 & ~S1 & ~S0;
    assign O1 = ~S2 & ~S1 & S0;
    assign O2 = ~S2 & S1 & ~S0;
    assign O3 = ~S2 & S1 & S0;
    assign O4 = S2 & ~S1 & ~S0;
    assign O5 = S2 & ~S1 & S0;
    assign O6 = S2 & S1 & ~S0;
    assign O7 = S2 & S1 & S0;

endmodule

module HALF_ADDER1(I0, I1, SUM, CARRY);
    
    input wire I0, I1;
    output wire SUM, CARRY;
    
    XOR_GATE SUM_CALCULATOR(.I0(I0), .I1(I1), .O(SUM));
    AND_GATE CARRY_CALCULATOR(.I0(I0), .I1(I1), .O(CARRY));

endmodule

module FULL_ADDER1(I0, I1, SUM, CARRY_IN, CARRY_OUT);

    input wire I0, I1, CARRY_IN;
    
    output wire SUM, CARRY_OUT;
    
    wire INTERMEDIATE_SUM, INTERMEDIATE_CARRY1, INTERMEDIATE_CARRY2;
    
    HALF_ADDER1 FIRST_HALF_ADDER(.I0(I0), .I1(I1), .SUM(INTERMEDIATE_SUM), .CARRY(INTERMEDIATE_CARRY1));
    HALF_ADDER1 SECOND_HALF_ADDER(.I0(INTERMEDIATE_SUM), .I1(CARRY_IN), .SUM(SUM), .CARRY(INTERMEDIATE_CARRY2));
    OR_GATE CARRY_CALCULATOR(.I0(INTERMEDIATE_CARRY1), .I1(INTERMEDIATE_CARRY2), .O(CARRY_OUT));

endmodule

module FULL_ADDER4(A, B, SUM, CARRY_IN, CARRY_OUT);

    input wire [3:0] A;
    input wire [3:0] B;
    input wire [0:0] CARRY_IN;
    
    output wire [3:0] SUM;
    output wire [0:0] CARRY_OUT;
    
    wire CARRY1, CARRY2, CARRY3;
    
    FULL_ADDER1 BIT1(.I0(A[0]),.I1(B[0]), .SUM(SUM[0]), .CARRY_IN(CARRY_IN), .CARRY_OUT(CARRY1));
    FULL_ADDER1 BIT2(.I0(A[1]),.I1(B[1]), .SUM(SUM[1]), .CARRY_IN(CARRY1), .CARRY_OUT(CARRY2));
    FULL_ADDER1 BIT3(.I0(A[2]),.I1(B[2]), .SUM(SUM[2]), .CARRY_IN(CARRY2), .CARRY_OUT(CARRY3));
    FULL_ADDER1 BIT4(.I0(A[3]),.I1(B[3]), .SUM(SUM[3]), .CARRY_IN(CARRY3), .CARRY_OUT(CARRY_OUT)); 
    
endmodule

module FULL_ADDER8(A, B, SUM, CARRY_IN, CARRY_OUT);

    input wire [7:0] A;
    input wire [7:0] B;
    input wire [0:0] CARRY_IN;
    
    output wire [7:0] SUM;
    output wire [0:0] CARRY_OUT;
    
    wire CARRY1, CARRY2, CARRY3, CARRY4, CARRY5, CARRY6, CARRY7;
    
    FULL_ADDER1 BIT1(.I0(A[0]),.I1(B[0]), .SUM(SUM[0]), .CARRY_IN(CARRY_IN), .CARRY_OUT(CARRY1));
    FULL_ADDER1 BIT2(.I0(A[1]),.I1(B[1]), .SUM(SUM[1]), .CARRY_IN(CARRY1), .CARRY_OUT(CARRY2));
    FULL_ADDER1 BIT3(.I0(A[2]),.I1(B[2]), .SUM(SUM[2]), .CARRY_IN(CARRY2), .CARRY_OUT(CARRY3));
    FULL_ADDER1 BIT4(.I0(A[3]),.I1(B[3]), .SUM(SUM[3]), .CARRY_IN(CARRY3), .CARRY_OUT(CARRY4));
    FULL_ADDER1 BIT5(.I0(A[4]),.I1(B[4]), .SUM(SUM[4]), .CARRY_IN(CARRY4), .CARRY_OUT(CARRY5));
    FULL_ADDER1 BIT6(.I0(A[5]),.I1(B[5]), .SUM(SUM[5]), .CARRY_IN(CARRY5), .CARRY_OUT(CARRY6));
    FULL_ADDER1 BIT7(.I0(A[6]),.I1(B[6]), .SUM(SUM[6]), .CARRY_IN(CARRY6), .CARRY_OUT(CARRY7));
    FULL_ADDER1 BIT8(.I0(A[7]),.I1(B[7]), .SUM(SUM[7]), .CARRY_IN(CARRY7), .CARRY_OUT(CARRY_OUT));
    
endmodule

module ADDER_SUBTRACTOR16(A, B, SWITCH, RESULT, CARRY_OUT);

    input wire [15:0] A;
    input wire [15:0] B;
    input wire [0:0] SWITCH; // IF SWITCH IS 0 ADD, IF SWITCH IS 1 SUBTRACT
    
    output wire [15:0] RESULT;
    output wire [0:0] CARRY_OUT;
    
    wire [15:0] C; // B OR TWOS COMPLEMENT OF B
    wire CARRY1, CARRY2, CARRY3, CARRY4, CARRY5, CARRY6, CARRY7, CARRY8, CARRY9, CARRY10, CARRY11, CARRY12, CARRY13, CARRY14, CARRY15; 
    
    XOR_GATE ADD_OR_SUBTRACT_BIT0(B[0], SWITCH, C[0]);
    XOR_GATE ADD_OR_SUBTRACT_BIT1(B[1], SWITCH, C[1]);
    XOR_GATE ADD_OR_SUBTRACT_BIT2(B[2], SWITCH, C[2]);
    XOR_GATE ADD_OR_SUBTRACT_BIT3(B[3], SWITCH, C[3]);
    XOR_GATE ADD_OR_SUBTRACT_BIT4(B[4], SWITCH, C[4]);
    XOR_GATE ADD_OR_SUBTRACT_BIT5(B[5], SWITCH, C[5]);
    XOR_GATE ADD_OR_SUBTRACT_BIT6(B[6], SWITCH, C[6]);
    XOR_GATE ADD_OR_SUBTRACT_BIT7(B[7], SWITCH, C[7]);  
    XOR_GATE ADD_OR_SUBTRACT_BIT8(B[8], SWITCH, C[8]);
    XOR_GATE ADD_OR_SUBTRACT_BIT9(B[9], SWITCH, C[9]);
    XOR_GATE ADD_OR_SUBTRACT_BIT10(B[10], SWITCH, C[10]);
    XOR_GATE ADD_OR_SUBTRACT_BIT11(B[11], SWITCH, C[11]);
    XOR_GATE ADD_OR_SUBTRACT_BIT12(B[12], SWITCH, C[12]);
    XOR_GATE ADD_OR_SUBTRACT_BIT13(B[13], SWITCH, C[13]);
    XOR_GATE ADD_OR_SUBTRACT_BIT14(B[14], SWITCH, C[14]);
    XOR_GATE ADD_OR_SUBTRACT_BIT15(B[15], SWITCH, C[15]);
    
    FULL_ADDER1 BIT1(.I0(A[0]),.I1(C[0]), .SUM(RESULT[0]), .CARRY_IN(SWITCH), .CARRY_OUT(CARRY1));
    FULL_ADDER1 BIT2(.I0(A[1]),.I1(C[1]), .SUM(RESULT[1]), .CARRY_IN(CARRY1), .CARRY_OUT(CARRY2));
    FULL_ADDER1 BIT3(.I0(A[2]),.I1(C[2]), .SUM(RESULT[2]), .CARRY_IN(CARRY2), .CARRY_OUT(CARRY3));
    FULL_ADDER1 BIT4(.I0(A[3]),.I1(C[3]), .SUM(RESULT[3]), .CARRY_IN(CARRY3), .CARRY_OUT(CARRY4));
    FULL_ADDER1 BIT5(.I0(A[4]),.I1(C[4]), .SUM(RESULT[4]), .CARRY_IN(CARRY4), .CARRY_OUT(CARRY5));
    FULL_ADDER1 BIT6(.I0(A[5]),.I1(C[5]), .SUM(RESULT[5]), .CARRY_IN(CARRY5), .CARRY_OUT(CARRY6));
    FULL_ADDER1 BIT7(.I0(A[6]),.I1(C[6]), .SUM(RESULT[6]), .CARRY_IN(CARRY6), .CARRY_OUT(CARRY7));
    FULL_ADDER1 BIT8(.I0(A[7]),.I1(C[7]), .SUM(RESULT[7]), .CARRY_IN(CARRY7), .CARRY_OUT(CARRY8));
    FULL_ADDER1 BIT9(.I0(A[8]),.I1(C[8]), .SUM(RESULT[8]), .CARRY_IN(CARRY8), .CARRY_OUT(CARRY9));
    FULL_ADDER1 BIT10(.I0(A[9]),.I1(C[9]), .SUM(RESULT[9]), .CARRY_IN(CARRY9), .CARRY_OUT(CARRY10));
    FULL_ADDER1 BIT11(.I0(A[10]),.I1(C[10]), .SUM(RESULT[10]), .CARRY_IN(CARRY10), .CARRY_OUT(CARRY11));
    FULL_ADDER1 BIT12(.I0(A[11]),.I1(C[11]), .SUM(RESULT[11]), .CARRY_IN(CARRY11), .CARRY_OUT(CARRY12));
    FULL_ADDER1 BIT13(.I0(A[12]),.I1(C[12]), .SUM(RESULT[12]), .CARRY_IN(CARRY12), .CARRY_OUT(CARRY13));
    FULL_ADDER1 BIT14(.I0(A[13]),.I1(C[13]), .SUM(RESULT[13]), .CARRY_IN(CARRY13), .CARRY_OUT(CARRY14));
    FULL_ADDER1 BIT15(.I0(A[14]),.I1(C[14]), .SUM(RESULT[14]), .CARRY_IN(CARRY14), .CARRY_OUT(CARRY15));
    FULL_ADDER1 BIT16(.I0(A[15]),.I1(C[15]), .SUM(RESULT[15]), .CARRY_IN(CARRY15), .CARRY_OUT(CARRY_OUT));

endmodule

module B_MINUS_2A_CALCULATOR(A, B,  RESULT);

    input wire [15:0] A;
    input wire [15:0] B;
    
    wire [15:0] _2A_;
    
    output wire [15:0] RESULT;
    
    ADDER_SUBTRACTOR16 _2A_FINDER(.A(A), .B(A), .SWITCH(0), .RESULT(_2A_), .CARRY_OUT()); // THERE WILL BE NO OVERFLOW FOR THE GIVEN EXAMPLES IN THE HOMEWORK, SO I WILL IGNORE OVERFLOW INSTANCES
    ADDER_SUBTRACTOR16 B_MINUS_2A(.A(B), .B(_2A_), .SWITCH(1), .RESULT(RESULT), .CARRY_OUT());

endmodule

module PART2(a, b, c, d, F);

    input wire a, b, c, d;
    wire not_a, not_b, not_d, not_b_not_d, ac, acd, bc, acd_or_not_a_bc, not_a_bc;
    output wire F;
    
    NOT_GATE NOT_A(.I(a), .O(not_a));
    NOT_GATE NOT_B(.I(b), .O(not_b));
    NOT_GATE NOT_D(.I(d), .O(not_d));    
    AND_GATE BC(.I0(b), .I1(c), .O(bc));
    AND_GATE NOT_B_NOT_D(.I0(not_b), .I1(not_d), .O(not_b_not_d));
    AND_GATE NOT_A_BC(.I0(not_a),.I1(bc),.O(not_a_bc));
    AND_GATE AC(.I0(a),.I1(c),.O(ac));
    AND_GATE ACD(.I0(ac),.I1(d),.O(acd));
    OR_GATE ACD_OR_NOT_A_BC(.I0(not_a_bc),.I1(acd),.O(acd_or_not_a_bc));
    OR_GATE OUTPUT_F(.I0(not_b_not_d),.I1(acd_or_not_a_bc),.O(F));
    
endmodule

module PART3(a, b, c, d, F);

    input wire a, b, c, d;
    wire not_a, not_b, not_d, b_or_d, a_or_not_b, not_a_b, a_or_not_b_or_not_c, not_a_or_not_c, ac, not_a_or_not_c_or_not_d, wire1, wire2;
    output wire F;
    
    NAND_GATE NOT_A(.I0(a), .I1(a),.O(not_a));
    NAND_GATE NOT_B(.I0(b), .I1(b),.O(not_b));
    NAND_GATE NOT_D(.I0(d), .I1(d),.O(not_d));
    NAND_GATE B_OR_D(.I0(not_b), .I1(not_d),.O(b_or_d));
    NAND_GATE A_OR_NOT_B(.I0(not_a), .I1(b),.O(a_or_not_b));
    NAND_GATE NOT_A_B(.I0(a_or_not_b), .I1(a_or_not_b),.O(not_a_b));
    NAND_GATE A_OR_NOT_B_OR_NOT_C(.I0(not_a_b), .I1(c),.O(a_or_not_b_or_not_c));
    NAND_GATE NOT_A_OR_NOT_C(.I0(a), .I1(c),.O(not_a_or_not_c));
    NAND_GATE AC(.I0(not_a_or_not_c), .I1(not_a_or_not_c),.O(ac));
    NAND_GATE NOT_A_OR_NOT_C_OR_NOT_D(.I0(ac), .I1(d),.O(not_a_or_not_c_or_not_d));
    NAND_GATE NAND_11(.I0(b_or_d), .I1(a_or_not_b_or_not_c),.O(wire1));
    NAND_GATE NAND_12(.I0(wire1), .I1(wire1),.O(wire2));
    NAND_GATE F_(.I0(wire2), .I1(not_a_or_not_c_or_not_d),.O(F));

endmodule

module PART4(a, b, c, d, F);
    input wire a, b, c, d;
    wire not_d;
    output wire F;
    
    NOT_GATE NOT_D(.I(d),.O(not_d));
    MULTIPLEXER81 MULTIPLEXER(.I0(not_d), .I1(not_d), .I2(0), .I3(1), .I4(not_d), .I5(1), .I6(0), .I7(d), .S2(a), .S1(b), .S0(c), .O(F));
    
endmodule

module PART5(a, b, c, F2, F3);

    input wire a, b, c;
    wire _3, _5, _6, _7;
    output wire F2, F3;
    
    DECODER38 DECODER(.S2(a), .S1(b), .S0(c), .O0(), .O1() ,.O2(), .O3(_3), .O4(), .O5(_5), .O6(_6), .O7(_7));
    OR_GATE F2_(.I0(_3), .I1(_5), .O(F2));
    OR_GATE F3_(.I0(_6), .I1(_7), .O(F3));
    
endmodule



// ÖZBERK HAZANTEKÝN 150200100
// LORA NOÇKA 150200912









