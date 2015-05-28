// MiniSlot.h: interface for the MiniSlot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MINISLOT_H__3A72AF25_578F_11D2_B365_00C0F0230BD7__INCLUDED_)
#define AFX_MINISLOT_H__3A72AF25_578F_11D2_B365_00C0F0230BD7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class MiniSlot  
{
    int tamano; // tamaño del minislot (bytes)
	int estado;
	int id; // identificador del terminal que ha usado el minislot
	int valor; // valor enviado en el minislot (si procede)
    
public:
	MiniSlot(int tam=3);
	virtual ~MiniSlot();

	void pon_peticion(int id);
	void pon_peticion(int id, int val);
	bool peticion_valida();
	bool colision();
	void reset();
	int read_value();
};

#endif // !defined(AFX_MINISLOT_H__3A72AF25_578F_11D2_B365_00C0F0230BD7__INCLUDED_)
