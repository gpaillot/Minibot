module check(
input logic [31:0] 	data1, data2,
output logic [7:0]	checksum
);
logic[7:0] id, length, instr, P0, P1, P2;
logic [31:0] inter;
always_comb
	begin
		id = data1[7:0];
		length = data1[15:8];
		instr = data1[23:16];
		P0 = data2[7:0];
		P1	= data2[15:8];
		P2	= data2[23:16];
	end
	assign inter = ~(id+length+instr+P0+P1+P2);
	
	assign checksum = inter[7:0];
	
	
	
endmodule