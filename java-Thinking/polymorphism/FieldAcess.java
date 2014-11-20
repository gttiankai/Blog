class Super{
    public int field = 0;
    public int getFiled(){return field;}
}

class Sub extends Super {
    public int field = 1;
    public int getFiled(){ return field;}
    public int getSuperField(){ return super.field;}
}
public class FieldAcess {
    public static void main(String[] args) {
        Super  sup = new Sub();
        System.out.println("sup.field = "+ sup.field + ". sup.getFiled = "
                           + sup.getFiled());

        Sub sub = new Sub();
        System.out.println("sub.field = "+ sub.field + ", sub.getFiled= "+
                           sub.getFiled() + ", sub.getSuperField =" +
                           sub.getSuperField());
    }
}
