#include <exec/types.h>
#include <intuition/intuition.h>

#include <libraries/dosextens.h>

#include <functions.h>

#define I_REV   31
#define G_REV   31

#define	EWDTH	640
#define	EHGHT	198

#define	NL	NULL


struct IntuitionBase *IntuitionBase;
struct GfxBase  { int b; } *GfxBase;

struct NewScreen TS = {
	0,0,640,200,2,
	1,2,
	HIRES,	WBENCHSCREEN,
	0L, 0L, 0L
	};

/* Used to open a Window   */
struct NewWindow EdWindow = {
    0,2,EWDTH,EHGHT-2,		/* LeftEdge,TopEdge,Width,Height */
    1,2,			/* DetailPen,BlockPen	*/
    MENUPICK | NEWSIZE | REFRESHWINDOW | ACTIVEWINDOW |
	MOUSEBUTTONS | RAWKEY | MOUSEMOVE,
    WINDOWDRAG | WINDOWSIZING | SIMPLE_REFRESH | ACTIVATE | WINDOWDEPTH,
    NL,NL,(UBYTE *)"Window",		/* FirstGadget, CheckMark, Title  */
    NL,				/* Screen ( Null)	*/
    NL,				/* BitMap		*/
    150,45,32767,32767,		/* MinW, MinH, MaxW, MaxH */
    CUSTOMSCREEN };		/* Type			*/


main()
{
struct Window	*eW;
struct Screen	*eS;

struct Process	*OurTask;
struct Window	*old_pr_WindowPtr;

static char	def_name[50] = "Meps";
static char	def_dir[50] = "df1:";

    if ( ! (IntuitionBase = (struct IntuitionBase *)
	OpenLibrary((UBYTE *)"intuition.library",(long)I_REV)) ||
	! (GfxBase =(struct GfxBase *)OpenLibrary((UBYTE *)"graphics.library",
													(long)G_REV)) )
	{
	printf("Can't open libraries\n");
	exit(20);
	}

    if ( ! (eS = (struct Screen *)OpenScreen(&TS)) )
	{
	printf("Can't Open Screen!!!!!\n");
	exit(22);
	}

    EdWindow.Screen = eS;

    if ( ! (eW =(struct Window *)OpenWindow(&EdWindow)) )
	{
	CloseScreen(eS);
	printf("Can't open window...\n");
	exit(21);
	}

    /* CAUTION!!! KNOW ABOUT pr_WindowPtr before you use it!!! */

    OurTask = (struct Process *)FindTask(0L);
    old_pr_WindowPtr = (struct Window *)OurTask->pr_WindowPtr;
    OurTask->pr_WindowPtr = (APTR)eW;

    get_fname(eW,eS,"Nicht",def_name,def_dir);

    printf("File name is :%s\n",def_name);
    printf("Directory is :%s\n",def_dir);

    /* ALWAYS RESTORE pr_WindowPtr BEFORE CLOSING THE WINDOW!!! */
    OurTask->pr_WindowPtr = (APTR)old_pr_WindowPtr;

    CloseWindow(eW);
    CloseScreen(eS);
    
    CloseLibrary((struct Library *)GfxBase);
    CloseLibrary((struct Library *)IntuitionBase);
}

