
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;
typedef float float32_t;
typedef double float64_t;

typedef struct
{
	float32_t Proportion;//比例常数
	float32_t Integral;//积分常数
	float32_t Derivative;//微分常数

	int64_t SumError;//累计误差
	int32_t CurrError;//Error[0]
	int32_t LastError;//Error[-1]
	int32_t PrevError;//Error[-2]

	int32_t	SetPoint;//目标点
	int32_t ActualPoint;//实际采集点

	int32_t Value;//PID计算出来的值
	int32_t (*Value2Point)(int32_t v);//PID值与实际输出间的映射关系
}PID_TypeDef;

extern PID_TypeDef *pPID;
void PID_Init(PID_TypeDef *p);
void PID_UpdateSetPoint(PID_TypeDef *p, int32_t Point);
void PID_UpdateActualPoint(PID_TypeDef *p, int32_t Point);
int32_t PID_Calc(PID_TypeDef *p);
