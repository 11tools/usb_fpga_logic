module	reset_delay(iCLK,oRESET);	
input		iCLK;
output   	oRESET;
reg	[19:0]	Cont=0;
reg oRESET;

always@(posedge iCLK)
begin
	if(Cont!=20'hFFFFF)
	begin
		Cont	<=	Cont+1;
		oRESET	<=	1'b0;
	end
	else
	oRESET	<=	1'b1;
end

endmodule
