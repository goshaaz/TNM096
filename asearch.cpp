#include <queue>
#include <iostream>
#include <unordered_set>
#include <array>
#include <set>
#include <chrono>
#include <algorithm>
#include <map>
#include <cmath>

struct Node {
public:
    std::array<int, 9> state;
	Node* parent = nullptr;
	int distance;
};

int emptyPos(const Node* n) {
    if (n->state[0] == 0) return 0;
    if (n->state[1] == 0) return 1;
    if (n->state[2] == 0) return 2;
    if (n->state[3] == 0) return 3;
    if (n->state[4] == 0) return 4;
    if (n->state[5] == 0) return 5;
    if (n->state[6] == 0) return 6;
    if (n->state[7] == 0) return 7;
    if (n->state[8] == 0) return 8;
}

void print_state(std::array<int, 9> arr) {
    std::cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << '\n'
        << arr[3] << ' ' << arr[4] << ' ' << arr[5] << '\n'
        << arr[6] << ' ' << arr[7] << ' ' << arr[8] << '\n';
}

void print_path(Node* n) {
    Node* curr = n;
    while (curr->parent != nullptr) {
        print_state(curr->state);
        std::cout << "\n"
            << "    ^" << "\n"
            << "    |" << "\n";
        curr = curr->parent;
    }
}

struct CompareNodes {
    bool operator()(const Node* n1, const Node* n2) {
        int h_node1 = 0;
        int h_node2 = 0;
        /*
        // h1 Tiles out of place
        if (n1->state[0] != 1) h_node1++;
        if (n1->state[1] != 2) h_node1++;
        if (n1->state[2] != 3) h_node1++;
        if (n1->state[3] != 4) h_node1++;
        if (n1->state[4] != 5) h_node1++;
        if (n1->state[5] != 6) h_node1++;
        if (n1->state[6] != 7) h_node1++;
        if (n1->state[7] != 8) h_node1++;

        if (n2->state[0] != 1) h_node2++;
        if (n2->state[1] != 2) h_node2++;
        if (n2->state[2] != 3) h_node2++;
        if (n2->state[3] != 4) h_node2++;
        if (n2->state[4] != 5) h_node2++;
        if (n2->state[5] != 6) h_node2++;
        if (n2->state[6] != 7) h_node2++;
        if (n2->state[7] != 8) h_node2++;
        */
        
        // h2 Manhattan distance
        std::map<int, std::array<int,2>> m1;
        std::map<int, std::array<int, 2>> m2;
        int idx = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                std::pair<int, std::array<int, 2>> p1;
                std::pair<int, std::array<int, 2>> p2;
                p1.first = n1->state[idx];
                p2.first = n2->state[idx];
                std::array<int, 2> arr;
                std::array<int, 2> arr2;
                arr[0] = i;
                arr[1] = j;
                arr2[0] = i;
                arr2[1] = j;
                p1.second = arr;
                p2.second = arr2;
                m1.insert(p1);
                m2.insert(p2);
                idx++;
            }
        }
        for (int i = 0; i < 9; i++) {
            int y = m1.find(i)->second[0];
            int x = m1.find(i)->second[1];
            int manhattan = 0;
            switch (i) {
                case 1:
                {
                    int diffx = std::abs(x - 0);
                    int diffy = std::abs(y - 0);
                    manhattan += (diffx + diffy);
                }
                break;
                case 2:
                {
                    int diffx = std::abs(x - 1);
                    int diffy = std::abs(y - 0);
                    manhattan += (diffx + diffy);
                }
                break;
                case 3:
                {
                    int diffx = std::abs(x - 2);
                    int diffy = std::abs(y - 0);
                    manhattan += (diffx + diffy);
                }
                break;
                case 4:
                {
                    int diffx = std::abs(x - 0);
                    int diffy = std::abs(y - 1);
                    manhattan += (diffx + diffy);
                }
                break;
                case 5:
                {
                    int diffx = std::abs(x - 1);
                    int diffy = std::abs(y - 1);
                    manhattan += (diffx + diffy);
                }
                break;
                case 6:
                {
                    int diffx = std::abs(x - 2);
                    int diffy = std::abs(y - 1);
                    manhattan += (diffx + diffy);
                }
                break;
                case 7:
                {
                    int diffx = std::abs(x - 0);
                    int diffy = std::abs(y - 2);
                    manhattan += (diffx + diffy);
                }
                break;
                case 8:
                {
                    int diffx = std::abs(x - 1);
                    int diffy = std::abs(y - 2);
                    manhattan += (diffx + diffy);
                }
                break;
            }
            h_node1 += manhattan;
        }

        for (int i = 0; i < 9; i++) {
            int y = m2.find(i)->second[0];
            int x = m2.find(i)->second[1];
            int manhattan = 0;
            switch (i) {
            case 1:
            {
                int diffx = std::abs(x - 0);
                int diffy = std::abs(y - 0);
                manhattan += (diffx + diffy);
            }
            break;
            case 2:
            {
                int diffx = std::abs(x - 1);
                int diffy = std::abs(y - 0);
                manhattan += (diffx + diffy);
            }
            break;
            case 3:
            {
                int diffx = std::abs(x - 2);
                int diffy = std::abs(y - 0);
                manhattan += (diffx + diffy);
            }
            break;
            case 4:
            {
                int diffx = std::abs(x - 0);
                int diffy = std::abs(y - 1);
                manhattan += (diffx + diffy);
            }
            break;
            case 5:
            {
                int diffx = std::abs(x - 1);
                int diffy = std::abs(y - 1);
                manhattan += (diffx + diffy);
            }
            break;
            case 6:
            {
                int diffx = std::abs(x - 2);
                int diffy = std::abs(y - 1);
                manhattan += (diffx + diffy);
            }
            break;
            case 7:
            {
                int diffx = std::abs(x - 0);
                int diffy = std::abs(y - 2);
                manhattan += (diffx + diffy);
            }
            break;
            case 8:
            {
                int diffx = std::abs(x - 1);
                int diffy = std::abs(y - 2);
                manhattan += (diffx + diffy);
            }
            break;
            }
            h_node2 += manhattan;
        }
        

        int lhs = n1->distance + h_node1;
        int rhs = n2->distance + h_node2;
        return lhs > rhs;
    }

};

