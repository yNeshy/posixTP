package exercice2;

public class Exercice2Main {
    public  static void main(String[]args) {
        Compte compte = new Compte();   // Par défaut, contient 100$.
        JobSylvieEtBruno sylvie = new JobSylvieEtBruno("Sylvie", compte, 5);
        JobSylvieEtBruno bruno = new JobSylvieEtBruno("Bruno", compte, 7);
        new Thread(sylvie).start();
        new Thread(bruno).start();
    }
}
