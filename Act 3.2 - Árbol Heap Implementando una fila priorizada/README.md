# Análisis de complejidad
## Push O(log n)
Debido al funcionamiento del heap donde sólo tendremos que trabajar en una de las mitades para insertar el elemento donde convenga, se tendrá una complejidad de O(log N)
## Pop O(log n)
Debido a que la función para eliminar un elemento del árbol es de O(1) y el método para rebalancearlo es de complejidad O(log n), tendríamos O(1) + O(log n) = O(log n).
## Top O(1)
Al sólo tener que devolver el valor con mayor prioridad y al ser este el que se encuentra al inicio del árbol, la complejidad sería de O(1)
## Empty O(1)
Al ser un método que comprueba un atributo del árbol y cosistir de un sólo paso para el peor de los casos, la complejidad sería de O(1)
## Size O(1)
Al tener que devolver el tamaño del arreglo y al este ser consultado en un sólo paso, la complejidad sería de O(1)
