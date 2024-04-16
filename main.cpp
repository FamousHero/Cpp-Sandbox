#include <fstream>      // std::ofstream
#include <Windows.h>
#include <iostream>
float FloatToInt(float base)
{
    //my theory could be right but its too computationally heavy to even
    //impelement in cpp. At the end of the day x86 has an instruction to do
    //it for you so who cares.
    //int exponent = (base >> 23);

    return 0.0f;
}

void FileCreation() {
    //test to see if file is created by ofstream.open if it doesn't exist
    std::ofstream ofs;
    ofs.open("test.txt", std::ofstream::out | std::ofstream::app);

    ofs << " more lorem ipsum";
    ofs.close();
    //It does 
    

}

void FileExecutor()
{
    //test to see if files can be executed through cpp
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    char cmdline[] = "cmd.exe /C test.bat";
    //test to see if file can be executed from cpp
    if(!CreateProcess(NULL, cmdline, NULL, NULL, false, 0,
        NULL, NULL, &si, &pi))
        std::cout << "process no work";
    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    //they can
    //Leveraging both with a code injection vulnerability would give you a RCE vul
    //you could write a batch file on target and execute thus compromising their system :)

}

int main () {

    FileExecutor();
    return 0;
}