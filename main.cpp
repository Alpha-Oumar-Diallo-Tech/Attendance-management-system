#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct Presence
{
    int numero;
    string matricule;
    string nom;
    string prenom;
    string departement;
    string date;
    string heureArrivee;
    string heureDepart;
};

const int MAX = 500;
Presence presences[MAX];
int nbrPresences = 0;

void afficherBienvenue()
{
    cout << "===================================================" << endl;
    cout << "GESTION DES PRESENCES DES EMPLOYES !" << endl;
    cout << "===================================================" << endl;
    cout << "Ce programme permet a la Direction des Ressources" << endl;
    cout << "Humaines de controler la presence des employes." << endl;
    cout << "Auteurs : Djiba" << endl;
    cout << endl;
}

bool identifer()
{
    const string UTILISATEUR = "admin";
    const string MOT_DE_PASSE = "1234";
    const int TENTATIVES_MAX = 3;
    int tentative = 0;

    string saisiUtilisateur;
    string saisiMotDePasse;

    while (tentative < TENTATIVES_MAX)
    {
        cout << "Entrez votre nom d'utilisateur : ";
        cin >> saisiUtilisateur;
        cout << "Entrez votre mot de passe : ";
        cin >> saisiMotDePasse;

        if (saisiUtilisateur == UTILISATEUR && saisiMotDePasse == MOT_DE_PASSE)
        {
            return true;
        }
        tentative++;
        cout << "Identifiants incorrects. Tentatives restantes : "
             << 3 - tentative << endl;
    }
    return false;
}

void afficherMenu()
{
    cout << endl
         << "========== MENU ==========" << endl;
    cout << "1. Enregistrer une presence" << endl;
    cout << "2. Verification des presences d'un employe a une date" << endl;
    cout << "3. Enregistrer l'heure de depart d'un employe" << endl;
    cout << "4. Supprimer la presence d'un employe" << endl;
    cout << "7. Modifier une presence" << endl;
    cout << "8. Situation des presences" << endl;
    cout << "9. Liste des presences a une date" << endl;
    cout << "10. Liste de toutes les presences" << endl;
    cout << "11. Liste des presences d'un employe a une date" << endl;
    cout << "12. Liste des presences d'un employe entre deux dates" << endl;
    cout << "13. Liste de toutes les presences d'un employe" << endl;
    cout << "14. Situation par departement a une date" << endl;
    cout << "15. Situation par departement entre deux dates" << endl;
    cout << "16. Situation globale par departement" << endl;
    cout << "0. Quitter" << endl;
}

string lireTexte(string invite)
{
    string texte;
    cout << invite;
    getline(cin >> ws, texte);
    return texte;
}

bool dateValide(string d)
{
    if (d.length() != 10 || d[2] != '/' || d[5] != '/')
        return false;
    for (int i = 0; i < 10; i++)
    {
        if (i != 2 && i != 5 && !isdigit(d[i]))
            return false;
    }
    return true;
}

string lireDate(string invite)
{
    string d = lireTexte(invite);
    while (!dateValide(d))
    {
        cout << "Format invalide. Utilisez jj/mm/aaaa." << endl;
        d = lireTexte(invite);
    }
    return d;
}

int dateEnNombre(string d)
{
    int jour = stoi(d.substr(0, 2));
    int mois = stoi(d.substr(3, 2));
    int annee = stoi(d.substr(6, 4));
    return annee * 10000 + mois * 100 + jour;
}

int chercherPresence(Presence presences[], int nbrPresences, string matricule, string date)
{
    for (int i = 0; i < nbrPresences; i++)
    {
        if (presences[i].matricule == matricule && presences[i].date == date)
            return i;
    }
    return -1;
}

int prochainNumero(Presence presences[], int nbrPresences)
{
    int max = 0;
    for (int i = 0; i < nbrPresences; i++)
    {
        if (presences[i].numero > max)
            max = presences[i].numero;
    }
    return max + 1;
}

