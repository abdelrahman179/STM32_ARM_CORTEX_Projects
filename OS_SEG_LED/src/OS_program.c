/******************************************************/
/* Author : AbdElrahman I.Zaki                        */
/* Date   : 07 September 2020                         */
/* Version: V01                                       */
/* Desc.  : Operating System Program File             */
/******************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_interface.h"

#include "OS_interface.h"
#include "OS_private.h"
#include "OS_config.h"

/* Array of tasks where the index of each element is the task priority */
/* static as the array won't be used in the main.c file */
static Task_TCB OS_Tasks[NUM_OF_TASKS] = {NULL};

void OS_voidStart(void)
{
    /* Systick Initialization */
	MSTK_voidInit();

    /* i/p: Tick Time = 1 mSec periodic 1000 uSec = 1 mSec , ISR function */
    /* Each 1mSec, call the scheduler */
	MSTK_voidSetIntervalPeriodic(TICK_TIME ,OS_voidScheduler);
}


void OS_voidSuspendTask(u8 Copy_u8TaskID)
{
	OS_Tasks[Copy_u8TaskID].State = TASK_SUSPEND;
}

void OS_voidResumeTask(u8 Copy_u8TaskID)
{
	OS_Tasks[Copy_u8TaskID].State = TASK_READY;
}

void OS_voidDeleteTask(u8 Copy_u8TaskID)
{
	OS_Tasks[Copy_u8TaskID].Task_Handler = NULL;
    OS_Tasks[Copy_u8TaskID].First_Delay  = 0   ;
    OS_Tasks[Copy_u8TaskID].Periodicity = 0   ;
}

void OS_voidCreateTask(u8 Copy_u8PriorityID, u16 Copy_u16Periodicity, void (*Copy_Task)( void ), u16 Copy_u16FirstDelay)
{
	if((OS_Tasks[Copy_u8PriorityID].Task_Handler == NULL) && (Copy_u8PriorityID < NUM_OF_TASKS))
    {
		OS_Tasks[ Copy_u8PriorityID ].Periodicity  = Copy_u16Periodicity  ;
		OS_Tasks[ Copy_u8PriorityID ].Task_Handler = Copy_Task            ;
		OS_Tasks[ Copy_u8PriorityID ].First_Delay  = Copy_u16FirstDelay   ;
		OS_Tasks[ Copy_u8PriorityID ].State        = TASK_READY           ;
	}
	else
    {
		/* Do Nothing */
	}
}

/* Ordering Tasks */
void OS_voidScheduler(void)
{
	u8 Local_u8TaskCounter;

    /* Ordering the array tasks loop */
	for(Local_u8TaskCounter = 0; Local_u8TaskCounter < NUM_OF_TASKS; Local_u8TaskCounter++)
    {
        /* Implement the tasks based on the periodicity and tick time */
        /* To assure that there is a task exists and in the ready state */
		if((OS_Tasks[Local_u8TaskCounter].Task_Handler != NULL) && (OS_Tasks[Local_u8TaskCounter].State == TASK_READY))
        {
            /* If first delay is equal to zero, execute the task */
			if(OS_Tasks[Local_u8TaskCounter].First_Delay == 0)
            {
                /* To switch the first delay to periodicity as it's used only once */
				OS_Tasks[Local_u8TaskCounter].First_Delay = OS_Tasks[Local_u8TaskCounter].Periodicity - 1;
                 /* Call the function */
				OS_Tasks[Local_u8TaskCounter].Task_Handler();
			}
			else
            {
                /* decrement the first delay */
				OS_Tasks[Local_u8TaskCounter].First_Delay--;
			}
		}
		else
        {
			/* Do Nothing */
		}
	}
}







