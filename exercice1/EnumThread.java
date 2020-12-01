package exercice1;

public class EnumThread extends Thread {
    @Override
    public void run() {
        System.out.println("Thread started.");
        for(int i=1; i<27; i++){
            System.out.println("Enum: "+i);
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println("Thread ended.");
    }
}
