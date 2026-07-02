COMPILER CHANGES

1/?/91	ms
	Code generated for resident library function having no arguments wasn't
	pushing A4.


1/25/91	jd
	Changed compiler so that A6 is always preserved on function entry and exit,
	when it's used by the function, even when using -R6 option.

1/28/91	jd
	When using compiler's -SN option, code generated for resident 
	library functions pushed and popped in different order.

1/29/91 kh
	Compiler required prototype to appear before a regcall pragma.

2/1/91 kh, jd
	Added code to allow regcall, etc functions to define return reg

2/1/91 jd
	Added code to allow pascal function that has args to return value in a0

2/4/91 jd
	Changed compiler to not preserve return register for regcall etc functions


2/5/91 jd
	When function whose args are in registers was compiled with -SN, 
	a return statement in the function confused compiler's notion of where
	things were on the stack.

2/5/91 jd
	Fixed code for libcall pragma to handle return reg

2/11/91 jd
	added code to verify that function arguments agree in pragmas and
	prototypes.

2/16/91 jd
	Incorporated changes for mac and 68k/rom.

2/21/91 jd
	When writing unnamed structure to precompiled header file, compiler
	wasn't leaving room for structure's null termination of name.

2/26/91 SCR 1: jd
	For the following function declaration:
		enum color f(){};
	the -qp compiler option generated the wrong prototype:
		int f(void);

3/1/91 SCR 2: jd
	libcall pragma didn't accept more than 6 args, but some toolbox calls
	take more than 6 (e.g. BltBitMap)

3/7/91 SCR 4: jd
	making assignment of two function types having different number of args
	caused strange results (e.g. enforcer hits)

3/7/91 SCR 5: jd
	when compiled w/ -f8, bad code generated for:
		register double x;
		x = 1-x;

3/7/91 SCR 6: jd
	for cross to amiga, precompiled headers didn't handle resident library
	basenames correctly.

3/13/91 SCR 7: jd
	changes made for specifying func return reg didn't allow for no args

3/15/91 SCR 8: jd
	for cross to amiga, couldn't use -R6 option 

3/17/91 SCR 9: jd
	call of registerized function that takes an argument in the 
	frame or data pointer register by a function destroys that register
	for accessing data.
	soln: don't allow registerized functions that use those registers;
	for the amiga functions that use those registers, make them call glue
	routines.

3/20/91 SCR 10: jd
	when compiled with -SN, code generated for h(register int i){...}
	accesses i from wrong spot on stack.

3/20/91 SCR 11: jd
	bad code generated for "regvar %= 10" when compiled for 020

3/21/91 SCR 12: jd
	bad code generated for assignments to bit fields when compiled for 020

3/22/91 SCR 13: jd
	bad code generated for 'if ("");'

3/22/91 SCR 14: jd
	functions that use doubles and that are compiled with -SN access args
	at wrong offset.

3/25/91 SCR 15: jd
	bad code generated for %%arg in #asm block if #asm comes before
	first executable statement in a function. soln: generate error msg

3/26/91 SCR 16: jd
	when using pre-compiled header files, comparison of #include file name
	to names in the pre-compiled file should be case-insensitive, otherwise
	the file can be included twice, once from pre-compiled file, once from
	#include statement.

4/1/91 SCR 17: jd
	added -mp option to prevent padding of structures that contain only
	chars. prevents alignment of such structures when in other structures, too.
	this is for lattice compatibility.

4/4/91 SCR 18: jd
	(1) Bad code generated for:
		 unsigned long ul=-1;
		 double d;
		 d = ul;
	    Soln required adding the following new internal math routines:
		 .Xflu to m881/xflt68.a68, mx_ieee/xflt68.a68
		 .Pflu to mx_ieee/flt68.a68, ma_ieee/pflt.a68
		 .Fflu to mx_ieee/floats.a68, ma_ieee/floats.a68, ffp/fflt.a68

	(2) When generating code for 68881 (-f8 option), incorrect code 
	    generated for:
		 ul = d;
		68881's "fmove.l fp0,d0" inst only handles signed longs.
		Soln required adding the following new internal math routines:
		 .Xfxu to m881/xflt68.a68

4/4/91 SCR 19: jd
	dumping node containing float CONST sometimes corrupted stack
	(dump.c)

4/4/91 SCR 20: jd
	d ends up with a negative number:
		double d;
		d = 0x80000000;

4/16/91 SCR 21: jd
	changed compiler so that keywords are allowed in #if's, except when
	doing strict ansi (-pa). This allows things like #if sizeof(int)==2 ...

