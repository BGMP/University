proceso calculadora
	repetir
		escribirMenu
		
		escribir "Elije una opci�n:"
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
				escribir "Calcular la ra�z cuadrada de:"
				leer subradical
				
				si (subradical < 0)
					escribir "Imposible calcular la ra�z cuadrada de " subradical ". El n�mero debe ser positivo."
				sino
					escribir "La ra�z cuadrada de " subradical " es ", raiz_cuadrada_de(subradical)
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
				escribir "�Adi�s ;)!"
			de otro modo:
				escribir "Opci�n " numero_de_opcion " inv�lida."
		finsegun
		
		escribir "Pulsa Enter para continuar."
		leer temp
	hasta que (numero_de_opcion == 8)
finproceso

// Escribe el men� de opciones
//
subproceso escribirMenu
	escribir "================= MENU DE OPCIONES - CALCULADORA UBB ==================="
	escribir "NOMBRES DE ESTUDIANTES: JOS� BENAVENTE E ISMAEL CABRERA"
	escribir "OPCIONES:"
	escribir "1.- SUMA"
	escribir "2.- RESTA"
	escribir "3.- MULTIPLICACI�N"
	escribir "4.- DIVISI�N"
	escribir "5.- FACTORIAL"
	escribir "6.- RAIZ CUADRADA"
	escribir "7.- PENDIENTE DE LA RECTA"
	escribir "8.- SALIR"
	escribir "========================================================================"
finsubproceso

// Realiza c�lculos simples y los imprime a pantalla.
// Hecho de esta manera para evitar c�digo boilerplate
// @param operacion => ["sumar", "restar", "multiplicar", "dividir"]
//
subproceso calculo_simple(operacion)
	escribir mayusculas(operacion) " los n�meros:"
	escribir "N�mero 1:"
	leer numero1
	escribir "N�mero 2:"
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
				escribir "Divisi�n por 0 inv�lida."
			sino
				escribir numero1 " / " numero2 " = ", numero1 / numero2
			finsi
	finsegun
finsubproceso

// Calcula el factorial de un n�mero entero positivo target
// @param target N�mero del cual se desea calcular el factorial 
// @return El factorial de target, � -1 si target no es entero o es negativo
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

// Retorna la ra�z cuadrada de un n�mero positivo subradical
// @param subradical N�mero del cual se desea calcular la ra�z cuadrada 
// @return La ra�z cuadrada del subradical prove�do
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

// C�lculo de pendiente
//
subproceso pendiente = pendiente_de(x1, y1, x2, y2)
	pendiente = (y2 - y1) / (x2 - x1)
finsubproceso
