proceso calculadora
	repetir
		escribirMenu
		
		escribir "Elije una opción:"
		leer numero_de_opcion

		segun numero_de_opcion hacer
			1:
				calculo_simple("sumar")
			2:
				calculo_simple("restar")
			3:
				calculo_simple("multiplicar")
			4:
				calculo_simple("dividir")
			5:
				escribir "Calcular el factorial de: "
				leer numero1
				
				factorial = factorial_de(numero1)
				si (factorial == -1)
					escribir "Imposible calcular el factorial de ", numero1
				sino
					escribir numero1 "! = ", factorial 
				finsi
			6:
				escribir "Calcular la raíz cuadrada de:"
				leer subradical
				
				si (subradical < 0)
					escribir "Imposible calcular la raíz cuadrada de " subradical ". El número debe ser positivo."
				sino
					escribir "La raíz cuadrada de " subradical " es ", raiz_cuadrada_de(subradical)
				finsi
			7:
				escribir "Calcular la pendiente a partir de los puntos:"
				
				escribir "Punto 1:"
				escribir "x1:"
				leer x1
				escribir "y1:"
				leer y1
				
				escribir "Punto 2:"
				escribir "x2:"
				leer x2
				escribir "y2:"
				leer y2
				
				escribir "La pendiente para los puntos (" x1 "," y1 ") y (" x2 "," y2 ") es ", pendiente_de(x1, y1, x2, y2)
			8:
				escribir "¡Adiós ;)!"
			de otro modo:
				escribir "Opción " numero_de_opcion " inválida."
		finsegun
		
		escribir "Pulsa Enter para continuar."
		leer temp
	hasta que (numero_de_opcion == 8)
finproceso

// Escribe el menú de opciones
//
subproceso escribirMenu
	escribir "================= MENU DE OPCIONES - CALCULADORA UBB ==================="
	escribir "NOMBRES DE ESTUDIANTES: JOSÉ BENAVENTE E ISMAEL CABRERA"
	escribir "OPCIONES:"
	escribir "1.- SUMA"
	escribir "2.- RESTA"
	escribir "3.- MULTIPLICACIÓN"
	escribir "4.- DIVISIÓN"
	escribir "5.- FACTORIAL"
	escribir "6.- RAIZ CUADRADA"
	escribir "7.- PENDIENTE DE LA RECTA"
	escribir "8.- SALIR"
	escribir "========================================================================"
finsubproceso

// Realiza cálculos simples y los imprime a pantalla.
// Hecho de esta manera para evitar código boilerplate
// @param operacion => ["sumar", "restar", "multiplicar", "dividir"]
//
subproceso calculo_simple(operacion)
	escribir mayusculas(operacion) " los números:"
	escribir "Número 1:"
	leer numero1
	escribir "Número 2:"
	leer numero2
	
	segun operacion
		"sumar":
			escribir numero1 " + " numero2 " = ", numero1 + numero2
		"restar":
			escribir numero1 " - " numero2 " = ", numero1 - numero2
		"multiplicar":
			escribir numero1 " * " numero2 " = ", numero1 * numero2
		"dividir":
			si (numero2 == 0)
				escribir "División por 0 inválida."
			sino
				escribir numero1 " / " numero2 " = ", numero1 / numero2
			finsi
	finsegun
finsubproceso

// Calcula el factorial de un número entero positivo target
// @param target Número del cual se desea calcular el factorial 
// @return El factorial de target, ó -1 si target no es entero o es negativo
//
subproceso factorial = factorial_de(target)
	si (target < 0 | target <> redon(target))
		factorial = -1
	sino
		factorial = 1;
		
		para count = 1 hasta target hacer
			factorial = factorial * count;
		finpara
	finsi
finsubproceso

// Retorna la raíz cuadrada de un número positivo subradical
// @param subradical Número del cual se desea calcular la raíz cuadrada 
// @return La raíz cuadrada del subradical proveído
//
subproceso raiz_cuadrada = raiz_cuadrada_de(subradical)
	aprox = subradical
	origen = 1
	precision = 0.0000000000000000000000000000000001

	mientras (aprox - origen > precision)
		aprox = (aprox + origen) / 2
		origen = subradical / aprox
	finmientras

	raiz_cuadrada = aprox
finsubproceso

// Cálculo de pendiente
//
subproceso pendiente = pendiente_de(x1, y1, x2, y2)
	pendiente = (y2 - y1) / (x2 - x1)
finsubproceso
