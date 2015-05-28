// stationDQSA1.h: interface for the stationDQSA1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATIONDQSA1_H__97AB9C81_5850_11D2_B365_00C0F0230BD7__INCLUDED_)
#define AFX_STATIONDQSA1_H__97AB9C81_5850_11D2_B365_00C0F0230BD7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "station.h"
#include "cola_paquetes.h"
#include <stdlib.h>

const int ENVIANDO_DATOS=1;
const int ENVIANDO_PETICION=2;

class stationDQSA1 : public station  
{

	int pos; //posición de la petición dentro de los minislots
	int TQ; //queue de transmisión
	int RQ; //queue de peticiones
	int pTQ; //pointer a la queue de transmisión
	int pRQ; //pointer a la queue de peticiones
	long num_segments; //numero segmentos de simulacion transcurridos
	cola_paquetes Packet_Size;  //A queue that keeps record of the Message size requested by each access request
	cola_paquetes queue; //A queue that records the delay of each packet
	long delay_total;
	long delay_max;
	long moment2_delay;
	long packets_sent;
	long packets_generated;
	double delay_average;
	long occupation_queue_average;
	long occupation_queue_max;
	int length_messages;
	double length_messages_average;
	long messages_generated;
	long messages_sent;
	long delay_total_messages;
	long delay_max_messages;
	long moment2_delay_messages;

	double p0; //probability of generating messages per segment

public:
	stationDQSA1();
	virtual ~stationDQSA1();

	long read_delay_total();
	long read_packets_sent();
	long read_packets_generated();
	int read_pointer_trans();
	long read_delay_max();
	long read_delay_max_messages();
	long read_moment2_delay();
	double read_occupation_queue_average();
	long read_occupation_queue_max();
	long read_messages_sent();
	long read_messages_generated();
	long read_delay_total_messages();
	long read_moment2_delay_messages();

	void ini(int i,double p, double l);

	void DTR(segment &s);
	void RTR(segment &s);
	void QDR(segment &s);

	bool messages_to_send();
	int generate_messages();
	bool data_transmitted();
	bool request_transmitted();

};

#endif // !defined(AFX_STATIONDQSA1_H__97AB9C81_5850_11D2_B365_00C0F0230BD7__INCLUDED_)
