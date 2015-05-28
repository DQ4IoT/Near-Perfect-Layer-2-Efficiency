// segment.h: interface for the segment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_segment_H__3A72AF24_578F_11D2_B365_00C0F0230BD7__INCLUDED_)
#define AFX_segment_H__3A72AF24_578F_11D2_B365_00C0F0230BD7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MiniSlot.h"

class segment  
{

	long num;
	int NumMiniSlots;
	MiniSlot MiniSlots[10];
	int estado;	//Indica si hay datos y si tienen errores.

public:
	segment(int mini);
	virtual ~segment();

	bool TieneErrores();
	void envia_datos(int id);
	int envia_peticion(int id);
	int envia_peticion (int id, int val);
	int num_pet_exito();
	int num_datos_exito();
	int num_colisiones();
	int posicion_exito(int pos);
	bool es_pet_exito(int pos);
	int posicion_colision(int pos);
	int read_success(int num);
	void reset();

};

#endif // !defined(AFX_segment_H__3A72AF24_578F_11D2_B365_00C0F0230BD7__INCLUDED_)
