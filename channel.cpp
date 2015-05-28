// channel.cpp: implementation of the channel class.
//
//////////////////////////////////////////////////////////////////////

//Funciones de la clase channel

#include <conio.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fstream.h>

#undef AFX_DATA
#define AFX_DATA AFX_EXT_DATA

#include "output.h"
#include "byte.h"
#include "segment.h"
#include "channel.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

channel::channel()
{
	estado=0;
	NumSegmentsEnviados=0;
	BER=20;
	tiempo_llegada=0;
}

channel::~channel()
{

}

int channel::LeeEstado () {
	return estado;
};

int channel::LeeNumSegmentsEnviados () {
	return NumSegmentsEnviados;
};

void channel::SendDataSegment (segment &s) {
	contenido=&s;
//	contenido.PonRuido(BER);   //Añadimos ERRORES.
	NumSegmentsEnviados++;
	if (NumSegmentsEnviados==1) {
		estado=1; //segment válido.
		tiempo_llegada=0;
	}
	else {
		estado=2; //Colisi¢n.
	};
};

bool channel::HaySegment (char *mensaje) {
	if (NumSegmentsEnviados==1)
	{
		if (contenido->TieneErrores())
		{
			return false;
		}
		else
		{
			return true;
		};
	}
	else
	{
		if (Colision())
			{
/*			mensaje[cadlen(mensaje)]=255;
			mensaje[cadlen(mensaje)+1]=0;
			char m[12]={'(','C','o','l','i','s','i','o','n',')','.',0};
			cadcat (mensaje,m);*/
			};
		return false;
	};
};

bool channel::HaySegment () {
	bool segment_ok=true;
	if (NumSegmentsEnviados==1)
	{
		segment_ok=contenido->TieneErrores();
		if (segment_ok)
		{
			return true;
		}
		else
		{
			return false;
		};
	}
	else
	{
		return false;
	};
};

segment *channel::Content() {
return contenido;
};

void channel::Ini() {
	NumSegmentsEnviados=0;
	estado=0;
	tiempo_llegada++;
};

bool channel::EstaLibre() {
	if (estado) return false;
	else return true;
};

bool channel::Colision() {
	if (NumSegmentsEnviados>1) {
		return true;
	}
	else {
		return false;
	};
};
Enter file contents here