int main() {
    auto starttime = std::chrono::high_resolution_clock::now();
    std::set<std::array<int, 9>> visited;
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> q;
    int start[] = {7, 4, 8, 2, 3, 1, 0, 5, 6};
    std::array<int, 9> goal = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
    Node* root = new Node();
    root->distance = 0;
    for (int i = 0; i < 9; i++) {
        root->state[i] = start[i];
    }
    q.push(root);
    int i = 0;
    Node* end = new Node();
    end->distance = 0;
    for (int j = 0; j < 9; j++) {
        end->state[j] = 0;
    }

    std::cout << "START\n";
    int iterations = 0;
    while (!q.empty()) {
        iterations++;
        Node* current = q.top();
        q.pop();
        if (current->state == goal){
            auto stoptime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(stoptime - starttime);
            std::cout << "RUNTIME= " << duration.count() << " seconds";
            std::cout << "\n Iterations=" << iterations;
            std::cout << "\n";
            print_state(current->state);
            end = current;
            break;
        }
        int empty_pos = emptyPos(current);
        if (visited.find(current->state) == visited.end()){ // 
            switch (empty_pos) {
            case 0:
            {
                Node* newNode1 = new Node();
                newNode1->distance = current->distance + 1;
                Node* newNode2 = new Node();
                newNode2->distance = current->distance + 1;
                for (int i = 0; i < 9; i++) {
                    newNode1->state[i] = current->state[i];
                }
                newNode1->state[0] = newNode1->state[1];
                newNode1->state[1] = 0;
                for (int j = 0; j < 9; j++) {
                    newNode2->state[j] = current->state[j];
                }
                newNode2->state[0] = newNode2->state[3];
                newNode2->state[3] = 0;
                newNode1->parent = current;
                newNode2->parent = current;
                q.push(newNode1);
                q.push(newNode2);
            }
            break;
            case 1:
            {
                Node* newNode3 = new Node();
                newNode3->distance = current->distance + 1;
                Node* newNode4 = new Node();
                newNode4->distance = current->distance + 1;
                Node* newNode5 = new Node();
                newNode5->distance = current->distance + 1;
                for (int i = 0; i < 9; i++) {
                    newNode3->state[i] = current->state[i];
                }
                newNode3->state[1] = newNode3->state[0];
                newNode3->state[0] = 0;
                for (int j = 0; j < 9; j++) {
                    newNode4->state[j] = current->state[j];
                }
                newNode4->state[1] = newNode4->state[4];
                newNode4->state[4] = 0;
                for (int k = 0; k < 9; k++) {
                    newNode5->state[k] = current->state[k];
                }
                newNode5->state[1] = newNode5->state[2];
                newNode5->state[2] = 0;
                newNode3->parent = current;
                newNode4->parent = current;
                newNode5->parent = current;
                q.push(newNode3);
                q.push(newNode4);
                q.push(newNode5);
            }
            break;
            case 2:
            {
                Node* newNode6 = new Node();
                newNode6->distance = current->distance + 1;
                Node* newNode7 = new Node();
                newNode7->distance = current->distance + 1;
                for (int i = 0; i < 9; i++) {
                    newNode6->state[i] = current->state[i];
                }
                newNode6->state[2] = newNode6->state[1];
                newNode6->state[1] = 0;
                for (int j = 0; j < 9; j++) {
                    newNode7->state[j] = current->state[j];
                }
                newNode7->state[2] = newNode7->state[5];
                newNode7->state[5] = 0;
                newNode6->parent = current;
                newNode7->parent = current;
                q.push(newNode6);
                q.push(newNode7);
            }
            break;
            case 3:
            {
                Node* newNode8 = new Node();
                newNode8->distance = current->distance + 1;
                Node* newNode9 = new Node();
                newNode9->distance = current->distance + 1;
                Node* newNode10 = new Node();
                newNode10->distance = current->distance + 1;
                for (int i = 0; i < 9; i++) {
                    newNode8->state[i] = current->state[i];
                }
                newNode8->state[3] = newNode8->state[0];
                newNode8->state[0] = 0;
                for (int j = 0; j < 9; j++) {
                    newNode9->state[j] = current->state[j];
                }
                newNode9->state[3] = newNode9->state[4];
                newNode9->state[4] = 0;
                for (int k = 0; k < 9; k++) {
                    newNode10->state[k] = current->state[k];
                }
                newNode10->state[3] = newNode10->state[6];
                newNode10->state[6] = 0;
                newNode8->parent = current;
                newNode9->parent = current;
                newNode10->parent = current;
                q.push(newNode8);
                q.push(newNode9);
                q.push(newNode10);
            }
            break;
            case 4:
            {
                Node* newNode11 = new Node();
                newNode11->distance = current->distance + 1;
                Node* newNode12 = new Node();
                newNode12->distance = current->distance + 1;
                Node* newNode13 = new Node();
                newNode13->distance = current->distance + 1;
                Node* newNode14 = new Node();
                newNode14->distance = current->distance + 1;
                for (int i = 0; i < 9; i++) {
                    newNode11->state[i] = current->state[i];
                }
                newNode11->state[4] = newNode11->state[3];
                newNode11->state[3] = 0;
                for (int j = 0; j < 9; j++) {
                    newNode12->state[j] = current->state[j];
                }
                newNode12->state[4] = newNode12->state[1];
                newNode12->state[1] = 0;
                for (int k = 0; k < 9; k++) {
                    newNode13->state[k] = current->state[k];
                }
                newNode13->state[4] = newNode13->state[5];
                newNode13->state[5] = 0;
                for (int l = 0; l < 9; l++) {
                    newNode14->state[l] = current->state[l];
                }
                newNode14->state[4] = newNode14->state[7];
                newNode14->state[7] = 0;
                newNode11->parent = current;
                newNode12->parent = current;
                newNode13->parent = current;
                newNode14->parent = current;
                q.push(newNode11);
                q.push(newNode12);
                q.push(newNode13);
                q.push(newNode14);
            }
            break;
            case 5:
            {
                Node* newNode15 = new Node();
                newNode15->distance = current->distance + 1;
                Node* newNode16 = new Node();
                newNode16->distance = current->distance + 1;
                Node* newNode17 = new Node();
                newNode17->distance = current->distance + 1;
                for (int i = 0; i < 9; i++) {
                    newNode15->state[i] = current->state[i];
                }
                newNode15->state[5] = newNode15->state[2];
                newNode15->state[2] = 0;
                for (int j = 0; j < 9; j++) {
                    newNode16->state[j] = current->state[j];
                }
                newNode16->state[5] = newNode16->state[4];
                newNode16->state[4] = 0;
                for (int k = 0; k < 9; k++) {
                    newNode17->state[k] = current->state[k];
                }
                newNode17->state[5] = newNode17->state[8];
                newNode17->state[8] = 0;
                newNode15->parent = current;
                newNode16->parent = current;
                newNode17->parent = current;
                q.push(newNode15);
                q.push(newNode16);
                q.push(newNode17);
            }
            break;
            case 6:
            {
                Node* newNode18 = new Node();
                newNode18->distance = current->distance + 1;
                Node* newNode19 = new Node();
                newNode19->distance = current->distance + 1;
                for (int i = 0; i < 9; i++) {
                    newNode18->state[i] = current->state[i];
                }
                newNode18->state[6] = newNode18->state[3];
                newNode18->state[3] = 0;
                for (int j = 0; j < 9; j++) {
                    newNode19->state[j] = current->state[j];
                }
                newNode19->state[6] = newNode19->state[7];
                newNode19->state[7] = 0;
                newNode18->parent = current;
                newNode19->parent = current;
                q.push(newNode18);
                q.push(newNode19);
            }
            break;
            case 7:
            {
                Node* newNode20 = new Node();
                newNode20->distance = current->distance + 1;
                Node* newNode21 = new Node();
                newNode21->distance = current->distance + 1;
                Node* newNode22 = new Node();
                newNode22->distance = current->distance + 1;
                for (int i = 0; i < 9; i++) {
                    newNode20->state[i] = current->state[i];
                }
                newNode20->state[7] = newNode20->state[6];
                newNode20->state[6] = 0;
                for (int j = 0; j < 9; j++) {
                    newNode21->state[j] = current->state[j];
                }
                newNode21->state[7] = newNode21->state[4];
                newNode21->state[4] = 0;
                for (int k = 0; k < 9; k++) {
                    newNode22->state[k] = current->state[k];
                }
                newNode22->state[7] = newNode22->state[8];
                newNode22->state[8] = 0;
                newNode20->parent = current;
                newNode21->parent = current;
                newNode22->parent = current;
                q.push(newNode20);
                q.push(newNode21);
                q.push(newNode22);
            }
            break;

            case 8:
            {
                Node* newNode23 = new Node();
                newNode23->distance = current->distance + 1;
                Node* newNode24 = new Node();
                newNode24->distance = current->distance + 1;
                for (int i = 0; i < 9; i++) {
                    newNode23->state[i] = current->state[i];
                }
                newNode23->state[8] = newNode23->state[5];
                newNode23->state[5] = 0;
                for (int j = 0; j < 9; j++) {
                    newNode24->state[j] = current->state[j];
                }
                newNode24->state[8] = newNode24->state[7];
                newNode24->state[7] = 0;
                newNode23->parent = current;
                newNode24->parent = current;
                q.push(newNode23);
                q.push(newNode24);
            }
            break;
            
            }// END OF SWITCH

            visited.insert(current->state);
        }
    }
    Node* test = end;
    while (test != nullptr) {
        print_state(test->state);
        std::cout << "\n";
        test = test->parent;
    }
    std::cout << "depth=" << end->distance;
    
    return 0;
}