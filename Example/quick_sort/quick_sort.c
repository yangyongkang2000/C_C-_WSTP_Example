/*
 * This file automatically produced by wsprep from:
 *	quick_sort.tm
 * wsprep Revision 19 Copyright (c) Wolfram Research, Inc. 1990-2020
 */

#define WSPREP_REVISION 19

#include "wstp.h"

int WSAbort = 0;
int WSDone  = 0;
long WSSpecialCharacter = '\0';

WSLINK stdlink = 0;
WSEnvironment stdenv = 0;
WSYieldFunctionObject stdyielder = (WSYieldFunctionObject)0;
WSMessageHandlerObject stdhandler = (WSMessageHandlerObject)0;

extern int WSDoCallPacket(WSLINK);
extern int WSEvaluate( WSLINK, char *);
extern int WSEvaluateString P(( WSLINK, char *));

/********************************* end header *********************************/


# line 8 "quick_sort.tm"
#include<wstp.h>
static void swap(int *a,int *b)
{
	int c;
	c=*a;*a=*b;*b=c;
}
void quick_sort(int *arr,  int size)
{
      int bench,benchindex,benchindex_1=0,benchindex_2=size-1;
              if(size>=2){
				    swap(arr,arr+(size>>1));
                     benchindex=0;bench=*arr;
                      for(int index=1;index<size;index++){
                                  if(arr[index]<bench){
                                           swap(arr+index,arr+benchindex++);
                                           if(index!=benchindex)
                                               swap(arr+index,arr+benchindex); }
                      }
                      for(int i=benchindex-1;i>=0;i--){
                          if(arr[i]!=bench){
                              benchindex_1=i+1;
                              break; }
                      }
                      for(int i=benchindex+1;i<size;i++){
                                     if(arr[i]!=bench) {
                                            benchindex_2=i;
                                            break;}
                      }
                      quick_sort(arr,benchindex_1);
                      quick_sort(arr+benchindex_2,size-benchindex_2);
              }
}
void sort(int *arr,long size)
{
    quick_sort(arr,size);
    WSPutInteger32List(stdlink,arr,size);
}
int main(int argc, char *argv[])
{ 
    return WSMain(argc, argv); 
}
# line 70 "quick_sort.c"


void sort P(( int * _tp1, long _tpl1));

static int _tr0( WSLINK wslp)
{
	int	res = 0;
	int * _tp1;
	long _tpl1;
	if ( ! WSGetIntegerList( wslp, &_tp1, &_tpl1) ) goto L0;
	if ( ! WSNewPacket(wslp) ) goto L1;

	sort(_tp1, _tpl1);

	res = 1;
L1:	WSReleaseInteger32List( wslp, _tp1, _tpl1);

L0:	return res;
} /* _tr0 */


static struct func {
	int   f_nargs;
	int   manual;
	int   (*f_func)P((WSLINK));
	const char  *f_name;
	} _tramps[1] = {
		{ 1, 0, _tr0, "sort" }
		};

#define CARDOF_EVALSTRS 0

static int _definepattern P(( WSLINK, char*, char*, int));

int  _WSDoCallPacket P(( WSLINK, struct func[], int));


int WSInstall( WSLINK wslp)
{
	int _res;
	_res = WSConnect(wslp);
	if (_res) _res = _definepattern(wslp, (char *)"sort[arr_List]", (char *)"{arr}", 0);
	if (_res) _res = WSPutSymbol( wslp, "End");
	if (_res) _res = WSFlush( wslp);
	return _res;
} /* WSInstall */


int WSDoCallPacket( WSLINK wslp)
{
	return _WSDoCallPacket( wslp, _tramps, 1);
} /* WSDoCallPacket */

/******************************* begin trailer ********************************/

#ifndef EVALSTRS_AS_BYTESTRINGS
#	define EVALSTRS_AS_BYTESTRINGS 1
#endif


