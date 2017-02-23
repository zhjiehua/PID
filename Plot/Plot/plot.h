#ifndef PLOT_H
#define PLOT_H

#include <QtGui/QMainWindow>
#include "ui_plot.h"

class Plot : public QMainWindow
{
	Q_OBJECT

public:
	Plot(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Plot();

private:
	Ui::PlotClass ui;
};

#endif // PLOT_H
