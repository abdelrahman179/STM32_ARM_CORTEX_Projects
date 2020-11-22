/*********************************************************/
/* Author : AbdElrahman I.Zaki                           */
/* Date   : 07 September 2020                            */
/* Version: V01                                          */
/* Desc.  : Operating System Public Functions prototypes */
/*********************************************************/

#ifndef OS_INTERFACE_H
#define OS_INTERFACE_H

/** Pre conditions :
	1 - No other module use STK driver
	2 - STK drivers files must be included in the project
	3 - Number of tasks must be configured  ( OS_NUMBER_OF_TASKS )
	4 - Clock must be selected right in STK driver to ensure right time
	5 - OS_voidStart must be called before while
	6 - OS_voidDispatcher must be called in the while
	7 - Global interrupt must be active
**/

/* Task States */
typedef enum
{
	TASK_READY   ,
	TASK_SUSPEND ,
}Task_States;

/* Start the OS and the scheduler */
void OS_voidStart(void);

/* OS_voidCreateTask - > Create a new task noting that maximum number of tasks is limited by
						the config parameter (NUM_OF_TASKS)
   I / P : Task Priority ID,  First delay of the first invoke of the function (u16)
			Period of the task (u16) Task function "implementation" */
void OS_voidCreateTask( u8 Copy_u8PriorityID , u16 Copy_u16Periodicity , void (*Copy_Task)( void ) , u16 Copy_u16FirstDelay);
/* Resume Task: change the state to suspend "pause" */
void OS_voidSuspendTask(u8 Copy_u8TaskID);
/* Resume Task: change the state back to ready */
void OS_voidResumeTask(u8 Copy_u8TaskID);
/* Delete Task: delete the task permanently from the scheduler */
void OS_voidDeleteTask(u8 Copy_u8TaskID);






#endif
