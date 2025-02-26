#include <iostream>
#include <vector>
using namespace std;

class Auto {
protected:
    int x,y;
public:
    Auto(int x,int y) {
        this->x=x;
        this->y=y;
    }
    void move() {
        y++;
        }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
};
class Semaforo {
private:
    int colore=0, posizione; //0 rosso, 1 giallo, 2 verde
public:
    Semaforo(int p) {
        this->posizione=p;
    }
    void CambiaColore() {
        if (colore==0) {
            if (rand()%100 <33) {
                colore=2;
            }
        }
        if (colore==1) {
            colore=0;
        }
        if (colore==2) {
            if (rand()%100 <33) {
                colore=1;
            }
        }

    }
    int getColore() {
        return colore;
    }
    int getPos() {
        return posizione;
    }
};
class Strada {
private:
    int corsie;
    vector<Auto> cars;
    vector<Semaforo> semafori;
    vector<vector<string>> road;

public:
    Strada(int corsie) {
        this->corsie = corsie;
        road.resize(corsie, vector<string>(11,".")); //tot corsie da 11 spazi
        for (int i=0;i<corsie;i++) {
            Semaforo s(i);
            semafori.push_back(s);
        }
    }
    void spawnCar(int numcars, int maxcorsie) {
        for (int i=0;i<numcars;i++) {
            Auto car(rand()%maxcorsie,0);
            cars.push_back(car);
        }

    }

    void display() {
        road.assign(corsie, vector<string>(11, "⬛"));

        for (Semaforo s : semafori) {
            if (s.getColore()==0)
                road[s.getPos()][5] = "🔴";
            if (s.getColore()==1)
                road[s.getPos()][5] = "🟡";
            if (s.getColore()==2)
                road[s.getPos()][5] = "🟢";
        }
        for (Auto a : cars) {
            road[a.getX()][a.getY()] = "🚗";
        }
        for (int i=0;i<corsie;i++) {
            cout<<i;
            for (int j=0;j<11;j++) {
                cout<<road[i][j];
            }
            cout<<endl;
        }
    }
    void update() {
        cars.erase(remove_if(cars.begin(), cars.end(), [](Auto &a) {
            return a.getY() >= 10;
        }), cars.end());

        for (Semaforo &s : semafori) {
            s.CambiaColore();
        }
        for (Auto &a : cars) {
            int nextY = a.getY() + 1;

            // Se l'auto è nella colonna 4, controlla il semaforo prima di avanzare
            if (a.getY() == 4) {
                if (semafori[a.getX()].getColore() == 2) { // Verde
                    a.move(); // L'auto può avanzare oltre il semaforo
                }
            } else {
                // Se l'auto non è alla colonna 4, avanza normalmente se la strada è libera
                if (road[a.getX()][nextY] == "⬛") {
                    a.move();
                }
            }
        }
    }
};

int main() {
    srand(time(0));
    int corsie=1;
    Strada road(corsie);

    while (true) {
        road.spawnCar(rand()%3,corsie);
        for (int i = 0; i < 50; i++) cout << endl;
        road.display();
        road.update();

        cin.get();
    }


}