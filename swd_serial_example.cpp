#include <string.h>
#include "wirish.h"

#define SWD_TIMEOUT 3000

uint8 localbuf[15];

volatile uint32 *DCRDR = (uint32 *)0xe000edf8;

class SWDSerial : public Print {
public:
    SWDSerial(void);

    void write(uint8);
    void write(const char *str);
    void write(const void*, uint32);
};

extern SWDSerial SerialSWD;


uint32 SWDSendBytes(uint8 *buf, uint32 len)
{
// bit0-bit3 - data length (1-15), set by Discovery 
// bit0-bit3 == 0 - reading complete flag, set by host
// bit8-bit31 buffer address relative to 0x20000000

uint32 addr;

    if (!buf || (*DCRDR & 0xF)) {
        return 0;
    }
    if (len > 15) {
        len = 15;
    }
    memcpy(localbuf, buf, len); 

    addr = (uint32)localbuf - 0x20000000;
    *DCRDR = ((addr<<8) & 0xFFFFFF00) | (len & 0xF);

    return len;
}

SWDSerial::SWDSerial(void) {
    *DCRDR = 0;
}

void SWDSerial::write(uint8 ch) {
    const uint8 buf[] = {ch};
    this->write(buf, 1);
}

void SWDSerial::write(const char *str) {
    this->write(str, strlen(str));
}

void SWDSerial::write(const void *buf, uint32 len) {
    if (!buf) {
        return;
    }

    uint32 txed = 0;
    uint32 old_txed = 0;
    uint32 start = millis();

    while (txed < len && (millis() - start < SWD_TIMEOUT)) {
        txed += SWDSendBytes((uint8*)buf + txed, len - txed);
        if (old_txed != txed) {
            start = millis();
        }
        old_txed = txed;
    }
}

SWDSerial SerialSWD;



void setup() {

    /* Set up the LED to blink  */
    pinMode(BOARD_LED_PIN, OUTPUT);


    SerialSWD.print("Hello!\n");
}

int i=0;

