package polymorphism;
import java.lang.*;

public class PrivateOverride {
    protected   void f(){
        System.out.println("private f()");
    }
    
    public static void main(String[] args) {
        PrivateOverride po = new Derived();
        po.f();
    }
}

class Derived extends PrivateOverride {

    public void f(){
        System.out.println("public f()");
    }
}