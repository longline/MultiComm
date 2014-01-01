/*
 * gather.h
 *
 * one serial port to one gather
 *
 *  Created on: Dec 2, 2013
 *      Author: lifeng
 */

#ifndef GATHER_H_
#define GATHER_H_

#include <pthread.h>
#include "frame_manager.h"

#define MAX_SENSOR	(200)

struct smart_sensor
{
	struct gather_port * port;
	int addr;
	int type;
	int timeout_count;
	char *tx_data;
	char *rx_data;
	char version[6];
	void (*query_digit)(struct smart_sensor *sensor);
	void (*query_analog)(struct smart_sensor *sensor);
	void (*query_curve)(struct smart_sensor *sensor);
	void (*query_others)(struct smart_sensor *sensor);

};


struct gather_port
{
  int used;
  int serial_fd;
  int tx_led_fd;
  int rx_led_fd;
  char  serial_name[50];
  char portIndex;
  int baudrate;

  char tx_data[128];
  char rx_data[1024*4];
  int sensor_num;
  struct smart_sensor  sensors[MAX_SENSOR];
  int last_badsensor;
  struct frame_manager * frame_manager;
  pthread_t thread_wk;


};




struct gather_port* create_gather(char*serial_name,int baudrate);

void gather_add_module(int addr,int type);

void start_gather_port(struct gather_port* pgather);
void stop_gather_port(struct gather_port* pgather);

void add_sensor_II(struct gather_port *port, int addr, int type);


#endif /* GATHER_H_ */
