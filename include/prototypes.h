
//#include <stdio.h>

 
void	meminit(void);

syscall	freememcc(
	  char		*blkaddr,	/* Pointer to memory block	*/
	  uint32	nbytes		/* Size of block in bytes	*/
	);

char  	*getmemcc(
	  uint32	nbytes		/* Size of memory requested	*/
	);

char  	*getstkcc(
	  uint32	nbytes		/* Size of memory requested	*/
	);
 
/* in file freemem.c */
extern	syscall	freemem(char *, uint32);


/* in file getmem.c */
extern	char	*getmem(uint32);


/* in file panic.c */
extern	void	panic(char *);

/* in file pci.c */
//extern	int32	pci_init(void);

/* in file pdump.c */
//extern	void	pdump(struct netpacket *);
//extern	void	pdumph(struct netpacket *);

/* in file platinit.c */
extern	void	platinit(void);

