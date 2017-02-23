
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
	float32_t Proportion;//��������
	float32_t Integral;//���ֳ���
	float32_t Derivative;//΢�ֳ���

	int64_t SumError;//�ۼ����
	int32_t CurrError;//Error[0]
	int32_t LastError;//Error[-1]
	int32_t PrevError;//Error[-2]

	int32_t	SetPoint;//Ŀ���
	int32_t ActualPoint;//ʵ�ʲɼ���

	int32_t Value;//PID���������ֵ
	int32_t (*Value2Point)(int32_t v);//PIDֵ��ʵ��������ӳ���ϵ
}PID_TypeDef;

extern PID_TypeDef *pPID;
void PID_Init(PID_TypeDef *p);
void PID_UpdateSetPoint(PID_TypeDef *p, int32_t Point);
void PID_UpdateActualPoint(PID_TypeDef *p, int32_t Point);
int32_t PID_Calc(PID_TypeDef *p);
