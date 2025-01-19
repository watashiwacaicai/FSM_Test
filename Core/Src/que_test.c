#include "./Cqueue/cQueue.h"
#include "./Malloc/malloc.h"
#include "./OLED/OLED.h"

cQueue_t* te_que;
char ol_ou;
char ks = 'a';
char* ol_ot;
char ol_ot_st[10];
char* err;

void qe_add(void)
{
	char* to_add = (char*)mymalloc(SRAMCCM, sizeof(char));
	*to_add = ks;
	cQPost(te_que, (void*)to_add);
}

void que_te(void)
{
	te_que = cQcreate(20);
	
	for(int i = 0; i < 10; i++)
	{
		qe_add();
		ks++;
	}
	
	for(int i = 0; i < 10; i++)
	{		
		ol_ot = (char*)cQRcv(te_que, err);	
		ol_ot_st[i] = *ol_ot;
		myfree(SRAMCCM, ol_ot);
	}
	
	OLED_ShowString(0, 20, ol_ot_st, OLED_8X16);
}
