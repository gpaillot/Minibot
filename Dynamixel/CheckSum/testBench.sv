`timescale 1ns/1ps 	

module testbench();
logic [31:0]	data1, data2;
logic [7:0]	checksum;
check Robinet(data1, data2, checksum);

initial
	begin
/*
		data1 = 32'h0003_05fe;
		data2 = 32'h0000_001e;
		#5
		data2 = 32'h0003_ff1e;
		#5
		data1 = 32'h000305fe;
		data2 = 32'h0001ff0e;
		#5
		data1 = 32'h000305fe;
		data2 = 32'h00020020;
		#5
		//allumage led
		data1 = 32'h0003_0408;
		data2 = 32'h0000_0119;
		#5
		//changer ID
		data1 = 32'h000304fe;
		data2 = 32'h00000803;
		//lire id
		#5
		data1 = 32'h00020408;
		data2 = 32'h00000103;
*/


		//allumage led
		#5
		data1 = 32'h0003_05fe;
		data2 = 32'h0000_0006;
		#5
		//changer ID
		data1 = 32'h000305fe;
		data2 = 32'h00000008;
		//lire id
		#5
		data1 = 32'h00030504;
		data2 = 32'h0000ff20;
		#5
		data1 = 32'h00030506;
		data2 = 32'h0001ff20;
		#5
		data1 = 32'h00030508;
		data2 = 32'h0002ff20;
		#5
		data1 = 32'h000204fe;
		data2 = 32'h0000012b;

	end
endmodule