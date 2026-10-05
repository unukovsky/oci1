
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

struct employee {
    int num;
    char name[10];
    double hours;
};

void runProcess(const std::string& appName, const std::string& args) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    std::string cmdLine = appName + " " + args;
    char* lpCmdLine = _strdup(cmdLine.c_str());
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    free(lpCmdLine);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string binFileName;
    int recordCount;
    std::cout << "Введите имя бинарного файла: ";
    std::cin >> binFileName;
    std::cout << "Введите количество записей: ";
    std::cin >> recordCount;

    std::string creatorArgs = binFileName + " " + std::to_string(recordCount);
    std::cout << "\n--- Запуск утилиты Creator.exe ---\n";
    runProcess("Creator.exe", creatorArgs);

    std::ifstream binFile(binFileName, std::ios::binary);
    if (!binFile) {
        std::cerr << "Не удалось открыть бинарный файл для чтения.\n";
        return 1;
    }

    std::cout << "\n--- Содержимое бинарного файла '" << binFileName << "': ---\n";
    employee emp;
    while (binFile.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        std::cout << "ID: " << emp.num << " | Имя: " << emp.name << " | Часы: " << emp.hours << "\n";
    }
    binFile.close();
    std::cout << "--------------------------------------------------\n\n";

    std::string reportFileName;
    std::string hourlyRateStr;
    std::cout << "Введите имя файла отчета: ";
    std::cin >> reportFileName;
    std::cout << "Введите оплату за час работы: ";
    std::cin >> hourlyRateStr;

    std::string reporterArgs = binFileName + " " + reportFileName + " " + hourlyRateStr;
    std::cout << "\n--- Запуск утилиты Reporter.exe ---\n";
    runProcess("Reporter.exe", reporterArgs);

    std::ifstream reportFile(reportFileName);
    if (!reportFile) {
        std::cerr << "Не удалось открыть файл отчета.\n";
        return 1;
    }

    std::cout << "\n--- Содержимое файла отчета '" << reportFileName << "': ---\n";
    std::string line;
    while (std::getline(reportFile, line)) {
        std::cout << line << "\n";
    }
    reportFile.close();
    std::cout << "--------------------------------------------------\n";
    return 0;
}
