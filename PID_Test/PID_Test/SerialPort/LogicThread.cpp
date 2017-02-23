#include "LogicThread.h"
#include <QString>

#ifdef linux
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <asm-generic/ioctl.h>
#include <fcntl.h>

#include <stdint.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <unistd.h>
#endif

#define TIMEOUT_PERIOD 20  //张杰华修改@2016-07-04，将100改成200

//check
#ifdef WIN32
#define MAINCOMPORT		"COM4"//上位机通讯接口
#elif linux
#define MAINCOMPORT		"/dev/ttySAC2"//上位机通讯接口
#endif

/*************************************************Worker*********************************************************/

Worker::Worker(QObject *parent /*= 0*/)
{
	setupSerialCommunication();

	m_pTimer = new QTimer(this);
	QObject::connect(m_pTimer, SIGNAL(timeout()), this, SLOT(timeoutFunc()) );//定时读取数据;
	startTimer();
	moveToThread(&m_workerThread);
	m_workerThread.start();

	//connect(myCom, SIGNAL(readyRead()), this, SLOT(timeoutFunc()));
}

Worker::~Worker()
{
	
}

void Worker::timeoutFunc()
{
	QByteArray data;

	if(myCom)
		data  = myCom->readAll();
	if(data.size())
		qDebug()<<"data = "<< data.data();
}

void Worker::setupSerialCommunication()
{
	
	//定义串口对象，并传递参数，在构造函数里对其进行初始化;
#ifdef WIN32
	myCom = new Win_QextSerialPort(MAINCOMPORT);
#elif linux
	//定义一个结构体，用来存放串口各个参数;
	struct PortSettings myComSetting = {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
	myCom = new Posix_QextSerialPort(MAINCOMPORT,myComSetting,QextSerialBase::Polling);//LINUX下串口无法使用事件驱动;
#endif

	//以可读写方式打开串口;
	myCom ->open(QIODevice::ReadWrite);	
	myCom->setTimeout(10);
	myCom->setBaudRate(BAUD9600);
	myCom->setDataBits(DATA_8);
	myCom->setStopBits(STOP_1);
	myCom->setParity(PAR_NONE);
	myCom->setFlowControl(FLOW_OFF);
}

void Worker::startTimer()
{
	m_pTimer->start(TIMEOUT_PERIOD);
}
