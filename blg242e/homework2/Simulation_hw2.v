`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 25.04.2022 22:58:12
// Design Name: 
// Module Name: Simulation
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


module NAND_GATE_TEST();
    reg a;
    reg b;
    wire result;
    
    NAND_GATE NAND_TEST(.A(a), .B(b), .O(result));
    
    initial begin
    
    a = 0; b = 0; #250;
    a = 0; b = 1; #250;
    a = 1; b = 0; #250;
    a = 1; b = 1; #250;
    
    end

endmodule

module NOR_GATE_TEST();
    reg a;
    reg b;
    wire result;
    
    NOR_GATE NOR_TEST(.A(a), .B(b), .O(result));
    
    initial begin
    
    a = 0; b = 0; #250;
    a = 0; b = 1; #250;
    a = 1; b = 0; #250;
    a = 1; b = 1; #250;
    
    end

endmodule

module SR_LATCH_TEST();
    reg s;
    reg r;
    wire q;
    wire q_neg;
    
    SR_LATCH SR_TEST(.S(s), .R(r), .Q(q), .Q_neg(q_neg));
    
    initial begin
    
    s = 0; r = 0; #200;
    s = 1; r = 0; #200;
    s = 0; r = 0; #200;
    s = 0; r = 1; #200;
    s = 0; r = 0; #200;
    
    end
    
endmodule

module SR_LATCH_WITH_ENABLE_TEST();
    reg s;
    reg r;
    reg enable;
    wire q;
    wire q_neg;
    
    SR_LATCH_WITH_ENABLE SR_WITH_ENABLE_TEST(.S(s), .R(r), .ENABLE(enable), .Q(q), .Q_neg(q_neg));
    
    initial begin
    
    s = 0; r = 0; enable = 0; #150;
    s = 1; r = 0; enable = 1; #150;
    s = 0; r = 0; enable = 0; #150;
    s = 0; r = 1; enable = 0; #150;
    s = 0; r = 1; enable = 1; #150;
    s = 1; r = 0; enable = 0; #150;
    s = 1; r = 0; enable = 1; #150;
    
    end
    
endmodule

module SR_FLIPFLOP_TEST();
    reg s;
    reg r;
    wire clock;
    wire q;
    wire q_neg;
    
    CLOCK_SIGNAL _CLOCK(.CLOCK(clock));
    SR_FLIPFLOP SR_FLFP_TEST(.S(s), .R(r), .CLOCK(clock), .Q(q), .Q_neg(q_neg));
    
    initial begin
    
    s = 1; r = 0; #150;
    s = 0; r = 0; #150;
    s = 0; r = 1; #150;
    s = 1; r = 0; #150;
    s = 0; r = 1; #150;
    s = 1; r = 0; #150;
    s = 0; r = 1; #100;
    
    end

endmodule

module D_LATCH_TEST();
    reg d;
    reg enable;
    wire q;
    wire q_neg;
    
    D_LATCH D_TEST(.D(d), .ENABLE(enable), .Q(q), .Q_neg(q_neg));
    
    initial begin
    
    d = 1; enable = 1; #200;
    d = 0; enable = 0; #200;
    d = 0; enable = 1; #200;
    d = 1; enable = 0; #200;
    d = 1; enable = 1; #200;
    
    end
    
endmodule

module D_FLIPFLOP_TEST();
    reg d;
    wire clock;
    wire q;
    wire q_neg;
    
    CLOCK_SIGNAL _CLOCK(.CLOCK(clock));
    D_FLIPFLOP D_FLFP_TEST(.D(d), .CLOCK(clock), .Q(q), .Q_neg(q_neg));
    
    initial begin
    
    d = 1; #100;
    d = 0; #50;
    d = 1; #50;
    d = 0; #100;
    d = 1; #150;
    d = 0; #150;
    d = 1; #200;
    d = 0; #200;
    
    end

endmodule

module JK_FLIPFLOP_TEST();
    reg j;
    reg k;
    reg clock;
    wire q;
    wire q_neg;
    
    initial begin
        clock = 0;
    end
    always begin
        clock = ~clock; #50;
    end
    
    JK_FLIPFLOP JK_FLFP_TEST(.J(j),.K(k),.CLOCK(clock),.Q(q),.Q_neg(q_neg));
    
    initial begin
    
    j = 0; k = 0;  #100;
    j = 1; k = 0;  #100;
    j = 1; k = 1;  #100;
    j = 1; k = 1;  #100;
    j = 1; k = 1;  #100;
    j = 0; k = 0;  #100;
    j = 1; k = 0;  #100;
    j = 0; k = 0;  #100;
    j = 0; k = 1;  #100;
    
    end

endmodule

module ASYNCHRONOUS_UP_COUNTER_TEST();

    reg clock;

    initial begin
        clock = 0;
    end
    always begin
        clock = ~clock; #50;
    end

    wire [3:0] q;

    ASYNCHRONOUS_UP_COUNTER AUP_TEST(.Q(q));
    
    initial begin
        force q = 3'd0; #50;
        #950;
    end
    
    
endmodule

module SYNCHRONOUS_UP_COUNTER_TEST();
    reg count_enable;
    wire clock;
    wire [3:0] Q;
    
    CLOCK_SIGNAL _CLOCK(.CLOCK(clock));
    
    SYNCHRONOUS_UP_COUNTER SUP_TEST(.CLOCK(clock),.COUNT_ENABLE(count_enable), .Q(Q));
    
    initial begin

    count_enable = 1; #300;
    count_enable = 0; #200;
    count_enable = 1; #500;
    
    end

endmodule

// ÖZBERK HAZANTEKÝN 150200100
// LORA NOÇKA 150200912
