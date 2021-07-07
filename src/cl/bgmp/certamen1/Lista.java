package cl.bgmp.certamen1;

public class Lista {
    Nodo inicio;

    public Lista(){
        inicio=null;
    }

    public void insertarInicio(int x){
        Nodo nuevo = new Nodo(x);
        if(inicio==null){
            inicio = nuevo;
        }
        else{
            nuevo.sig = inicio;
            inicio = nuevo;
        }
    }

    public void insertarFinal(int x){
        Nodo nuevo = new Nodo(x);

        if(inicio==null){
            inicio = nuevo;
        }
        else{
            Nodo aux =inicio;
            while(aux.sig!=null){
                aux = aux.sig;
            }
            aux.sig = nuevo;
        }
    }

    public boolean encontrar(int x){
        Nodo aux =inicio;
        while(aux!=null){
            if(aux.dato==x){
                return true;
            }
            aux=aux.sig;
        }
        return false;
    }

    public void eliminar(int x){
        if(inicio.dato ==x){
            inicio = inicio.sig;
        }
        else{
            Nodo anterior = inicio;
            Nodo aux = inicio.sig;
            while(aux!=null){
                if(aux.dato==x){
                    anterior.sig=aux.sig;
                    aux = aux.sig;
                }
                else{
                    anterior=anterior.sig;
                    aux=aux.sig;
                }
            }
        }
    }

    void insertarAntes(int x, int antesDe){

        if(inicio.dato==antesDe) {
            insertarInicio(x);
        }
        else{
            Nodo aux = inicio.sig;
            Nodo anterior = inicio;
            while(aux!=null){
                if(aux.dato==antesDe){
                    Nodo nuevo = new Nodo(x);
                    anterior.sig=nuevo;
                    nuevo.sig = aux;
                    anterior=aux;
                    aux = aux.sig;
                }
                else {
                    aux = aux.sig;
                    anterior=anterior.sig;
                }
            }
        }

    }

    void insertarDespues(int x, int despuesDe){
        Nodo nuevo = new Nodo(x);
        Nodo aux = inicio;
        while(aux!=null){
            if(aux.dato==despuesDe){
                nuevo.sig = aux.sig;
                aux.sig = nuevo;
                break;
            }
            else{
                aux = aux.sig;
            }
        }
    }

    void intercambiar(int a,int b){
        Nodo aux = inicio;
        while(aux!=null){
            if(aux.dato==a){
                aux.dato=b;
            }
            aux=aux.sig;
        }
    }

    float promedio(){
        float promedio=0;
        int cont=0;
        Nodo aux = inicio;
        while(aux!=null){
            cont++;
            promedio+=aux.dato;
            aux=aux.sig;
        }
        return promedio/cont;
    }
    void listaMayoresProm(){
        Nodo aux = inicio;
        float promedio = promedio();

        while(aux!=null){
            if(aux.dato<=promedio){
                eliminar(aux.dato);
            }
            aux=aux.sig;
        }
    }

    public void eliminarPorPosicion(int posicion) {
        if (inicio == null || posicion < 1) return;

        Nodo instancia = this.inicio;
        while (posicion != 1) {
            instancia = instancia.sig;
            posicion--;
        }

        this.eliminar(instancia.dato);
    }

    public void intercambiar() {
        int size = 1;
        Nodo instance = this.inicio;
        while (instance.sig != null) {
            instance = instance.sig;
            size++;
        }

        Nodo origin = inicio;
        Nodo next = inicio.sig;
        int element;
        if (size % 2 == 0) {
            while (next != null) {
                element = origin.dato;
                origin.dato = next.dato;
                next.dato = element;
                origin = next.sig;
                next = origin.sig;

                if (next.sig != null) continue;

                element = origin.dato;
                origin.dato = next.dato;
                next.dato = element;
                break;
            }
        } else {
            while (next != null) {
                element = origin.dato;
                origin.dato = next.dato;
                next.dato = element;
                origin = next.sig;
                next = origin.sig;
            }
        }
    }
    public boolean esPalindroma() {
        if (inicio == null) return false;

        int size = 1;
        Nodo instance = this.inicio;
        while (instance.sig != null) {
            instance = instance.sig;
            size++;
        }

        // 1-->2-->4-->2-->1
        Nodo node = this.inicio;
        int half = size / 2;
        int[] firstHalf = new int[half]; // [1,2]
        int[] secondHalf = new int[half]; // [1,2]

        int i = 0;
        for (; i < half; i++) {
            firstHalf[i] = node.dato;
            node = node.sig;
        }

        if (size % 2 != 0) node = node.sig;

        for (; i > 0; i--) {
            secondHalf[i - 1] = node.dato;
            node = node.sig;
        }

        for (int j = 0; j < half; j++) {
            if (firstHalf[j] != secondHalf[j]) return false;
        }

        return true;
    }

    @Override
    public String toString(){
        String salida ="";
        Nodo aux = inicio;

        while(aux!=null){
            salida = salida + aux.toString();
            aux = aux.sig;
        }

        return salida;
    }
}
