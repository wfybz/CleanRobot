#include "adc.h"

#define ADC1_DR_Address  ((u32)0x40012400 + 0x4c)
__IO uint16_t ADC_ConvertedVal;


/* 
 * 使能ADC1, DMA1的时钟，初始化PC.01 
 * ADC1通道11
 */
static void ADC1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//Enable DMA Clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//Enable ADC1 and GPIOC clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
	
	//Configure PC1 as analog input
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
}

#if 1
/*
* 配置ADC1的工作模式为DMA模式
*/
static void ADC1_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	
	//DMA channel configuration
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStruct.DMA_PeripheralBaseAddr = ADC1_DR_Address; //外设即ADC转换后存放数据地址
	DMA_InitStruct.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedVal; //内存地址
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC; //ADC为源
	DMA_InitStruct.DMA_BufferSize = 1;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址固定不递增
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStruct.DMA_PeripheralDataSize= DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStruct);
	
	//Enable DMA Channel1
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	/* ADC1 Configuration */
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent; //独立ADC模式
	ADC_InitStruct.ADC_ScanConvMode = DISABLE; //禁止扫描模式，扫描模式用于多通道采集
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE; //不停的进行ADC转换
	ADC_InitStruct.ADC_ExternalTrigConv  = ADC_ExternalTrigConv_None; //不使用外部触发转换
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right; //采集数据右对齐
	ADC_InitStruct.ADC_NbrOfChannel= 1; //要转换的通道数目为1
	ADC_Init(ADC1, &ADC_InitStruct);
	
	//配置ADC时钟，为PCLK2的8分频，即9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	//配置ADC1的通道11为55.5个采样周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_55Cycles5);
	
	//Enable ADC1 DMA
	ADC_DMACmd(ADC1, ENABLE);
	//Enable ADC1
	ADC_Cmd(ADC1, ENABLE);
	
	//复位校准寄存器
	ADC_ResetCalibration(ADC1);
	//等待校准寄存器复位完成
	while(ADC_GetResetCalibrationStatus(ADC1));
	
	//ADC校准
	ADC_StartCalibration(ADC1);
	//等待校准完成
	while(ADC_GetCalibrationStatus(ADC1));
	
	//由于没有采用外部触发，使用软件触发ADC转换
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
#endif

void ADC1_Config(void)
{
	ADC1_GPIO_Config();
	ADC1_Mode_Config();
}






















