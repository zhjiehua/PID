#ifndef LOGICTHREAD_H
#define LOGICTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>

#ifdef WIN32
#include "win_qextserialport.h"
#elif linux
#include "posix_qextserialport.h"
#endif

/*负责后台逻辑处理;*/
class Worker : public QObject
{
	Q_OBJECT
public:
	Worker(QObject *parent = 0);
	~Worker();

#ifdef WIN32
	Win_QextSerialPort *myCom;
#elif linux
	Posix_QextSerialPort *myCom;
#endif

	void startTimer();
private:
	QThread m_workerThread;
	QTimer *m_pTimer;								//用于定时读取通讯数据的定时器;

	void setupSerialCommunication();				//设置串口通讯;

public slots:
	void timeoutFunc();
};

#endif // LOGICTHREAD_H
