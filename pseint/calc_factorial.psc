proceso calc_factorial
	definir target como real;

	leer target;
	si (target < 1 | target <> redon(target))
		repetir
			escribir("El número debe ser entero, positivo y distinto de cero.");
			leer target;
		hasta que (target >= 1)
	finsi

	factorial = 1;

	para count = 1 hasta target hacer
		factorial = factorial * count;
	finpara

	escribir "El factorial de ", target, " es ", factorial, ".";
finproceso
