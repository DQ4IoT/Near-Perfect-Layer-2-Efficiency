// segment.cpp: implementation of the segment class.
//
//////////////////////////////////////////////////////////////////////

#include "byte.h"
#include "segment.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

segment::segment(int mini)
{
num=0;
NumMiniSlots=mini;
estado=0;
}

segment::~segment()
{

}

bool segment::TieneErrores()
{
	return false;
};

void segment::envia_datos(int id)
{
	estado++;
};

int segment::envia_peticion (int id)
{
	int aux;
	aux=random(NumMiniSlots);
	MiniSlots[aux].pon_peticion(id);
	return aux+1;
};

int segment::envia_peticion (int id, int val)
{
	int aux;
	aux=random(NumMiniSlots);
	MiniSlots[aux].pon_peticion(id, val);
	return aux+1;
};

int segment::read_success (int num)  //returns the num_th success from the Minislots
{
	int aux=0;
	int n=0;
	int valor=0;
	while ((n<num)&&(aux<NumMiniSlots))
	{
		if (MiniSlots[aux].peticion_valida())
		{
			valor=MiniSlots[aux].read_value();
			n++;
		};
		aux++;
	};
	return valor;
};

int segment::num_pet_exito()
{
	int aux=0;
	for (int i=0;i<NumMiniSlots;i++)
		if (MiniSlots[i].peticion_valida())
			aux++;
	return aux;
};

int segment::num_datos_exito()
{
	if (estado==1)
		return 1;
	else
		return 0;
};

int segment::num_colisiones()
{
	int aux=0;
	for (int i=0;i<NumMiniSlots;i++)
		if (MiniSlots[i].colision())
			aux++;
	return aux;
};

int segment::posicion_exito(int pos)
{
	int aux=0;
	for (int i=0;i<pos;i++)
		if (MiniSlots[i].peticion_valida())
			aux++;
	return aux;
};

bool segment::es_pet_exito(int pos)
{
	return (MiniSlots[pos-1].peticion_valida());
};

int segment::posicion_colision(int pos)
{
	int aux=0;
	for (int i=0;i<pos;i++)
		if (MiniSlots[i].colision())
			aux++;
	return aux;
};

void segment::reset()
{
	estado=0;
	for (int n=0;n<NumMiniSlots;n++)
		MiniSlots[n].reset();
	num++;
};
