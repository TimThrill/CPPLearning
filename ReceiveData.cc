#include "ReceiveData.h"

ReceiveData::ReceiveData()
{
	receiveWindow = 1024;	/* Set default receive window */
	socket = -1;	/* initialise socket */
}

int ReceiveData::ReadData(char* writeBuff)
{
	int cntReceive = 0;
	while(1)
	{
		int ret = read(socket, writeBuff + cntReceive, receiveWindow);
		if(ret != 0)
		{
			if(ret > 0)
			{
				cntReceive += ret;
			}
		}
		else	/* read() returns 0 which means there is no more data or reach the end of file */
		{
			return cntReceive;
		}
	}
	return;
}
