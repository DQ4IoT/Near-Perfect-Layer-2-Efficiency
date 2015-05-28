// channel.h: interface for the channel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_channel_H__3A72AF23_578F_11D2_B365_00C0F0230BD7__INCLUDED_)
#define AFX_channel_H__3A72AF23_578F_11D2_B365_00C0F0230BD7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class channel  
{
int estado; //Estado del channel.
int NumSegmentsEnviados;  //N£m. de Segments que intentan 'pasar' por el canal.
segment *contenido; //Segment que pasa por el canal.
unsigned int tiempo_llegada; //Tiempo de llegada entre Segments.
float BER;  //Bit Error Rate

public:
	channel();
	virtual ~channel();

	
	int LeeEstado (); //Devuelve el estado del canal.
	int LeeNumSegmentsEnviados (); //Devuelve NumSegmentsEnviados.
	bool EstaLibre (); //Devuelve True si el canal está libre.
	void SendDataSegment (segment &s); //Manda un Segment por el canal.
	bool Colision (); //Devuelve True si hay m s de un Segment por el canal.
	bool HaySegment (char *mensaje); //Devuelve True si contenido tiene un valor válido.
	bool HaySegment (); //Idem.
	segment *Content(); //Devuelve un puntero al Segment que está pasando por el canal.
	void Ini(); //Inicia un Segment en el canal. 'Limpia' el canal.

};

#endif // !defined(AFX_channel_H__3A72AF23_578F_11D2_B365_00C0F0230BD7__INCLUDED_)
