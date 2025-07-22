/*
 * Timers.h
 *
 * Created: 7/20/2025 11:42:57 PM
 *  Author: Zyad Ayman
 */ 

/*		
	***********************************Example for using in main**************************************



int main(void) {
	// Enable global interrupts
	sei();

	Timer1ConfigType config = {
		.mode = TIMER1_MODE_CTC_OCR1A,
		.prescaler = TIMER1_PRESCALER_64,
		.interrupt_mask = TIMER1_INTERRUPT_COMPA,
		.compareA_value = 62500
	};

	Timer1_Init(&config);
	Timer1_SetCompareACallback(Toggle_LED);
	Timer1_Start();

	while (1) {
		 Main loop	
	}
}


*/





#ifndef TIMERS_H_
#define TIMERS_H_


/************************************************************************/
/*                        Registers & Bits                              */
/************************************************************************/

#define TCCR1A   (*(volatile u8*)0x4F)
#define TCCR1B   (*(volatile u8*)0x4E)
#define TCNT1H   (*(volatile u8*)0x4D)
#define TCNT1L   (*(volatile u8*)0x4C)
#define OCR1AH   (*(volatile u8*)0x4B)
#define OCR1AL   (*(volatile u8*)0x4A)
#define TIMSK    (*(volatile u8*)0x59)

#define TCNT1    (*(volatile u16*)0x4C)  /* 16-bit access	*/
#define OCR1A    (*(volatile u16*)0x4A)  /* 16-bit access	*/

/*****************************   TCCR1A – Timer/Counter1 Control Register A   *****************************/  
#define WGM10    0
#define WGM11    1
#define FOC1B    2
#define FOC1A    3
#define COM1B0   4
#define COM1B1   5
#define COM1A0   6
#define COM1A1   7

/*****************************    TCCR1B – Timer/Counter1 Control Register B   *****************************/
#define CS10     0
#define CS11     1
#define CS12     2
#define WGM12    3
#define WGM13    4
#define ICES1    6
#define ICNC1    7


/*****************************   TIMSK – Timer Interrupt Mask Register   *****************************/

#define TOIE1    2   /* Timer1 Overflow Interrupt Enable				*/
#define OCIE1A   4   /* Timer1 Output Compare A Match Interrupt Enable	*/
#define OCIE1B   3   /* Timer1 Output Compare B Match Interrupt Enable	*/
#define TICIE1   5   /* Timer1 Input Capture Interrupt Enable			*/


/************************************************************************/
/*                        Configurations                                */
/************************************************************************/


/* ----------------- Modes ----------------- */


typedef enum 
{
	TIMER1_MODE_NORMAL,
	TIMER1_MODE_CTC	
	
}Timer1_Mode;




/* ------------- Prescaler Values (CS12:0) ------------- */
typedef enum 
{		
	TIMER1_NO_CLOCK,
	TIMER1_PRESCALER_1,
	TIMER1_PRESCALER_8,
	TIMER1_PRESCALER_64,
	TIMER1_PRESCALER_256,
	TIMER1_PRESCALER_1024,
	TIMER1_EXT_FALLING,
	TIMER1_EXT_RISING
}Timer1_Prescalers;




/* ------------- Interrupts (TIMSK Bits) ------------- */

typedef enum
{
	TIMER1_INTERRUPT_DISABLED,
	TIMER1_INTERRUPT_ENABLED
	
}Timer1_Interrupt_Mode;

#define TIMER1_INTERRUPT_NONE      0
#define TIMER1_INTERRUPT_OVERFLOW  (1 << TOIE1)
#define TIMER1_INTERRUPT_COMPA     (1 << OCIE1A)


/* ------------ Configuration Struct ------------ */


typedef struct 
{
	Timer1_Mode Mode;
	Timer1_Interrupt_Mode Interrupt_timer1 ;
	
}Timer1_Configurations;


/************************************************************************/
/*                        Functions Prototypes                          */
/************************************************************************/

void TIMER1_vInit(const Timer1_Configurations* Config);


void TIMER1_vStart(Timer1_Prescalers Prescaler_Value);

void TIMER1_vStop(void);



void TIMER1_vSetValueNormalMode(u16 value);
u16 TIMER1_u16GetValue(void);



void TIMER1_vSetValueCompareCTC(u16 value);



void TIMER1_vSetOverflowCallback(void (*callback)(void));
void TIMER1_vSetCompareCTCCallback(void (*callback)(void));



#endif /* TIMERS_H_ */

