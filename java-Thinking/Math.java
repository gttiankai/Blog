import java.util.*;
public class Math {

    static int max(int a, int b){
        return a > b? a:b;
    }

    static short max(short a, short b){
        return a > b? a:b;
    }
    static float max(float a, float b){
        return a > b? a:b;
    }
    public static void main(String[] args) {

        int a1 = 1, b1 = 2;
        short a2 = 1, b2 = 2;
        float a3 = 1, b3 = 2;
        System.out.println(max(a1,b1));
        System.out.println(max(a2,b2));
        System.out.println(max(a3,b3));
    }
}
