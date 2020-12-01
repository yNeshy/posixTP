package exercice2;

public class JobSylvieEtBruno implements Runnable {
    Compte compte ;
    String nom ;
    int montant;
    public JobSylvieEtBruno(String nom, Compte compte, int montantDebit){
        this.nom = nom;
        this.compte = compte;
        this.montant = montantDebit;
    }
    @Override
    public void run() {
        int i = 10;
        while(i>0) {
            i--;
            if (this.compte.retirer(this.montant)) {
                System.out.println(this.nom + " a débiter " + this.montant + "$");
            } else System.out.println(this.nom + " ne peut pas débiter: Solde insuffisant.");
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
