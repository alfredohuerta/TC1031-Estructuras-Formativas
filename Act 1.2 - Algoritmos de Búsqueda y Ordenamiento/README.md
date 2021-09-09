# Análisis de complejidad
 ###selectionSort -> O(n^2)
* Al hacer uso de ciclos for anidados (O(n)) la unión de estos dan como resultado un O(n^2)= O(n) * O(n)
###bubbleSort -> O(n^2).
* Al hacer uso de ciclos for anidados (O(n)) la unión de estos dan como resultado un O(n^2)= O(n) * O(n)
###mergeSort -> O(n log(n)).
* Con cada iteración del ciclo, su duración se va reduciendo en una razón logarítmica (O(log(n)), sin embargo,
por el uso de cliclos for se le agrega una O(n). Dando como resultado O(n log(n))= O(log(n)) * O(n).
###sequencialSearch -> O(n).
* Ya que se basa únicamente en el uso de un ciclo for, su complejidad temporal se queda en lineal, ya que el 
ciclo siempre tardará en correrse el número de índices tenga el arreglo.
###binarySearch -> O(log(n)).
* Debido a que el ciclo siempre está dividiéndose a la mitad, el número de iteraciones se irá reduciendo con
cada vuelta a él.
