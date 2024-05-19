# Technical-task

### Клонирование репозитория
```
git clone https://github.com/Termtre/Technical-task
```
### Сборка проекта
1. В папке с репозиторием в терминале введите 
```
mkdir build
```
2. Перейдите в эту папку
```
cd build
```
3. Соберите проект
```
cmake ../
```
### Компиляция
1. Перейдите в папку с бинарными файлами
```
cd build
```
2. Скомпилируйте исполняемый файл
```
<<<<<<< HEAD
cmake --build
=======
cmake --build . --target task
>>>>>>> 7a6790ab2ebcbf063ac63701c360510127d69ff1
```
3. Исполняемый файл будет в следующей директории:
```
cd ../testExample/Debug
```
или
```
cd ../testExample/Realese
```
### Пример использования
В папке `testExample` лежат несколько `.txt` файлов для тестирования программы.
Для запуска программы необходимо перейти в папку `testExample/Debug` или `testExample/Realese` и запустить исполняемый файл:
```
task.exe ../test1.txt
```
