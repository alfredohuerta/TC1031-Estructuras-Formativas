# Análisis de complejidad.
## Insertion -> O(1) / O(n)
Debido a que dentro de la función se pueden llevar a cabo dos acciones aparentemente iguales, se tiene dos complejidades. En caso de estar agregando por primera vez un elemento en la lista, sería una complejidad de O(1) ya que apenas empieza a recorrer la lista, ya se ha completado la función.
 En caso de que se agregen elementos posteriores al primero, sería una complejidad de O(n) ya que deberá recorrer todo el arreglo hasta llegar a un espacio dónde poder agregar el nuevo elemento.
## Search -> O(n)
Ya que usa un ciclo while para recorrer los datos de la lista, la complejidad en el peor de los casos será O(n).
## Update -> O(n)
Se usa un ciclo while para avanzar en los datos de la lista, comenzando desde el inicio hasta la posición n donde se encuentra el dato que se busca reeemplazar, por lo que la complejidad será de O(n)
## Delete At -> O(1) / O(n)
Debido a que el dato puede estar en el primer espacio y hay una función que manipula ello, puede tener una complejidad de O(1). En caso de no ser el primer paso, O(n).
