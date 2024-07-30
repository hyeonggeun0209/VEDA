#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class GameObject {
protected:
    int distance;
    int x, y;

public:
    GameObject(int startX, int startY, int distance) {
        this->x = startX;
        this->y = startY;
        this->distance = distance;
    }
    virtual ~GameObject() {};
    virtual void move() = 0;
    virtual char getShape() = 0;

    int getX() { return x; }
    int getY() { return y; }
    bool collide(GameObject *p) {
        if (this->x == p->getX() && this->y == p->getY())
            return true;
        else
            return false;
    }
};

class Human : public GameObject {
public:
    Human() : GameObject(0, 0, 1) {}
    void move() {
        char c;
        cin >> c;
        if (c == 'a') {
            if (0 <= y - distance && y - distance <= 19)
                y = y - distance;
        }
        else if (c == 's') {
            if (0 <= x + distance && x + distance <= 9)
                x = x + distance;
        }
        else if (c == 'd') {
            if (0 <= x - distance && x - distance <= 9)
                x = x - distance;
        }
        else if (c == 'f') {
            if (0 <= y + distance && y + distance <= 19)
                y = y + distance;
        }
        else
            cout << "Wrong input!" << endl;
    }
    char getShape() {
        return 'H';
    }
};

class Monster : public GameObject {
public:
    Monster() : GameObject(5, 5, 2) {}
    void move() {
        bool b = true;
        while (b) {
            srand(time(NULL));
            int n = rand() % 4;
            switch (n) {
                case 0: {
                    if (0 <= y - distance && y - distance <= 19) {
                        y = y - distance;
                        b = !b;
                    }
                    break;
                }
                case 1: {
                    if (0 <= x + distance && x + distance <= 9) {
                        x = x + distance;
                        b = !b;
                    }
                    break;
                }
                case 2: {
                    if (0 <= x - distance && x - distance <= 9)
                    {
                        x = x - distance;
                        b = !b;
                    }
                    break;
                }
                case 3: {
                    if (0 <= y + distance && y + distance <= 19)
                    {
                        y = y + distance;
                        b = !b;
                    }
                    break;
                }
            }
        }
    }
    char getShape() {
        return 'M';
    }
};

class Food : public GameObject {
public:
    Food() : GameObject(9, 9, 1) {}
    void move() {
        int n = 0;
        bool b = true;
        if (n > 2) {
            while (b) {
                srand(time(NULL));
                int m = rand() % 4;
                switch (n) {
                    case 0: {
                        if (0 <= y - distance && y - distance <= 19) {
                            y = y - distance;
                            b = !b;
                        }
                        break;
                    }
                    case 1: {
                        if (0 <= x + distance && x + distance <= 9) {
                            x = x + distance;
                            b = !b;
                        }
                        break;
                    }
                    case 2: {
                        if (0 <= x - distance && x - distance <= 9) {
                            x = x - distance;
                            b = !b;
                        }
                        break;
                    }
                    case 3: {
                        if (0 <= y + distance && y + distance <= 19) {
                            y = y + distance;
                            b = !b;
                        }
                        break;
                    }
                }
            }
        }
        n++;
        if (n == 5)
            n = 0;
    }
    char getShape() {
        return '@';
    }
};

class Game {
    char board[10][20];

public:
    Game() {
        setBoard();
        run();
    }
    void run();
    void show(GameObject *h, GameObject *m, GameObject *f);
    void setBoard();
};

void Game::show(GameObject *h, GameObject *m, GameObject *f) {
    board[h->getX()][h->getY()] = h->getShape();
    board[m->getX()][m->getY()] = m->getShape();
    board[f->getX()][f->getY()] = f->getShape();

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}

void Game::setBoard() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            board[i][j] = '-';
        }
    }
}

void Game::run() {
    cout << "** Human의 Food 먹기 게임을 시작합니다. **" << endl
         << endl;
    GameObject *h = new Human();
    GameObject *f = new Food();
    GameObject *m = new Monster();

    while (!(h->collide(m) || h->collide(f) || m->collide(f))) {
        setBoard();
        show(h, m, f);
        cout << "왼쪽(a), 아래(s), 위(d), 오른쪽(f) >> ";
        h->move();
        m->move();
        f->move();

    }
    if (h->collide(m))
        cout << "Monster is Winner!!" << endl;
    if (h->collide(f))
        cout << "Human is Winner!!" << endl;
    if (m->collide(f))
        cout << "Monster is Winner!!" << endl;

    delete h;
    delete f;
    delete m;
}

int main() {
    Game *g = new Game();
    delete g;
    return 0;
}