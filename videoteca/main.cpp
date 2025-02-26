#include <iostream>
#include <vector>
using namespace std;

class Movie {
private:
    string title;
    string regista;
    int year;

public:
    Movie(string title, string regista,int year) {
        this->title = title;
        this->regista = regista;
        this->year = year;
    }
    void display() {
        cout<< "Titolo: "<< title <<", Regista: "<< regista <<", Anno di Pubblicazione: "<<year<<endl;
    }
};
class VideoStore {
private:
    vector<Movie> Movies;
public:
    void addMovie(Movie movie) {
        Movies.push_back(movie);
    }
    void list() {
        if (Movies.empty()) {
            cout<<"no films"<<endl;
        }else {
            for (Movie m : Movies) {
                m.display();
            }
        }
    }
    void remove(int index) {
        Movies.erase(Movies.begin()+index-1);
    }
};

int main() {
    int choose,year,deletionChoice;
    string title,regista;
    VideoStore Videoteca;
    while (choose != 0) {
        cout<<"make a choice"<<endl;
        cout<<"0- esci"<<endl;
        cout<<"1- inserisci film"<<endl;
        cout<<"2- vedi i film"<<endl;
        cout<<"3- elimina film"<<endl;
        cin>>choose;
        if (choose==1) {
            cout<<"titolo: "<<endl;
            cin>>title;
            cout<<"regista: "<<endl;
            cin>>regista;
            cout<<"anno di pubblicazione: "<<endl;
            cin>>year;
            Videoteca.addMovie(Movie(title,regista,year));
        }
        if (choose==2) {
            Videoteca.list();
        }
        if (choose == 3) {
            cout<<"quale film vuoi eliminare? (selezioinare la riga)"<<endl;
            Videoteca.list();
            cin>>deletionChoice;
            Videoteca.remove(deletionChoice);
        }
    }
}