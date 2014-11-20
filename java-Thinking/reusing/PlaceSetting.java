import java.util.*;

class Plate {
    Plate(int i){
        System.out.println("plate constructor" + i);
    }
}

class DinnerPlate extends Plate {

    DinnerPlate(int i){
        super(i);
        System.out.println("DinnderPlate constructor" + i);
    }
}

class Utensil{
    
    Utensil(int i){
        System.out.println("Utensil constructor"+ i);
    }
}

class Spoon extends Utensil{
    Spoon(int i){
        super(i);
        System.out.println("Spoon constructor"+ i);
    }
}
class Fork extends Utensil{
    Fork(int i){
        super(i);
        System.out.println("fork constructor" + i);
    }
}
class Knife extends Utensil{
    Knife(int i){
        super(i);
        System.out.println("Knife constructor"+ i);
    }
}
class Custom{
    Custom(int i){
        System.out.println("custom constructor"+ i);
    }
}
public class PlaceSetting extends Custom{
    private Spoon sp;
    private Fork frk;
    private Knife kn;
    private DinnerPlate pl;

    // constructor the father class
    public PlaceSetting(int i){
        super(i + 1);
        sp = new Spoon(i+2);
        frk = new Fork(i+3);
        kn = new Knife(i+4);
        pl = new DinnerPlate(i+5);
        System.out.println(" Pleastting constructor");
    }
    public static void main(String[] args) {
        PlaceSetting x = new PlaceSetting(9);
    }
}
