// Music Playlist Management System (doubly linked list)

#include <iostream>
#include <string>
using namespace std;

struct Song {
    string title;
    string artist;
    Song* prev;
    Song* next;
};

Song* head = NULL;
Song* tail = NULL;
Song* current = NULL;

const int MAX_SONGS = 50;
int count = 0;

bool isDuplicate(string title, string artist, Song* ignore) {
    Song* temp = head;
    while (temp != NULL) {
        if (temp != ignore && temp->title == title && temp->artist == artist) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

Song* findSong(string title) {
    Song* temp = head;
    while (temp != NULL) {
        if (temp->title == title) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void insertAtEnd(string title, string artist) {
    Song* newSong = new Song;
    newSong->title = title;
    newSong->artist = artist;
    newSong->prev = NULL;
    newSong->next = NULL;

    if (head == NULL) {
        head = newSong;
        tail = newSong;
        current = newSong;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }
    count++;
}

void addSong() {
    if (count >= MAX_SONGS) {
        cout << "The playlist is full (" << MAX_SONGS << " songs). Delete a song first.\n";
        return;
    }

    string title, artist;
    cout << "Enter song title: ";
    getline(cin, title);
    if (title == "") {
        cout << "The title cannot be empty.\n";
        return;
    }
    cout << "Enter artist name: ";
    getline(cin, artist);
    if (artist == "") {
        artist = "Unknown";
    }

    if (isDuplicate(title, artist, NULL)) {
        cout << "That song by that artist is already in the playlist.\n";
        return;
    }

    insertAtEnd(title, artist);
    cout << "Song added successfully!\n";
}

void deleteSong() {
    if (head == NULL) {
        cout << "The playlist is empty. Nothing to delete.\n";
        return;
    }

    string title;
    cout << "Enter the title of the song to delete: ";
    getline(cin, title);

    Song* temp = findSong(title);
    if (temp == NULL) {
        cout << "Song not found.\n";
        return;
    }

    if (current == temp) {
        if (temp->next != NULL) {
            current = temp->next;
        } else {
            current = temp->prev;
        }
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    } else {
        tail = temp->prev;
    }

    delete temp;
    count--;
    cout << "Song deleted successfully!\n";
}

void updateSong() {
    if (head == NULL) {
        cout << "The playlist is empty. Nothing to update.\n";
        return;
    }

    string title;
    cout << "Enter the title of the song to update: ";
    getline(cin, title);

    Song* temp = findSong(title);
    if (temp == NULL) {
        cout << "Song not found.\n";
        return;
    }

    string newTitle, newArtist;
    cout << "Enter the new title: ";
    getline(cin, newTitle);
    if (newTitle == "") {
        cout << "The title cannot be empty. Nothing was changed.\n";
        return;
    }
    cout << "Enter the new artist: ";
    getline(cin, newArtist);
    if (newArtist == "") {
        newArtist = "Unknown";
    }

    if (isDuplicate(newTitle, newArtist, temp)) {
        cout << "That song by that artist is already in the playlist. Nothing was changed.\n";
        return;
    }

    temp->title = newTitle;
    temp->artist = newArtist;
    cout << "Song updated successfully!\n";
}

void playCurrent() {
    if (current == NULL) {
        cout << "The playlist is empty.\n";
    } else {
        cout << "Now playing: " << current->title << " by " << current->artist << "\n";
    }
}

void nextSong() {
    if (current == NULL) {
        cout << "The playlist is empty.\n";
    } else if (current->next == NULL) {
        cout << "This is the last song. There is no next song.\n";
    } else {
        current = current->next;
        playCurrent();
    }
}

void previousSong() {
    if (current == NULL) {
        cout << "The playlist is empty.\n";
    } else if (current->prev == NULL) {
        cout << "This is the first song. There is no previous song.\n";
    } else {
        current = current->prev;
        playCurrent();
    }
}

void displayPlaylist() {
    if (head == NULL) {
        cout << "The playlist is empty.\n";
        return;
    }

    int number = 1;
    Song* temp = head;
    while (temp != NULL) {
        cout << number << ". " << temp->title << " - " << temp->artist;
        if (temp == current) {
            cout << "   <-- current song";
        }
        cout << "\n";
        temp = temp->next;
        number++;
    }
    cout << "Total songs: " << count << "\n";
}

void searchSong() {
    string title;
    cout << "Enter the title to search for: ";
    getline(cin, title);

    Song* temp = findSong(title);
    if (temp == NULL) {
        cout << "Song not found.\n";
    } else {
        cout << "Song found: " << temp->title << " by " << temp->artist << "\n";
    }
}

int main() {
    int choice = -1;

    while (choice != 0) {
        cout << "\n=====================================\n";
        cout << "        MUSIC PLAYLIST SYSTEM\n";
        cout << "=====================================\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Update Song\n";
        cout << "4. Play Current Song\n";
        cout << "5. Next Song\n";
        cout << "6. Previous Song\n";
        cout << "7. Display Playlist\n";
        cout << "8. Search Song\n";
        cout << "0. Exit\n";
        cout << "-------------------------------------\n";
        cout << "Enter your choice (0-8): ";

        cin >> choice;
        if (cin.fail()) {
            if (cin.eof()) break;
            cin.clear();
            choice = -1;
        }
        cin.ignore(1000, '\n');
        cout << "\n";

        if (choice == 1) addSong();
        else if (choice == 2) deleteSong();
        else if (choice == 3) updateSong();
        else if (choice == 4) playCurrent();
        else if (choice == 5) nextSong();
        else if (choice == 6) previousSong();
        else if (choice == 7) displayPlaylist();
        else if (choice == 8) searchSong();
        else if (choice == 0) cout << "Goodbye!\n";
        else cout << "Invalid choice. Please enter a number from 0 to 8.\n";
    }

    while (head != NULL) {
        Song* temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}
