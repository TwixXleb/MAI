# Отчет по лабораторной работе № 21
## по курсу "Фундаментальная информатика"

Студент группы М8О-108Б-23 Ширшов Даниил Константинович

Работа выполнена 

Преподаватель: каф. 806 Севастьянов Виктор Сергеевич

1. **Тема**: Bash, linux terminal
2. **Цель работы**: Составить программу выполнения заданных действий над файлами на одном из интерпретируемых командных языков
3. **Задание**: Удаление файлов, суммарная длина которых не меньше заданного числа блоков
4. **Идея, метод, алгоритм решения задачи**: 
```
$ Ввод директории
$ Ввод размера
$ Цикл по файлам в веденной папке
$ В цикле анализ блочного размера файла, и если он больше
или равен нужному - удаление
```
5. **Сценарий выполнения работы**: 
- Открыть терминал
- Создать папку под 21 лабу
- Создать в ней файл с отчетом
- Написать скрипт на Баш
- Создать тестовую папку с файлами разных размеров и протестировать
работоспособность
- В гите создать ветку под 21 лабу
- Добавить туда созданную папку с скриптом и отчетом
- Закоммитить
- Запушить в Гит ветки Мэйн и 21 лабы
- Смерджить 
- Запушить Мэйн
6. **Протокол**:
```
echo "Please enter the nuznaya dir"

read directory

echo "Please enter the nyzniy size"

read size

for file in "$directory"*

do
blocksize=$(stat -f %b "$file")
if [ $blocksize -ge $size ]
then
rm "$file"
fi
done
``` 
7. **Замечания автора** по существу работы: Нет
8. **Выводы**: В результате выполнения данной лабораторной работы я еще лучше разобрался как работать 
с Башэм, научился создавать выполняемые скрипты и в целом начал понимать что к чему