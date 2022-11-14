module usb_sinterface(
	clk,
   rst, 	
	u_ifclk,
	u_data_out,			//-->fifo_db[15:0];
	data_in,
	u_slwr,				//-->u_slwr#;
	u_slrd,				//-->u_slrd#;
	u_sloe, 			   //-->u_sloe#;
	u_slcs,
	u_addr0,
	u_addr1,
	u_flaga,
	u_flagb,
	u_flagc,
	led );
				
//input :
input	clk, rst;				
input	u_flaga, u_flagb, u_flagc;
	
//USB interface :
output	u_ifclk,
		   u_slwr,
		   u_slrd,
		   u_sloe,
		   u_slcs,
		   u_addr0,
		   u_addr1;
		
output 	[15:0]	u_data_out;

reg      u_slwr,
		   u_slrd,
		   u_sloe; 			
			
reg		[15:0]	u_data_out;
wire 	   u_ifclk;
output    led;
reg       led;

input    [15:0] data_in;


//internal registers :
reg	   [1:0]	STATE;

parameter  	IDLE='H0,
			   WRITE_READY='H1,
			   WRITE='H2;

always @(negedge clk)
begin
if(!rst)
	begin
	u_data_out<='hffff;
	u_slwr<='b1;
	u_slrd<='b1;
	u_sloe<='b1;
	led <= 1;
	STATE<=IDLE;
	end
else
	begin
	case(STATE)
	IDLE:
		begin
		STATE<=WRITE;
		led <= 1;
		end
	WRITE:
		begin
		if(u_flagb)
			begin
			u_slwr<='b0;
			u_data_out <= data_in;
			STATE<=WRITE;
			led <= 0;
			end
		else
			begin
			u_slwr<='b1;
			STATE<=IDLE;
			end
		end
	default:
		STATE<=IDLE;
	endcase
	end
end
assign u_slcs = 'b0;
assign u_addr0 = 'b0;
assign u_addr1 = 'b1;


ODDR2 #(
      .DDR_ALIGNMENT("NONE"),     // Sets output alignment to "NONE", "C0" or "C1"
      .INIT(1'b0),                // Sets initial state of the Q output to 1'b0 or 1'b1
      .SRTYPE("SYNC")             // Specifies "SYNC" or "ASYNC" set/reset
       ) ODDR2_inst1 (
      .Q(u_ifclk),                // 1-bit DDR output data
      .C0(!clk),                  // 1-bit clock input
		.C1(clk),                   // 1-bit clock input
      .CE(1'b1),                  // 1-bit clock enable input
      .D0(1'b1),                  // 1-bit data input (associated with C0)
      .D1(1'b0),                  // 1-bit data input (associated with C1)
      .R(1'b0),                   // 1-bit reset input
      .S(1'b0)                    // 1-bit set input
    );	

//assign u_ifclk = ~clk;	//pixclk


endmodule