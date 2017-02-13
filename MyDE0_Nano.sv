//=======================================================
//  MyARM
//=======================================================

module MyDE0_Nano(


//////////// CLOCK //////////
input logic 		          		CLOCK_50,

//////////// LED //////////
output logic		     [7:0]		LED,

//////////// KEY //////////
input logic 		     [1:0]		KEY,

//////////// SW //////////
input logic 		     [3:0]		SW,

//////////// SDRAM //////////
output logic		    [12:0]		DRAM_ADDR,
output logic		     [1:0]		DRAM_BA,
output logic		          		DRAM_CAS_N,
output logic		          		DRAM_CKE,
output logic		          		DRAM_CLK,
output logic		          		DRAM_CS_N,
inout logic 		    [15:0]		DRAM_DQ,
output logic		     [1:0]		DRAM_DQM,
output logic		          		DRAM_RAS_N,
output logic		          		DRAM_WE_N,

//////////// EPCS //////////
output logic		          		EPCS_ASDO,
input logic 		          		EPCS_DATA0,
output logic		          		EPCS_DCLK,
output logic		          		EPCS_NCSO,

//////////// Accelerometer and EEPROM //////////
output logic		          		G_SENSOR_CS_N,
input logic 		          		G_SENSOR_INT,
output logic		          		I2C_SCLK,
inout logic 		          		I2C_SDAT,

//////////// ADC //////////
output logic		          		ADC_CS_N,
output logic		          		ADC_SADDR,
output logic		          		ADC_SCLK,
input logic 		          		ADC_SDAT,

//////////// 2x13 GPIO Header //////////
inout logic 		    [12:0]		GPIO_2,
input logic 		     [2:0]		GPIO_2_IN,

//////////// GPIO_0, GPIO_0 connect to GPIO Default //////////
inout logic 		    [33:0]		GPIO_0_PI,
input logic 		     [1:0]		GPIO_0_PI_IN,

//////////// GPIO_1, GPIO_1 connect to GPIO Default //////////
inout logic 		    [33:0]		GPIO_1,
input logic 		     [1:0]		GPIO_1_IN
);

//=======================================================
//  SPI
//=======================================================
		logic 			spi_clk, spi_cs, spi_mosi, spi_miso, cs_spi;
		logic [31:0]  spi_data, DataAdrM;

	spi_slave spi_slave_instance(
		.SPI_CLK    (spi_clk),
		.SPI_CS     (spi_cs),
		.SPI_MOSI   (spi_mosi),
		.SPI_MISO   (spi_miso),
		.Data_WE    (cs_spi), 	// to be changed with WE chosen => MemWriteM & cs_spi
		.Data_Addr  (DataAdrM),            
		.Data_Write (DataToPI),
		.Data_Read  (spi_data),
		.Clk        (clk)
	);
	
	assign spi_clk  		= GPIO_0_PI[11];	// SCLK = pin 16 = GPIO_11
	assign spi_cs   		= GPIO_0_PI[9];	// CE0  = pin 14 = GPIO_9
	assign spi_mosi     	= GPIO_0_PI[15];	// MOSI = pin 20 = GPIO_15
	
	assign GPIO_0_PI[13] = spi_cs ? 1'bz : spi_miso;  // MISO = pin 18 = GPIO_13 


