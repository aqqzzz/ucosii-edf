/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*                          (c) Copyright 2009-2011; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                          APPLICATION CODE
*
*                                          Microsoft Windows
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : JJL
*                 FGK
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>



/*-----------------------------------------------------------------------------------------------------
my definitions
-------------------------------------------------------------------------------------------------------
*/

#define          TASK_STK_SIZE     512

/*---   priorities ---*/
#define TASK_1_PRIO		21
#define TASK_2_PRIO		22


/*---   task IDs ---*/
#define TASK_1_ID		1
#define TASK_2_ID		2


/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            LOCAL VARIABLES
*********************************************************************************************************
*/

static  CPU_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];

/*------------------------------------------------------------------------------------------------------
my variables
--------------------------------------------------------------------------------------------------------
*/

/*---   stacks ---*/
OS_STK TASK1STK[TASK_STK_SIZE];
OS_STK TASK2STK[TASK_STK_SIZE];
OS_STK TASK3STK[TASK_STK_SIZE];
OS_STK TASK4STK[TASK_STK_SIZE];
OS_STK TASK5STK[TASK_STK_SIZE];

/*---   edf_datas ---*/
// EDF_DATA{c_value,p_value,comp_time,ddl,start,end]
EDF_DATA edf_datas[] =
{
	{ 1,3,1,4,1,1 },
	{ 3,5,3,6,1,1 },

};


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskStart(void  *p_arg);

/*------------------------------------------------------------------------------------------------------
my function prototypes
--------------------------------------------------------------------------------------------------------
*/
static void task1(void* pdata);
static void task2(void* pdata);


/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

int  main(void)
{
	OSInit();                                                   /* Init uC/OS-II.                                       */

																//  OSTaskCreateExt((void(*)(void *))AppTaskStart,                                            */
																//        (void          *) 0,
																//        (OS_STK        *)&AppTaskStartStk[APP_TASK_START_STK_SIZE - 1],
																/**        (INT8U          ) APP_TASK_START_PRIO,
																(INT16U         ) APP_TASK_START_PRIO,
																(OS_STK        *)&AppTaskStartStk[0],
																(INT32U         ) APP_TASK_START_STK_SIZE,
																(void          *) 0,
																(INT16U         )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
																**/
	OSTaskCreateExt((void(*)(void *))task1,
		(void          *)0,
		(OS_STK		   *)&TASK1STK[TASK_STK_SIZE - 1],
		(INT8U)TASK_1_PRIO,
		(INT16U)TASK_1_ID,
		(OS_STK        *)&TASK1STK[0],
		(INT32U)TASK_STK_SIZE,
		(void          *)&edf_datas[0],
		(INT16U)0);

	OSTaskCreateExt((void(*)(void *))task2,
		(void          *)0,
		(OS_STK		   *)&TASK2STK[TASK_STK_SIZE - 1],
		(INT8U)TASK_2_PRIO,
		(INT16U)TASK_2_ID,
		(OS_STK        *)&TASK2STK[0],
		(INT32U)TASK_STK_SIZE,
		(void          *)&edf_datas[1],
		(INT16U)0);

	OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II).  */
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Argument(s) : p_arg       is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Note(s)     : (1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                   used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart(void *p_arg)
{
	OS_ERR  err;


	(void)p_arg;

	BSP_Init();                                                 /* Initialize BSP functions                             */
	CPU_Init();                                                 /* Initialize uC/CPU services                           */

#if OS_CFG_STAT_TASK_EN > 0u
	OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif
	APP_TRACE_DBG(("uCOS-II is Running...\n\r"));

	while (DEF_ON) {                                            /* Task body, always written as an infinite loop.       */
																//OSTimeDlyHMSM(0, 0, 1, 0);
		OSTimeDly(3);

		APP_TRACE_DBG(("\n\r#Time: %d", OSTimeGet(&err)));
	}
}

static void task1(void *pdata) {
	INT32U start;
	INT32U end;
	INT32U to_delay;
	OSTimeDly(1);
	start = 0;
	for (;;) {
		while (((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->comp_time>0) {
			//do nothing
		}
		OS_ENTER_CRITICAL();
		APP_TRACE("\n @@@@@@@@@ in task1");
		//end=OSTimeGet();
		//to_delay=((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->p_value-(end-start);
		//start=start+((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->p_value;
		//((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->comp_time=((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->c_value;
		//((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->ddl=((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->ddl+((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->p_value;
		OS_EXIT_CRITICAL();
		//OSTimeDly(to_delay);


	}
}

static void task2(void* pdata) {
	INT32U start;
	INT32U end;
	INT32U to_delay;
	//BSP_Init();
	//CPU_Init();
	start = 0;
	OSTimeDly(1);
	for (;;) {
		while (((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->comp_time>0) {
			//do nothing
		}
		OS_ENTER_CRITICAL();
		APP_TRACE("\n @@@@@@@@ in task2");
		//end=OSTimeGet();
		//to_delay=((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->p_value-(end-start);
		//start=start+((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->p_value;
		//((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->comp_time=((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->c_value;
		//((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->ddl=((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->ddl+((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->p_value;
		OS_EXIT_CRITICAL();
		//OSTimeDly(to_delay);

	}
}