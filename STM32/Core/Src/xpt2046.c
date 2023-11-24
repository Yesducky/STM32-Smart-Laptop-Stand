#include "xpt2046.h"
#include "lcd.h"
#include <stdio.h> 
#include <string.h>
#include "led.h"


static void                   XPT2046_DelayUS                       ( __IO uint32_t ulCount );
static void                   XPT2046_WriteCMD                      ( uint8_t ucCmd );
static uint16_t               XPT2046_ReadCMD                       ( void );
static uint16_t               XPT2046_ReadAdc                       ( uint8_t ucChannel );
static void                   XPT2046_ReadAdc_XY                    ( int16_t * sX_Ad, int16_t * sY_Ad );
static uint8_t                XPT2046_ReadAdc_Smooth_XY             ( strType_XPT2046_Coordinate * pScreenCoordinate );
static uint8_t                XPT2046_Calculate_CalibrationFactor   ( strType_XPT2046_Coordinate * pDisplayCoordinate, strType_XPT2046_Coordinate * pScreenSample, strType_XPT2046_Calibration * pCalibrationFactor );



strType_XPT2046_TouchPara strXPT2046_TouchPara = { 0.085958, -0.001073, -4.979353, -0.001750, 0.065168, -13.318824 };  
                                              // { 0.001030, 0.064188, -10.804098, -0.085584, 0.001420, 324.127036 };  

volatile uint8_t ucXPT2046_TouchFlag = 0;




	
static void XPT2046_DelayUS ( __IO uint32_t ulCount )
{
	uint32_t i;


	for ( i = 0; i < ulCount; i ++ )
	{
		uint8_t uc = 12;     
	      
		while ( uc -- );     

	}
	
}


static void XPT2046_WriteCMD ( uint8_t ucCmd ) 
{
	uint8_t i;


	macXPT2046_MOSI_0();
	
	macXPT2046_CLK_LOW();

	for ( i = 0; i < 8; i ++ ) 
	{
		( ( ucCmd >> ( 7 - i ) ) & 0x01 ) ? macXPT2046_MOSI_1() : macXPT2046_MOSI_0();
		
	  XPT2046_DelayUS ( 5 );
		
		macXPT2046_CLK_HIGH();

	  XPT2046_DelayUS ( 5 );

		macXPT2046_CLK_LOW();
	}
	
}


static uint16_t XPT2046_ReadCMD ( void ) 
{
	uint8_t i;
	uint16_t usBuf=0, usTemp;
	


	macXPT2046_MOSI_0();

	macXPT2046_CLK_HIGH();

	for ( i=0;i<12;i++ ) 
	{
		macXPT2046_CLK_LOW();    
	
		usTemp = macXPT2046_MISO();
		
		usBuf |= usTemp << ( 11 - i );
	
		macXPT2046_CLK_HIGH();
		
	}
	
	return usBuf;

}


static uint16_t XPT2046_ReadAdc ( uint8_t ucChannel )
{
	XPT2046_WriteCMD ( ucChannel );

  return 	XPT2046_ReadCMD ();
	
}


static void XPT2046_ReadAdc_XY ( int16_t * sX_Ad, int16_t * sY_Ad )  
{ 
	int16_t sX_Ad_Temp, sY_Ad_Temp; 

	
	
	sX_Ad_Temp = XPT2046_ReadAdc ( macXPT2046_CHANNEL_X );

	XPT2046_DelayUS ( 1 ); 

	sY_Ad_Temp = XPT2046_ReadAdc ( macXPT2046_CHANNEL_Y ); 
	
	
	* sX_Ad = sX_Ad_Temp; 
	* sY_Ad = sY_Ad_Temp; 
	
	
}


static uint8_t XPT2046_ReadAdc_Smooth_XY ( strType_XPT2046_Coordinate * pScreenCoordinate )
{
	uint8_t ucCount = 0, i;
	
	int16_t sAD_X, sAD_Y;
	int16_t sBufferArray [ 2 ] [ 10 ] = { { 0 },{ 0 } };  
	
	int32_t lX_Min, lX_Max, lY_Min, lY_Max;


	do					       				
	{		  
		XPT2046_ReadAdc_XY ( & sAD_X, & sAD_Y );  
		
		sBufferArray [ 0 ] [ ucCount ] = sAD_X;  
		sBufferArray [ 1 ] [ ucCount ] = sAD_Y;
		
		ucCount ++;  
		
	}	while ( ( macXPT2046_EXTI_Read() == macXPT2046_EXTI_ActiveLevel ) && ( ucCount < 10 ) );
	

	if ( macXPT2046_EXTI_Read() != macXPT2046_EXTI_ActiveLevel )
		ucXPT2046_TouchFlag = 0;			


	if ( ucCount ==10 )		 					
	{
		lX_Max = lX_Min = sBufferArray [ 0 ] [ 0 ];
		lY_Max = lY_Min = sBufferArray [ 1 ] [ 0 ];       
		
		for ( i = 1; i < 10; i ++ )
		{
			if ( sBufferArray [ 0 ] [ i ] < lX_Min )
				lX_Min = sBufferArray [ 0 ] [ i ];
			
			else if ( sBufferArray [ 0 ] [ i ] > lX_Max )
				lX_Max = sBufferArray [ 0 ] [ i ];

		}
		
		for ( i = 1; i < 10; i ++ )
		{
			if ( sBufferArray [ 1 ] [ i ] < lY_Min )
				lY_Min = sBufferArray [ 1 ] [ i ];
			
			else if ( sBufferArray [ 1 ] [ i ] > lY_Max )
				lY_Max = sBufferArray [ 1 ] [ i ];

		}
		

		pScreenCoordinate ->x =  ( sBufferArray [ 0 ] [ 0 ] + sBufferArray [ 0 ] [ 1 ] + sBufferArray [ 0 ] [ 2 ] + sBufferArray [ 0 ] [ 3 ] + sBufferArray [ 0 ] [ 4 ] + 
		                           sBufferArray [ 0 ] [ 5 ] + sBufferArray [ 0 ] [ 6 ] + sBufferArray [ 0 ] [ 7 ] + sBufferArray [ 0 ] [ 8 ] + sBufferArray [ 0 ] [ 9 ] - lX_Min-lX_Max ) >> 3;
		
		pScreenCoordinate ->y =  ( sBufferArray [ 1 ] [ 0 ] + sBufferArray [ 1 ] [ 1 ] + sBufferArray [ 1 ] [ 2 ] + sBufferArray [ 1 ] [ 3 ] + sBufferArray [ 1 ] [ 4 ] + 
		                           sBufferArray [ 1 ] [ 5 ] + sBufferArray [ 1 ] [ 6 ] + sBufferArray [ 1 ] [ 7 ] + sBufferArray [ 1 ] [ 8 ] + sBufferArray [ 1 ] [ 9 ] - lY_Min-lY_Max ) >> 3; 
		
		
		return 1;
		

	}   
	
	
	return 0;    
	
	
}



