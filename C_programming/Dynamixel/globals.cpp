/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "globals.h"

double speed_counter = 500000.0;
double speed_counter_ref_clk =  50000000.0;
double speed_counter_res_inverse = speed_counter_ref_clk/speed_counter;
int enc_pulse_per_rotation_motor = 13800;
int enc_pulse_per_rotation_tower = 3540;