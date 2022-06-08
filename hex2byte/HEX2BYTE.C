#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define	bool	char
#define	true	1
#define	false	0
FILE *FR,*FW, *FBIN;
char s1[1000];
unsigned char s2[1000];

char	mif_head[]=
"WIDTH=%d;\n"
"DEPTH=%d;\n"
//"ADDRESS_RADIX=UNS;\n"
"ADDRESS_RADIX=HEX;\n"
"DATA_RADIX=HEX;\n"
"\n"
"CONTENT BEGIN\n"	;

int fgets0(char *s,int n,FILE *F)
{
    if (feof(F)) return(0);
    s[0]=0;
    fgets(s,n,F);
    return(s[0]);
}

unsigned hex(char c)
{
    if ((c>='0')&&(c<='9')) return(c-'0');
    else if ((c>='A')&&(c<='F')) return(c-'A'+10);
    else if ((c>='a')&&(c<='f')) return(c-'a'+10);
    else return(0);
}
unsigned hexbyte(char *s)
{
    return(hex(s[0])*16+hex(s[1]));
}

int HEXDATA(unsigned char *d,unsigned short *p,char *s)
{
int i,n,d0,d1;
    if (s[0]!=':') return(0);
    n=hexbyte(s+1);
    d1=hexbyte(s+3);
    d0=hexbyte(s+5);
    *p=(d1*256)+d0;
    for(i=0;i<n;i++) d[i]=hexbyte(s+9+i*2);
    return(n);
}

void ROMSTR(char *s,unsigned long a,unsigned char b)
{
unsigned short m;
int i;
    m=0x80;
    for(i=0;i<8;i++) {
        if ((b&m)==0) s[i]='0'; else s[i]='1';
        m>>=1;
    }
    s[8]='\n'; s[9]=0;
    //sprintf(s+8," %08lX\n",a);
}

void output(FILE *FW,unsigned char *data0,int maxlen,char oformat, bool oparity,char osize, int mif_shift, int bank)
{
unsigned short chksum;
unsigned char parity;
int i,j,n,a,line=1;
    chksum=0; parity=0;
    if (oparity) {
	for(i=0;i<maxlen-4;i++) { chksum+=data0[i]; parity^=data0[i];}
        i=maxlen;
        chksum+=0xFF;  //parity+~parity;
        j=(unsigned char)(~chksum);

	data0[i-4]=j;
	data0[i-3]=(unsigned char)(chksum>>8);
	parity^=data0[i-4];
	parity^=data0[i-3];
	data0[i-2]=parity;
	data0[i-1]=~parity;
	printf("byte chksum=%04X parity=%02X\n",chksum,parity);
    }

    if (oformat=='b') {
	fwrite(data0,maxlen,1,FW);
    } else {
	n=(maxlen+osize-1)/osize;
	if (oformat=='m') {
	    if (bank==0) {
		fprintf(FW,mif_head,osize*8,n+(mif_shift/osize));
	    }
	}
	for(i=0;i<n;i++) {
	    a=i+mif_shift+(bank<<16);
	    if (oformat=='m') fprintf(FW,"\t%04X\t:\t",a);
	    if (oformat=='a') {
		fprintf(FW,"\tDB");
		for(j=0;j<osize;j++) {fprintf(FW,"%c0%02Xh",((j==0)?'\t':','),data0[i*osize+j]); }
		fprintf(FW,"; //%04X",i*osize);
	    } else {
		for(j=osize-1;j>=0;j--) fprintf(FW,"%02X",data0[i*osize+j]);
	    }
	    if (oformat=='m') fprintf(FW,";\n");
	    else fprintf(FW,"\n");
	}
    }
}

void main(int argn,char *argv[])
{
int i,j,n,line=1;
int maxlen=0;
int mif_shift=0;
unsigned short v;
char osize=1;
bool oparity=false;
int bank=0;
char oformat='t';
char *name=NULL;
char *wtype="w";
unsigned char data0[65536];
unsigned char dirty[65536];
    for(i=1;i<argn;i++) {
	if ((argv[i][0]=='-')&&(argv[i][1]=='1')&&(argv[i][2]=='6')) osize=16;
	else if ((argv[i][0]=='-')&&(argv[i][2]==0)) {
	    if (argv[i][1]=='1') {if (argv[i][2]=='6') osize=16; else osize=1;}
	    else if (argv[i][1]=='2') osize=2;
	    else if (argv[i][1]=='4') osize=4;
	    else if (argv[i][1]=='8') osize=8;
	    else if (argv[i][1]=='t') oformat='t';
	    else if (argv[i][1]=='m') oformat='m';
	    else if (argv[i][1]=='b') oformat='b';
	    else if (argv[i][1]=='a') oformat='a';
	    else if (argv[i][1]=='p') oparity=true;
	} else if (argv[i][0]=='+') {
	    j=atoi(argv[i]+1);
	    mif_shift=j;
	} else {
	    if (name==NULL) name=argv[i];
	    else maxlen=atoi(argv[i]);
	}
    }
    if (oparity&&(maxlen==0)) maxlen=65536;

    if (name==NULL) {
        printf("Usage: HEX2BYTE [-1/-2/-4/-8][-t/-m] [-p] [+32768] filename(.hex) maxlen\n");
	printf("       -1:byte, -2:word, -3:dword, -8:qword\n");
	printf("       -t:text, -m:mif -b:bin -a:asm output\n");
	printf("       -p:gen parity\n");
	return;
    }
    strcpy(s1,name);
    i=strlen(s1)-1;
    while((i>0)&&((s1[i]!='\\')&&(s1[i]!='.'))) i--;
    if ((s1[i]!='.')||(stricmp(s1+i+1,"hex")))  {i=strlen(s1); strcat(s1,".hex");}
    FR=fopen(s1,"r");
    if (FR==NULL) {printf("%s file not found\n",s1); return;}
    strcpy(s1,name);

    if (oformat=='t') {
	strcpy(s1+i,".t");
	wtype="w";
    } else if (oformat=='m') {
	strcpy(s1+i,".mif");
	wtype="w";
    } else if (oformat=='a') {
	strcpy(s1+i,".asi");
	wtype="w";
    } else if (oformat=='b') {
	strcpy(s1+i,".bin");
	wtype="wb";
    }
    FW=fopen(s1,wtype);
    if (FW==NULL) {printf("%s cannot create file\n",s1); return;}

    for(j=0;j<65536;j++) data0[j]=0;
    for(j=0;j<65536;j++) dirty[j]=0;
    while(fgets0(s1,1000,FR)!=0) {
	n=HEXDATA(s2,&v,s1);
	for(i=0;i<n;i++) {
	    if (dirty[v+i]!=0) {
		output(FW,data0,65536,oformat,oparity,osize,mif_shift,bank);
		for(j=0;j<65536;j++) data0[j]=0;
		for(j=0;j<65536;j++) dirty[j]=0;
		maxlen=0;
		bank++;
		break;
	    }
	}

	j=v+n;
        if (n>0) {if (j>maxlen) maxlen=j;}
	for(i=0;i<n;i++) {
            j=v+i;
            data0[j]=s2[i];
	    dirty[j]=1;
        }
    }
    if (maxlen!=0) {
	output(FW,data0,maxlen,oformat,oparity,osize,mif_shift,bank);
    }
    if (oformat=='m') fprintf(FW,"END;\n");
    fclose(FR);
    fclose(FW);
}
