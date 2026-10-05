
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc < 4) {
        std::cerr << "Использование: Reporter.exe <бинарный_файл> <файл_отчета> <оплата_за_час>\n";
        return 1;
    }

    std::string binFileName = argv[1];
    std::string reportFileName = argv[2];
    double hourlyRate = std::stod(argv[3]);

    std::ifstream inFile(binFileName, std::ios::binary);
    if (!inFile) {
        std::cerr << "Ошибка открытия бинарного файла: " << binFileName << "\n";
        return 1;
    }

    std::ofstream outFile(reportFileName);
    if (!outFile) {
        std::cerr << "Ошибка создания файла отчета: " << reportFileName << "\n";
        return 1;
    }

    outFile << "Отчет по файлу \"" << binFileName << "\"\n";
    outFile << "Номер сотрудника, имя сотрудника, часы, зарплата\n";

    employee emp;
    outFile << std::fixed << std::setprecision(2);

    while (inFile.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        double salary = emp.hours * hourlyRate;
        outFile << emp.num << ", " << emp.name << ", " << emp.hours << ", " << salary << "\n";
    }

    inFile.close();
    outFile.close();

    std::cout << "Файл отчета '" << reportFileName << "' успешно создан.\n";
    return 0;
}