void afficherPresence(Presence p)
{
    cout << "Numero: " << p.numero << endl;
    cout << "Matricule: " << p.matricule << endl;
    cout << "Nom: " << p.nom << endl;
    cout << "Prenom: " << p.prenom << endl;
    cout << "Departement: " << p.departement << endl;
    cout << "Date: " << p.date << endl;
    cout << "Heure d'arrivee: " << p.heureArrivee << endl;
    cout << "Heure de depart: " << (p.heureDepart == "" ? "pas encore" : p.heureDepart) << endl;
    cout << "-----------------------------------------------" << endl;
}

void enregistrerPresence(Presence presences[], int &nbrPresences)
{
    if (nbrPresences >= MAX)
    {
        cout << "Le tableau est plein." << endl;
        return;
    }

    Presence p;
    p.matricule = lireTexte("Entrez le numero de matricule : ");
    p.date = lireDate("Entrez la date (jj/mm/aaaa) : ");

    if (chercherPresence(presences, nbrPresences, p.matricule, p.date) != -1)
    {
        cout << "Cet employe est deja enregistre a cette date." << endl;
        return;
    }

    p.heureArrivee = lireTexte("Entrez l'heure d'arrivee (hh:mm) : ");
    p.nom = lireTexte("Entrez le nom : ");
    p.prenom = lireTexte("Entrez le prenom : ");
    p.departement = lireTexte("Entrez le departement : ");
    p.heureDepart = "";
    p.numero = prochainNumero(presences, nbrPresences);

    presences[nbrPresences] = p;
    nbrPresences++;
    cout << "Presence enregistree avec succes (numero " << p.numero << ")." << endl;
}

void verifierPresence(Presence presences[], int nbrPresences)
{
    string matricule = lireTexte("Entrez le matricule : ");
    string date = lireDate("Entrez la date (jj/mm/aaaa) : ");

    int i = chercherPresence(presences, nbrPresences, matricule, date);
    if (i == -1)
    {
        cout << "Aucune presence ne correspond a ce matricule a cette date." << endl;
    }
    else
    {
        cout << "Presence correspondante :" << endl;
        afficherPresence(presences[i]);
    }
}

void listeToutesPresences(Presence presences[], int nbrPresences)
{
    cout << "=============== Liste des presences ===============" << endl;
    if (nbrPresences == 0)
        cout << "Aucune presence enregistree." << endl;
    for (int i = 0; i < nbrPresences; i++)
        afficherPresence(presences[i]);
}

void enregistrerDepart(Presence presences[], int nbrPresences)
{
    string matricule = lireTexte("Entrez le matricule : ");
    string date = lireDate("Entrez la date (jj/mm/aaaa) : ");

    int i = chercherPresence(presences, nbrPresences, matricule, date);
    if (i == -1)
        cout << "Cet employe n'est pas enregistre a cette date." << endl;
    else if (presences[i].heureDepart != "")
        cout << "Le depart est deja enregistre : " << presences[i].heureDepart << endl;
    else
    {
        presences[i].heureDepart = lireTexte("Entrez l'heure de depart (hh:mm) : ");
        cout << "Heure de depart enregistree." << endl;
    }
}

void supprimerPresence(Presence presences[], int &nbrPresences)
{
    string matricule = lireTexte("Entrez le matricule : ");
    string date = lireDate("Entrez la date (jj/mm/aaaa) : ");

    int i = chercherPresence(presences, nbrPresences, matricule, date);
    if (i == -1)
    {
        cout << "Aucune presence ne correspond." << endl;
        return;
    }

    afficherPresence(presences[i]);
    string reponse = lireTexte("Confirmer la suppression (o/n) : ");
    if (reponse == "o" || reponse == "O")
    {
        for (int j = i; j < nbrPresences - 1; j++)
            presences[j] = presences[j + 1];
        nbrPresences--;
        cout << "Presence supprimee." << endl;
    }
    else
        cout << "Suppression annulee." << endl;
}

