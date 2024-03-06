#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

/*

D:\reposC++\QualityControll\lw1Checker\x64\Debug\lw1Checker.exe путь до этого приложения
D:\reposC++\QualityControll\lw1App\x64\Debug\lw1App.exe путь до приложения что нужно проверить
D:\reposC++\QualityControll\lw1Checker\x64\Debug\lw1Checker.exe D:\reposC++\QualityControll\lw1App\x64\Debug\lw1App.exe команда для чекера
https://docs.google.com/document/d/1u8zOnhJ654bcbgjHlAi6sk3WklmsStIyAltURylIMeI/edit ТЗ
*/


int main(int argc, char* argv[])
{
    //задаём русский язык
    setlocale(LC_ALL, "Russian");

    // Проверяем, что был передан путь к программе
    if (argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <path_to_lw1App.exe>" << std::endl;
        return 1;
    }

    //получаем путь до тестируемого приложения
    std::string lw1AppPath = argv[1];

    //открываем файлы для работы
    std::ifstream inputFile("D:\\reposC++\\QualityControll\\lw1Checker\\testCases.txt");
    std::ofstream outputFile("D:\\reposC++\\QualityControll\\lw1Checker\\results.txt");

    // Проверяем открытие файлов для тестов и результатов
    if (!inputFile.is_open() || !outputFile.is_open())
    {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }


    std::string line;
    int Sucsesses = 0;// кол-во успехов (опционально)
    int Fails = 0;//кол-во неудач (опционально)

    while (std::getline(inputFile, line))
    {
        if (!line.empty())
        {
            // Разделяем строку на параметры и ожидаемый результат по знаку ";"
            std::size_t pos = line.find_last_of(';');
            std::string params = line.substr(0, pos);
            std::string expected_result = line.substr(pos + 2);

            // Запускаем тестируемое приложение и перенаправляем вывод в файл
            std::string command = lw1AppPath + " " + params + " > output.txt";
            system(command.c_str());

            // Считываем результат из файла
            std::ifstream output_file("output.txt");
            std::string result;
            std::getline(output_file, result);
            output_file.close();

            // Сравниваем результат с ожидаемым, выводим успех или неуспех
            if (result == expected_result)
            {
                Sucsesses++;
                outputFile << "success" << std::endl;
            }
            else
            {
                Fails++;
                outputFile << "error" << std::endl;
            }
        }
    }

    // Удаляем лишний файл и закрываем необходимые
    std::remove("output.txt");
    inputFile.close();
    outputFile.close();
    std::cout << "Done, sucsesses: " << Sucsesses << " Fails: " << Fails << std::endl;//выводим кол-во удач и неудач (опционально)
    return 0;
}

/*
тесты
0 0 0; ошибка: некорректные данные.
0 0 0; обычный
0 0 0; равнобедренный
0 0 0; равносторонний

-1 -1 -1; ошибка: некорректные данные.
-1 -1 -1; обычный
-1 -1 -1; равнобедренный
-1 -1 -1; равносторонний

2 4 5; обычный
2 4 5; равнобедренный
2 4 5; равносторонний
2 4 5; не треугольник

3 4 6; обычный
3 4 6; равнобедренный
3 4 6; равносторонний
3 4 6; не треугольник

слова вместо цифр; ошибка: некорректные данные.

просто слова введны; ошибка: некорректные данные.

12 12 12 12 12; ошибка: неверное количество аргументов. Формат запуска: .exe a b c
*/