//=======================================================
//  MyARM
//=======================================================

	logic clk, reset, MemWrite;
	logic [2:0] thread;
	logic [31:0] PC, Instr, DataAdr, WriteData, ReadData, ReadData_dmem, WriteData2, WriteData3, WriteData4,WriteData5,DataToPI;
	logic [31:0] posBeacon,negBeacon, WriteData6,WriteData7,WriteData8,WriteData9, nTikz, posBeaconPremier;
	logic  cs_dmem, cs_led, cs_spi_wr, cs_spi_rd;
	logic [7:0] led_reg;
	logic key1,key0;
	
	logic [31:0] count_mot_left, count_mot_left_b, count_mot_right, count_mot_right_b, premier, premier_posEdge;
		
	// Declaration of all signals
	logic mot_left_cod_a,mot_left_cod_b;
	logic mot_right_cod_a,mot_right_cod_b;
	logic laser_cod_a,laser_cod_b;
	logic laser_sync,laser_signal;
	logic uart_tx,uart_rx,uart_dir;
	logic current_a, previous_a, current_b, previous_b;
	logic CountS1Enable,CountS1Reset,PosedgeDetected, nTickzMotorEnable, PosReset;
	logic [31:0] new_count_mot_right, CountS1;
	
	// boolean
		logic we_phi;
		initial
			begin
			we_phi = 1'b0;
			end
			
	//logic a,b;
	logic [31:0] count_laser_a,count_laser_b;
	
	assign clk = CLOCK_50;
	assign reset = GPIO_0_PI[1];
	
	// keys
	assign key0=~KEY[0];
	assign key1=~KEY[1];
	
	// switches
	assign sw0= SW[0]; 
  	assign sw1= SW[1]; 
	assign sw2= SW[2]; 
	assign sw3= SW[3]; 
	
	// Corresponding between signals and GPIO's
	assign mot_left_cod_a =GPIO_1[0];
	assign mot_left_cod_b = GPIO_1_IN[0];
	assign mot_right_cod_a =GPIO_1[2];
	assign mot_right_cod_b = GPIO_1[1];
	/*assign laser_cod_a =GPIO_1[4] ;
	assign laser_cod_b = GPIO_1[5];
	assign laser_sync = GPIO_1[7];*/
	//assign laser_signal =  GPIO_1[8];
	assign uart_tx =  GPIO_1[26];
	assign uart_rx =  GPIO_1[24];
	assign uart_dir =GPIO_1[22];

	antiGlitch antiGlitchLaserSig (.clk(clk), .reset(key0), .in(GPIO_1[8]), .out(laser_signal));
	antiGlitch antiGlitchLaserSync (.clk(clk), .reset(key0), .in(GPIO_1[7]), .out(laser_sync));
	antiGlitch antiGlitchLaserMotorA (.clk(clk), .reset(key0), .in(GPIO_1[4]), .out(laser_cod_a));
	antiGlitch antiGlitchLaserMotorB (.clk(clk), .reset(key0), .in(GPIO_1[5]), .out(laser_cod_b));
	
	
	// MOTOR COUNTERS
	always_ff @(posedge mot_left_cod_a, posedge key0) begin
	if(key0) count_mot_left<= 32'b0;
	else begin if (mot_left_cod_b) 
	count_mot_left<= count_mot_left+32'b1;
			else count_mot_left<= count_mot_left-32'b1;
			end
	end


	always_ff @(posedge mot_right_cod_a, posedge key0) begin
	if(key0) count_mot_right<= 32'b0;
	else begin  if (mot_right_cod_b) count_mot_right<= count_mot_right+32'b1;
		else count_mot_right<= count_mot_right-32'b1;
		end
	end
	/*
	//--- SPI FSM -------------------------------------------------
	typedef enum logic [1:0] {S0,S1,S2} statetype;
	statetype state, nextstate;
	
	always_ff @(posedge mot_left_cod_a)
		begin
			if (mot_left_cod_a && ~PosReset ) PosedgeDetected <=1'b1;
		end
		
	always_ff @(posedge clk)
		begin 
		state <= nextstate;
		end

	always_ff @(posedge clk)
		begin 
		if(CountS1Enable)
		CountS1 <= CountS1+1;
		else if(CountS1Reset)
		CountS1 <= 32'b0;
		end
		
// Next State Logic

	always_comb begin
	
		// Default value
		CountS1Reset = 0; 
		CountS1Enable = 0;
		nTickzMotorEnable = 0;
		PosReset = 0;
		case (state)
			S0 : if (PosedgeDetected) 
						begin 			// Posedge of count_motor
						nextstate = S1;
						CountS1Reset=1;
						PosReset=1;
						end
					else nextstate = S0;
					
			S1	: if (mot_right_cod_a) // Count state
						begin			
						CountS1Enable= 1;
						nextstate = S1;
						end
					else 
						begin 
						CountS1Enable=0;
						nextstate=S2;
						end 
					
			S2 : if (CountS1>=50)
					begin
						nTickzMotorEnable=1;
						nextstate = S0;
					end
					else nextstate = S0;
					PosReset = 0;
					
		endcase
		
	end

	// NEW wheel encode
	
	always_ff @(posedge clk, posedge key0) begin
	if(key0) new_count_mot_right<= 32'b0;
	else begin  if (nTickzMotorEnable) new_count_mot_right<= new_count_mot_right+32'b1;
		//else count_mot_right<= count_mot_right-32'b1;
		end
	end
	
	*/
	
	// LASER MOTOR COUNTERS
	always_ff @(posedge laser_sync, posedge laser_cod_a) 
	begin
		if(laser_sync) count_laser_a<= 32'd0;
		else 
			begin  
				if (laser_cod_a) count_laser_a<= count_laser_a+32'b1;
			end
	end
	
	always_ff @(posedge laser_sync)
	begin
		nTikz <= count_laser_a;
	end
	
	always_ff @(posedge laser_signal)
	begin
		if(premier)
			posBeaconPremier <= count_laser_a;
		else
		posBeacon <= count_laser_a;
		
	end
	
	always_ff @(posedge laser_signal,posedge laser_sync)
	begin
		if(laser_sync) premier <= 0;
		else
			begin 
			premier<= premier+32'b1;
			end
	end
	
	always_ff @(negedge laser_signal)
	begin
		negBeacon <= count_laser_a;
	end
	
	
	always_ff @(posedge laser_sync, posedge laser_cod_b) 
	begin
		if(laser_sync)begin count_laser_b<= 32'b0; premier_posEdge <= premier; end 
		else 
			begin  
				if (laser_cod_b) count_laser_b<= count_laser_b+32'b1;
			end
	end
		
	
	assign WriteData= {24'b0,laser_sync,laser_signal,laser_cod_a,laser_cod_b,mot_right_cod_a,mot_right_cod_b,mot_left_cod_a,mot_left_cod_b};
	assign WriteData2=count_mot_left;
	assign WriteData3=count_mot_right;
	assign WriteData4=count_laser_a;
	assign WriteData5=count_laser_b;
	assign WriteData6 = posBeacon;
	assign WriteData7 = negBeacon;
	assign WriteData8 = nTikz; // alpha/2 -> angle entre extrémité et milieu beacon
	assign WriteData9 =  new_count_mot_right;
	// LED logic	 
	assign LED = led_reg;

always_ff @(posedge clk)
		begin 	
		led_reg<=laser_signal;
		end
	/*always_ff @(posedge clk)
		begin 
    	 led_reg[0] <= mot_left_cod_a;
		 led_reg[1] <= mot_left_cod_b;
		 led_reg[2] <= 1'b0;
		 led_reg[3] <= laser_signal;
		 led_reg[4] <= laser_sync;
		 led_reg[5] <= 1'b0;
		 led_reg[6] <= mot_right_cod_a;
		 led_reg[7] <= mot_right_cod_b;
		 end
*/


	// SPI output Register
	 always_ff @(posedge clk)
	begin 
		if (sw0)
		begin
		cs_spi = 1;
		DataToPI<= WriteData9;
		DataAdrM = 32'h0000_0000;
		end
		
		else if (sw1)
		begin
			case (thread)
			3'b000:
				begin 
					if (spi_data ==32'h0000_0005) 
						begin
						cs_spi = 1;
						DataToPI<= 0;
						DataAdrM = 32'h0000_0004;
						thread = 3'b001; 
						end
					
					else 
						begin 	
						cs_spi = 1;
						DataToPI<= WriteData2;
						DataAdrM = 32'h0000_0004;
						thread = 3'b001; 
						end 
					end
			3'b001: 
				begin
					if (spi_data ==32'h0000_0005) 
						begin
						cs_spi = 1;
						DataToPI<= 0;
						DataAdrM = 32'h0000_0008;
						thread = 3'b010; 
						end
					else 
						begin
						cs_spi = 1;
						DataToPI<= WriteData3;
						DataAdrM = 32'h0000_0008;
						thread = 3'b010; 
						end 
				end 	
				
			3'b010:
				begin 
						cs_spi = 1;
						DataAdrM = 32'h0000_000C;
						DataToPI<=WriteData4;
						thread=3'b011;
				end
		
			3'b011:
				begin 
						cs_spi = 1;
						DataAdrM = 32'h0000_0010;
						DataToPI<=WriteData5;
						thread=3'b100;
				end
			3'b100:
				begin
						cs_spi = laser_sync;
						DataAdrM = 32'h0000_0014;
						DataToPI<=WriteData6; //posBeacon
						thread=3'b101;
						
				end
			3'b101:
				begin
						cs_spi = laser_sync;
						DataAdrM = 32'h0000_0018;
						DataToPI<=WriteData7; //negBeacon
						thread=3'b110;
						
				end
			3'b110:
				begin
						cs_spi = 1;
						DataAdrM = 32'h0000_001C;
						DataToPI<=WriteData8; //nTikz
						thread=3'b000;
						
				end
			default:	begin
						cs_spi = 0;
						DataToPI<= 32'b0;
						DataAdrM = 32'bx;
						thread=3'b000;
					end
	endcase
end
end

endmodule