void modifierPresence(Presence presences[], int nbrPresences)
{
    string matricule = lireTexte("Entrez le matricule : ");
    string date = lireDate("Entrez la date (jj/mm/aaaa) : ");

    int i = chercherPresence(presences, nbrPresences, matricule, date);
    if (i == -1)
    {
        cout << "Aucune presence ne correspond." << endl;
        return;
    }

    afficherPresence(presences[i]);
    cout << "1. Nom" << endl;
    cout << "2. Prenom" << endl;
    cout << "3. Departement" << endl;
    cout << "4. Heure d'arrivee" << endl;
    cout << "5. Heure de depart" << endl;
    cout << "Champ a modifier : ";
    int choix;
    cin >> choix;

    switch (choix)
    {
    case 1:
        presences[i].nom = lireTexte("Nouveau nom : ");
        break;
    case 2:
        presences[i].prenom = lireTexte("Nouveau prenom : ");
        break;
    case 3:
        presences[i].departement = lireTexte("Nouveau departement : ");
        break;
    case 4:
        presences[i].heureArrivee = lireTexte("Nouvelle heure d'arrivee : ");
        break;
    case 5:
        presences[i].heureDepart = lireTexte("Nouvelle heure de depart : ");
        break;
    default:
        cout << "Choix invalide." << endl;
        return;
    }
    cout << "Presence modifiee." << endl;
}

void situationPresences(Presence presences[], int nbrPresences)
{
    int sansDepart = 0;
    for (int i = 0; i < nbrPresences; i++)
    {
        if (presences[i].heureDepart == "")
            sansDepart++;
    }
    cout << "Nombre de presences enregistrees : " << nbrPresences << endl;
    cout << "Places restantes : " << MAX - nbrPresences << endl;
    cout << "Presences sans heure de depart : " << sansDepart << endl;
}

void listePresencesDate(Presence presences[], int nbrPresences)
{
    string date = lireDate("Entrez la date (jj/mm/aaaa) : ");
    int compte = 0;
    for (int i = 0; i < nbrPresences; i++)
    {
        if (presences[i].date == date)
        {
            afficherPresence(presences[i]);
            compte++;
        }
    }
    if (compte == 0)
        cout << "Aucune presence a cette date." << endl;
    else
        cout << compte << " presence(s) a cette date." << endl;
}

void listePresencesEmployeDate(Presence presences[], int nbrPresences)
{
    string matricule = lireTexte("Entrez le matricule : ");
    string date = lireDate("Entrez la date (jj/mm/aaaa) : ");
    int compte = 0;
    for (int i = 0; i < nbrPresences; i++)
    {
        if (presences[i].matricule == matricule && presences[i].date == date)
        {
            afficherPresence(presences[i]);
            compte++;
        }
    }
    if (compte == 0)
        cout << "Aucune presence pour cet employe a cette date." << endl;
}

void listePresencesEmployePeriode(Presence presences[], int nbrPresences)
{
    string matricule = lireTexte("Entrez le matricule : ");
    int debut = dateEnNombre(lireDate("Date de debut (jj/mm/aaaa) : "));
    int fin = dateEnNombre(lireDate("Date de fin (jj/mm/aaaa) : "));

    if (debut > fin)
    {
        cout << "La date de debut doit preceder la date de fin." << endl;
        return;
    }

    int compte = 0;
    for (int i = 0; i < nbrPresences; i++)
    {
        int d = dateEnNombre(presences[i].date);
        if (presences[i].matricule == matricule && d >= debut && d <= fin)
        {
            afficherPresence(presences[i]);
            compte++;
        }
    }
    if (compte == 0)
        cout << "Aucune presence sur cette periode." << endl;
}

