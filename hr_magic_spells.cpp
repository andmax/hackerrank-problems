#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Spell { 
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Fireball : public Spell { 
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell { 
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell { 
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
}; 
string SpellJournal::journal = "";

void counterspell(Spell *spell) {
  /* Enter your code here */
    Fireball *fir = dynamic_cast<Fireball *>(spell);
    Frostbite *fro = dynamic_cast<Frostbite *>(spell);
    Thunderstorm *thu = dynamic_cast<Thunderstorm *>(spell);
    Waterbolt *wat = dynamic_cast<Waterbolt *>(spell);
    if (fir != NULL) {
        fir->revealFirepower();
    } else if (fro != NULL) {
        fro->revealFrostpower();
    } else if (thu != NULL) {
        thu->revealThunderpower();
    } else if (wat != NULL) {
        wat->revealWaterpower();
    } else {
        string roots[2] = {spell->revealScrollName(), SpellJournal::read()};
        int maxh = min(roots[0].size(), roots[1].size());
        vector<int> seqi, seqj;
        for (int i = 0; i < roots[0].size(); ++i) {
            for (int j = 0; j < roots[1].size(); ++j) {
                if (roots[0][i] == roots[1][j]) {
                    seqi.push_back(i);
                    seqj.push_back(j);
                }
            }
        }
        vector<int> mati[maxh], matj[maxh];
        maxh = -1;
        for (int j = 0; j < seqj.size(); ++j) {
            int curi = seqi[j], curj = seqj[j];
            int bh = 0;
            for (int h = maxh; h >= 0; --h) {
                for (int k = 0; k < matj[h].size(); ++k) {
                    if (curj > matj[h][k] and curi > mati[h][k]) {
                        bh = h+1;
                        break;
                    }
                }
                if (bh > 0)
                    break;
            }
            mati[bh].push_back(curi);
            matj[bh].push_back(curj);
            if (bh > maxh)
                maxh = bh;
        }
        cout << maxh+1 << '\n';
    } // else spell generic
} // counterspell

class Wizard {
    public:
        Spell *cast() {
            Spell *spell;
            string s; cin >> s;
            int power; cin >> power;
            if(s == "fire") {
                spell = new Fireball(power);
            }
            else if(s == "frost") {
                spell = new Frostbite(power);
            }
            else if(s == "water") {
                spell = new Waterbolt(power);
            }
            else if(s == "thunder") {
                spell = new Thunderstorm(power);
            } 
            else {
                spell = new Spell(s);
                cin >> SpellJournal::journal;
            }
            return spell;
        }
};

int main() {
    int T;
    cin >> T;
    Wizard Arawn;
    while(T--) {
        Spell *spell = Arawn.cast();
        counterspell(spell);
    }
    return 0;
}
