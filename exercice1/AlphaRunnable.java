package exercice1;

public class AlphaRunnable implements Runnable {
    @Override
    public void run() {
        System.out.println("Runnable started.");
        for (char c='a'; c<='z'; c++){
            System.out.println("Runnable: "+c);
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println("Runnable ended.");
    }
}
