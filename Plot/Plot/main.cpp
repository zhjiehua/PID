//#include "plot.h"
//#include <QtGui/QApplication>
//
//int main(int argc, char *argv[])
//{
//	QApplication a(argc, argv);
//	Plot w;
//	w.show();
//	return a.exec();
//}

#include "Plotter/Plotter.h"
#include "PID/PID.h"

#include <QApplication>
#include <QtGui>

void readFlightCurves(Plotter *plotter, const QString &fileName)
{
//
//	QVector<QPointF> data[6];
//
//	double factX = 0.0013;
//
//	double factY[6] = { 0.0008, 0.1, 0.2, 0.2, 0.1, 0.8 };
//
//	double offsY[6] = { +500, -55, +309, +308, 0, 0 };
//
//	int pos[6] = { 3, 6, 7, 8, 9, 10 };
//
//	QFile file(fileName);
//
//	double offsX = 0.0;
//
//
//	if (file.open(QIODevice::ReadOnly)) 
//
//	{
//
//		QTextStream in(&file);
//
//		while (!in.atEnd()) 
//
//		{
//
//			QString line = in.readLine();
//
//			QStringList coords = line.split(' ', QString::SkipEmptyParts);
//
//			if (coords.count() >= 6) 
//
//			{
//
//				double x = factX * coords[0].toDouble();
//
//				if (data[0].isEmpty())
//
//					offsX = x;
//
//				for (int i = 0; i < 6; ++i) 
//
//				{
//
//					double y = coords[pos[i]].toDouble();
//
//					data[i].append(QPointF(x - offsX, factY[i] * (y - offsY[i])));
//
//				}
//
//			}
//
//		}
//
//	}
//
//
//	plotter->setCurveData(0, data[0]);
//
//	plotter->setCurveData(1, data[1]);
//
//	plotter->setCurveData(2, data[2]);
//
//	plotter->setCurveData(3, data[3]);
//
//	plotter->setCurveData(4, data[4]);
//
//	plotter->setCurveData(5, data[5]);
//
}

int main(int argc, char *argv[])
{
	QVector<QPointF> PID_Data;

	QApplication a(argc, argv);

	Plotter plotter;
	plotter.setWindowTitle(QObject::tr("PID Test Plotter"));

	PID_Init(pPID);
	PID_UpdateSetPoint(pPID, 200);

	//readFlightCurves(&plotter, "C:/Cplusdev/Project/in1.txt");

	for(quint32 i=0;i<500;i++)
	{
		int32_t ActualPoint = PID_Calc(pPID);
		PID_UpdateActualPoint(pPID, ActualPoint);
		//QByteArray Array = intToByte(ActualPoint);
		//pWorker->myCom->write(Array.data());
		PID_Data.append(QPointF(i, ActualPoint));
	}

	//for(quint32 i=0;i<PID_Data.size();i++)
	//	qDebug() << PID_Data.at(i);

	plotter.setCurveData(0, PID_Data);

	plotter.show();

	return a.exec();
}