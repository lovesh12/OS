class Shared {
    boolean[] flag;
    int turn;
    int counter;

    Shared() {
        counter = 0;
        flag = new boolean[2];
        flag[0] = false;
        flag[1] = false;
    }
}

class Process1 extends Thread {

    Shared s;

    Process1(Shared s) {
        this.s = s;
    }

    public void run() {
        int loop = 10;
        do
        {
            s.flag[0] = true;
            s.turn = 1;

            while (s.flag[1] && s.turn == 1)
                ;
            // Critical Section
            s.counter++;
            System.out.println("Counter after Process 1: "+s.counter);
            s.flag[0] = false;
        } while (loop-- > 0);
    }
}

class Process2 extends Thread {
    Shared s;

    Process2(Shared s) {
        this.s = s;
    }

    public void run() {
        int loop = 10;
        do
        {
            s.flag[1] = true;
            s.turn = 0;

            while (s.flag[0] && s.turn == 0)
                ;
            // Critical Section
            s.counter++;
            System.out.println("Counter after Process 2: "+s.counter);
            s.flag[1] = false;
        } while (loop-- > 0);
    }
}

public class Peterson {
    public static void main(String args[]) throws InterruptedException {
        Shared s = new Shared();

        Process1 p1 = new Process1(s);
        Process2 p2 = new Process2(s);

        p1.start();
        p2.start();

        p1.join();
        p2.join();
    }
}
