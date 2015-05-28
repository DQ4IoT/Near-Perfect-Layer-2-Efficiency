// cola_paquetes.h: interface for the cola_paquetes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLA_PAQUETES_H__65E4A121_59E9_11D2_B365_00C0F0230BD7__INCLUDED_)
#define AFX_COLA_PAQUETES_H__65E4A121_59E9_11D2_B365_00C0F0230BD7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if !defined MAX_QUEUE_SIZE
#define MAX_QUEUE_SIZE 200
#endif

class cola_paquetes  
{
	int num_elementos;
	int max_elementos;
	long *cola;
	bool *marcas;

public:
	cola_paquetes();
	virtual ~cola_paquetes();

	void reset();
	void push();
	void push(long valor);
	long pop(bool &fin);
	void pop();

	long lee_1er_elemento();
	int lee_num_elementos();
	int read_message_size();
	void operator ++ ();
	long *operator [] (int n);
	long suma_total();
	void marca_final();
};

#endif // !defined(AFX_COLA_PAQUETES_H__65E4A121_59E9_11D2_B365_00C0F0230BD7__INCLUDED_)