uint8_t XPT2046_Get_TouchedPoint ( strType_XPT2046_Coordinate * pDisplayCoordinate, strType_XPT2046_TouchPara * pTouchPara )
{
	uint8_t ucRet = 1;           
	
	strType_XPT2046_Coordinate strScreenCoordinate; 
	

  if ( XPT2046_ReadAdc_Smooth_XY ( & strScreenCoordinate ) )
  {    
		pDisplayCoordinate ->x = ( ( pTouchPara ->dX_X * strScreenCoordinate .x ) + ( pTouchPara ->dX_Y * strScreenCoordinate .y ) + pTouchPara ->dX );        
		pDisplayCoordinate ->y = ( ( pTouchPara ->dY_X * strScreenCoordinate .x ) + ( pTouchPara ->dY_Y * strScreenCoordinate .y ) + pTouchPara ->dY );

  }
	 
	else ucRet = 0;            
	
	return ucRet;
	
	
} 

ButtonCoordinates ResetButton = { { 25, 170 }, { 120, 210 } };
ButtonCoordinates AutoButton = { { 135, 170 }, { 220, 210 } };
ButtonCoordinates UpButton = { { 240, 10 }, { 300, 60 } };
ButtonCoordinates DownButton = { { 240, 160 }, { 300, 210 } };
ButtonCoordinates PauseButton = { { 240, 75 }, { 300, 145 } };

int Check_touchkey()
{
		strType_XPT2046_Coordinate strDisplayCoordinate;
	
	if ( XPT2046_Get_TouchedPoint ( & strDisplayCoordinate, & strXPT2046_TouchPara ) )
	{
		char str1[33];
		char str2[33];

		snprintf(str1,32,"%d", strDisplayCoordinate.x);
		snprintf(str2,32,"%d", strDisplayCoordinate.y);

		LCD_Clear(50,100,30,30,0xFFFF);
		LCD_DrawString(50, 100, str1);
		LCD_DrawString(50, 115, str2);


		if( (strDisplayCoordinate.x >= ResetButton.Top_Left.x && strDisplayCoordinate.x <= ResetButton.Bottom_Right.x)  &&
			(strDisplayCoordinate.y >= ResetButton.Top_Left.y && strDisplayCoordinate.y <= ResetButton.Bottom_Right.y)){
				return 1;
			}

		if( (strDisplayCoordinate.x >= AutoButton.Top_Left.x && strDisplayCoordinate.x <= AutoButton.Bottom_Right.x)  &&
			(strDisplayCoordinate.y >= AutoButton.Top_Left.y && strDisplayCoordinate.y <= AutoButton.Bottom_Right.y)){
				return 2;
			}

		if( (strDisplayCoordinate.x >= UpButton.Top_Left.x && strDisplayCoordinate.x <= UpButton.Bottom_Right.x)  &&
			(strDisplayCoordinate.y >= UpButton.Top_Left.y && strDisplayCoordinate.y <= UpButton.Bottom_Right.y)){
				return 3;
			}

		if( (strDisplayCoordinate.x >= DownButton.Top_Left.x && strDisplayCoordinate.x <= DownButton.Bottom_Right.x)  &&
			(strDisplayCoordinate.y >= DownButton.Top_Left.y && strDisplayCoordinate.y <= DownButton.Bottom_Right.y)){
				return 4;
			}

		if( (strDisplayCoordinate.x >= PauseButton.Top_Left.x && strDisplayCoordinate.x <= PauseButton.Bottom_Right.x)  &&
			(strDisplayCoordinate.y >= PauseButton.Top_Left.y && strDisplayCoordinate.y <= PauseButton.Bottom_Right.y)){
				return 5;
			}


	}
	else{
		return 0;
	}
}



