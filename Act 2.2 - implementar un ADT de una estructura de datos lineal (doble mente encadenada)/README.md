# Análisis de complejidad.

### Insertion -> O(1) / O(n)
Al estar dividido en dos funciones, una atada a su primer dato únicamente la cual tiene una complejidad de O(1) por no contar con ningún ciclo; también está la segunda función que
está atada a todos los datos que no sean el primero, lo que nos da una complejidad de O(n) al tener que recorrer, en el peor de los casos, el arreglo completo.
### Search -> O(n)
Al tener un ciclo while que varía en función del tamaño de la lista, su complejidad es de O(n).
### Update -> O(n)
Al tener un ciclo while cuya longitud varía en función de los datos de la lista, su complejidad será de O(n) ya que en el peor de los casos tendrá que recorrer los n datos de la lista.
### Delete At -> O(1) / O(n)
Al tener una función dedicada al primer elemento, dicha función es de una complejidad O(1) por carecer de un ciclo de búsqueda. En cuanto a la función que aplica a los demás datos
esta es de una complejodad O(n) por poder llegar a tener que recorrer los n datos de la lista en el peor caso.
