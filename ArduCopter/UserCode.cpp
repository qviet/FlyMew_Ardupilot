#include "Copter.h"

#ifdef USERHOOK_INIT
void Copter::userhook_init()
{
    // put your initialisation code here
    // this will be called once at start-up
    c_buff = 0;     //0: temp-buf
    c_state = 0;    //0: wait-start-buff, 1: data-buffer, 2: end-buffer-->0
    ips_bytes = 0;
    s16_US_HEIGHT = 156;
    optflow.init();
    pid_posx.init(pid_pos_x_param);
    pid_posy.init(pid_pos_y_param);
    
}
#endif

#ifdef USERHOOK_FASTLOOP
void Copter::userhook_FastLoop()
{
    
    // if(g.scale_roll == 4.0f)
    // {
    //     //copter.gcs_send_text_fmt(MAV_SEVERITY_INFO,"scale_roll: %.2f",g.scale_roll);
    //     cliSerial->printf("scale_roll: %.2f",(float)g.scale_roll);
    // }
    // put your 100Hz code here
    // uartF: serial5, baud 115200
//================================IPS_POSITION====================================//
    // Get available bytes
    ips_bytes = hal.uartF->available();
    while (ips_bytes-- > 0) {
        // Get data string here
        ips_char[0] = hal.uartF->read();
        if(ips_char[0] == 's'){
            c_buff = 1;
            c_state = 1;
        }
        else if(ips_char[0] == 'e'){
            // end-of-frame: get ips_pos & time_stamp
            if((ips_char[4] ==',')&& (c_buff == 8)){
                // valid frame
                ips_data[0] = (ips_char[1]-0x30)*100 + (ips_char[2]-0x30)*10 + (ips_char[3]-0x30); //pos_x
                ips_data[1] = (ips_char[5]-0x30)*100 + (ips_char[6]-0x30)*10 + (ips_char[7]-0x30); //pos_y
                th_roll = ips_data[0];
                th_pitch = ips_data[1];
                copter.gcs_send_text_fmt(MAV_SEVERITY_INFO,"%d,%d",ips_data[0], ips_data[1]);
                //hal.uartF->printf("%d,%d,%d,%d",ips_data[0],ips_data[1],ips_data[2],ips_data[3]);
                
            }
            //hal.uartF->printf("\r\n");
            c_buff = 0;
            c_state = 0;
        }
        else{
            if(c_state == 1){
                ips_char[c_buff] = ips_char[0];
                // hal.uartF->printf("%c",ips_char[c_buff]);
                c_buff++;
            }
        }

        s16_US_HEIGHT = ips_data[2];
    }
//==============================PX4FLOW======================================//
    optflow.update();
    // Vector2f opt_flowRate = optflow.flowRate();
    // Vector2f opt_bodyRate = optflow.bodyRate();
    // uint32_t opt_integration_timespan = optflow.integration_timespan();
    // float bodyRateZ = optflow.bodyRateZ();
    
    // hal.uartF->printf("%f,%f,%f,%f,%d\r\n",opt_flowRate.x,opt_flowRate.y,opt_bodyRate.x,opt_bodyRate.y,opt_integration_timespan);

//==============================INS======================================//
    
    ips_gyro = ins.get_gyro();
    ips_accel = ins.get_accel();
    // hal.uartF->printf("INS:%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\r\n",ips_gyro.x,ips_gyro.y,ips_gyro.z,ips_accel.x,ips_accel.y,ips_accel.z);

}
#endif

#ifdef USERHOOK_50HZLOOP
void Copter::userhook_50Hz()
{
    // put your 50Hz code here
}
#endif

#ifdef USERHOOK_MEDIUMLOOP
void Copter::userhook_MediumLoop()
{
    // put your 20Hz code here
//==============================TEMPERATURE======================================//
    air_temperature = barometer.get_temperature();
    // hal.uartF->printf("temp:%f",air_temperature);

//==============================IPS_TRANSMIT======================================//
    hal.uartE->printf("{PARAM,TRIGGER_US}\n");
    ips_delay_ms = AP_HAL::millis();    // trigger IPS_transmission on Tiva C
}
#endif

#ifdef USERHOOK_SLOWLOOP
void Copter::userhook_SlowLoop()
{
    // put your 3.3Hz code here
}
#endif

#ifdef USERHOOK_SUPERSLOWLOOP
void Copter::userhook_SuperSlowLoop()
{
    // put your 1Hz code here
}
#endif
