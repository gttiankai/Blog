import java.util.*;
class Tree{
    int height;
    Tree(){
        System.out.println("Plant a seeding");
        height = 0;
    }
    Tree(int initialHeight)
    {
        height = initialHeight;
        System.out.println("Creating new Tree that is "+ height + " feet tall");
        
    }
    void info()
    {
        System.out.println("Tree is "+ height + "feet tall!");
    }
    void info(String s)
    {
        System.out.println(s + ": Tree is " + height + " feet tall!");
    }
}

public class Overloading {
    public static void main(String[] args) {
        Tree t1 = new Tree();
        t1.info();
        t1.info("this is default declare");
        for(int i = 0; i < 5; i++)
        {
            Tree t = new Tree(i);
            t.info();
            t.info("overloaded method");
        }
    }
}