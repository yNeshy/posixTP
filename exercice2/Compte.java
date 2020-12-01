package exercice2;

public class Compte {

    int solde ;
    public Compte(){
        this.solde = 100;
    }

    public Compte(int solde){
        this.solde = solde;
    }

    public boolean retirer(int montant){
        if (this.solde > montant) {
            this.solde -= montant;
            return true;
        }
        else
            return false;
    }
}