4/17/91 SCR 22: jd
	When -MM option puts vars in code segment, compiler allowed assignments
	to such vars, but the assembler wouldn't assemble it, even when using
	large code memory model. 
	 Changed compiler so that vars that -MM forces into code segment are 
	treated as const. This allows compiler to issue an error message about 
	assignments to such vars.
	 Assembler also needs to be changed to allow assignments to vars in code
	segment, by selecting absolute addressing mode for the variable instead
	of pc-relative.

4/17/91 SCR 23: jd
	When a comment was exactly as long as the compiler's read buffer, and
	was on the last line of a file, and the line wasn't terminated by newline,
	the compiler would report an unterminated comment.

4/18/91 SCR 24: jd
	When long double declaration appears before first function and module is
	compiled with -f8, compile generates incorrect size for variable (8 instead
	of 12).

4/19/91 SCR 25: jd
	When comparing two function prototypes, compiler didn't allow one func's
	"void *" arg to match other's non-"void *" arg. That is,
		void f(void *), (*fp)(long *);
		fp = f;
	generated ptr-to-ptr conversion error. Same error for qsort's comparison
	function.

4/23/91 SCR 26: jd
	Wrong error message "error 40: internal error" generated when assigning
	a non-constant initializer to a field needing a constant initializer.
	Changed to "error 41: invalid initializer"

4/24/91 SCR 27: jd
	"Expression too complex" error message incorrectly generated after code
	generator walked expression trees in the wrong order.

4/25/91 SCR 28: jd
	Compiler using one field in the expression tree structure for multiple
	purposes, causing the compiler to generate non-optimal code for an 
	expression.

4/25/91 SCR 29: jd
	-MR option didn't affect 68881 register usage. Made it use FP3 for
	temporaries.

4/25/91 SCR 30: jd
	Modified compiler so that it detects error 168 ("can't registerize double
	argument") to the declaration of the
	function's prototype or pragma, not when the function is called.

4/25/91 SCR 31: jd
	Compiler didn't report an error when declaring a struct as argument to
	regcall-type function, just generated incorrect code.

4/26/91 SCR 32: jd
	Compiler didn't report an error for regcall-type function that returns
	double or struct.
	Added error 172 for this error.

5/6/91 SCR 33: jd
	compiler didn't report an error when redefining an enum member. e.g.
	no error on
		enum {a};
		enum {a=42};

5/6/91 SCR 34: jd
	when computing the type of a conditional expr, compiler didn't 'or'
	in the type qualifiers of the left and right operands, when both
	operands were pointers. e.g. no error was reported on
		char *cp; const char *ccp; int i;
		*(i?cp:ccp)=0;

5/7/91 SCR 35: jd
	for a conditional expr whose left and right operands were pointers,
	compiler didn't check that they were to compatible types. e.g. no error on
		char *cp; int *ip, i; void *vp;
		vp=i?cp:ip;

5/7/91 SCR 36: jd
	under ansi, two pointers that are subtracted must be of compatible types.
	the compiler only requires that they be pointers to the same sized object.
	changed compiler to issue error msg if ansi is in effect and if pointers
	aren't to compatible types; if not ansi, no change.

5/8/91 SCR 37: jd
	compiler got enforcer hit when an invalid expression was parenthesized.

5/8/91 SCR 38: jd
	compiler considered pointers to two different structures to be compatible,
	if they had different type qualifiers. e.g. no error reported for
		struct s1 {int v1;} s1; const struct s2 {char v2;} s2; int i; void *vp;
		vp = i? &s1 : &s2;

5/8/91 SCR 39: jd
	if condition of conditional expr was a constant, compiler returned the
	left or right side unchanged, without 'or'ing in the other side's type
	modifiers.

-----------------------
5/13/91 SCR 40: jd
	apparently c++ front ends can create declarations for static functions 
	which are never defined. the compiler always reported this as an error.
	changed the compiler to report this as a warning, not an error, and to
	by default not issue a message. also added a new -wf option to enable 
	this warning, and made the -wl option enable this warning.

5/16/91: SCR 41 jd
	incorrect value used inside compiler for size of __VERSION's 
	macro structure.

6/10/91: SCR 42 jd
	for 8086 host, floating point constants need to be reversed

6/11/91: SCR 43 jd
	c86 doesn't support long doubles yet, so make change to fltext68.c for cross

6/12/91: SCR 44 jd
	pre- and post-inc of float value don't work on pc cross

6/12/91: SCR 45 jd
	don't user more than eight chars in compiler source file names, for pc
	compatibility

7/16/91: SCR 46 jd
	for registerized function having return reg equal to arg reg, bad
	code is generated when moving return value into D0

9/25/91: SCR 47	jd
	add -wc option to disable ptr/ptr warning for (char *) <-> (uchar *)
