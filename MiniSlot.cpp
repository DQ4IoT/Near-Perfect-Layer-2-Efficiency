// MiniSlot.cpp: implementation of the MiniSlot class.
//
//////////////////////////////////////////////////////////////////////

#include "MiniSlot.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MiniSlot::MiniSlot(int tam)
{
    tamano = tam;
};
    
MiniSlot::~MiniSlot()
{

};

void MiniSlot::pon_peticion(int id)
{
	estado++;
};

void MiniSlot::pon_peticion(int id, int val)
{
	estado++;
	valor=val;
};

int MiniSlot::read_value ()
{
	return valor;
};

bool MiniSlot::peticion_valida()
{
	return (estado==1);
};

bool MiniSlot::colision()
{
	return (estado>1);
};

void MiniSlot::reset()
{
	estado=0;
};
