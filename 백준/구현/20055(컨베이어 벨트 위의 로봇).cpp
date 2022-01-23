#include <iostream>
#include <deque>
using namespace std;
struct info {
    int safty;
    bool isRobot;

    info(int safty) {
        this->safty = safty;
        this->isRobot = false;
    }
};

void putFront(deque<info>& container, int& zeroCnt) {
    if(container[0].safty > 0) {
        container[0].safty--;
        container[0].isRobot = true;

        if(container[0].safty == 0) {
            zeroCnt++;
        }
    }
}
void moveRobot(deque<info>& container, int N, int& zeroCnt) {
    for(int i=N-2; i>=0; --i) {
        if(!container[i].isRobot) {
            continue;
        }

        if(container[i+1].isRobot || container[i+1].safty == 0) {
            continue;
        }

        container[i+1].isRobot = true;
        container[i+1].safty--;
        container[i].isRobot = false;

        if(container[i+1].safty == 0) {
            zeroCnt++;
        }
    }

    if(container[N-1].isRobot) {
        container[N-1].isRobot = false;
    }
}
void moveContainer(deque<info>& container, int N) {

    container.push_front(container.back());
    container.pop_back();

    if(container[N-1].isRobot) {
        container[N-1].isRobot = false;
    }
}
int simulation(int N, int K, deque<info>& container) {
    int curStep = 1;
    int zeroCnt = 0;
    while(true) {
        moveContainer(container, N);

        moveRobot(container, N, zeroCnt);

        putFront(container, zeroCnt);

        if(zeroCnt >= K) {
            break;
        }
        curStep++;
    }
    return curStep;
}
void input(int& N, int& K, deque<info>& container) {
    cin >> N >> K;
    container.assign(2 * N, info(0));
    for(int i=0; i<(2 * N); ++i) {
        cin >> container[i].safty;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K;
    deque<info> container;
    input(N, K, container);

    int answer = simulation(N, K, container);

    cout << answer;
    return 0;
}
