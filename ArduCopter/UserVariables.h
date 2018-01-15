#include "pid.h"
// user defined variables

// example variables used in Wii camera testing - replace with your own
// variables
#ifdef USERHOOK_VARIABLES
#define BUFFER_FRAME_SIZE   15

uint16_t ips_bytes;
uint16_t ips_data[4];
uint16_t c_buff;
uint16_t c_state;
char ips_char[BUFFER_FRAME_SIZE];
uint32_t ips_delay_ms; 
float air_temperature;
Vector3f ips_gyro, ips_accel;
Vector2f opt_flowRate;
Vector2f opt_bodyRate;
uint32_t opt_integration_timespan;
uint16_t th_roll;
uint16_t th_pitch;
PID::PID_PARAMETERS pid_pos_x_param = {.Kp = 0.11, .Ki = 0.0, .Kd = 0.14,
		.Ts = 0.0025, .PID_Saturation = 250, .e=0,  .e_=0, .e__=0, .u =0,  .u_=0};
PID::PID_PARAMETERS pid_pos_y_param = {.Kp = 0.11, .Ki = 0.0, .Kd = 0.14,
		.Ts = 0.0025, .PID_Saturation = 250, .e=0,  .e_=0, .e__=0, .u =0,  .u_=0};

PID pid_posx;
PID pid_posy;
uint16_t s16_US_HEIGHT;

// PID 2
float d2_target, pos_kp, h_accel_cms, h_speed_cms, linear_d, d_target, vel_target_x, vel_target_y;
float h_dt, accel_feedforward_x, accel_feedforward_y, h_vel_last_x, h_vel_last_y, h_vel_error_x, h_vel_error_y, h_vel_error_x_, h_vel_error_y_, accel_target_x, accel_target_y;
float lean_ang_max, accel_max, h_accel_total, accel_target_x_, accel_target_y_, h_accel_forward, h_accel_right, h_pitch_target, cos_pitch_target, h_roll_target;
float pid_roll, pid_pitch, pid_mode;
// #if WII_CAMERA == 1
// WiiCamera           ircam;
// int                 WiiRange=0;
// int                 WiiRotation=0;
// int                 WiiDisplacementX=0;
// int                 WiiDisplacementY=0;
// #endif  // WII_CAMERA

#endif  // USERHOOK_VARIABLES


