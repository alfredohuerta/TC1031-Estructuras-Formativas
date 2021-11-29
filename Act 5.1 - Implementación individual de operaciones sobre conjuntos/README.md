# Análisis de complejidad
## Put -> O(n)
Ya que al momento de ingresar el nuevo valor la validación cuadrática avanza en la tabla para evitar coliciones, la inserción de datos será de O(1). Sin embargo, como el tamaño
de la tabla es fijo, puede llegar a saturarse y nos daría una complejidad e O(n) en este caso, ya que debería recorrer la tabla hasta encontrar un sitio vacío donde hacer la inserción.
## Get -> O(n)
Ya que la función de búsqueda también corre con la función indexof que hace la validación de la llave y recorre todo la tabla en búsqueda del valor, la complejidad de esta función
también sería de O(n) en el peor de los casos.
