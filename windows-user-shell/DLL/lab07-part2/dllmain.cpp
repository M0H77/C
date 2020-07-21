// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"

#include <stdio.h>
#include <shellapi.h>


extern "C" __declspec(dllexport)
void add_user(char* username, char* passwd) {
	char verb[10] = "runas";
	char cmd[10] = "net";
	char params[50]; 
	//strcat(params, username);
	//strcat(params, space);
	//strcat(params, passwd);
	//strcat(params, space);
	//strcat(params, option);
	//    printf("%s",params);
	sprintf_s(params, 30, "user %s %s /add", username,passwd);

	ShellExecuteA(NULL, verb, cmd, params, 0, SW_HIDE);
}

extern "C" __declspec(dllexport)
void change_pswd(char* username, char* passwd) {
	char verb[10] = "runas";
	char cmd[10] = "net";
	char params[30];
	//strcat(params, username);
	//strcat(params, space);
	//strcat(params, passwd);
	//strcat(params, space);
	//strcat(params, option);
	//    printf("%s",params);
	sprintf_s(params, 30, "user %s %s", username, passwd);
	ShellExecuteA(NULL, verb, cmd, params, 0, SW_HIDE);
}

extern "C" __declspec(dllexport)
void delete_user(char* username) {
	char verb[10] = "runas";
	char cmd[10] = "net";
	char params[30];
	//strcat(params, username);
	//strcat(params, space);
	//strcat(params, option);
	//    printf("%s",params);
	sprintf_s(params, 30, "user %s /delete", username);
	ShellExecuteA(NULL, verb, cmd, params, 0, SW_HIDE);
}





BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

