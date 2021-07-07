package cl.bgmp.certamen1;

public class Certamen1 {
    public static void main(String [] args) {
        testEliminarPosicion();
        testIntercambiar();
        testPalindromo();
    }

    public static void testEliminarPosicion() {
        Lista list = new Lista();
        list.insertarFinal(2);
        list.insertarFinal(4);
        list.insertarFinal(6);

        System.out.println(list);
        list.eliminarPorPosicion(2);
        System.out.println(list);
    }

    public static void testIntercambiar() {
        Lista list = new Lista();
        list.insertarFinal(2);
        list.insertarFinal(4);
        list.insertarFinal(6);
        list.insertarFinal(7);

        System.out.println(list);
        list.intercambiar();
        System.out.println(list);
    }

    public static void testPalindromo() {
        Lista list = new Lista();
        list.insertarFinal(1);
        list.insertarFinal(2);
        list.insertarFinal(5);
        list.insertarFinal(2);
        list.insertarFinal(1);

        System.out.println(list);
        System.out.println(list.esPalindroma());
    }
}