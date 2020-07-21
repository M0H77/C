#include <windows.h>
#include <stdio.h>


//typedef (__stdcall myfun_t)();
//typedef (__stdcall myfun_t)();
//typedef (__stdcall myfun_t)();
//typedef (__stdcall myfun_t)();

typedef void (*myfun1_t)(char*,char*);
typedef void (*myfun2_t)(char*,char*);
typedef void (*myfun3_t)(char*);
//typedef void (*myfun4_t)(char*);

void check_account(char* username) {

	char params[30];

	//strcat(params, username);
	sprintf_s(params, 30, "net user %s ", username);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	(LPWSTR)params;
	// Start the child process.
	if (!CreateProcess(NULL,   // No module name (use command line)
		params,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles.
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}


int main() {
	myfun1_t myfun1;
	myfun2_t myfun2;
	myfun3_t myfun3;
	//myfun4_t myfun4;
	

    HINSTANCE mydll = LoadLibrary("C:\\Users\\student\\source\\repos\\DLL\\Debug\\LAB07PART2.dll");
	myfun1 = (myfun1_t)GetProcAddress(mydll, "add_user");
	myfun2 = (myfun2_t)GetProcAddress(mydll, "change_pswd");
	myfun3 = (myfun3_t)GetProcAddress(mydll, "delete_user");
	//myfun4 = (myfun4_t)GetProcAddress(mydll, "check_account");

	char exit[] = "exit";
	char one[] = "1";
	char two[] = "2";
	char three[] = "3";
	char four[] = "4";

	
	while (1) {
		printf("1. add user\n2. change password\n3. delete user\n4. check user account\n");
		printf("choose one option by typing the option's number or exit to quit\n");
		printf("user>>");
		char* input = (char*)malloc(50);
		scanf_s("%s", input, 50);

		if (strcmp(input, exit) == 0) {  //if exit break
			break;

		}
		else if (strcmp(input, one) == 0) {              // add user
			char* username[50];
			char* passwd[50];
			printf("Enter username: ");
			scanf_s("%s", username, 50);
			printf("Enter password: ");
			scanf_s("%s", passwd, 50);
			myfun1(username, passwd);
			system("pause");
			system("cls");


		}
		else if (strcmp(input, two) == 0) {                   // change password
			char* username[50];
			char* passwd[50];
			printf("Enter username: ");
			scanf_s("%s", username, 50);
			printf("Enter a new password: ");
			scanf_s("%s", passwd, 50);
			myfun2(username, passwd);
			system("pause");
			system("cls");


		}
		else if (strcmp(input, three) == 0) {               // delete password
			char* username[50];
			printf("Enter the username for the account you to delete: ");
			scanf_s("%s", username, 50);
			myfun3(username);
			system("pause");
			system("cls");


		}
		else if (strcmp(input, four) == 0) {                   // check account
			char* username = (char*)malloc(50);
			printf("Enter username: ");
			scanf_s("%s", username, 50);
			check_account(username);
			system("pause");
			system("cls");
		}
		system("cls");

	}
	return 0;
}