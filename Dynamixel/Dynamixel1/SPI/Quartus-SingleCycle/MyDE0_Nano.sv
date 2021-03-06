
//=======================================================
//  DYNAMIXEL
//=======================================================

module Dynamixel(


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

	logic clk, reset, MemWrite, thread;
	logic [31:0] PC, Instr, DataAdr, WriteData, ReadData, ReadData_dmem, WriteData2, WriteData3, DataToPI;
	logic  cs_dmem, cs_led, cs_spi_wr, cs_spi_rd;
	logic [7:0] led_reg;
	logic key1,key0;
	
		
	// Declaration of all signals

	//Dynamixel
	logic Debug;
	logic [31:0] Data_useful;
	logic [31:0] Write_data;
	logic Write_en, Read_en; 
	logic [2:0] Rw_ad;
	logic uart_tx,uart_rx,uart_dir;
	
	//assign
	assign Write_en = 1'b1;
	assign Read_en = 1'b0;
	
	
	
	//logic a,b;

	assign clk = CLOCK_50;
	assign reset = GPIO_0_PI[1];
	
	// keys
	assign key0=~KEY[0];
	assign key1=~KEY[1];
	
	// switches
	assign sw0= ~SW[0]; 
  	assign sw1= ~SW[1]; 
	assign sw2= ~SW[2]; 
	assign sw3= ~SW[3]; 
	
	/*// Corresponding between signals and GPIO's
	assign mot_left_cod_a =GPIO_1[0];
	assign mot_left_cod_b = GPIO_1_IN[0];
	assign mot_right_cod_a =GPIO_1[2];
	assign mot_right_cod_b = GPIO_1[1];
	assign laser_cod_a =GPIO_1[4] ;
	assign laser_cod_b = GPIO_1[5];
	assign laser_sync = GPIO_1[7];
	assign laser_signal =  GPIO_1[8];
*/
	assign GPIO_1[26] = uart_tx;
	assign uart_rx =  GPIO_1[24];
	assign GPIO_1[22] = uart_dir ;

	UART_Dynamixel Darras (
		.clk(CLOCK_50),
		.reset(key0),
		.write_en(Write_en),
		.read_en(Read_en),
		.rw_ad(Rw_ad),
		.write_data(Write_data),
		.data_useful(Data_useful),
		.RXD(uart_rx),
		.TXD(uart_tx),
		.UART_DIR(uart_dir),
		.debug(Debug)
);

//assign WriteData = 32'd3;



	// LED logic	
	assign LED = led_reg;	
	always_ff @(posedge clk)
		begin 
    	 led_reg[0] <= spi_data[0];
		 led_reg[1] <= spi_data[1];
		 led_reg[2] <= spi_data[2];
		 led_reg[3] <= spi_data[3];
		 led_reg[4] <= spi_data[4];
		 led_reg[5] <= spi_data[5];
		 led_reg[6] <= spi_data[6];
		 led_reg[7] <= spi_data[7];
		 end



	// SPI output Register
	 always_ff @(posedge clk)
	begin 
		if (sw0)
		begin
		cs_spi = 1;
		DataToPI<= WriteData;
		DataAdrM = 32'h0000_0000;
		end
		else
		begin
		cs_spi = 0;
		DataToPI<= 32'b0;
		DataAdrM = 32'bx;
		end
	end
	
	
	/*

	//Allumage led 
	typedef enum logic [1:0] {first, second, third} statetype;
	statetype state, nextstate;
	
	
	logic [63:0] All_data;
	
	
	always_ff @(posedge clk, posedge key0) begin
		if(key0) state <= first;
		else state <= nextstate;
	end
	
	always_comb begin
	//nextstate = state;
	//All_data = 64'hf603_04fe_0000_0119;
		case(state)
			first: if(key1) nextstate = second;
			second: nextstate = third;
			third: nextstate = first;
		endcase
	end
	
	always_ff @(posedge clk, posedge key0) begin
		if (state==first) Rw_ad <= 3'b100;
		else if (state==second) begin
			Rw_ad <= 3'b101;
			Write_data <= 32'hf603_04fe;
		end
		else if (state==third) begin
			Rw_ad <= 3'b110;
			Write_data <= 32'h0000_0119;
		end
	end
			
		
	*/

//logic [31:0] data;
//logic [2:0] ad;
	typedef enum logic [1:0] {S0,S1,S2} statetype;
	statetype state, nextstate;
	
// State Register & Bit counter & SPI Register & MISO
	always_ff @(posedge clk) begin
	
		if (key0)			state <= S0;
		else 							state <= nextstate;
		
	end
	
// Next State Logic

	always_comb begin
	
		// Default value
		nextstate = state;
		Rw_ad = 3'b000; 
		Write_data = 32'h00000000;
		WriteData = 32'hffffffff;
		
		case (state)
			S0 : if (key1) begin 			
						Rw_ad = 3'b100;
						Write_data = 32'd1;
						WriteData = 32'h0000_000f;
						nextstate = S1;
					end
					else begin
						WriteData = 32'h0000_0000;
						nextstate = S0;
					end
					
			S1	:  begin			
						Rw_ad = 3'b101;
						Write_data = 32'hf603_04fe;
						WriteData = 32'h0000_0001;
						if(sw3) nextstate = S2;
						else nextstate = S1;
					end
					
			S2 : begin			
					Rw_ad = 3'b110;
					Write_data = 32'h0000_0119;
					WriteData = 32'h0000_0002;
					nextstate = S2;
					end
					
		endcase
	end
	
	//assign Rw_ad = ad;
	//assign Write_data = data;

endmodule
s