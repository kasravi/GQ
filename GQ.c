#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Morteza");
MODULE_DESCRIPTION("I just done this for free condoms :)");

#define GOAL 		70000000
#define CHILDEVERYMONTH 2
#define MAXWORKINGTIME  6
#define REVENUETIME  	4
#define CHILDMARGIN	6

///////////

long long pop=0;
long long richpop=0;

typedef struct cell{
        char time;
		char childnum;
        struct cell * child[MAXWORKINGTIME*CHILDEVERYMONTH];
        }cell;

cell *allcell;

bool memoryallocatecells(void)
{
if ( NULL == (allcell = vmalloc((GOAL)*sizeof(cell)) )) {
		  printk("Not Enought Memory\n");
		  return true;
		}

return false;
}
cell* initCell(void)
{
pop++;
	cell* pcell;
	pcell = &allcell[pop-1];
	pcell->time=0;
	pcell->childnum=0;
	return pcell;
}
bool reachGoal(void)
{
	
	if (pop>=GOAL)
		return true;
	return false;
}
bool addChild(cell* pcell )
{
	
	if(pcell->childnum==MAXWORKINGTIME*CHILDEVERYMONTH)
		return false;
	cell* ch = initCell();
	if(ch==NULL)
		return true;
	pcell->child[pcell->childnum] = ch;
	pcell->childnum++;

	if(reachGoal()) return true; else return false;
}
bool act(cell* pcell)
{
	
	int i =0;
	for(i=0;i<CHILDEVERYMONTH;i++)
		if(addChild(pcell)) return true;
	if(pcell->childnum>=CHILDMARGIN)
	pcell->time++;
	return false;
}
bool recursive(cell* pcell)
{
	int i=0;
	for(i=0;i<MAXWORKINGTIME*CHILDEVERYMONTH;i++)
	{
		if(i<pcell->childnum)
		{if(recursive(pcell->child[i])) return true;}
		else
		{
			if(act(pcell)) return true;
			break;
		}
	}
if(pcell->time>=REVENUETIME)
		richpop++;
	
	return false;
}

///////////

static int __init GQ_init(void)
{
if(memoryallocatecells())
	return 0;

  cell* pcell = initCell();
  int i=0;
  for(;;)
  {
	

	if(recursive(pcell)) break;

	printk("after %d months -> Population: %d, rich ones: %d, ratio: %d%\n",i,(int)pop,(int)richpop,(int)(100*(float)richpop/(float)pop));

	i++;
	
  }


vfree(allcell);
  printk("after %d months -> Population: %d, rich ones: %d, ratio: %d%\n",i,(int)pop,(int)richpop,(int)(100*(float)richpop/(float)pop));
	
  return 0;
}

static void __exit GQ_cleanup(void)
{

    printk(KERN_INFO "Cleaning up module.\n");

}



module_init(GQ_init);
module_exit(GQ_cleanup);
