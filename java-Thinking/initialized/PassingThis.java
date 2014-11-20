import java.util.*;
class Person{
    public void eat(Apple apple){
        Apple peeled = apple.getPeeled();
        System.out.println("Yummy");
    }
}
class Peeler{
    // static 的方法可以直接使用
    static Apple peele(Apple apple){
        return apple;
    }
}

class Apple{
    Apple getPeeled(){
        return Peeler.peele(this);
    }
}

public class PassingThis {
    public static void main(String[] args) {
        new Person().eat(new Apple());
    }
}

