#include <QtCore/QCoreApplication>
#include "SerialPort/LogicThread.h"
#include "PID.h"

QByteArray intToByte(int i)  
{  
	QByteArray abyte0;  
	abyte0.resize(4);  
	abyte0[0] = (uchar)  (0x000000ff & i);  
	abyte0[1] = (uchar) ((0x0000ff00 & i) >> 8);  
	abyte0[2] = (uchar) ((0x00ff0000 & i) >> 16);  
	abyte0[3] = (uchar) ((0xff000000 & i) >> 24);  
	return abyte0;  
}

int bytesToInt(QByteArray bytes) {  
	int addr = bytes[0] & 0x000000FF;  
	addr |= ((bytes[1] << 8) & 0x0000FF00);  
	addr |= ((bytes[2] << 16) & 0x00FF0000);  
	addr |= ((bytes[3] << 24) & 0xFF000000);  
	return addr;  
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	PID_Init(pPID);
	PID_UpdateSetPoint(pPID, 200);
	
	Worker *pWorker = new Worker;

	for(quint32 i=0;i<500;i++)
	{
		int32_t ActualPoint = PID_Calc(pPID);
		PID_UpdateActualPoint(pPID, ActualPoint);
		QByteArray Array = intToByte(ActualPoint);
		pWorker->myCom->write(Array.data());
	}

	return a.exec();
}
