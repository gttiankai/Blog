class Super{
	public int filed = 0;
	public int getFiled(){return filed;};
}
class Sub extends Super{
	public int filed = 1;
	public int getFiled(){return filed;};
}

public class FiledAccess {
    public static void main(String[] args) {

    	Super sup = new Sub();
    	System.out.println("Super.filed = "+ sup.filed +
															"sup.getFiled() = " +sup.getFiled());
    	Sub sub = new Sub();
    	System.out.println("sub.filed = " + sub.filed +
																"sub.getFiled() = " +sub.getFiled());
        }
}
