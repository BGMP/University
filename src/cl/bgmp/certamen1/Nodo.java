package cl.bgmp.certamen1;

public class Nodo {
    int dato;
    Nodo sig;

    public Nodo(int x){
        dato = x;
        sig = null;
    }

    @Override
    public String toString(){
        return dato+"-->";
    }
}
