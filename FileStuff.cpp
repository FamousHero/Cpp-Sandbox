#include <iostream>
#include <fstream>
#include <Windows.h>

static void FileCreation() {
    //test to see if file is created by ofstream.open if it doesn't exist
    std::ofstream ofs;
    ofs.open("test_code.txt");
    ofs << "This file contains malicious code. If malicous actor wites out compiled bits to this file \n \
    and labels it executable, they can call it from a bat file. All they need is to be able to inject their own code";
    ofs.close();

    ofs.open("test.bat", std::ofstream::out | std::ofstream::app);

    ofs << "@echo off\n";
    ofs << "Start notepad \"test_code.txt\"\n";
    ofs << "exit";

    ofs.close();
    //It does 


}

static void FileExecutor()
{
    //test to see if files can be executed through cpp
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    char cmdline[] = "cmd.exe /C test.bat";
    //test to see if file can be executed from cpp
    if (!CreateProcess(NULL, cmdline, NULL, NULL, false, 0,
        NULL, NULL, &si, &pi))
        std::cout << "process no work";
    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    //they can
    //Leveraging both with a code injection vulnerability would give you a RCE vul
    //you could write a batch file on target and execute thus compromising their system :)

}