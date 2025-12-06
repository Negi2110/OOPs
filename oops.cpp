#include <iostream>
using namespace std;
 class basicPlayer {
    int size;
    public:
    void Hello() {
        cout<<"hello"<<endl;
    }
    void goodbye();
    int getnumber();
 };
void basicPlayer::goodbye() {
    cout<<"goodbye"<<endl;
}

int main() {
    basicPlayer *player = new basicPlayer();
    player->Hello();
    player->goodbye();
    delete player;
    return 0;
}