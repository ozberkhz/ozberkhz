`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 25.04.2022 15:47:21
// Design Name: 
// Module Name: sr_latch
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

module CLOCK_SIGNAL(CLOCK);
    output wire CLOCK;
    wire INTERMEDIATE_WIRE;
    reg INVERTER;

    initial begin
        INVERTER = 0;
    end
    always begin 
        INVERTER = ~INVERTER; #50;
    end
    
    assign INTERMEDIATE_WIRE = INVERTER;
    assign CLOCK = ~INTERMEDIATE_WIRE;

endmodule

module NOR_GATE(A, B, O);
    input wire A, B;
    output wire O;
    
    assign O = ~(A | B);

endmodule

module NAND_GATE(A, B, O);
    input wire A, B;
    output wire O;

    assign O = ~(A & B);
    
endmodule

module SR_LATCH(S, R, Q, Q_neg);
    input wire S, R;
    output wire Q, Q_neg;
    
    NOR_GATE Q_GATE(.A(R), .B(Q_neg), .O(Q));
    NOR_GATE Q_NEG_GATE(.A(S), .B(Q), .O(Q_neg));

endmodule

module SR_LATCH_WITH_ENABLE(S, R, ENABLE, Q, Q_neg);
    input wire S, R, ENABLE;
    output wire Q, Q_neg;
    wire S_INVERSE_ENABLED, R_INVERSE_ENABLED;
    
    NAND_GATE S_INVERSE_WITH_ENABLE(.A(S), .B(ENABLE), .O(S_INVERSE_ENABLED));
    NAND_GATE R_INVERSE_WITH_ENABLE(.A(R), .B(ENABLE), .O(R_INVERSE_ENABLED));
    NAND_GATE Q_GATE(.A(S_INVERSE_ENABLED), .B(Q_neg), .O(Q));
    NAND_GATE Q_NEG_GATE(.A(R_INVERSE_ENABLED), .B(Q), .O(Q_neg));

endmodule

module SR_FLIPFLOP(S, R, CLOCK, Q, Q_neg);
    input wire S, R, CLOCK;
    output wire Q, Q_neg;
    wire CLOCK_INVERTED, S_INTERMEDIATE, R_INTERMEDIATE;
    
    NAND_GATE INVERTED_CLOCK(.A(CLOCK), .B(CLOCK), .O(CLOCK_INVERTED));
    SR_LATCH_WITH_ENABLE MASTER_SR_LATCH(.S(S), .R(R), .ENABLE(CLOCK_INVERTED), .Q(S_INTERMEDIATE), .Q_neg(R_INTERMEDIATE));
    SR_LATCH_WITH_ENABLE SLAVE_SR_LATCH(.S(S_INTERMEDIATE), .R(R_INTERMEDIATE), .ENABLE(CLOCK), .Q(Q), .Q_neg(Q_neg));
    
endmodule

module D_LATCH(D, ENABLE, Q, Q_neg);

    input wire D, ENABLE;
    output wire Q, Q_neg;
    wire D_INVERSE, D_ENABLED, D_INVERSE_ENABLED;
    
    NAND_GATE D_INVERTED(.A(D), .B(D), .O(D_INVERSE));
    NAND_GATE D_ENABLED_NAND(.A(D), .B(ENABLE), .O(D_ENABLED));
    NAND_GATE D_INVERTED_ENABLED_NAND(.A(D_INVERSE), .B(ENABLE), .O(D_INVERSE_ENABLED));
    NAND_GATE Q_NAND(.A(D_ENABLED), .B(Q_neg), .O(Q));
    NAND_GATE NOT_Q_NAND(.A(D_INVERSE_ENABLED), .B(Q), .O(Q_neg));
    
endmodule

module D_FLIPFLOP(D, CLOCK, Q, Q_neg);
    input wire D, CLOCK;
    output wire Q, Q_neg;
    wire Q_INTERMEDIATE, INVERTED_CLOCK; 
    
    assign INVERTED_CLOCK = ~CLOCK;
    
    D_LATCH MASTER_D_LATCH(.D(D), .ENABLE(INVERTED_CLOCK), .Q(Q_INTERMEDIATE), .Q_neg());
    D_LATCH SLAVE_D_LATCH(.D(Q_INTERMEDIATE), .ENABLE(CLOCK), .Q(Q), .Q_neg(Q_neg));
    
endmodule

module JK_FLIPFLOP(J, K, CLOCK, Q_neg, Q);
    input wire J, K, CLOCK;
    output wire Q, Q_neg;
    wire J_AND_Q_NEG, K_AND_Q, NOT_J_AND_Q_NEG, NOT_K_AND_Q; 
    
    NAND_GATE NOT_J_AND_Q_NEG_GATE(.A(J), .B(Q_neg), .O(NOT_J_AND_Q_NEG));
    NAND_GATE J_AND_Q_NEG_GATE(.A(NOT_J_AND_Q_NEG), .B(NOT_J_AND_Q_NEG), .O(J_AND_Q_NEG));
    NAND_GATE NOT_K_AND_Q_GATE(.A(K), .B(Q), .O(NOT_K_AND_Q));
    NAND_GATE K_AND_Q_GATE(.A(NOT_K_AND_Q), .B(NOT_K_AND_Q), .O(K_AND_Q));
    
    SR_FLIPFLOP SR(.S(J_AND_Q_NEG),.R(K_AND_Q),.CLOCK(CLOCK),.Q(Q),.Q_neg(Q_neg));
    
    initial begin
        force Q = 0;
        force Q_neg = 1;
        force J_AND_Q_NEG = 0;
        force K_AND_Q = 0;
        #100;
        release Q; 
        release Q_neg;
        release J_AND_Q_NEG;
        release K_AND_Q;
    end
            
endmodule

module ASYNCHRONOUS_UP_COUNTER(Q);

    reg clock;
    initial begin
        clock = 0;
    end
    always begin
        clock = ~clock; #50;
    end 
    
    output wire [3:0] Q;
    wire LOGIC_1, Q0, Q1, Q2, Q3;
    
    assign LOGIC_1 = 1;
    assign Q[0] = Q0;
    assign Q[1] = Q1;
    assign Q[2] = Q2;
    assign Q[3] = Q3;
    
    JK_FLIPFLOP FIRST_JK(.J(LOGIC_1), .K(LOGIC_1), .CLOCK(CLOCK), .Q(Q0), .Q_neg());
    JK_FLIPFLOP SECOND_JK(.J(LOGIC_1), .K(LOGIC_1), .CLOCK(Q0), .Q(Q1), .Q_neg());
    JK_FLIPFLOP THIRD_JK(.J(LOGIC_1), .K(LOGIC_1), .CLOCK(Q1), .Q(Q2), .Q_neg());
    JK_FLIPFLOP FOURTH_JK(.J(LOGIC_1), .K(LOGIC_1), .CLOCK(Q2), .Q(Q3), .Q_neg());   

endmodule

module SYNCHRONOUS_UP_COUNTER(CLOCK, COUNT_ENABLE, Q);
    input wire CLOCK, COUNT_ENABLE;
    output wire [3:0] Q;
    wire Q0, Q1, Q2, Q3, NEXT_STAGE_1, NEXT_STAGE_2, NEXT_STAGE_3;
    
    assign NEXT_STAGE_1 = Q0 & COUNT_ENABLE;
    assign NEXT_STAGE_2 = Q1 & NEXT_STAGE_1;
    assign NEXT_STAGE_3 = Q2 & NEXT_STAGE_2;
        
    JK_FLIPFLOP FIRST_JK(.J(COUNT_ENABLE), .K(COUNT_ENABLE), .CLOCK(CLOCK), .Q(Q0), .Q_neg());
    JK_FLIPFLOP SECOND_JK(.J(NEXT_STAGE_1), .K(NEXT_STAGE_1), .CLOCK(CLOCK), .Q(Q1), .Q_neg());
    JK_FLIPFLOP THIRD_JK(.J(NEXT_STAGE_2), .K(NEXT_STAGE_2), .CLOCK(CLOCK), .Q(Q2), .Q_neg());
    JK_FLIPFLOP FOURTH_JK(.J(NEXT_STAGE_3), .K(NEXT_STAGE_3), .CLOCK(CLOCK), .Q(Q3), .Q_neg());
    
    assign Q[0] = Q0;
    assign Q[1] = Q1;
    assign Q[2] = Q2;
    assign Q[3] = Q3;

endmodule

module PULSE_GENERATOR(clock, out); 
    input wire [0:0] clock;
    output reg [0:0] out;
    reg [7:0] load_input;
    reg [0:0] load_flag;  
    reg [7:0] load;
    reg [0:0] least_significant_bit;
    integer i;
    
    // implement circular shift to the right
    
    always @ (posedge clock)
        begin
        if (load_flag)
            begin
                load = load_input;
            end
        else
            begin
                least_significant_bit = load[0];
                for (i = 0;  i < 7; i = i+1)
                    begin 
                    load[i] = load[i + 1];
                    end
            end
        out = load[0];
        end

endmodule

// ÖZBERK HAZANTEKÝN 150200100
// LORA NOÇKA 150200912
