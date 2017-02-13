module antiGlitch(
	input logic clk,
	input logic reset,
	input logic in,
	output logic out
	);
	
logic [3:0] glitch;

always_ff @ (posedge clk)
if(reset) 
begin 
	glitch <= 4'b0;
	out <= 1'b0;
end
else
begin
glitch <= {glitch[2:0],in};
case(glitch)
4'b0: out <= 1'b0;
4'b1111: out <= 1'b1;
default: out <= out;
endcase
end
endmodule