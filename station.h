// station.h: interface for the station class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_station_H__3A72AF26_578F_11D2_B365_00C0F0230BD7__INCLUDED_)
#define AFX_station_H__3A72AF26_578F_11D2_B365_00C0F0230BD7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class station  
{

public:

	int id; //Identificador del terminal
	int estado; //estado del terminal
	station();
	virtual ~station();

};

#endif // !defined(AFX_station_H__3A72AF26_578F_11D2_B365_00C0F0230BD7__INCLUDED_)
