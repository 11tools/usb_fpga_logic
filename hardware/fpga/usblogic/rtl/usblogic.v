module usblogic(sys_clk,
                  led_a, 
						led_b,
						led_c,
						led_d,
						din,
						usb_fifoaddr,         		 //CY68013 FIFO Address
						usb_slcs,                   //CY68013 Chipset select
						usb_sloe,                   //CY68013 Data output enable
						usb_slrd,                   //CY68013 READ indication
						usb_slwr,                   //CY68013 Write indication
						usb_fd,                     //CY68013 Data
						usb_flaga,                  //CY68013 EP2 FIFO empty indication; 1:not empty; 0: empty
						usb_flagb,                  //CY68013 EP4 FIFO empty indication; 1:not empty; 0: empty
						usb_flagc,                  //CY68013 EP6 FIFO full indication; 1:not full; 0: full
						usb_ifclk,
						pa0);


input [15:0] din;
input sys_clk;
output led_a, led_b, led_c, led_d;
output [1:0]usb_fifoaddr;         		 //CY68013 FIFO Address
output usb_slcs;                   //CY68013 Chipset select
output usb_sloe;                   //CY68013 Data output enable
output usb_slrd;                   //CY68013 READ indication
output usb_slwr;                   //CY68013 Write indication
inout [15:0]usb_fd;                     //CY68013 Data
input usb_flaga;                  //CY68013 EP2 FIFO empty indication; 1:not empty; 0: empty
input usb_flagb;                  //CY68013 EP4 FIFO empty indication; 1:not empty; 0: empty
input usb_flagc;                  //CY68013 EP6 FIFO full indication; 1:not full; 0: full
output usb_ifclk;
output pa0;

assign led_a = 1'b1;
assign led_d = 1'b0;
assign led_c = 1'b1;
assign pa0 = 1'b0;


wire rst;

wire clk_100m;
wire clk_200m;
wire clk_300m;

reg [15:0] datas;


usb_sinterface usb_sinterface_inst(
	.clk(clk_100m),
   .rst(rst),
	.u_ifclk(usb_ifclk),
	.u_data_out(usb_fd[15:0]),			//-->fifo_db[15:0];
	.data_in(datas),
	.u_slwr(usb_slwr),				//-->u_slwr#;
	.u_slrd(usb_slrd),				//-->u_slrd#;
	.u_sloe(usb_sloe), 			   //-->u_sloe#;
	.u_slcs(usb_slcs),
	.u_addr0(usb_fifoaddr[0]),
	.u_addr1(usb_fifoaddr[1]),
	.u_flaga(usb_flaga),
	.u_flagb(usb_flagb),
	.u_flagc(usb_flagc),
	.led(led_b)
);




pll pll_inst(
  .CLK_IN1(sys_clk),
  .CLK_OUT1(clk_100m),
  .CLK_OUT2(clk_200m),
  .CLK_OUT3(clk_300m),
  .RESET(1'b0)
);



always @(negedge clk_100m) begin
	if(usb_flagb)
		datas <= din;
end



reset_delay reset_delay_inst(
	.iCLK(clk_100m),
	.oRESET(rst)
);


			

endmodule