void listeToutesPresencesEmploye(Presence presences[], int nbrPresences)
{
    string matricule = lireTexte("Entrez le matricule : ");
    int compte = 0;
    for (int i = 0; i < nbrPresences; i++)
    {
        if (presences[i].matricule == matricule)
        {
            afficherPresence(presences[i]);
            compte++;
        }
    }
    if (compte == 0)
        cout << "Aucune presence pour cet employe." << endl;
    else
        cout << compte << " presence(s) au total." << endl;
}

int listerDepartements(Presence presences[], int nbrPresences, string departements[])
{
    int nb = 0;
    for (int i = 0; i < nbrPresences; i++)
    {
        bool existe = false;
        for (int j = 0; j < nb; j++)
        {
            if (departements[j] == presences[i].departement)
            {
                existe = true;
                break;
            }
        }
        if (!existe)
        {
            departements[nb] = presences[i].departement;
            nb++;
        }
    }
    return nb;
}

void afficherSituationDepartements(Presence presences[], int nbrPresences, int debut, int fin)
{
    string departements[MAX];
    int nbDep = listerDepartements(presences, nbrPresences, departements);

    if (nbDep == 0)
    {
        cout << "Aucune presence enregistree." << endl;
        return;
    }

    int total = 0;
    for (int k = 0; k < nbDep; k++)
    {
        int compte = 0;
        for (int i = 0; i < nbrPresences; i++)
        {
            int d = dateEnNombre(presences[i].date);
            if (presences[i].departement == departements[k] && d >= debut && d <= fin)
                compte++;
        }
        cout << departements[k] << " : " << compte << " presence(s)" << endl;
        total += compte;
    }
    cout << "Total : " << total << " presence(s)" << endl;
}

void situationDepartementDate(Presence presences[], int nbrPresences)
{
    int n = dateEnNombre(lireDate("Entrez la date (jj/mm/aaaa) : "));
    afficherSituationDepartements(presences, nbrPresences, n, n);
}

void situationDepartementPeriode(Presence presences[], int nbrPresences)
{
    int debut = dateEnNombre(lireDate("Date de debut (jj/mm/aaaa) : "));
    int fin = dateEnNombre(lireDate("Date de fin (jj/mm/aaaa) : "));
    if (debut > fin)
    {
        cout << "La date de debut doit preceder la date de fin." << endl;
        return;
    }
    afficherSituationDepartements(presences, nbrPresences, debut, fin);
}

void situationGlobaleDepartement(Presence presences[], int nbrPresences)
{
    afficherSituationDepartements(presences, nbrPresences, 0, 99999999);
}

int main()
{
    afficherBienvenue();

    if (!identifer())
    {
        cout << "Acces refuse." << endl;
        return 0;
    }

    int choix;
    do
    {
        afficherMenu();
        cout << "Entrez votre choix : ";
        cin >> choix;

        switch (choix)
        {
        case 1:
            enregistrerPresence(presences, nbrPresences);
            break;
        case 2:
            verifierPresence(presences, nbrPresences);
            break;
        case 3:
            enregistrerDepart(presences, nbrPresences);
            break;
        case 4:
            supprimerPresence(presences, nbrPresences);
            break;
        case 7:
            modifierPresence(presences, nbrPresences);
            break;
        case 8:
            situationPresences(presences, nbrPresences);
            break;
        case 9:
            listePresencesDate(presences, nbrPresences);
            break;
        case 10:
            listeToutesPresences(presences, nbrPresences);
            break;
        case 11:
            listePresencesEmployeDate(presences, nbrPresences);
            break;
        case 12:
            listePresencesEmployePeriode(presences, nbrPresences);
            break;
        case 13:
            listeToutesPresencesEmploye(presences, nbrPresences);
            break;
        case 14:
            situationDepartementDate(presences, nbrPresences);
            break;
        case 15:
            situationDepartementPeriode(presences, nbrPresences);
            break;
        case 16:
            situationGlobaleDepartement(presences, nbrPresences);
            break;
        case 0:
            cout << "Au revoir." << endl;
            break;
        default:
            cout << "Choix invalide." << endl;
        }
    } while (choix != 0);

    return 0;
}