#if CARDOF_EVALSTRS
static int  _doevalstr( WSLINK wslp, int n)
{
	long bytesleft, charsleft, bytesnow;
#if !EVALSTRS_AS_BYTESTRINGS
	long charsnow;
#endif
	char **s, **p;
	char *t;

	s = (char **)evalstrs;
	while( n-- > 0){
		if( *s == 0) break;
		while( *s++ != 0){}
	}
	if( *s == 0) return 0;
	bytesleft = 0;
	charsleft = 0;
	p = s;
	while( *p){
		t = *p; while( *t) ++t;
		bytesnow = t - *p;
		bytesleft += bytesnow;
		charsleft += bytesnow;
#if !EVALSTRS_AS_BYTESTRINGS
		t = *p;
		charsleft -= WSCharacterOffset( &t, t + bytesnow, bytesnow);
		/* assert( t == *p + bytesnow); */
#endif
		++p;
	}


	WSPutNext( wslp, WSTKSTR);
#if EVALSTRS_AS_BYTESTRINGS
	p = s;
	while( *p){
		t = *p; while( *t) ++t;
		bytesnow = t - *p;
		bytesleft -= bytesnow;
		WSPut8BitCharacters( wslp, bytesleft, (unsigned char*)*p, bytesnow);
		++p;
	}
#else
	WSPut7BitCount( wslp, charsleft, bytesleft);
	p = s;
	while( *p){
		t = *p; while( *t) ++t;
		bytesnow = t - *p;
		bytesleft -= bytesnow;
		t = *p;
		charsnow = bytesnow - WSCharacterOffset( &t, t + bytesnow, bytesnow);
		/* assert( t == *p + bytesnow); */
		charsleft -= charsnow;
		WSPut7BitCharacters(  wslp, charsleft, *p, bytesnow, charsnow);
		++p;
	}
#endif
	return WSError( wslp) == WSEOK;
}
#endif /* CARDOF_EVALSTRS */


static int  _definepattern( WSLINK wslp, char *patt, char *args, int func_n)
{
	WSPutFunction( wslp, "DefineExternal", (long)3);
	  WSPutString( wslp, patt);
	  WSPutString( wslp, args);
	  WSPutInteger( wslp, func_n);
	return !WSError(wslp);
} /* _definepattern */


int _WSDoCallPacket( WSLINK wslp, struct func functable[], int nfuncs)
{
	int len;
	int n, res = 0;
	struct func* funcp;

	if( ! WSGetInteger( wslp, &n) ||  n < 0 ||  n >= nfuncs) goto L0;
	funcp = &functable[n];

	if( funcp->f_nargs >= 0
	&& ( ! WSTestHead(wslp, "List", &len)
	     || ( !funcp->manual && (len != funcp->f_nargs))
	     || (  funcp->manual && (len <  funcp->f_nargs))
	   )
	) goto L0;

	stdlink = wslp;
	res = (*funcp->f_func)( wslp);

L0:	if( res == 0)
		res = WSClearError( wslp) && WSPutSymbol( wslp, "$Failed");
	return res && WSEndPacket( wslp) && WSNewPacket( wslp);
} /* _WSDoCallPacket */


wsapi_packet WSAnswer( WSLINK wslp)
{
	wsapi_packet pkt = 0;
	int waitResult;

	while( ! WSDone && ! WSError(wslp)
		&& (waitResult = WSWaitForLinkActivity(wslp),waitResult) &&
		waitResult == WSWAITSUCCESS && (pkt = WSNextPacket(wslp), pkt) &&
		pkt == CALLPKT)
	{
		WSAbort = 0;
		if(! WSDoCallPacket(wslp))
			pkt = 0;
	}
	WSAbort = 0;
	return pkt;
} /* WSAnswer */



/*
	Module[ { me = $ParentLink},
		$ParentLink = contents of RESUMEPKT;
		Message[ MessageName[$ParentLink, "notfe"], me];
		me]
*/


