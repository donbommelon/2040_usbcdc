/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "bsp/board.h"
#include "tusb.h"

//------------- prototypes -------------//
static void cdc_task(void);
uint16_t sendflag(void);

#define array_size 1024

uint16_t buffer[array_size];

uint16_t send1(uint16_t *ptr)
{
    uint8_t itf = 0;
    while (tud_cdc_n_write_available(itf) < 1) 
        {
        tud_task();
        tud_cdc_n_write_flush(itf);
    }

    tud_cdc_n_write(itf, ptr, 1);
    tud_cdc_n_write_flush(itf);
    return 64;
}

uint16_t send64(uint16_t *ptr)
{
    uint8_t itf = 0;
    uint32_t packet_size = 64;
    uint16_t timeouts = 0;
    while (tud_cdc_n_write_available(itf) < packet_size) 
        {
        
        tud_task();
        if (timeouts == 0)  
            tud_cdc_n_write_flush(itf);
        
        timeouts++;
    }

    tud_cdc_n_write(itf, ptr, packet_size);
    tud_cdc_n_write_flush(itf);
    //sendflag();
    return timeouts;
}

uint16_t sendstring(char const* str){

    uint8_t itf = 0;
    while (tud_cdc_n_write_available(itf) < 64) 
        {
        tud_task();
        tud_cdc_n_write_flush(itf);
    }

    tud_cdc_write_str(str);
    tud_cdc_n_write_flush(itf);
    return 64;
}

uint16_t sendflag(void){

    uint8_t itf = 0;
    uint32_t value = 4294967295; 
    while (tud_cdc_n_write_available(itf) < 4) 
        {
        tud_task();
        tud_cdc_n_write_flush(itf);
    }

    tud_cdc_write(&value,2);
    tud_cdc_n_write_flush(itf);
    return 64;
}


uint16_t cleartxbuffer(){

    uint8_t itf = 0;
    while (tud_cdc_n_write_available(itf) < 1) 
        {
        tud_task();
        tud_cdc_n_write_flush(itf);
    }

    tud_cdc_n_write_clear(itf);
    tud_cdc_n_write_flush(itf);
    return 64;
}


/*------------- MAIN -------------*/
int main(void)
{
  board_init();

  // init device stack on configured roothub port
  tud_init(BOARD_TUD_RHPORT);

    for(uint16_t i = 0; i<1024; i++ )
        buffer[i] = i;
        
  while (1)
  {
    tud_task(); // tinyusb device task
    cdc_task();
  }

  return 0;
}

/*void tobase94(char * base94, int Value){
    
    base94[0] = putchar( Value / 94 + 32 );
    base94[1] = putchar( Value % 94 * 94 + 32);
    
}*/

// echo to either Serial0 or Serial1
// with Serial0 as all lower case, Serial1 as all upper case
static void echo_serial_port(/*uint8_t itf, uint8_t buf[], uint32_t count*/)
{
  //uint8_t const case_diff = 'a' - 'A';

  /*for(uint32_t i=0; i<count; i++)
  {
    if (itf == 0)
    {
      // echo back 1st port as lower case
      if (isupper(buf[i])) buf[i] += case_diff;
    }
    else
    {
      // echo back 2nd port as upper case
      if (islower(buf[i])) buf[i] -= case_diff;
    }*/
    

    //char out_buf[64];
    //sprintf(out_buf,"%d",TUD_OPT_HIGH_SPEED);
    //sendstring(out_buf); 
    uint32_t n=0;
   
    uint32_t start_time =  time_us_32();
    //tud_cdc_n_write_char(itf, buf[count-1]);
    //putchar()
    //char arr[2];
    //tobase94(arr,buffer[0]);
    //n += 
    //sleep_ms(50);
    sendstring("\nStart");
    //tud_cdc_write_str((char)arr);	            
    // }
    //n += 
   
    //tud_cdc_n_write_flush(itf);
    //tud_task();
    //n += tud_cdc_write_flush();
    //uint16_t *buffer64 = malloc(sizeof(uint16_t)*64);
    //memcpy(buffer64, buffer, sizeof(uint16_t) * 64);

    /*uint16_t buffer64[256] = {   4096, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                                16, 17, 18 ,19 , 20, 21 , 22, 23, 24, 25, 26, 27 , 28, 29,
                                30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
                                44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
                                58, 59, 60, 61, 62, 63,
                                4096, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                                16, 17, 18 ,19 , 20, 21 , 22, 23, 24, 25, 26, 27 , 28, 29,
                                30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
                                44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
                                58, 59, 60, 61, 62, 63, 
                                4096, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                                16, 17, 18 ,19 , 20, 21 , 22, 23, 24, 25, 26, 27 , 28, 29,    
                                30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
                                44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
                                58, 59, 60, 61, 62, 63,
                                4096, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                                16, 17, 18 ,19 , 20, 21 , 22, 23, 24, 25, 26, 27 , 28, 29,
                                30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
                                44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
                                58, 59, 60, 61, 62, 63
                                };*/
    
    for (int i = 0; i < 32; i++)
    {
        int i2 = (32*i)%1024;
        n += send64( &buffer[i2]);
       
    }
    //tud_cdc_n_write_clear(itf);
    /*n += send64( &buffer64[0]);
    n += send64( &buffer64[64]);
    n += send64( &buffer64[128]);
    n += send64( &buffer64[192]);
    */
    //n += tud_cdc_n_write(itf, buffer, 64);
    // n += 
    //tud_cdc_n_write_clear(itf);
    //tud_cdc_n_write_flush(itf);
    //tud_task();
    //n += 
    sendstring("Stop\n");
    //tud_cdc_n_write_flush(itf);
    //tud_task();
    //tud_cdc_write_flush();
    uint32_t end_time =  time_us_32();
    char in_buf[64];
    sprintf(in_buf, "0-Duration: %lu us Bytes: %lu\n",(end_time-start_time), n);
    //tud_task();
    //tud_cdc_write_flush();
    //n += 
    sendstring(in_buf);
    //n += 
    //tud_cdc_write_flush();
    //cleartxbuffer();
}

//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+
static void cdc_task(void)
{
  //uint8_t itf;

  /*for (itf = 0; itf < CFG_TUD_CDC; itf++)
  {*/
    // connected() check for DTR bit
    // Most but not all terminal client set this when making connection
    // if ( tud_cdc_n_connected(itf) )
    {
      if ( tud_cdc_n_available(0) )//itf
      {
        //uint8_t buf[64];
        
        //uint32_t count = 
        //tud_cdc_n_read(0, buf, sizeof(buf));//itf

        // echo back to both serial ports
        echo_serial_port(/*0, buf, count*/);
        //echo_serial_port(1, buf, count);
       
      }
    }
  /*}*/
}
