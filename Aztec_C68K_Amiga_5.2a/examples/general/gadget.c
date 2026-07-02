 /**************************************************************************
 *     F U N   W I T H   G A D G E T S
 *
 ***************************************************************************/
 #include <exec/types.h>
 #include <exec/nodes.h>
 #include <exec/lists.h>
 #include <exec/ports.h>
 #include <exec/devices.h>
 #include <devices/keymap.h>
 #include <graphics/regions.h>
 #include <graphics/copper.h>
 #include <graphics/gels.h>
 #include <graphics/gfxbase.h>
 #include <graphics/gfx.h>
 #include <graphics/clip.h>
 #include <graphics/view.h>
 #include <graphics/rastport.h>
 #include <graphics/layers.h>
 #include <intuition/intuition.h>
 #include <hardware/blit.h>
  
 /***************************************************************************
         IMPORTANT CONSTANTS
 ***************************************************************************/
 unsigned int mask = 0;            /*  ONE BIT SET FOR EACH OPEN */
  
 #define  INTUITION   0x00000001
 #define  GRAPHICS    0x00000002
 #define  SCREEN      0x00000004
 #define  WINDOW      0x00000008
 #define  COLORMAP    0x00000010
 #define  MATH        0x00000020
 #define  MATHTRANS   0x00000040
  
 #define NL 0
  
 /***************************************************************************
 *          I N T U I T I O N      G L O B A L      V A R S
 ***************************************************************************/
  
 struct IntuitionBase *IntuitionBase;
 struct GfxBase *GfxBase;
 struct IntuiMessage *message;
 struct RastPort *rp;
 struct Window *w;
  
 /***************************************************************************
             G A D G E T S      L I V E      H E R E
 ***************************************************************************/
  
 /*  Image for a custom proportional gadget */
  
 UWORD custimage[] = {
 0x0000, 0x0000, 0x0180, 0x0660, 0x1818, 0x2004, 0x4002, 0x4002,
 0x4002, 0x4002, 0x2004, 0x1818, 0x0660, 0x0180, 0x0000, 0x0000
 };
  
 struct Image cus_image = {
   0, 0,                    /* LeftEdge, TopEdge */
   16, 16, 1,               /* Width, Height, Depth */
   &custimage[0],           /* Pointer to bit image */
   1,  0,                   /* PlanePick, Planeonoff */
   NULL                     /* No other images */
 };
  
  
 struct IntuiText rtxt = {2,2,JAM1,-9,2,NL,(UBYTE *)"R",NL};
 struct IntuiText gtxt = {2,2,JAM1,-9,2,NL,(UBYTE *)"G",NL};
 struct IntuiText btxt = {2,2,JAM1,-9,2,NL,(UBYTE *)"B",NL};
  
 struct IntuiText ntext = {2,2,JAM1, 10, -11, NL,
   (UBYTE *) "Number entry", NL};
  
 struct IntuiText cus_text = {2,2,JAM1, 2, -11, NL,
   (UBYTE *) "Custom Prop Gadget", NL};
  
 struct IntuiText cus1_txt = {2,2,JAM1, 161, 23, NL,
   (UBYTE *) "Vert side", &cus_text };
  
 struct IntuiText cus2_txt = {2,2,JAM1, 20, 50, NL,
   (UBYTE *) "Hor side", &cus1_txt };
  
 struct IntuiText bool_str = {2,2,JAM1, 4, 1, NL,
   (UBYTE *) "START", NL };
  
 struct IntuiText bool2_str = {2,2,JAM1, 9, 1, NL,
   (UBYTE *) "STOP", NL };
  
 struct Image    r_img, g_img, b_img;
 struct PropInfo r_prop,g_prop,b_prop;
  
 struct PropInfo cust_prop = {
    FREEHORIZ | FREEVERT,            /* Want knob to go both vert and horiz */
    0x8000,  0x8000,                 /* Want knob to be centered initially  */
    0x800,   0x800,                  /* Smallest increment the knob can move */
    150, 50,                         /* cWidth, cHeight - Container w & h */
    1, 1,                            /* HPosres, VPotres - Pot increments */
    0, 0                             /* Container borders  */
 };
  
  
 #define STRINGSIZE 512
 UBYTE DefString[STRINGSIZE] = "000000000000";
 UBYTE Undo [STRINGSIZE];
  
 struct StringInfo TexString = {
    DefString,                      /* Buffer - Pointer to Buffer */
    Undo,                           /* UndoBuffer - Undo buf ptr  */
    0,                              /* BufferPos - Init Chr Posn */
    STRINGSIZE,                     /* MaxChars - Max number of Chars */
    0, 0,                           /* DispPos - First Disp Chr */
    13,                             /* NumChars - Number of Characters */
    0, 0, 0,                        /* Posn Vars calc by Intuition */
    NULL,                           /* No pointer to Rasport */
    0,                              /* Longint Value */
    NULL                            /* No pointer to alt Keyboard */
 };
  
 SHORT Pairs[] = {
 -1,  -1,                            /* Information describing the */
 160, -1,                           /* border around the gadget */
 160, 9,
 -1, 9,
 -1, -1
  };
  
 SHORT Pairs1[] = {
  0,  0,
 51,  0,
 51, 11,
 0,  11,
 0,  0
 };
  
 #define NUM_PAIRS 5                /* There are Four pairs above */
  
 struct Border StrBorder = {
  -1, -1,                           /* LeftEdge, TopEdge */
  1, 0, JAM1,                       /* FrontPen,  BackPen  DrawMode  */
  NUM_PAIRS,                        /* Number of XY Pairs */
  Pairs,                      /* XY, Pointer to XY Pairs */
  NULL                              /* No more borders */
 };
  
 struct Border butt_border = {
  -1, -1,
  1, 0, JAM1,
  NUM_PAIRS,
  Pairs1,
  NULL
 };
  
 #define BLUE_GADGET 0
 struct Gadget blue_gad = {
    NL, 17,112, 150,11, GADGHCOMP, GADGIMMEDIATE | RELVERIFY,
    PROPGADGET,(APTR)&b_img, NL,
    &btxt, NL,(APTR)&b_prop, BLUE_GADGET, NL
 };
  
  
 #define GREEN_GADGET 1        /* Another personal ID */
 struct Gadget green_gad = {
    &blue_gad, 17,97, 120,11, GADGHCOMP, GADGIMMEDIATE | RELVERIFY,
    PROPGADGET,(APTR)&g_img, NL,
    &gtxt, NL,(APTR)&g_prop, GREEN_GADGET, NL
 };
  
  
 #define RED_GADGET 2          /* And yet another gadget */
 struct Gadget red_gad = {
    &green_gad, 17,82, 90,11, GADGHCOMP, GADGIMMEDIATE | RELVERIFY,
    PROPGADGET,(APTR)&r_img, NL,
    &rtxt, NL,(APTR)&r_prop, RED_GADGET, NL
 };
  
  
 #define TEX_GAD 3
 struct Gadget tex_gad = {
    &red_gad, 30, 30, 150,11, GADGHCOMP, STRINGCENTER | LONGINT | RELVERIFY,
    STRGADGET, (APTR)&StrBorder, NL,
    &ntext, NL, (APTR)&TexString, TEX_GAD, NL
 };
  
 #define CUST_KNOB 4
 struct Gadget cust_knob = {
    &tex_gad, 17, 140, 150, 50, GADGHCOMP, GADGIMMEDIATE | RELVERIFY,
    PROPGADGET, (APTR)&cus_image, NL,
    &cus2_txt, NL, (APTR)&cust_prop, CUST_KNOB, NL
 };
  
 #define BOOL_GAD1 5
 struct Gadget bool_gad = {
    &cust_knob, 30, 46, 50, 10, GADGHCOMP, GADGIMMEDIATE | RELVERIFY,
    BOOLGADGET, (APTR)&butt_border, NL,
    &bool_str, NL, NL, BOOL_GAD1, NL
 };
  
 #define BOOL_GAD2 6
 struct Gadget bool2_gad = {
   &bool_gad, 30, 60, 50, 10, GADGHCOMP, GADGIMMEDIATE | RELVERIFY,
   BOOLGADGET, (APTR)&butt_border, NL,
   &bool2_str,  NL, NL, BOOL_GAD2, NL
 };
  
 /***************************************************************************
 *                  N E W     W I N D O W     S T R U C T U R E
 ***************************************************************************/
  
 struct NewWindow nw = {
   0, 0,                  /*  Start position                               */
   320, 200,              /*  width, height,                               */
   0, 1,                  /*  detail, block pens                           */
   CLOSEWINDOW            /*  IDCMP flags                             */
 | REFRESHWINDOW
 | MOUSEBUTTONS
 | MOUSEMOVE
 | GADGETDOWN
 | GADGETUP,
                          /*  Regular flags for gadgets and such           */
   WINDOWDEPTH
 | WINDOWSIZING
 | WINDOWDRAG
 | REPORTMOUSE
 | WINDOWCLOSE
 | SMART_REFRESH,
  
   &bool2_gad,             /* First gadget in list                          */
   NULL,                  /* User checkmark                                */
   (UBYTE *)"Fun with Gadgets",    /* Window Title                         */
   NULL,                  /* Pointer to screen (Set later)                 */
   NULL,                  /* Pointer to superbitmap                        */
   0, 0, 320, 186,        /* Ignored because not sizeable                  */
   WBENCHSCREEN,          /* Using the Workbench screen                    */
   };
  
 /***************************************************************************
                  M A I N     P R O G R A M     M O D U L E
 ***************************************************************************/
 main()
 {
    ULONG MessageClass;
    USHORT code;
    int good_boy = FALSE;     /*  Be a "Bad boy", and hog the system  **/
	void *OpenLibrary();
	struct Window *OpenWindow();
	struct Message *GetMsg();
  
 /***************************************************************************
            Must Initialize the Proportional "Specialinfo" before
       opening up the window.   Init Flags,  and position.
 ***************************************************************************/
  
    r_prop.Flags = g_prop.Flags = b_prop.Flags = FREEHORIZ | AUTOKNOB;
    r_prop.HorizBody = g_prop.HorizBody = b_prop.HorizBody = 0x1000;
    r_prop.HorizPot = g_prop.HorizPot = b_prop.HorizPot = 0x8000;
  
 /***************************************************************************
            Read in the ligraries,  and set each "read" mask bit.
 ***************************************************************************/
  
    if(!(GfxBase = (struct GfxBase *)OpenLibrary("graphics.library",0L)))
    {
       printf("no graphics library!!!\n");
       close_things();
       exit(1);
    }
    mask |= GRAPHICS;
  
  if(!(IntuitionBase = (struct IntuitionBase *)
        OpenLibrary("intuition.library",0L)))
    {
       printf("no intuition here!!\n");
       close_things();
       exit(2);
    }
    mask |= INTUITION;
  
 /***************************************************************************
                 OPEN UP THE WINDOW ON TOP OF WORKBENCH SCREEN
 ***************************************************************************/
  
    if (!(w = (struct Window *)OpenWindow(&nw) ))
    {
       printf("could not open the window\n");
       close_things();
       exit(3);
    }
    mask |= WINDOW;
  
 /***************************************************************************
                  INITIALIZATION BEFORE ENTERING MAIN LOOP
 ***************************************************************************/
  
    rp = w->RPort;
    RefreshGadgets(&red_gad,w,NULL);
  
 /***************************************************************************
                             MAIN EVENT LOOP
 ***************************************************************************/
  
    for (;;)
    {
  
       if (message = (struct IntuiMessage *)GetMsg(w->UserPort))  {
         MessageClass = message->Class;
         code = message->Code;
         ReplyMsg(message);
         switch (MessageClass) {
  
            case GADGETUP    :
            case GADGETDOWN  : do_gadgets(message, w);
                               break;
  
            case CLOSEWINDOW : close_things();
                               exit(0);
                               break;
            case MOUSEBUTTONS: break;
         }   /* Case */
       }  /* if */
    }  /* for */
 } /* main */
 /***************************************************************************
                            HANDLE THE GADGETS
 ***************************************************************************/
 do_gadgets (mes, win)
  
 struct IntuiMessage *mes;
 struct Window *win;
 {
         struct Gadget *igad;     /* Ptr to gadget that Intuition found    */
         int  gadgid;             /* ID Code identifying which gadget      */
         ULONG val;
  
      igad = (struct Gadget *) mes->IAddress;      /* Ptr to a gadget      */
         gadgid = igad->GadgetID;    /* My own personal code for this gad  */
         val = (ULONG)TexString.LongInt;
         switch(gadgid) {
  
             case GREEN_GADGET: break;
             case BLUE_GADGET : break;
             case TEX_GAD     : printf("got here ...\n");
                                printf("val = %ld\n", val);
                                break;
         }
 }
  
  
 /***************************************************************************
                           CLOSE EVERYTHING DOWN
 ***************************************************************************/
  
 close_things()
 {
    if (mask & WINDOW)    CloseWindow(w);
    if (mask & GRAPHICS)  CloseLibrary(GfxBase);
     OpenWorkBench();
    if (mask & INTUITION) CloseLibrary(IntuitionBase);
 }
  

