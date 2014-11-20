public class ArrayConstrcut {
    
    //int a[] = new int[10];
    //@当我们的初始化数组在这里的时候，就会产生一个编译的错误，
    public static void main(String[] args) {
        //当时在这个地方的时候，我们就不会产生编译错误，
        
        int a[] = new int[10];// 编译器对堆上分配的空间进行初始化了！
        System.out.println(a[6]);        
        
    }
}
