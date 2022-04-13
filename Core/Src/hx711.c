#include <hx711.h>

uint32_t  HX711_Buffer;
uint32_t  Weight_Maopi;
uint32_t  Weight_Shiwu;
uint8_t   Flag_Error = 0;

#define SCALE      476.55 //校正系数

unsigned long HX711_Read(void)	//增益128
{
	unsigned long data=0; 
	unsigned char i;
	
  HAL_GPIO_WritePin(HX711_SCK_PORT ,HX711_SCK_PIN,GPIO_PIN_RESET);
	Delay_ms(1);
	
  while(HAL_GPIO_ReadPin(HX711_DOUT_PORT ,HX711_DOUT_PIN)==GPIO_PIN_SET);
	for(i=0;i<24;i++)
	{  
	  	HAL_GPIO_WritePin(HX711_SCK_PORT ,HX711_SCK_PIN,GPIO_PIN_SET);

		Delay_ms(1);
			data=data<<1; 
			HAL_GPIO_WritePin(HX711_SCK_PORT ,HX711_SCK_PIN,GPIO_PIN_RESET); 
	
		  if(HAL_GPIO_ReadPin(HX711_DOUT_PORT ,HX711_DOUT_PIN)== GPIO_PIN_SET) 
			   data++;
	}
  
	 HAL_GPIO_WritePin(HX711_SCK_PORT ,HX711_SCK_PIN,GPIO_PIN_SET);
	 data=data^0x800000;//第25个脉冲下降沿来时，转换数据	
	 Delay_ms(1);
	 HAL_GPIO_WritePin(HX711_SCK_PORT ,HX711_SCK_PIN,GPIO_PIN_RESET); 
 
	 	
	
	return (data);
}
 
//****************************************************
//获取毛皮重量
//****************************************************
void Get_Maopi(void)
{
	Weight_Maopi = HX711_Read()/SCALE;	
} 
 
//****************************************************
//称重
//****************************************************
uint16_t Get_Weight(void)
{
//	Get_Maopi();
//	HX711_Buffer = HX711_Read();
//	
//	if(HX711_Buffer >= Weight_Maopi)			
//	{
//		Weight_Shiwu = HX711_Buffer;
//		Weight_Shiwu = Weight_Shiwu - Weight_Maopi;				//获取实物的AD采样数值。
//	
//		Weight_Shiwu = (uint32_t)((float)Weight_Shiwu/SCALE); 	//计算实物的实际重量
//																		//因为不同的传感器特性曲线不一样，因此，每一个传感器需要矫正这里的GapValue这个除数。
//																		//当发现测试出来的重量偏大时，增加该数值。
//																		//如果测试出来的重量偏小时，减小改数值。
//	}
		Weight_Shiwu =HX711_Read()/SCALE;
		if(Weight_Shiwu>=Weight_Maopi){
				Weight_Shiwu=Weight_Shiwu-Weight_Maopi;
				
			}
		else
				Weight_Shiwu=0;
	return Weight_Shiwu;
}
 
 


void Delay_ms(uint8_t time)
{
  uint8_t i;
	while(time--){
	for(i=0;i<113;i++);
	}
}
	