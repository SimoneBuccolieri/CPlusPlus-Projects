#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Character {
private:
    string nome;
    int hp;
    int attacco;

public:
    Character(string nome, int hp, int attacco) {
        this->nome = nome;
        this->hp = hp;
        this->attacco = attacco;
    }

    int getHp() {
        return hp;
    }

    void getStats() {
        cout << nome << ": " << hp << " HP" << endl;
    }

    void getAttacked(int n) {
        hp -= n;
        if (hp < 0) hp = 0;
    }

    void heal(int n) {
        hp += n;
        if (hp > 100) hp = 100;
    }

    int attack() {
        return rand() % (attacco + 1) + 5;
    }
};

class Monster {
private:
    string nome;
    int hp;
    int attacco;

public:
    Monster(string nome, int hp, int attacco) {
        this->nome = nome;
        this->hp = hp;
        this->attacco = attacco;
    }

    int getHp() {
        return hp;
    }

    void getStats() {
        cout << nome << ": " << hp << " HP" << endl;
    }

    void getAttacked(int n) {
        hp -= n;
        if (hp < 0) hp = 0;
    }

    void heal(int n) {
        hp += n;
        if (hp > 100) hp = 100;
    }

    int attack() {
        return rand() % (attacco + 1) + 5;
    }

    int action() {
        if (hp < 30) {
            return (rand() % 3 == 0) ? 0 : 1;
        }
        return 1;
    }
};

class Game {
private:
    Character player;
    Monster monster;
    int difficulty;

public:
    Game(int d)
        : player("Guerriero", 100, (d == 1 || d == 2) ? 15 : 12),
          monster("Drago", 100, (d == 1) ? 12 : (d == 2) ? 15 : (d == 3) ? 15 : 18),
          difficulty(d) {}

    void display() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        cout << "\n--- STATISTICHE ATTUALI ---" << endl;
        player.getStats();
        monster.getStats();
        cout << "---------------------------" << endl;
        cout << "Scegli un'azione:\n";
        cout << "1 - Attacca\n";
        cout << "2 - Cura (+10 HP)\n";
    }

    void start() {
        int azione, danno;

        while (player.getHp() > 0 && monster.getHp() > 0) {
            display();
            cin >> azione;

            if (azione == 0) {
                cout << "Hai abbandonato la battaglia!\n";
                return;
            }

            if (azione == 1) {
                danno = player.attack();
                monster.getAttacked(danno);
                cout << "Hai inflitto " << danno << " danni al mostro!\n";
            } else if (azione == 2) {
                player.heal(10);
                cout << "Ti sei curato di 10 HP!\n";
            } else {
                cout << "Scelta non valida! Perdi un turno.\n";
            }

            if (monster.getHp() > 0) {
                int mostroazione = monster.action();
                if (mostroazione == 1) {
                    danno = monster.attack();
                    player.getAttacked(danno);
                    cout << "Il mostro ti ha inflitto " << danno << " danni!\n";
                } else {
                    monster.heal(10);
                    cout << "Il mostro si è curato di 10 HP!\n";
                }
            }
        }

        cout << "\n--- RISULTATO DEL COMBATTIMENTO ---" << endl;
        if (player.getHp() > 0) {
            cout << "Hai sconfitto il mostro!\n";
        } else {
            cout << "Sei stato sconfitto dal mostro\n";
        }
    }
};

int main() {
    srand(time(0));
    int difficulty;

    cout << "Difficoltà: 1 (easy), 2 (medium), 3 (hard), 4 (extreme)" << endl;
    cout << "Difficoltà: ";
    cin >> difficulty;

    Game gioco(difficulty);
    gioco.start();

    return 0;
}
