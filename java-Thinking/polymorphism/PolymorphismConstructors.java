import java.lang.*;

class Glyph{
    void draw(){System.out.println("Glyph.draw()");}
    Glyph(){

        System.out.println("Glyph befor draw()");
        draw();
        System.out.println("Glyph after draw()");
    }
}

class RoundGlyph extends Glyph{
    private int radius = 1;
    RoundGlyph (int r){
        radius = r;
        System.out.println("RoundGlyph.RoundGlyph().radius = " + radius);
    }
    // 将父类中的方法重载了，所以我们调用的时候是调用的子类中的方法．
    void draw(){
        System.out.println("RoundGlyph.draw(). radius = "+ radius);
    }
}

public class PolymorphismConstructors {
    public static void main(String[] args) {
        new RoundGlyph(5);
    }
}
