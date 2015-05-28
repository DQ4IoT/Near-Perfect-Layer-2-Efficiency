
//DQSA Simulation (option 1).

#include <iostream.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <fstream.h>
#include <string.h>
#include <math.h>

#include "byte.h"

#include "segment.h"
#include "stationDQSA1.h"

long NumSimulated_Segments=500000;
const NumStations=100;
double length_messages_average=10;
const NumMiniSlots=3;
stationDQSA1 stations[NumStations];
segment s_dq(NumMiniSlots);
double tam_MiniSlots=0.05; //MiniSlots size normalized to the segment size
double p_inicial=0.0001;  //Probability of generating a message each segment time (initial value for several simulations)
double p_final=0.001;	//Probability of generating a message each segment time (final value)
double p_step=0.00005;	//Step size for each simulation
long messages_sent=0;
long messages_generated=0;
double delay_average_messages=0;
long packets_generated=0;
long packets_sent=0;
long delay_total=0;		//Delay normalized to segment size
long delay_total_messages=0;
long delay_max=0;
long delay_max_messages=0;
double occupation_buffers_average=0;
long occupation_buffers_max=0;
double delay_average=0;
double variance_delay=0;
long moment_2=0;
long moment_2_messages=0;
double variance_delay_messages=0;
ofstream output_file("result.txt");

void main()
{
	output_file<<"Throughput"<<";";
	output_file<<"Throughput net"<<";";
	output_file<<"load offered"<<";";
	output_file<<"delay average"<<";";
	output_file<<"delay max"<<";";
	output_file<<"variance delay"<<";";
	output_file<<"occupation buffers average"<<";";
	output_file<<"occupation buffers max"<<";";
	output_file<<"Througput mens/segment"<<";";
	output_file<<"load mens/segment"<<";";
	output_file<<"delay average messages"<<";";
	output_file<<"delay max messages"<<";";
	output_file<<"variance delay messages"<<";";
	output_file<<'\n';
	srand( (unsigned)time( NULL ) );
	int n;
	int paq_gen;

	//The simulation is performed several times for traffic loads from p_inicial to p_final
	for (double p=p_inicial;p<p_final;p+=p_step)
	{
		//Initialization of each simulation
		for (n=0;n<NumStations;n++)
			stations[n].ini(n+1,p,length_messages_average);
		for (long i=0;i<NumSimulated_Segments;i++)
		{
			//Only to see on screen the simulation process
			if (!(i%10000))
			{
				cout<<i<<"-";
				cout.flush();
			};

			//The order of execution of the rules seems to be changed, but it is only
			//a matter of simplicity for simulation purposes. The transmission of the feedback information
			//is not actually performed here, but the current segment is passed by reference to the stations
			//when executing the rules, so they 'write' and 'read' the segment directly. Then, the segment
			//is cleared only when its contents have been read in the QDR.

			s_dq.reset();  //The segment is initalized (next segment)

			//Traffic generation for all stations. Changing the contents of the function generate_messages
			//allows to simulate any traffic model.
			for (n=0;n<NumStations;n++)
			{
				paq_gen=stations[n].generate_messages();
				packets_generated+=paq_gen;
			};

			//Execution of DTR
			for (n=0;n<NumStations;n++)
				stations[n].DTR(s_dq);

			//Execution of RTR
			for (n=0;n<NumStations;n++)
				stations[n].RTR(s_dq);

			//In the simulation QDR are executed before resetting the segment, in order to
			//'read' the contents of the CMS. In the real system, at this point is where
			//the next segment actually begins, once received the feedback from the previous one

			for (n=0;n<NumStations;n++)
				stations[n].QDR(s_dq);

		};

		//Statistical calculations (once each simulation has been finished)
		delay_total=0;
		delay_max=0;
		moment_2=0;
		delay_total_messages=0;
		delay_max_messages=0;
		moment_2_messages=0;
		packets_generated=0;
		packets_sent=0;
		messages_generated=0;
		messages_sent=0;
		occupation_buffers_average=0;
		occupation_buffers_max=0;
		for (n=0;n<NumStations;n++)
		{
			delay_total+=stations[n].read_delay_total();
			moment_2+=stations[n].read_moment2_delay();
			if (stations[n].read_delay_max()>delay_max)
				delay_max=stations[n].read_delay_max();
			delay_total_messages+=stations[n].read_delay_total_messages();
			moment_2_messages+=stations[n].read_moment2_delay_messages();
			if (stations[n].read_delay_max_messages()>delay_max_messages)
				delay_max_messages=stations[n].read_delay_max_messages();
			occupation_buffers_average+=stations[n].read_occupation_queue_average();
			if (stations[n].read_occupation_queue_max()>occupation_buffers_max)
				occupation_buffers_max=stations[n].read_occupation_queue_max();
			packets_generated+=stations[n].read_packets_generated();
			packets_sent+=stations[n].read_packets_sent();
			messages_generated+=stations[n].read_messages_generated();
			messages_sent+=stations[n].read_messages_sent();
		};
		if (packets_sent>0)
		{
			occupation_buffers_average=(double)((double)occupation_buffers_average/NumStations);
			delay_average=(double)((double)delay_total/packets_sent)+1.5;
			variance_delay=(double)((double)moment_2/packets_sent)-(double)pow((delay_average-1.5),2);
			delay_average_messages=(double)((double)delay_total_messages/messages_sent)+1.5;
			variance_delay_messages=(double)((double)moment_2_messages/messages_sent)-(double)pow((delay_average_messages-1.5),2);
		};
		output_file<<(double)((double)packets_sent/NumSimulated_Segments)<<";";
		output_file<<(double)((double)packets_sent/NumSimulated_Segments)/(1+NumMiniSlots*tam_MiniSlots)<<";";
		output_file<<(double)((double)packets_generated/NumSimulated_Segments)<<";";
		output_file<<delay_average<<";";
		output_file<<delay_max<<";";
		output_file<<variance_delay<<";";
		output_file<<occupation_buffers_average<<";";
		output_file<<occupation_buffers_max<<";";
		output_file<<(double)((double)messages_sent/NumSimulated_Segments)<<";";
		output_file<<(double)((double)messages_generated/NumSimulated_Segments)<<";";
		output_file<<delay_average_messages<<";";
		output_file<<delay_max_messages<<";";
		output_file<<variance_delay_messages<<";";
		output_file<<'\n';
		cout<<'\n';
		cout<<"Number of segments simulated="<<NumSimulated_Segments<<'\n';
		cout<<"relative traffic load="<<(float)(p*NumStations*length_messages_average)<<'\n';
		cout<<"delay average packets="<<delay_average<<'\n';
		cout<<"delay max packets="<<delay_max<<'\n';
		cout<<"variance delay packets="<<variance_delay<<'\n';
		cout<<"delay average messages="<<delay_average_messages<<'\n';
		cout<<"variance delay messages="<<variance_delay_messages<<'\n';
		cout.flush();
		packets_generated=0;
		packets_sent=0;
	};
	output_file.close();
};

Enter file contents here
