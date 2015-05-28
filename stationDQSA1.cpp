// stationDQSA1.cpp: implementation of the stationDQSA1 class.
//
//////////////////////////////////////////////////////////////////////

#include <math.h>
#include "byte.h"
#include "segment.h"
#include "stationDQSA1.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

stationDQSA1::stationDQSA1()
{
pos=0; 
TQ=0;
RQ=0;
pTQ=0;
pRQ=0;
num_segments=0;
delay_total=0;
packets_sent=0;
packets_generated=0;
delay_max=0;
moment2_delay=0;
occupation_queue_average=0;
occupation_queue_max=0;
messages_generated=0;
messages_sent=0;
delay_total_messages=0;
delay_max_messages=0;
moment2_delay_messages=0;
length_messages_average=5;
p0=0.05;
}

stationDQSA1::~stationDQSA1()
{

}

void stationDQSA1::ini(int i,double p, double l)
{
	id=i;
	pos=0; 
	TQ=0;
	RQ=0;
	pTQ=0;
	pRQ=0;
	num_segments=0;
	delay_total=0;
	packets_sent=0;
	packets_generated=0;
	delay_max=0;
	occupation_queue_average=0;
	occupation_queue_max=0;
	moment2_delay=0;
	messages_generated=0;
	messages_sent=0;
	delay_total_messages=0;
	delay_max_messages=0;
	moment2_delay_messages=0;
	queue.reset();
	Packet_Size.reset();
	length_messages_average=l;
	p0=p;
};

void stationDQSA1::DTR(segment &s)
{
/*	OPTIONAL, in principle do not use with XDQRAP
	if (TQ==0 && RQ==0)
	{
		if (hay_message())
		{
			s.envia_datos(id);
			estado=ENVIANDO_DATOS;
		};
	};*/

	//Rule (b)
	if (TQ>0)
	{
		if (pTQ==1)
		{
			s.envia_datos(id);  //Here the station must actually send the current packet from its buffer
			estado=ENVIANDO_DATOS;
		};
	};
}

void stationDQSA1::RTR(segment &s)
{
	pos=0;

	//Rule (a)
	if ((RQ==0)&&(pTQ==0)&&(pRQ==0))
	{
		if (messages_to_send())
		{
			pos=s.envia_peticion(id,queue.read_message_size());	//The inclusion of the id is optional in actual implementation
			estado|=ENVIANDO_PETICION;
		};
		};
	
	//Rule (b)
	if (RQ>0)
	{
		if (pRQ==1)
		{
			pos=s.envia_peticion(id,queue.read_message_size());	//The inclusion of the id is optional in actual implementation
			estado|=ENVIANDO_PETICION;
		};
	};
};

void stationDQSA1::QDR(segment &s)
{
	//Rule (a)
	if (TQ>0) (*Packet_Size[1])--;

	//Rule (b)
	if ((TQ>0) && (*Packet_Size[1]==0))
	{
		TQ--;
		if (pTQ>0) pTQ--;
		Packet_Size.pop();
	};

	//Rule (c)
	TQ=TQ+s.num_pet_exito();
	for (int n=0;n<s.num_pet_exito();n++)
		Packet_Size.push(s.read_success(n+1));

	//Rule (d)
	if (RQ>0)
		RQ--;

	//Rule (e)
	if (pRQ>0)
		pRQ--;

	//Rule (f)
	RQ=RQ+s.num_colisiones();

	//Rule (g)
	if (request_transmitted())
	{
		//Rule (g.1)
		if (s.es_pet_exito(pos))
			pTQ=TQ-s.num_pet_exito()+s.posicion_exito(pos);
		//Rule (g.2)
		if (!s.es_pet_exito(pos))
			pRQ=RQ-s.num_colisiones()+s.posicion_colision(pos);
	};

//Statistics (not needed in actual implementation)
	if (data_transmitted()&&s.num_datos_exito())
	{
		long aux;
		bool fin_message;
		packets_sent++;
		aux=queue.pop(fin_message);
		if (aux>delay_max)
			delay_max=aux;
		if (fin_message)
		{
			messages_sent++;
			delay_total_messages+=aux;
			moment2_delay_messages+=(long)pow(aux,2);
			if (aux>delay_max_messages)
				delay_max_messages=aux;
		};
		delay_total+=aux;
		moment2_delay+=(long)pow(aux,2);
	};
	estado=0;
	num_segments++;
	if (queue.lee_num_elementos()>0)
	{
		queue++;
		if (queue.lee_num_elementos()>occupation_queue_max)
			occupation_queue_max=queue.lee_num_elementos();
		occupation_queue_average+=queue.lee_num_elementos();
	};
};

int stationDQSA1::generate_messages()
{
	//Poisson arrival (actually can be any model)
	double aux=(double)rand();
	aux=(double)aux/RAND_MAX;
	if (aux<p0)
	{
		messages_generated++;
		length_messages=(int)(((double)rand()/RAND_MAX)*2*length_messages_average)+1;
		packets_generated+=length_messages;
		for (int n=0;n<length_messages;n++)
			queue.push();
		queue.marca_final();
		return length_messages;
	}
	else
		return 0;
};


bool stationDQSA1::messages_to_send()
{
	return (queue.lee_num_elementos()>0);
};

bool stationDQSA1::data_transmitted()
{
	if ((estado&ENVIANDO_DATOS)==0)
		return false;
	else
		return true;
	
};

bool stationDQSA1::request_transmitted()
{
	if ((estado&ENVIANDO_PETICION)==0)
		return false;
	else
		return true;
};

long stationDQSA1::read_delay_total()
{
	return delay_total;
};

long stationDQSA1::read_packets_sent()
{
	return packets_sent;
};

long stationDQSA1::read_packets_generated()
{
	return packets_generated;
};

int stationDQSA1::read_pointer_trans()
{
	return pTQ;
};

long stationDQSA1::read_delay_max()
{
	return delay_max;
};

long stationDQSA1::read_delay_max_messages()
{
	return delay_max_messages;
};

long stationDQSA1::read_moment2_delay()
{
	return moment2_delay;
};

double stationDQSA1::read_occupation_queue_average()
{
	return (double)((double)occupation_queue_average/num_segments);
};

long stationDQSA1::read_occupation_queue_max()
{
	return occupation_queue_max;
};

long stationDQSA1::read_messages_sent()
{
	return messages_sent;
};

long stationDQSA1::read_messages_generated()
{
	return messages_generated;
};

long stationDQSA1::read_delay_total_messages()
{
	return delay_total_messages;
};

long stationDQSA1::read_moment2_delay_messages()
{
	return moment2_delay_messages;
};
