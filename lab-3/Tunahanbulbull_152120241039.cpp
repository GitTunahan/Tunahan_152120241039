#include <iostream>
#include <string>

using namespace std;


struct Page {
    string url;
    string title;
    int accessTime[3]; 
    Page* next;
    Page* prev;
};


Page* head = nullptr;
Page* current = nullptr; 

void visit(string u, string t, int h, int m, int s) {
    Page* newPage = new Page();
    newPage->url = u;
    newPage->title = t;
    newPage->accessTime[0] = h;
    newPage->accessTime[1] = m;
    newPage->accessTime[2] = s;
    newPage->next = nullptr;

    if (head == nullptr) {
        newPage->prev = nullptr;
        head = newPage;
        current = newPage;
    }
    else {
        Page* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newPage;
        newPage->prev = temp;
        current = newPage; 
    }
    cout << "Ziyaret edildi: " << t << endl;
}


void goBack() {
    if (current != nullptr && current->prev != nullptr) {
        current = current->prev;
        cout << "Geri gidildi. Su anki sayfa: " << current->title << endl;
    }
    else {
        cout << "Geri gidecek sayfa yok!" << endl;
    }
}


void goForward() {
    if (current != nullptr && current->next != nullptr) {
        current = current->next;
        cout << "Ileri gidildi. Su anki sayfa: " << current->title << endl;
    }
    else {
        cout << "Ileri gidecek sayfa yok!" << endl;
    }
}


void deleteEntry() {
    if (current == nullptr) return;

    Page* toDelete = current;

    if (toDelete->prev != nullptr)
        toDelete->prev->next = toDelete->next;
    else
        head = toDelete->next;

    if (toDelete->next != nullptr)
        toDelete->next->prev = toDelete->prev;

    
    if (toDelete->prev != nullptr) current = toDelete->prev;
    else current = toDelete->next;

    delete toDelete;
    cout << "Sayfa gecmisten silindi." << endl;
}

void displayHistory() {
    Page* temp = head;
    cout << "\n--- TARAYICI GECMISI ---" << endl;
    while (temp != nullptr) {
        if (temp == current) cout << "[SU ANKI] -> ";

        cout << "Baslik: " << temp->title << " | URL: " << temp->url << " | Zaman: ";

        for (int i = 0; i < 3; i++) {
            cout << temp->accessTime[i] << (i < 2 ? ":" : "");
        }
        cout << endl;
        temp = temp->next;
    }
}


void clearMemory() {
    Page* temp = head;
    while (temp != nullptr) {
        Page* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    head = nullptr;
    current = nullptr;
}

int main() {
    int choice;
    while (true) {
        cout << "\n1. Visit Page\n2. Back\n3. Forward\n4. Delete Current\n5. Display History\n6. EXIT\nSecim: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore();

        if (choice == 1) {
            string u, t;
            int h, m, s;
            cout << "URL: "; getline(cin, u);
            cout << "Baslik: "; getline(cin, t);
            cout << "Saat Dakika Saniye (boslukla): "; cin >> h >> m >> s;
            visit(u, t, h, m, s);
        }
        else if (choice == 2) goBack();
        else if (choice == 3) goForward();
        else if (choice == 4) deleteEntry();
        else if (choice == 5) displayHistory();
        else if (choice == 6) {
            clearMemory();
            cout << "Bellek temizlendi, cikiliyor..." << endl;
            break;
        }
    }
    return 0;
}