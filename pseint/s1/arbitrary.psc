proceso arbitrary

	definir i como real;

	escribir "Ingresa un número i para evaluar en la"
	escribir "siguiente función arbitraria:"
	escribir "-------------------------------------------"
	escribir ">> 	       / i*4 - 3*i/5 + i^3     si i < 3"
	escribir ">> f(i) -|  ((-i+1) * (i-1)) / i  si i = 3"
	escribir ">> 	       \ i! - (i-1)!           si i > 3"
	escribir "-------------------------------------------"

	leer i;
	
	si (i < 3) entonces
		escribir i*4 - 3*i/5 + i^3;
	sino
		si (i == 3)
			escribir ((-i+1) * (i-1)) / i;
		sino
			escribir (calc_factorial(i)) - calc_factorial(i-1);
		finsi
	finsi

finproceso

subproceso factorial = calc_factorial(target)
	si (target < 1 | target <> redon(target))
		factorial = -1
	sino
		factorial = 1;
		
		para count = 1 hasta target hacer
			factorial = factorial * count;
		finpara
	finsi
finsubproceso
