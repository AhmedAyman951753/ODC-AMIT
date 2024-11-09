/*
 * KEYPAD_prog.c
 *
 * Created: 8/23/2024 2:58:21 PM
 *  Author: AMIT
 */ 
#include "../../LIB/BIT_MATH.h" 
#include "../../LIB/STD_TYPE.h" 
#include "../../MCAL/DIO/DIO_interface.h" 
#include "KEYPAD_config.h"


u8 keypad_arr[4][4]={ {7,8,9,'/'},
	                  {4,5,6,'*'},
					  {1,2,3,'-'},
					  {'c',0,'=','+'}	} ;   
					  	  	   
	                  



void KEYPAD_voidInit(void){
	
	 u8 COL_arr[4]={KEYPAD_COL0_PIN,KEYPAD_COL1_PIN,KEYPAD_COL2_PIN,KEYPAD_COL3_PIN} ; 
	u8  ROW_arr[4]={KEYPAD_ROW0_PIN,KEYPAD_ROW1_PIN,KEYPAD_ROW2_PIN,KEYPAD_ROW3_PIN} ; 	 
	
	u8 LOC_row=0 ; 
	u8 LOC_col=0 ; 
	
	for (LOC_row=0 ,LOC_col=0 ; LOC_row<4 && LOC_col<4 ;LOC_row++,LOC_col++)
	{
		 /* make all rows as input */
		DIO_voidSetPinDir(KEYPAD_ROWPORT,ROW_arr[LOC_row],INPUT) ; 
		/* enable internal pull up */
		DIO_voidSetPinVal(KEYPAD_ROWPORT,ROW_arr[LOC_row],HIGH) ; 
		
    	 /* make all col as  output */
    	 DIO_voidSetPinDir(KEYPAD_COLPORT,COL_arr[LOC_col],OUTPUT) ;
    	 /*  set all col as HIGH  */
    	 DIO_voidSetPinVal(KEYPAD_COLPORT,COL_arr[LOC_col],HIGH) ;
		
		
	}

	

	
}

u8 KEYPAD_u8GetKey(void){
		 u8 COL_arr[4]={KEYPAD_COL0_PIN,KEYPAD_COL1_PIN,KEYPAD_COL2_PIN,KEYPAD_COL3_PIN} ;
		 u8  ROW_arr[4]={KEYPAD_ROW0_PIN,KEYPAD_ROW1_PIN,KEYPAD_ROW2_PIN,KEYPAD_ROW3_PIN} ;
		 
		 u8 LOC_row=0 ;
		 u8 LOC_col=0 ;
		 u8 loc_val=0xff ; 
		 
		 for (LOC_col=0 ; LOC_col<4 ;LOC_col++)
		 {
			 /* set col(num) as low */
          DIO_voidSetPinVal(KEYPAD_COLPORT,COL_arr[LOC_col],LOW) ;
		  
		  for (LOC_row=0 ; LOC_row<4 ;LOC_row++)
		  {
			   /* check if any button is pressed */
			  if (DIO_u8ReadpinVal(KEYPAD_ROWPORT, ROW_arr[LOC_row])==0)
			  {
				  loc_val=keypad_arr[LOC_row][LOC_col] ; 
				  while(DIO_u8ReadpinVal(KEYPAD_ROWPORT, ROW_arr[LOC_row])==0) ; 
				  
				  return loc_val  ; 
				   
				  
				  
			  }
			  
			  
		  }
			  /* set col(num) as high */
			  DIO_voidSetPinVal(KEYPAD_COLPORT,COL_arr[LOC_col],HIGH) ;
			 
			 
			 
			 
		 }
	
	
	
	
	
	
	return loc_val ; 
}


u8 ReturnKey_void(void)
{
	u8 key = 0xff;
	do
	{
		key=KEYPAD_u8GetKey() ;
		
	} while (key==0xff);
	
	return key;
}