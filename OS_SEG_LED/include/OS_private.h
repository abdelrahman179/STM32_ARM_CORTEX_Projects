/***********************************************************/
/* Author : AbdElrahman I.Zaki                             */
/* Date   : 07 September 2020                              */
/* Version: V01                                            */
/* Desc.  : Operating System Private Functions prototypes  */
/***********************************************************/


#ifndef OS_PRIVATE_H
#define OS_PRIVATE_H


#define NULL    ((void *) 0)

/* Task structure that contains the task details */

typedef struct
{
    u16 Periodicity;
    u16 First_Delay;
    Task_States State;   /* State, running, wait, suspense */
    void (*Task_Handler) (void);

}Task_TCB;


static void OS_voidScheduler(void);



#endif