static int refuse_to_be_a_frontend( WSLINK wslp)
{
	int pkt;

	WSPutFunction( wslp, "EvaluatePacket", 1);
	  WSPutFunction( wslp, "Module", 2);
	    WSPutFunction( wslp, "List", 1);
		  WSPutFunction( wslp, "Set", 2);
		    WSPutSymbol( wslp, "me");
	        WSPutSymbol( wslp, "$ParentLink");
	  WSPutFunction( wslp, "CompoundExpression", 3);
	    WSPutFunction( wslp, "Set", 2);
	      WSPutSymbol( wslp, "$ParentLink");
	      WSTransferExpression( wslp, wslp);
	    WSPutFunction( wslp, "Message", 2);
	      WSPutFunction( wslp, "MessageName", 2);
	        WSPutSymbol( wslp, "$ParentLink");
	        WSPutString( wslp, "notfe");
	      WSPutSymbol( wslp, "me");
	    WSPutSymbol( wslp, "me");
	WSEndPacket( wslp);

	while( (pkt = WSNextPacket( wslp), pkt) && pkt != SUSPENDPKT)
		WSNewPacket( wslp);
	WSNewPacket( wslp);
	return WSError( wslp) == WSEOK;
}


int WSEvaluate( WSLINK wslp, char *s)
{
	if( WSAbort) return 0;
	return WSPutFunction( wslp, "EvaluatePacket", 1L)
		&& WSPutFunction( wslp, "ToExpression", 1L)
		&& WSPutString( wslp, s)
		&& WSEndPacket( wslp);
} /* WSEvaluate */


int WSEvaluateString( WSLINK wslp, char *s)
{
	int pkt;
	if( WSAbort) return 0;
	if( WSEvaluate( wslp, s)){
		while( (pkt = WSAnswer( wslp), pkt) && pkt != RETURNPKT)
			WSNewPacket( wslp);
		WSNewPacket( wslp);
	}
	return WSError( wslp) == WSEOK;
} /* WSEvaluateString */


WSMDEFN( void, WSDefaultHandler, ( WSLINK wslp, int message, int n))
{
	switch (message){
	case WSTerminateMessage:
		WSDone = 1;
	case WSInterruptMessage:
	case WSAbortMessage:
		WSAbort = 1;
	default:
		return;
	}
}


static int _WSMain( char **argv, char **argv_end, char *commandline)
{
	WSLINK wslp;
	int err;

	if( !stdenv)
		stdenv = WSInitialize( (WSEnvironmentParameter)0);

	if( stdenv == (WSEnvironment)0) goto R0;

	if( !stdhandler)
		stdhandler = (WSMessageHandlerObject)WSDefaultHandler;


	wslp = commandline
		? WSOpenString( stdenv, commandline, &err)
		: WSOpenArgcArgv( stdenv, (int)(argv_end - argv), argv, &err);
	if( wslp == (WSLINK)0){
		WSAlert( stdenv, WSErrorString( stdenv, err));
		goto R1;
	}

	if( stdyielder) WSSetYieldFunction( wslp, stdyielder);
	if( stdhandler) WSSetMessageHandler( wslp, stdhandler);

	if( WSInstall( wslp))
		while( WSAnswer( wslp) == RESUMEPKT){
			if( ! refuse_to_be_a_frontend( wslp)) break;
		}

	WSClose( wslp);
R1:	WSDeinitialize( stdenv);
	stdenv = (WSEnvironment)0;
R0:	return !WSDone;
} /* _WSMain */


int WSMainString( char *commandline)
{
	return _WSMain( (charpp_ct)0, (charpp_ct)0, commandline);
}

int WSMainArgv( char** argv, char** argv_end) /* note not FAR pointers */
{   
	static char FAR * far_argv[128];
	int count = 0;
	
	while(argv < argv_end)
		far_argv[count++] = *argv++;
		 
	return _WSMain( far_argv, far_argv + count, (charp_ct)0);

}


int WSMain( int argc, char **argv)
{
 	return _WSMain( argv, argv + argc, (char *)0);
}
 
