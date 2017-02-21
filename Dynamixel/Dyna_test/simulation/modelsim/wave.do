onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /MyTestBench/clk
add wave -noupdate /MyTestBench/reset
add wave -noupdate /MyTestBench/KEY
add wave -noupdate /MyTestBench/sw
add wave -noupdate /MyTestBench/LED
add wave -noupdate -height 25 /MyTestBench/clk
add wave -noupdate -height 25 /MyTestBench/reset
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/write_en
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/read_en
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/rw_ad
add wave -noupdate -height 25 -radix hexadecimal /MyTestBench/dut/Thierry/write_data
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/RXD
add wave -noupdate -height 25 -radix binary /MyTestBench/dut/Thierry/TXD
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/UART_DIR
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/debug
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/data_useful
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/baud_clk
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/TXD_done
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/RXD_enable
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/RXD_done
add wave -noupdate -height 25 -radix hexadecimal /MyTestBench/dut/Thierry/TXD_data_1
add wave -noupdate -height 25 -radix hexadecimal /MyTestBench/dut/Thierry/TXD_data_2
add wave -noupdate -height 25 -radix hexadecimal /MyTestBench/dut/Thierry/RXD_data_1
add wave -noupdate -height 25 -radix hexadecimal /MyTestBench/dut/Thierry/RXD_data_2
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/communication_fail
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/start_RX
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/TXD_enable_prev
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/TXD_enable
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/start_communication
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/read_data
add wave -noupdate -radix hexadecimal /MyTestBench/dut/Thierry/txd/frame
add wave -noupdate -radix hexadecimal /MyTestBench/dut/Thierry/txd/data1
add wave -noupdate -radix hexadecimal /MyTestBench/dut/Thierry/txd/data2
add wave -noupdate -radix hexadecimal /MyTestBench/dut/Thierry/txd/length
add wave -noupdate -radix hexadecimal /MyTestBench/dut/Thierry/txd/id
add wave -noupdate -radix hexadecimal /MyTestBench/dut/Thierry/txd/instr
add wave -noupdate -radix hexadecimal /MyTestBench/dut/Thierry/txd/checksum
add wave -noupdate -radix hexadecimal /MyTestBench/dut/Thierry/txd/P0
add wave -noupdate -radix hexadecimal /MyTestBench/dut/Thierry/txd/P1
add wave -noupdate -radix hexadecimal /MyTestBench/dut/Thierry/txd/P2
add wave -noupdate -radix unsigned /MyTestBench/dut/Thierry/txd/ubyte/cnt
add wave -noupdate -radix hexadecimal /MyTestBench/dut/Thierry/txd/ubyte/buffer
add wave -noupdate /MyTestBench/dut/Thierry/txd/ubyte/out
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 5} {783116938 ps} 0} {{Cursor 6} {1621149328 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 150
configure wave -valuecolwidth 89
configure wave -justifyvalue left
configure wave -signalnamewidth 1
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ps
update
WaveRestoreZoom {0 ps} {799190767 ps}
