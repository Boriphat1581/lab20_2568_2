#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<iomanip>

using namespace std;

class Equipment {
    int hpmax, atk, def;
public:
    Equipment(int h, int a, int d) : hpmax(h), atk(a), def(d) {}
    vector<int> getStat() { return {hpmax, atk, def}; }
};

class Unit {
    string name, type;
    int hp, hpmax, atk, def;
    bool guard_on, dodge_on;
    Equipment* equipment;
public:
    Unit(string t, string n) {
        type = t; name = n;
        if (type == "Hero") {
            hpmax = rand() % 20 + 120; atk = rand() % 5 + 14; def = rand() % 3 + 9;
        } else {
            hpmax = rand() % 20 + 250; atk = rand() % 5 + 25; def = rand() % 3 + 5;
        }
        hp = hpmax; guard_on = false; dodge_on = false; equipment = NULL;
    }

    void showStatus() {
        if (type == "Hero") {
            cout << "---------------------------------------\n" << name << "\n";
            cout << "HP: " << hp << "/" << hpmax << "\tATK: " << atk << "\tDEF: " << def << "\n---------------------------------------\n";
        } else {
            cout << "\t\t\t\t---------------------------------------\n\t\t\t\t" << name << "\n";
            cout << "\t\t\t\tHP: " << hp << "\tATK: " << atk << "\tDEF: " << def << "\n\t\t\t\t---------------------------------------\n";
        }
    }

    void newTurn() { guard_on = false; dodge_on = false; }

    int beAttacked(int oppatk) {
        int dmg = 0;
        if (oppatk > def) dmg = oppatk - def;

        if (dodge_on) {
            if (rand() % 2 == 0) {
                dmg = 0; 
            } else {
                dmg *= 2; ขโจทย์
            }
        } else {
            if (guard_on) dmg /= 3;
        }

        hp -= dmg;
        if (hp <= 0) hp = 0;
        return dmg;
    }

    int attack(Unit& opp) { return opp.beAttacked(atk); }
    int ultimateAttack(Unit& opp) { return opp.beAttacked(atk * 2); }
    
    int heal() {
        int h = rand() % 21 + 10;
        if (hp + h > hpmax) h = hpmax - hp;
        hp += h; return h;
    }
    
    void guard() { guard_on = true; }
    void dodge() { dodge_on = true; }
    bool isDead() { return hp <= 0; }
    
    void equip(Equipment* e) {
        if (equipment) {
            vector<int> s = equipment->getStat();
            hpmax -= s[0]; atk -= s[1]; def -= s[2];
        }
        equipment = e;
        if (equipment) {
            vector<int> s = e->getStat();
            hpmax += s[0]; atk += s[1]; def += s[2];
        }
        if (hp > hpmax) hp = hpmax;
    }
};

void drawScene(char p_action, int p, char m_action, int m) {
    cout << "\n";
    if (p_action == 'A' || p_action == 'U') cout << "                                        " << -p << "\n";
    else cout << "\n";
    cout << "                                 * * \n";
    cout << "                                 ** ********* ** \n";
    cout << "                                 **** **** \n";
    if (m_action == 'A' || m_action == 'U') cout << "                  " << setw(5) << -m << "            *** ** ** *** Attack!\n";
    else if (m_action == 'G') cout << "                                  *** ** ** *** Guard!\n";
    else if (m_action == 'D') cout << "                                  *** ** ** *** Dodge!\n";
    else cout << "                                  *** ** ** ***\n";
    cout << "                                   ** ** ** ** \n";
    cout << "                    *** * * \n";
    if (p_action == 'A' || p_action == 'U') cout << "         Attack!    *** * ********* \n";
    else if (p_action == 'H') cout << "      Heal! +" << setw(2) << p << "    *** * ********* \n";
    else if (p_action == 'G') cout << "         Guard!     *** * ********* \n";
    else if (p_action == 'D') cout << "         Dodge!     *** * ********* \n";
    else cout << "                    *** * ********* \n";
    cout << "                     * * *** * * * \n";
    cout << "                   ***** ** * * \n";
    cout << "                     * * *** \n";
    cout << "                    * * ** * \n";
    cout << "                   * * \n\n";
}

void playerWin() { cout << "***************************\n* YOU WIN!!!        *\n***************************\n"; }
void playerLose() { cout << "***************************\n* YOU LOSE!!!       *\n***************************\n"; }