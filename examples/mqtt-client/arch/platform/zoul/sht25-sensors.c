/*
 * Copyright (c) 2017, George Oikonomou - http://www.spd.gr
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*---------------------------------------------------------------------------*/
#include "contiki.h"
#include "dev/sht25.h"
#include "mqtt-client.h"


#include <string.h>
#include <stdio.h>
/*---------------------------------------------------------------------------*/
#define TMP_BUF_SZ 32
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
char tmp_buf[TMP_BUF_SZ];
int16_t temperature, humidity;

/*---------------------------------------------------------------------------*/
static char *
temp_reading(void)
{

  memset(tmp_buf, 0, TMP_BUF_SZ);
  temperature=sht25.value(SHT25_VAL_TEMP);
  snprintf(tmp_buf, TMP_BUF_SZ, "\"Temperature(ºC)\":%02d.%02d", 
           temperature / 100, temperature % 100);
  return tmp_buf;
}
/*---------------------------------------------------------------------------*/
static void
temp_init(void)
{
  SENSORS_ACTIVATE(sht25);
  sht25.configure(SHT25_RESOLUTION, SHT2X_RES_14T_12RH);
}
/*---------------------------------------------------------------------------*/
const mqtt_client_extension_t sht25_zoul_temp= {
  temp_init,
  temp_reading,
};
/*---------------------------------------------------------------------------*/
static char *
hum_reading(void)
{
  memset(tmp_buf, 0, TMP_BUF_SZ);
  humidity=sht25.value(SHT25_VAL_HUM);
  snprintf(tmp_buf, TMP_BUF_SZ, "\"Humidity(RH)\":%02d.%02d",
           humidity / 100, humidity % 100);
  return tmp_buf;
}
/*---------------------------------------------------------------------------*/
static void
hum_init(void)
{
  SENSORS_ACTIVATE(sht25);
  sht25.configure(SHT25_RESOLUTION, SHT2X_RES_14T_12RH);
}

/*---------------------------------------------------------------------------*/
const mqtt_client_extension_t sht25_zoul_humidity= {
  hum_init,	
  hum_reading,
};
/*---------------------------------------------------------------------------*/


