proceso primes_in_range

	escribir "Imprimir los números primos entre el: "
	leer origin

	escribir "y el: "
	leer end
	
	si (origin < end) entonces
		min <- origin
		max <- end
	sino
		max <- origin
		min <- end
	finsi

	si (min <= 0) Entonces
		min <- 2
	finsi

	para i <- min hasta max hacer

		primo <- verdadero

		para j <- min hasta i hacer
			si (i mod j == 0 y j <> i y j <> 1) entonces
				primo <- falso
			finsi
		finpara

		si primo Entonces
			escribir i
		finsi

	finpara

finproceso
