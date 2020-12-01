package exercice1;

public class Exercice1Main {
    public static void main(String[]args){
        new EnumThread().start();
        new Thread(new AlphaRunnable() ).start();
    }
}
