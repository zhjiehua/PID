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

/*�����̨�߼�����;*/
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
	QTimer *m_pTimer;								//���ڶ�ʱ��ȡͨѶ���ݵĶ�ʱ��;

	void setupSerialCommunication();				//���ô���ͨѶ;

public slots:
	void timeoutFunc();
};

#endif // LOGICTHREAD_H
