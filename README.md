# Инструкция по CMake сборке проекта:

### Важно: если вы добавляете новый файл, напишите его название в add_executable снизу

1) Установить CMake версии 4.0.2 и выше.
2) Создать каталог ./build
3) Перейти в каталог ./build
4) Выполнить команду ```Bash cmake ..```
5) После удачного завершения выполнить ```Bash cmake --build . --config Release --target LAD_APP``` 

После этого в каталоге ./buld/Release появится готовый к запуску LAD_APP.exe

### Запуск тестов!

#### Обязательно выполнить:
    ```Bash git clone https://github.com/google/googletest```
    Затем следовать инструкции по сборке проекта, заменить LAD_APP на TEST_APP

1) Запуск тестов с отчётностью ```Bash {путь к файлу} --gtest_output=json:report.json```

2) Запуск тестов без отчётности ```Bash {путь к файлу}```

3) Или можно выполнить ```Bash ctest --C Debug --output-on-failure```