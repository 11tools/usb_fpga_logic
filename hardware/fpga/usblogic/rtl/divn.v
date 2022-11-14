`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:08:33 12/14/2017 
// Design Name: 
// Module Name:    divn 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module divn    (
input clk,
input rst_n,
output o_clk
);

parameter WIDTH = 32;
parameter N     = 2;

reg [WIDTH-1:0] cnt_p;// �����ؼ�����λ
reg [WIDTH-1:0] cnt_n;// �½��ؼ�����λ
reg             clk_p;// ������ʱ��
reg             clk_n;// �½���ʱ��

assign o_clk = (N == 1) ? clk :
               (N[0])   ? (clk_p | clk_n) : (clk_p);//����N==1���жϲ���Ƶ��N[0]���ж�����������ż������Ϊ1����������Ƶ������ż������ż����Ƶ��
        
always@(posedge clk or negedge rst_n) begin
if (!rst_n)
    cnt_p <= 0;
else if (cnt_p == (N-1))
    cnt_p <= 0;
else
    cnt_p <= cnt_p + 1;
end

always@(posedge clk or negedge rst_n) begin
if (!rst_n) 
    clk_p <= 1;//�˴�����Ϊ0Ҳ�ǿ��Եģ����û��Ӳ�Ե�Ҫ�󣬲�����ȡ0����ȡ1���������ȷ�ġ�
else if (cnt_p < (N>>1))/*N���������ƶ�һλ�����λ���㣬��ʵ����N/2�������ڼ���������ʱ���к����Ե���Խ��*/
    clk_p <= 1;
else
    clk_p <= 0;    
end

always@(negedge clk or negedge rst_n) begin
if (!rst_n)
    cnt_n <= 0;
else if (cnt_n == (N-1))
    cnt_n <= 0;
else
    cnt_n <= cnt_n + 1;
end

always@(negedge clk or negedge rst_n) begin
if (!rst_n)
    clk_n <= 1;
else if (cnt_n < (N>>1))
    clk_n <= 1;
else
    clk_n <= 0;
end

endmodule
