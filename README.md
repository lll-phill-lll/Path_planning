# project_pathplanning
Филитов Михаил, 164 группа, Pathplanning

Актуальность проблемы:
-----------------------

Все больше и больше сложной, опасной для жизни работы мы можем доверить роботам, тем самым избежав человеческих жертв, но чтобы робот корректно справился с поставленной задачей, он должен верно сконструировать безопасный и кротчайший путь. Таким образом проблема плоложения пути для робота является насущной и крайне важной. Длянахождения путей испДанные роботы уже используются в быту (работы-пылесосы), в науке(лунаходы).

Будет использоваться:
---------------------

Операционная система ubuntu, поскольку она позволяет более удобно работать с кодом и с библиотеками.
В качестве IDE будет использоваться QT Creator, поскольку он является кроссплатформенным, поддерживает различные компиляторы, а также поддерживает системы контроля версий, в том числе Git.
Также будет использоваться TinyXML, поскольку в качестве исходного кода программа будет принимать XML файл с разметкой карты, и как разультат выдавать файл в том же формате, который впоследствии будет обрабатываться роботом. Он удобен, поскольку поддерживается с++.
Для решения поставленной задачи предлгается рзбить плоскость на квадраты (большие в областях, где нет препятствий, меленькие в областях, где рядом есть препятствия) и строить маршрут в  графе, где вершинами выступают узлы сетки, а ребрами - ребра квадратов, в качестве весов ребер можно выбрать, к примеру, расстояние между точкамивершинами на плоскости. Также, чтобы не учитывать размер робота, можно увеличить размеры препятствий, тогда можно будет считать робота точкой.Также будем делать робота круглым с возможностью поворота на месте, чтобы облегчить планирование траектории и избежать учета траектории поворота.


План:
------

Январь - Февраль: Функционал A* реализован в программном коде, все опции (разрешенные движения, вес эвристики, breaking ties стратегии и пр.) hard-coded, проект компилируется и корректно работает (выходной файл требуемого формата).

Февраль - Март:  Функционал A* реализован в программном коде, поддерживаются различные опции поиска (вес эвристики, breaking ties стратегии, разрешенные движения и пр.), проект компилируется и корректно работает (выходной файл требуемого формата).

Март - Апрель: Функционал A*, Theta* и JPS реализован в программном коде с использованием грамотной иерархии классов (наследование, не дублирование основного функционала и пр.), поддерживаются различные опции поиска (вес эвристики, breaking ties стратегии, разрешенные движения и пр.), проект компилируется и корректно работает (выходной файл требуемого формата).

Апрель - Май:  Программный код встроен в ROS и используется для планирования траектории TurtleBot (симуляция в Gazebo).

Состав файла XML:
------------------
Файл представляет из себя описание поля с препятствиями и формат используемого алгоритма поиска пути.

1. *width* - задает ширину поля в условных единицах.
2. *height* - задает высоту поля в условных единицах.
3. *cellsize* - задает размер условнх единиц.
4. *startx*, *starty*, *finishx*, *finishy* - задают соответственно координаты начала движения и конечной точки.
5. *grid* - само поле.
6. *row* - строки поля со значениями 0 - свободно, 1 - препятствие.
7. *algorithm* - параметры применяемого алгоритма.
8. *searchtupe* - выбрать алгоритм (astar, theta, gps).
9. *metrictype* - используемая метрика для определния кратчайшего расстояния (euclid, diagonal, manhattan, chebyshev.
10. *breakingties* -----
11. *hweight* вес эвристики.
12. *allowdiagonal* - разрешено ли ходить по диагонали.
13. *cutcorners* - можно ли угол препятствия обходить по диагонали.
14. *allowsqueeze* если два препятствия касаются углами, можно ли между ними пройти.
15. *loglevel* - каким образом завершился алгоритм.
16. *logpath* - имя каталога, куда будет писаться лог.
17. *logfilename* - имя файла, куда будет писаться лог.

