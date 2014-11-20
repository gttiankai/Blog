import java.util.*;
class Book{
    boolean checkedOut = false;
    Book(boolean checkOut){
        checkedOut = checkOut;
    }
    void checkIn() {
        checkedOut = false;
    }

    protected void finalize(){
        if(checkedOut){
            System.out.println("ERRO: checked out!");
        }
    }
}
public class TerminationCondition {
    public static void main(String[] args) {
        Book novel = new Book(true);
        novel.checkIn();
        new Book(true);
        // 该方法用于强制的进行终结动作
        System.gc();
    }
}


