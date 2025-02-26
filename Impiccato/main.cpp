#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Impiccato {
private:
    string parola;
    string parolaHidden;
    int errori=0;
public:
    Impiccato() {
        vector<string> parole;
        fstream fs("/Users/simonebuccolieri/CLionProjects/Impiccato/cmake-build-debug/Words.txt");

        if (!fs.is_open()) {
            cerr << "Errore" << endl;
            exit(1);
        }

        string word;
        while (getline(fs, word)) {
            parole.push_back(word);
        }
        fs.close();
        // Scegli parola casuale
        parola = parole[rand() % parole.size()];
        parolaHidden = string(parola.length(), 'X');
    }
    void check(char s){
        int guess=0;
        for (int i=0;i<parola.length();i++) {
            if (parola[i] == s) {
                parolaHidden[i]=s;
                guess=1;
            }
        }
        if (guess==0) {
            errori++;
        }
        display();
    }
    int win() {
        if (parola==parolaHidden) {
            cout<<"Hai Vinto!";
            return 0;
        }
        if (errori==6) {
            cout<<"Hai Perso! La parola era "<<parola;
            return 0;
        }
        return 1;
    }
    void display() {
        #ifdef _WIN32
                system("cls");
        #else
                system("clear");
        #endif
        cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
        cout<<parolaHidden<<endl;
        vector<string> impiccato = {
            "   +---+\n"
            "   |   |\n"
            "       |\n"
            "       |\n"
            "       |\n"
            "       |\n"
            "=========\n",  // 0 errori

            "   +---+\n"
            "   |   |\n"
            "   O   |\n"
            "       |\n"
            "       |\n"
            "       |\n"
            "=========\n",  // 1 errore

            "   +---+\n"
            "   |   |\n"
            "   O   |\n"
            "   |   |\n"
            "       |\n"
            "       |\n"
            "=========\n",  // 2 errori

            "   +---+\n"
            "   |   |\n"
            "   O   |\n"
            "  /|   |\n"
            "       |\n"
            "       |\n"
            "=========\n",  // 3 errori

            "   +---+\n"
            "   |   |\n"
            "   O   |\n"
            "  /|\\  |\n"
            "       |\n"
            "       |\n"
            "=========\n",  // 4 errori

            "   +---+\n"
            "   |   |\n"
            "   O   |\n"
            "  /|\\  |\n"
            "  /    |\n"
            "       |\n"
            "=========\n",  // 5 errori

            "   +---+\n"
            "   |   |\n"
            "   O   |\n"
            "  /|\\  |\n"
            "  / \\  |\n"
            "       |\n"
            "=========\n"  // 6 errori -> GAME OVER
        };

        cout << impiccato[errori] << endl;
        cout<< "Errori: "<<errori<<"/6"<<endl;
    }
};
int main() {
    srand(time(0));
    Impiccato game;
    char word;
    game.display();
    while (game.win()) {
        cin>>word;
        game.check(tolower(word));
    }
}