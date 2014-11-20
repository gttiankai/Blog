import java.util.*;

class WithFinals{
    public  void f(){
        System.out.println("withFinals.f()");
    }
    public void g(){
        System.out.println("withFinals.g()");
    }
}

class OveridingPrivate extends WithFinals{
    @Override
    public void f(){
        System.out.println("OveridingPrivate.f()");
    }
    @Override
    public void g(){
        System.out.println("OveridingPrivate.g()");
    }
}
class OveridingPrivate2 extends OveridingPrivate{
    
    public  void f(){
        System.out.println("OveridingPrivate2.f()");
    }
    
    public final void g(){
        System.out.println("OveridingPrivate2.g()");
    }
}
public class FinalOverridingIllusion {
    public static void main(String[] args) {
        OveridingPrivate2 op2 = new OveridingPrivate2();
        op2.f();
        op2.g();
        OveridingPrivate op = op2;
        op.f();
        op.g();
        WithFinals wf = op2;
        wf.f();
        wf.g();
    }
}
