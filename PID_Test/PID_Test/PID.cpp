#include "QDebug"
#include "PID.h"

static PID_TypeDef sPID;
PID_TypeDef *pPID = &sPID;

static int32_t Value2Point(int32_t Val)
{
	return (Val*1.0);
}

void PID_Init(PID_TypeDef *p)
{
	qDebug("PID_Init!\n");
	p->Proportion = 0.2;
	p->Integral = 0.015;
	p->Derivative = 0.2;

	p->SumError = 0;
	p->LastError = 0;
	p->PrevError = 0;

	p->SetPoint = 0;
	p->ActualPoint = 0;
	p->Value = 0;
	p->Value2Point = Value2Point;

	qDebug("PID_Init finish!\n");
}

void PID_UpdateSetPoint(PID_TypeDef *p, int32_t Point)
{
	p->SetPoint = Point;	
}

void PID_UpdateActualPoint(PID_TypeDef *p, int32_t Point)
{
	p->ActualPoint = Point;	
}

int32_t PID_Calc(PID_TypeDef *p)
{
	p->CurrError = p->SetPoint - p->ActualPoint;

	p->SumError += p->CurrError;

	p->Value = (p->Proportion * p->CurrError)
		+ (p->Integral * p->SumError)
		+ (p->Derivative * (p->CurrError - p->LastError));

	p->PrevError = p->LastError;
	p->LastError = p->CurrError;

	return (p->Value2Point(p->Value));
}