void loop() {
    toggleLED();
    delay(100);
    SerialSWD.print("\n");
    SerialSWD.print(i);
    i++;
}

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.
__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (true) {
        loop();
    }

    return 0;
}
/*  
// Can be compiled using Tiny C Compiler http://bellard.org/tcc/
// Requires ST-LINK_CLI.exe and STLinkUSBDriver.dll in working directory or on PATH

#include <windows.h> 
#include <tchar.h>
#include <stdio.h> 

//#define PRINT_ST-LINK_OUTPUT 
//#define VERBOSE

#define BUFSIZE 4096 

CHAR buff[BUFSIZE];
 
HANDLE g_hChildStd_IN_Rd = NULL;
HANDLE g_hChildStd_IN_Wr = NULL;
HANDLE g_hChildStd_OUT_Rd = NULL;
HANDLE g_hChildStd_OUT_Wr = NULL;


SECURITY_ATTRIBUTES saAttr; 
 
void CreateChildProcess(PTSTR); 
void WriteToPipe(void); 
void ReadFromPipe(CHAR *); 
void WriteByte(ULONG, UCHAR);
UINT ReadNBytes(ULONG, UINT, UCHAR *);
 
int _tmain(int argc, TCHAR *argv[]) 
{ 
UCHAR DCRDR[4], data[15];
ULONG addr, n, i;

// Set the bInheritHandle flag so pipe handles are inherited. 
 
saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
saAttr.bInheritHandle = TRUE; 
saAttr.lpSecurityDescriptor = NULL; 

while(1){
   ReadNBytes(0xe000edf8, 4, DCRDR); // Read DCRDR
   if (DCRDR[0]) {
       addr = DCRDR[1] + (DCRDR[2]<<8) + (DCRDR[3]<<16);
       addr += 0x20000000; 
       n = DCRDR[0];
       ReadNBytes(addr, n, data);    // Read data buffer

#ifdef VERBOSE
       printf("\naddr abs : %X", addr);
       printf("\nlen : %X\n", n);
       printf("\ndata : ");
       for (i=0;i<n;i++) printf("%X ",data[i]);
       printf("\n");
#endif
       for (i=0;i<n;i++) 
           printf("%c",data[i]);

       WriteByte(0xe000edf8, 0);     // Reading complete flag
   }
}

   return 0; 
} 
 
void CreateChildProcess(PTSTR arg)
// Create a child process that uses the previously created pipe for STDOUT.
{ 
   TCHAR szCmdline[100]=TEXT("st-link_cli -c SWD");
   PROCESS_INFORMATION piProcInfo; 
   STARTUPINFO siStartInfo;
   BOOL bSuccess = FALSE; 

   strcat(szCmdline, arg);
 
// Set up members of the PROCESS_INFORMATION structure. 
 
   ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
 
// STARTUPINFO structure specifies the STDIN and STDOUT handles for redirection.
 
   ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
   siStartInfo.cb = sizeof(STARTUPINFO); 
   siStartInfo.hStdError = g_hChildStd_OUT_Wr;
   siStartInfo.hStdOutput = g_hChildStd_OUT_Wr;
   siStartInfo.hStdInput = g_hChildStd_IN_Rd;
   siStartInfo.dwFlags |= STARTF_USESTDHANDLES;
 
   bSuccess = CreateProcess(NULL, 
      szCmdline,     // command line 
      NULL,          // process security attributes 
      NULL,          // primary thread security attributes 
      TRUE,          // handles are inherited 
      0,             // creation flags 
      NULL,          // use parent's environment 
      NULL,          // use parent's current directory 
      &siStartInfo,  // STARTUPINFO pointer 
      &piProcInfo);  // receives PROCESS_INFORMATION 
   
   if ( ! bSuccess ) 
          ExitProcess(1);
   else 
   {
      // Close handles to the child process and its primary thread.
      CloseHandle(piProcInfo.hProcess);
      CloseHandle(piProcInfo.hThread);
   }
}
 
void ReadFromPipe(CHAR *chBuf) 

// Read output from the child process's pipe for STDOUT
// Stop when there is no more data. 
{ 
   DWORD dwRead, dwWritten; 
   BOOL bSuccess = FALSE;
   HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

// Close the write end of the pipe before reading from the 
// read end of the pipe, to control child process execution.

   if (!CloseHandle(g_hChildStd_OUT_Wr)) 
      ExitProcess(1);
 
   for (;;) 
   { 
      bSuccess = ReadFile( g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);
      if( ! bSuccess || dwRead == 0 ) break; 
 
#ifdef PRINT_ST-LINK_OUTPUT
      bSuccess = WriteFile(hParentStdOut, chBuf, 
                           dwRead, &dwWritten, NULL);
      if (! bSuccess ) break; 
#endif
   } 
} 
 
void WriteByte(ULONG addr, UCHAR data)
{
TCHAR argStr[30];

// Create a pipe for the child process's STDOUT. 
// Ensure the read handle to the pipe for STDOUT is not inherited.
 
   if ( ! CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0) ) 
      ExitProcess(1);


   if ( ! SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0) )
      ExitProcess(1);
   
   sprintf(argStr, " -w8 %X %X", addr, data);

   CreateChildProcess(argStr);
   ReadFromPipe(buff); 
}

UINT ReadNBytes(ULONG addr, UINT n, UCHAR * data)
{
TCHAR argStr[30];
UCHAR ch, *pos;
INT i;

   if (n > 16) {
       n = 16;
   }

   if ( ! CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0) ) 
      ExitProcess(1);

   if ( ! SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0) )
      ExitProcess(1);
   
   sprintf(argStr, " -r8 %X %X", addr, n);

   CreateChildProcess(argStr);
   ReadFromPipe(buff); 
   
   pos = 14 + strstr(buff,"\n0x");
   for (i = 0; i < n; i++) {
       sscanf(pos, "%x",&ch);
       *(data+i) = ch;
       pos+=4;
   }

   return(n);
}
*/
