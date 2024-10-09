/* Xinu for STM32
 *
 * Original license applies
 * Modifications for STM32 by Robin Krens
 * Please see LICENSE and AUTHORS 
 * 
 * $LOG$
 * 2019/11/11 - ROBIN KRENS
 * Initial version 
 * 
 * $DESCRIPTION$
 *
 * */

/* initialize.c - nulluser, sysinit */

/* Handle system initialization and become the null process */

#include <xinu.h>
#include <gpio.h>
#include "disk.h"
#include "fat_filelib.h"
 
extern	void	start(void);	/* Start of Xinu code			*/
extern	void	*_end;		/* End of Xinu code			*/

/* Function prototypes */
extern void meminitcc();
extern	void main(void);	/* Main is the first process created	*/
static	void sysinit(); 	/* Internal system initialization	*/
extern	void meminit(void);	/* Initializes the free memory list	*/
 
/* Declarations of major kernel variables */
 
struct	memblk	memlist;	/* List of free memory blocks		*/
struct	memblkcc	memlistcc;	/* List of free memory blocks		*/

/* Active system status */

 
 
int  initFat32(){
	uint32 size=sd_init();
    fl_init();
      // Attach media access functions to library
	if (fl_attach_media(sd_readsector, sd_writesector) != FAT_INIT_OK)
	{
	      printf("ERROR: Failed to init file system\n");
	      return -1;
	}
    //printf("fat32 (%d) %d\n",512,size);
  // List the root directory
    fl_listdirectory("/");
    return OK;
}



 


extern bool uart_available(void);
extern char uart_get();
void	nulluser()
{	
	struct	memblk	*memptr;	/* Ptr to memory block		*/
	uint32	free_mem;		/* Total amount of free memory	*/

    hw_cfg_pin(GPIOx(GPIO_A),8,GPIOCFG_MODE_OUT | GPIOCFG_OSPEED_VHIGH  | GPIOCFG_OTYPE_PUPD | GPIOCFG_PUPD_PUP);
    hw_cfg_pin(GPIOx(GPIO_A),0,GPIOCFG_MODE_INP | GPIOCFG_OSPEED_VHIGH  | GPIOCFG_OTYPE_OPEN | GPIOCFG_PUPD_PUP);

    meminit();
    meminitcc();

	  platinit();
    /* Enable interrupts */
	  enable();

	/* Initialize the system */
   
    while(1){

        if(!hw_get_pin(GPIOx(GPIO_A),0) || uart_available()){
            break;
        }
        
        hw_toggle_pin(GPIOx(GPIO_A),8);
        delay(50);
    }
 
	/* Output Xinu memory layout */
	free_mem = 0;
	for (memptr = memlist.mnext; memptr != NULL;
						memptr = memptr->mnext) {
		free_mem += memptr->mlength;
	}
	kprintf ("Build date: %s %s\n\n", __DATE__, __TIME__);
	kprintf("%10d bytes of free memory.  Free list:\n", free_mem);
	for (memptr=memlist.mnext; memptr!=NULL;memptr = memptr->mnext) {
	    kprintf("           [0x%08X to 0x%08X]\n",
		(uint32)memptr, ((uint32)memptr) + memptr->mlength - 1);
	}

	kprintf("%10d bytes of Xinu code.\n",
		(uint32)&_etext - (uint32)&_text);
	kprintf("           [0x%08X to 0x%08X]\n",
		(uint32)&_text, (uint32)&_etext - 1);
	kprintf("%10d bytes of data.\n",
		(uint32)&_ebss - (uint32)&_sdata);
	kprintf("           [0x%08X to 0x%08X]\n\n",
		(uint32)&_sdata, (uint32)&_ebss - 1);
 
	  
	for(;;);

}

/* Startup does a system call, the processor switches to handler 
 * mode and prepares for executing the null process (see syscall.c) 
 * This is also where a kernel mode to user mode switch can
 * take place */


/*------------------------------------------------------------------------
 *
 * sysinit  -  Initialize all Xinu data structures and devices
 *
 *------------------------------------------------------------------------
 */

 
int32	stop(char *s)
{
	kprintf("%s\n", s);
	kprintf("looping... press reset\n");
	while(1)
	;
}

 
 