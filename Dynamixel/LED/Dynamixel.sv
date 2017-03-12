
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
		logic [31:0]  spi_data, DataAdrR, DataAdrW; //DataAdrR: from PI to DE0, DataAdrW: from DE0 to PI

	spi_slave spi_slave_instance(
		.SPI_CLK    (spi_clk),
		.SPI_CS     (spi_cs),
		.SPI_MOSI   (spi_mosi),
		.SPI_MISO   (spi_miso),
		.Data_WE    (cs_spi), 	// to be changed with WE chosen => MemWriteM & cs_spi
		.Data_Addr_read  (DataAdrR),
		.Data_Addr_write (DataAdrW),
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
	logic [31:0] PC, Instr, DataAdr, WriteData, ReadData, ReadData_dmem, DataToPI;
	logic  cs_dmem, cs_led, cs_spi_wr, cs_spi_rd;
	logic [7:0] led_reg;
	logic key1,key0;
	
		
	// Declaration of all signals

	//Dynamixel
	logic Debug;
	logic [31:0] Read_data;
	logic [31:0] Write_data;
	logic Write_en, Read_en; 
	logic [2:0] Rw_ad;
	logic uart_tx,uart_rx,uart_dir, TXD_Done;
	
	logic Reset;
	logic [31:0] my_counter;
	
	initial my_counter = 32'b0;
	
	
	
	//logic a,b;

	assign clk = CLOCK_50;
	//assign reset = GPIO_0_PI[1];
	
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
	assign GPIO_1[22] = ~uart_dir ;
	

	UART_Dynamixel Dyna (
		.clk(CLOCK_50),
		.reset(Reset),
		.write_en(Write_en),
		.read_en(Read_en),
		.rw_ad(Rw_ad),
		.write_data(Write_data),
		.read_data(Read_data),
		.RXD(uart_rx),
		.TXD(uart_tx),
		.UART_DIR(uart_dir),
		.debug(Debug),
		.TXD_done(TXD_Done)
);



//=======================================================
//  READ DATA
//=======================================================

	typedef enum logic [3:0] {S0,S1,S2, S3, S4,S5,S6,S6_Write, S7} statetype; //,S5,  S6, S7} statetype;
	statetype state, nextstate;
/*
// State Register & Bit counter & SPI Register & MISO
	always_ff @(posedge clk) begin
	
		if (~KEY[0])			state <= S0;
		else 							state <= nextstate;
		
	end
	*/
	
//RESET + states
	always_ff @(posedge clk) begin
	
		if(my_counter==32'd2000000 || my_counter==32'd0)
		begin
			Reset <= 1'b1;
			my_counter <= 32'd1;
			state <= S0;
		end
		else 
		begin
			my_counter <= my_counter + 1;
			Reset <= 32'd0;
			state <= nextstate;
		end
	end
	
// Next State Logic

	always_comb begin
	
		// Default value
		nextstate = state;
		Rw_ad = 3'b000; 
		Write_data = 32'h00000000;
		WriteData = 32'h0;
		DataAdrR = 32'h0;
		DataAdrW = 32'h0;

		
		case (state)
			S0	:  begin			
						Rw_ad = 3'b101;
						Write_en = 1'b1;
						Read_en = 1'b0;
						DataAdrR = 32'd0;
						Write_data = spi_data;
						//Write_data = 32'hcf0204fe;//hardcode test read_data
						nextstate = S1;
						end
			S1 : begin			
						Rw_ad = 3'b110;
						Write_en = 1'b1;
						Read_en = 1'b0;
						DataAdrR = 32'd4;
						Write_data = spi_data;
						//Write_data = 32'h0000012b;//hardcode test read_data
						nextstate = S2;
					end					
			S2 : begin 			
						Rw_ad = 3'b100;
						Write_en = 1'b1;
						Read_en = 1'b0;
						Write_data = 32'd1;
						nextstate = S3;
					end
			S3: begin
						Rw_ad = 3'b100;
						Write_en = 1'b0;
						Read_en = 1'b1;
						if(Read_data[0]) nextstate = S4; // quand TXD_done => 1
						else nextstate = S3;
					end	
			S4: begin
						Rw_ad = 3'b000;// mettre read_data à 0 ==> sinon il reste a 1 a cause du TXD_Done de l etape precedente 
						Write_en = 1'b0;
						Read_en = 1'b1;
						nextstate = S5;
					end
			S5 : begin
						Rw_ad = 3'b000;
						Read_en = 1'b1;
						Write_en = 1'b0;
						if (Read_data[0]) //quand RXD_Done =>1
							begin
								nextstate = S6;
							end
						else 
							begin
								nextstate = S5;
							end
					end			
				S6 : 	begin
						Rw_ad = 3'b001; //data1
						Read_en = 1'b1;
						Write_en = 1'b0;
						DataAdrW = 32'd8;
						WriteData = Read_data;
						if(my_counter==32'd1500000)
							nextstate = S6_Write; // wait 1 clock50 for writing spi register
						else
							nextstate = S6;
					end
		S6_Write : 	begin
						Rw_ad = 3'b001; //data1
						Read_en = 1'b1;
						Write_en = 1'b0;
						DataAdrW = 32'd8;
						WriteData = Read_data;
						nextstate = S7;
					end
				S7 : 	begin
						Rw_ad = 3'b010;//data2
						Read_en = 1'b1;
						Write_en = 1'b0;
						DataAdrW = 32'd12;
						WriteData = Read_data;
						nextstate = S7;
						end
		endcase
	end

//assign WriteData = Read_data;



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
		begin
		cs_spi = 1;
		DataToPI<= WriteData;
		//DataAdrW = 32'h0000_0000;
		end
	end



	/*
//=======================================================
//  ALLUMAGE LED 
//=======================================================

	typedef enum logic [1:0] {S0,S1,S2, S3} statetype;
	statetype state, nextstate;
	
// State Register & Bit counter & SPI Register & MISO
	always_ff @(posedge clk) begin
	
		if (~KEY[0])			state <= S0;
		else 							state <= nextstate;
		
	end
	
// Next State Logic

	always_comb begin
	
		// Default value
		nextstate = state;
		Rw_ad = 3'b000; 
		Write_data = 32'h00000000;
		DataAdrW = 32'd0;
		
		case (state)
			S0	:  begin			
						Rw_ad = 3'b101;
						DataAdrR = 32'h0000_0000;
						Write_data = spi_data;
						//Write_data = 32'he003_04fe;
						nextstate = S1;
					end
			S1 : begin			
					Rw_ad = 3'b110;
					DataAdrR = 32'h0000_0004;
					Write_data = spi_data;
					//Write_data = 32'h0000_0119;
					nextstate = S2;
					end					
			S2 : begin 			
						Rw_ad = 3'b100;
						Write_data = 32'd1;
						nextstate = S3;
					end
			S3: begin
						Rw_ad = 3'b100;
						Write_data = 32'd0;
						nextstate = S0;
					end
			
			
		endcase
	end

*/

endmodule
