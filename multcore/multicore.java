// LockOne
public class lock {

    class LockOne implements Lock{
        private boolean[] flag = new boolean[2];
        // thread-local index , 0 or 1
        public void lock(){
            int i = ThreadID.get();
            int j = 1 - i;
            flag[i] = true;
            while(flag[j])
            ;
        }
        public void unlock()
        {
            int i = ThreadID.get();
            flag[i] = false;
        }
    }


// peterson lock

    class Peterson implements lock {
        private volatile boolean[] falg = new boolean[2];
        private volatile int victim;
        public void lock(){
            int i = ThreadID.get();
            int j = 1 - i;
            flag[i] = true;
            victim = i;
            while (flag[j] && victim == i)
                {};
        }
        public void unlock(){
            int i = ThreadID.get();
            flag[i] = false;
        }
    }

}