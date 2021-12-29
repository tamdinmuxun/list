#include <iostream>
#include "node2.h"
#include "node2run.cpp"
#include <random>

using namespace std;
#define nln '\n';
std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator
std::uniform_int_distribution<> distr(1, 9);
list<int> row = list<int>();
int score = 0;

bool check(node<int> * ptr){
    if (ptr == nullptr) return false;
    auto p = ptr->prev, n = ptr->next;
    if (p != nullptr && n != nullptr){
        if (p->val == n->val && p->val == ptr->val){
            auto pp = p->prev, nn = n->next;
            if (pp != nullptr) {
                pp->next = nn;
            }
            if (nn != nullptr) nn->prev = pp;
            if (nn){
                row.ptr = nn;
            }else if (pp){
                row.ptr = pp;
            }else{
                row.ptr = nullptr;
            }
            if (p == row.head) row.head = nn;
            if (n == row.tail) row.tail = pp;
            delete p;
            delete ptr;
            delete n;
            return true;
        }
    }
    return false;
}
void check(int &cnt){
    if (check(row.ptr)){
        cnt--;
        if (row.ptr == row.tail)--cnt;
        cout << row << '\n';
        for (int i = 0; i < 2 * cnt; i++){
            cout << ' ';
        }cout << "^\n";
        score += 3;
        cout << "PLUS 3 POINTS!\n YOUR SCORE IS: " << score << '\n';
    } else if (row.ptr != nullptr && check(row.ptr->prev)){
        cnt-=2;
        if (row.ptr == row.tail) --cnt;
        cout << row << '\n';
        for (int i = 0; i < 2 * cnt; i++){
            cout << ' ';
        }cout << "^\n";
        score += 3;
        cout << "PLUS 3 POINTS!\n YOUR SCORE IS: " << score << '\n';
    } else if (row.ptr != nullptr && row.ptr->prev != nullptr && check(row.ptr->prev->prev)){
        cnt-=3;
        cout << row << '\n';
        if (row.ptr == row.tail)--cnt;
        for (int i = 0; i < 2 * cnt; i++){
            cout << ' ';
        }cout << "^\n";
        score += 3;
        cout << "PLUS 3 POINTS!\n YOUR SCORE IS: " << score << '\n';
    }
}
void check(){
    if (check(row.ptr)){
        score += 3;
    } else if (row.ptr != nullptr && check(row.ptr->prev)){
        score += 3;
    } else if (row.ptr != nullptr && row.ptr->prev != nullptr && check(row.ptr->prev->prev)){
        score += 3;
    }
}
void robot(){
    cout << "initiation size is 1e6\n";
    int n = 1e6;
    for (int i = 0; i < n; i++){
        row.push_back(distr(gen));
        if (check(row.back()->prev)){
            i -= 3;
        }
    }
    unsigned long long steps = 0;
    while (true){
        if (steps % 1000000 == 0) {
            cout << row << '\n';
            cout << "the score is " <<score << '\n';
        }
        int x = distr(gen);
        row.push_ptr(x);
        check();
        ++steps;
    }
}

int main(){
    cout << "bot mode?\n";
    string bot;
    cin >> bot;
    if (bot == "yes"){
        robot();
        return 0;
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        row.push_back(distr(gen));
        if (check(row.back()->prev)){
            i -= 3;
        }
    }
//    for (int i = 0; i < 2; i++){
//        row.push_back(1);
//    }row.push_back(2);
    int cnt = 0;
    while (true){
        if (row.head == nullptr){
            cout << "YOU WON!\n";
            exit(0);
        }
        cout << row << nln;
        for (int i = 0; i < 2 * cnt; i++){
            cout << ' ';
        }cout << "^\n";
        int x = distr(gen);
//        int x = 1;
        int pos = cnt;
        while (true){
            cout << x << " put here(h) or go left(l) or go right(r)?\n";
            string ans;
            cin >> ans;
            if (ans == "h"){
                row.push_ptr(x);
                cnt++;
                check(cnt);
                break;
            }else if (ans == "l"){
                if (!row.move_ptr(0)){
                    cout << "no you can't go there!\n";
                    continue;
                }
                cnt--;
                cout << row << nln;
                for (int i = 0; i < 2 * cnt; i++){
                    cout << ' ';
                }cout << "^\n";
            }else if (ans == "r"){
                if (!row.move_ptr(1)){
                    cout << "no you can't go there!\n";
                    continue;
                }
                cnt++;
                cout << row << nln;
                for (int i = 0; i < 2 * cnt; i++){
                    cout << ' ';
                }cout << "^\n";
            }
            if (abs(cnt - pos) == 5){
                row.push_ptr(x);
                cnt++;
                check(cnt);
                break;
            }

        }
    }
}