`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06.04.2022 17:14:36
// Design Name: 
// Module Name: Simulation.v
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

module AND_GATE_TEST();
    reg a;
    reg b;
    wire result;
    
    AND_GATE AND_TEST(.I0(a), .I1(b), .O(result));
    
    initial begin
    
    a = 0; b = 0; #250;
    a = 0; b = 1; #250;
    a = 1; b = 0; #250;
    a = 1; b = 1; #250;
    
    end
endmodule

module OR_GATE_TEST();
    reg a;
    reg b;
    wire result;
    
    OR_GATE OR_TEST(.I0(a), .I1(b), .O(result));
    
    initial begin
    
    a = 0; b = 0; #250;
    a = 0; b = 1; #250;
    a = 1; b = 0; #250;
    a = 1; b = 1; #250;
    
    end
endmodule

module NOT_GATE_TEST();
    reg a;
    wire complement_of_a;
    
    NOT_GATE NOT_TEST(.I(a), .O(complement_of_a));
    
    initial begin
    
    a = 0; #500;
    a = 1; #500;
    
    end
endmodule

module XOR_GATE_TEST();
    reg a;
    reg b;
    wire result;
    
    XOR_GATE XOR_TEST(.I0(a), .I1(b), .O(result));
    
    initial begin
    
    a = 0; b = 0; #250;
    a = 0; b = 1; #250;
    a = 1; b = 0; #250;
    a = 1; b = 1; #250;
    
    end
endmodule

module NAND_GATES_TEST();
    reg a;
    reg b;
    wire result;
    
    NAND_GATE NAND_TEST(.I0(a), .I1(b), .O(result));
    
    initial begin
    
    a = 0; b = 0; #250;
    a = 0; b = 1; #250;
    a = 1; b = 0; #250;
    a = 1; b = 1; #250;
    
    end
endmodule

module MULTIPLEXER81_TEST();
    reg a;
    reg b;
    reg c;
    
    wire F;
    
    MULTIPLEXER81 MULTIPLEXER_TEST(.I0(0), .I1(1), .I2(0), .I3(1), .I4(0), .I5(1), .I6(0), .I7(1), .S2(a), .S1(b), .S0(c), .O(F));
    
    initial begin
    
    a = 0; b = 0; c = 0; #125;
    a = 0; b = 0; c = 1; #125;
    a = 0; b = 1; c = 0; #125;
    a = 0; b = 1; c = 1; #125;
    a = 1; b = 0; c = 0; #125;
    a = 1; b = 0; c = 1; #125;
    a = 1; b = 1; c = 0; #125;
    a = 1; b = 1; c = 1; #125;
    
    end

endmodule

module DECODER38_TEST();
    reg a;
    reg b;
    reg c;
    
    wire _0, _1, _2, _3, _4, _5, _6, _7;
    
    DECODER38 DECODER_TEST(.S2(a), .S1(b), .S0(c), .O0(_0), .O1(_1) ,.O2(_2), .O3(_3), .O4(_4), .O5(_5), .O6(_6), .O7(_7));
    
    initial begin
    
    a = 0; b = 0; c = 0; #125;
    a = 0; b = 0; c = 1; #125;
    a = 0; b = 1; c = 0; #125;
    a = 0; b = 1; c = 1; #125;
    a = 1; b = 0; c = 0; #125;
    a = 1; b = 0; c = 1; #125;
    a = 1; b = 1; c = 0; #125;
    a = 1; b = 1; c = 1; #125;
    
    end
    
endmodule

module HALF_ADDER1_TEST();
    reg a;
    reg b;
    wire result;
    wire carry_out;
    
    HALF_ADDER1 HALF_ADDING_TEST(.I0(a), .I1(b), .SUM(result), .CARRY(carry_out));
    
    initial begin
    
    a = 0; b = 0; #250;
    a = 0; b = 1; #250;
    a = 1; b = 0; #250;
    a = 1; b = 1; #250;
    
    end
endmodule

module FULL_ADDER1_TEST();
    reg a;
    reg b;
    reg carry_in;
    wire result;
    wire carry_out;
    
    FULL_ADDER1 FULL_ADDING1_TEST(.I0(a), .I1(b), .SUM(result), .CARRY_IN(carry_in), .CARRY_OUT(carry_out));
    
    initial begin
    
    a = 0; b = 0; carry_in = 0; #125;
    a = 0; b = 0; carry_in = 1; #125;
    a = 0; b = 1; carry_in = 0; #125;
    a = 0; b = 1; carry_in = 1; #125;
    a = 1; b = 0; carry_in = 0; #125;
    a = 1; b = 0; carry_in = 1; #125;
    a = 1; b = 1; carry_in = 0; #125;
    a = 1; b = 1; carry_in = 1; #125;
    
    end
endmodule

module FULL_ADDER4_TEST();
    reg [3:0] a;
    reg [3:0] b;
    reg [0:0] carry_in;
    wire [3:0] result;
    wire [0:0] carry_out;
    
    FULL_ADDER4 FULL_ADDING4_TEST(.A(a), .B(b), .SUM(result), .CARRY_IN(carry_in), .CARRY_OUT(carry_out));
    
    initial begin
    
    a = 4'd8; b = 4'd1; carry_in = 0; #125;
    a = 4'd2; b = 4'd7; carry_in = 0; #125;
    a = 4'd4; b = 4'd5; carry_in = 0; #125;
    a = 4'd11; b = 4'd10; carry_in = 0; #125;
    a = 4'd14; b = 4'd5; carry_in = 0; #125;
    a = 4'd15; b = 4'd9; carry_in = 0; #125;
    a = 4'd6; b = 4'd3; carry_in = 0; #125;
    a = 4'd8; b = 4'd12; carry_in = 0; #125;
    
    end
endmodule

module FULL_ADDER8_TEST();
    reg [7:0] a;
    reg [7:0] b;
    reg [0:0] carry_in;
    wire [7:0] result;
    wire [0:0] carry_out;
    
    FULL_ADDER8 FULL_ADDING8_TEST(.A(a), .B(b), .SUM(result), .CARRY_IN(carry_in), .CARRY_OUT(carry_out));
    
    initial begin
    
    a = 8'd29; b = 8'd5; carry_in = 0; #125;
    a = 8'd51; b = 8'd92; carry_in = 0; #125;
    a = 8'd17; b = 8'd28; carry_in = 0; #125;
    a = 8'd191; b = 8'd2; carry_in = 0; #125;
    a = 8'd200; b = 8'd95; carry_in = 0; #125;
    a = 8'd49; b = 8'd25; carry_in = 0; #125;
    a = 8'd78; b = 8'd255; carry_in = 0; #125;
    a = 8'd43; b = 8'd59; carry_in = 0; #125;

    end
endmodule

module ADDER_SUBTRACTOR16_TEST();
    reg [15:0] a;
    reg [15:0] b;
    reg [0:0] switch;
    wire [15:0] result;
    wire [0:0] carry_out;
    
    ADDER_SUBTRACTOR16 ADDER_SUBTRACTOR_TEST(.A(a), .B(b), .SWITCH(switch), .RESULT(result), .CARRY_OUT(carry_out));
    
    initial begin
    
    a = 16'd23; b = 16'd3; switch = 0; #125;
    a = 16'd21; b = 16'd75; switch = 0; #125;
    a = 16'd16800; b = 16'd16900; switch = 0; #125;
    a = 16'd69834; b = 16'd66500; switch = 0; #125;
    a = 16'd325; b = 16'd97; switch = 0; #125;
    a = 16'd44; b = 16'd190; switch = 0; #125;
    a = 16'd463; b = 16'd241; switch = 0; #125;
    a = 16'd86; b = 16'd572; switch = 0; #125;
    
    end
endmodule

module B_MINUS_2A_CALCULATOR_TEST();
    reg [15:0] a;
    reg [15:0] b;
    wire [15:0] result;
    
    B_MINUS_2A_CALCULATOR B_MINUS_2A_TEST(.A(a), .B(b), .RESULT(result));
    
    initial begin
    
    a = 16'd32; b = 16'd7; #125;
    a = 16'd21; b = 16'd85; #125;
    a = 16'd16; b = 16'd36; #125;
    a = 16'd256; b = 16'd5; #125;
    a = 16'd200; b = 16'd95; #125;
    a = 16'd45; b = 16'd135; #125;
    a = 16'd36; b = 16'd255; #125;
    a = 16'd25; b = 16'd65; #125;
    
    end
endmodule

module PART2_TEST();
    reg a;
    reg b;
    reg c;
    reg d;
    
    wire F;
    
    PART2 PART2_TESTING(.a(a), .b(b), .c(c), .d(d), .F(F));
    
    initial begin
    
    a = 0; b = 0; c = 0; d = 0; #62.5;
    a = 0; b = 0; c = 0; d = 1; #62.5;
    a = 0; b = 0; c = 1; d = 0; #62.5;
    a = 0; b = 0; c = 1; d = 1; #62.5;
    a = 0; b = 1; c = 0; d = 0; #62.5;
    a = 0; b = 1; c = 0; d = 1; #62.5;
    a = 0; b = 1; c = 1; d = 0; #62.5;
    a = 0; b = 1; c = 1; d = 1; #62.5;
    a = 1; b = 0; c = 0; d = 0; #62.5;
    a = 1; b = 0; c = 0; d = 1; #62.5;
    a = 1; b = 0; c = 1; d = 0; #62.5;
    a = 1; b = 0; c = 1; d = 1; #62.5;
    a = 1; b = 1; c = 0; d = 0; #62.5;
    a = 1; b = 1; c = 0; d = 1; #62.5;
    a = 1; b = 1; c = 1; d = 0; #62.5;
    a = 1; b = 1; c = 1; d = 1; #62.5;
    
    end
endmodule
    
module PART3_TEST();
    reg a;
    reg b;
    reg c;
    reg d;
    
    wire F;
    
    PART3 PART3_TESTING(.a(a), .b(b), .c(c), .d(d), .F(F));
    
    initial begin
    
    a = 0; b = 0; c = 0; d = 0; #62.5;
    a = 0; b = 0; c = 0; d = 1; #62.5;
    a = 0; b = 0; c = 1; d = 0; #62.5;
    a = 0; b = 0; c = 1; d = 1; #62.5;
    a = 0; b = 1; c = 0; d = 0; #62.5;
    a = 0; b = 1; c = 0; d = 1; #62.5;
    a = 0; b = 1; c = 1; d = 0; #62.5;
    a = 0; b = 1; c = 1; d = 1; #62.5;
    a = 1; b = 0; c = 0; d = 0; #62.5;
    a = 1; b = 0; c = 0; d = 1; #62.5;
    a = 1; b = 0; c = 1; d = 0; #62.5;
    a = 1; b = 0; c = 1; d = 1; #62.5;
    a = 1; b = 1; c = 0; d = 0; #62.5;
    a = 1; b = 1; c = 0; d = 1; #62.5;
    a = 1; b = 1; c = 1; d = 0; #62.5;
    a = 1; b = 1; c = 1; d = 1; #62.5;
    
    end
endmodule

module PART4_TEST();
    reg a;
    reg b;
    reg c;
    reg d;
    
    wire F;
    
    PART4 PART4_TESTING(.a(a), .b(b), .c(c), .d(d), .F(F));
    
    initial begin
    
    a = 0; b = 0; c = 0; d = 0; #62.5;
    a = 0; b = 0; c = 0; d = 1; #62.5;
    a = 0; b = 0; c = 1; d = 0; #62.5;
    a = 0; b = 0; c = 1; d = 1; #62.5;
    a = 0; b = 1; c = 0; d = 0; #62.5;
    a = 0; b = 1; c = 0; d = 1; #62.5;
    a = 0; b = 1; c = 1; d = 0; #62.5;
    a = 0; b = 1; c = 1; d = 1; #62.5;
    a = 1; b = 0; c = 0; d = 0; #62.5;
    a = 1; b = 0; c = 0; d = 1; #62.5;
    a = 1; b = 0; c = 1; d = 0; #62.5;
    a = 1; b = 0; c = 1; d = 1; #62.5;
    a = 1; b = 1; c = 0; d = 0; #62.5;
    a = 1; b = 1; c = 0; d = 1; #62.5;
    a = 1; b = 1; c = 1; d = 0; #62.5;
    a = 1; b = 1; c = 1; d = 1; #62.5;
    
    end
 endmodule
 
 module PART5_TEST();
    reg a;
    reg b;
    reg c;
    
    wire F2;
    wire F3;
    
    PART5 PART5_TESTING(.a(a), .b(b), .c(c), .F2(F2), .F3(F3));
    
    initial begin
    
    a = 0; b = 0; c = 0; #125;
    a = 0; b = 0; c = 1; #125;
    a = 0; b = 1; c = 0; #125;
    a = 0; b = 1; c = 1; #125;
    a = 1; b = 0; c = 0; #125;
    a = 1; b = 0; c = 1; #125;
    a = 1; b = 1; c = 0; #125;
    a = 1; b = 1; c = 1; #125;
    
    end
 endmodule
 
// ÖZBERK HAZANTEKÝN 150200100
// LORA NOÇKA 150200912