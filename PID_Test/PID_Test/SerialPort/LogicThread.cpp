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

#define TIMEOUT_PERIOD 20  //�Žܻ��޸�@2016-07-04����100�ĳ�200

//check
#ifdef WIN32
#define MAINCOMPORT		"COM4"//��λ��ͨѶ�ӿ�
#elif linux
#define MAINCOMPORT		"/dev/ttySAC2"//��λ��ͨѶ�ӿ�
#endif

/*************************************************Worker*********************************************************/

Worker::Worker(QObject *parent /*= 0*/)
{
	setupSerialCommunication();

	m_pTimer = new QTimer(this);
	QObject::connect(m_pTimer, SIGNAL(timeout()), this, SLOT(timeoutFunc()) );//��ʱ��ȡ����;
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
	
	//���崮�ڶ��󣬲����ݲ������ڹ��캯���������г�ʼ��;
#ifdef WIN32
	myCom = new Win_QextSerialPort(MAINCOMPORT);
#elif linux
	//����һ���ṹ�壬������Ŵ��ڸ�������;
	struct PortSettings myComSetting = {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
	myCom = new Posix_QextSerialPort(MAINCOMPORT,myComSetting,QextSerialBase::Polling);//LINUX�´����޷�ʹ���¼�����;
#endif

	//�Կɶ�д��ʽ�򿪴���;
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
