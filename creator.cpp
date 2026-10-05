#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc < 3) {
        std::cerr << "Использование: Creator.exe <имя_файла> <количество_записей>\n";
        return 1;
    }

    std::string fileName = argv[1];
    int recordCount = std::stoi(argv[2]);

    std::ofstream outFile(fileName, std::ios::binary);
    if (!outFile) {
        std::cerr << "Ошибка открытия файла для записи: " << fileName << "\n";
        return 1;
    }

    for (int i = 0; i < recordCount; ++i) {
        employee emp;
        std::cout << "\nВвод данных для сотрудника #" << (i + 1) << ":\n";
        std::cout << "ID (номер): ";
        std::cin >> emp.num;
        std::cout << "Имя (макс. 9 символов): ";
        std::cin >> emp.name;
        std::cout << "Часы: ";
        std::cin >> emp.hours;

        outFile.write(reinterpret_cast<const char*>(&emp), sizeof(employee));
    }

    outFile.close();
    std::cout << "\nБинарный файл '" << fileName << "' успешно создан.\n";
    return 0;
}

