// cola_paquetes.cpp: implementation of the cola_paquetes class.
//
//////////////////////////////////////////////////////////////////////

#include "cola_paquetes.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cola_paquetes::cola_paquetes()
{
cola=new long [MAX_QUEUE_SIZE];
marcas=new bool [MAX_QUEUE_SIZE];
num_elementos=0;
max_elementos=MAX_QUEUE_SIZE;
}

cola_paquetes::~cola_paquetes()
{
delete [] cola;
delete [] marcas;
}

void cola_paquetes::push()
{
	if (num_elementos<max_elementos)
	{
		cola[num_elementos]=0;
		marcas[num_elementos]=false;
		num_elementos++;
	};
};

void cola_paquetes::push(long valor)
{
	if (num_elementos<max_elementos)
	{
		cola[num_elementos]=valor;
		marcas[num_elementos]=false;
		num_elementos++;
	};
};

long cola_paquetes::pop(bool &fin)
{
	long out;
	if (num_elementos)
	{
		out=cola[0];
		fin=marcas[0];
		for (int n=1;n<num_elementos;n++)
		{
			cola[n-1]=cola[n];
			marcas[n-1]=marcas[n];
		};
		num_elementos--;
	};
	return out;
};

void cola_paquetes::pop()
{
	long out;
	if (num_elementos)
	{
		out=cola[0];
		for (int n=1;n<num_elementos;n++)
		{
			cola[n-1]=cola[n];
			marcas[n-1]=marcas[n];
		};
		num_elementos--;
	};
	return;
};

void cola_paquetes::operator ++ ()
{
	for (int n=0;n<num_elementos;n++)
		cola[n]++;
};

long *cola_paquetes::operator [] (int n)
{
	if (n>0)
		return &cola[n-1];
	else
		return &cola[0];
};

int cola_paquetes::lee_num_elementos()
{
	return num_elementos;
};

int cola_paquetes::read_message_size()
{
	int aux=0;
	if (num_elementos) aux=1;
	for (int n=0;(n<num_elementos)&&(!marcas[n]);n++)
		aux++;
	return aux;
};

long cola_paquetes::suma_total()
{
	long aux=0;
	for (int n=0;n<num_elementos;n++)
		aux+=cola[n];
	return aux;
};

void cola_paquetes::reset()
{
	num_elementos=0;
};

long cola_paquetes::lee_1er_elemento()
{
	return cola[0];
};

void cola_paquetes::marca_final()
{
	marcas[num_elementos-1]=true;
};
