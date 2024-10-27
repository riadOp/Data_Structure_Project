/**
 *    author:  riad
 *    created: 05.12.2024 11:00:14
**/

#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <set>
#include <algorithm>        // For std::find
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>       // For usleep (for Linux and MacOS)
#endif
#include <ctime>

using namespace std;

// Structs and Classes
struct User {
    int userId;
    string name;
    string password;
    string country;
    string gender;
    int age;
    list<int> friends; // To store friend ids
};



struct Post {
    int postId;
    string content;
    int userId; // User ID of the post creator
    time_t timestamp;
};

struct FriendRequest {
    int senderId;
    int receiverId;
};

// Global Variables
int currentUserId = -1;
int postIdCounter = 1;
map<int, User> users;
map<int, Post> posts;                        // Posts indexed by post ID
queue<FriendRequest> friendRequests;        // FIFO queue for pending friend requests
set<int> loggedInUsers;                      // To track logged in users

// Function prototypes
void Welcome_Interface();
void Registration();
void Login();
void Main_Menu();
void Add_Friend();
void Pending_Friends();
void View_Friends();
void Create_Post();
void View_Feed();
void Like_Post();
void Comment_On_Post();
void Admin_Database();
void Logout();
void Loading_Animation();
void Printing_at_Center(const string &text, int width);

// Function to print text at the center of the screen
void Printing_at_Center(const string &text, int width) {
    int padding = (width - text.size()) / 2;
    cout << string(padding, ' ') << text << string(padding, ' ') << endl;
}

// Function to show a loading animation
void Loading_Animation() {
    const int loading_time = 500; // Milliseconds
    const int screen_width = 100; // Terminal width

    cout << "\nLoading";
    for (int i = 1; i < 10; i++) {
        cout << '.'; 
        #ifdef _WIN32
        Sleep(loading_time);
        #else
        usleep(loading_time * 1000); // for Mac/Linux
        #endif
    }
    cout << "\n\n";
}

// Welcome Interface
void Welcome_Interface() {
    const int screen_width = 100;
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    Printing_at_Center("\033[1;35mWelcome to ChipiChipi Social Media!\033[0m", screen_width);
    Printing_at_Center("\033[1;37mA new way to connect with friends, share your moments, and interact with people!\033[0m", screen_width);
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;

    Loading_Animation();
    Printing_at_Center("\033[1;36mPlease register to get started.\033[0m", screen_width);
    cout << endl;

    Printing_at_Center("\033[1;32m1. Register New Account\033[0m", screen_width);
    Printing_at_Center("\033[1;32m2. Login\033[0m", screen_width);
    Printing_at_Center("\033[1;33m3. Exit\033[m", screen_width);

    cout << endl;

    // User input for choice
    int choice;
    while (true) {
        cout << "\nEnter your choice (1 or 2): ";
        cin >> choice;

        if (choice == 1 || choice == 2 || choice ==3) {
            break;
        } else {
            cout << "\033[1;31mInvalid option! Please choose 1 or 2.\033[0m" << endl;
        }
    }

    if (choice == 1) {
        Registration();
    } else if (choice == 2) {
        Login();
    } else if(choice == 3){
        cout << "Exiting... Goodbye!" << endl;
        exit(0);
    }
}

// Registration Function
void Registration() {
    cout << "\033[1;36mEnter your name: \033[0m";
    string name;
    cin.ignore();
    getline(cin, name);

    cout << "\033[1;36mEnter your age: \033[0m";
    int age;
    cin >> age;

    cout << "\033[1;36mEnter your country: \033[0m";
    string country;
    cin.ignore();
    getline(cin, country);

    cout << "\033[1;36mEnter your gender (Male/Female): \033[0m";
    string gender;
    getline(cin, gender);

    cout << "\033[1;36mEnter a password: \033[0m";
    string password;
    getline(cin, password);

    // Assign a new User ID
    int userId = users.size() + 1;
    users[userId] = {userId, name, password, country, gender, age};

    cout << "\033[1;32mRegistration Successful! Your User ID is " << userId << ".\033[0m" << endl;

    // Post registration options
    cout << "\n\033[1;36mWhat would you like to do next?\033[0m" << endl;
    cout << "\033[1;32m1. Login\033[0m" << endl;
    cout << "\033[1;33m2. Create a New Account\033[0m" << endl;
    cout << "\033[1;31m3. Exit\033[0m" << endl;

    int choice;
    cin >> choice;

    if (choice == 1) {
        Login();
    } else if (choice == 3) {
        exit(0);
    } else {
        Registration();  // Recursively call registration if option 2 is chosen
    }
}

// Login Function
void Login() {
    cout << "\033[1;36mEnter your User ID: \033[0m";
    int userId;
    cin >> userId;

    cout << "\033[1;36mEnter your password: \033[0m";
    string password;
    cin >> password;

    if (users.find(userId) != users.end() && users[userId].password == password) {
        cout << "\033[1;32mLogin Successful!\033[0m" << endl;
        currentUserId = userId;
        loggedInUsers.insert(userId);
        Main_Menu();
    } else {
        cout << "\033[1;31mInvalid User ID or Password. Please try again.\033[0m" << endl;
        Login();
    }
}

// Main Menu
void Main_Menu() {
    while (true) {
        cout << "\n\033[1;36mMain Menu:\033[0m" << endl;
        cout << "\033[1;32m1. Add Friend\033[0m" << endl;
        cout << "\033[1;33m2. Pending Friend Requests\033[0m" << endl;
        cout << "\033[1;34m3. View Friends\033[0m" << endl;
        cout << "\033[1;35m4. Create Post\033[0m" << endl;
        cout << "\033[1;36m5. View Feed\033[0m" << endl;
        cout << "\033[1;37m6. Logout\033[0m" << endl;
        cout << "\033[1;31m7. Admin Database (Admin Only)\033[0m" << endl;

        cout << "\n\033[1;36mEnter your choice (1-7): \033[0m";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: Add_Friend(); break;
            case 2: Pending_Friends(); break;
            case 3: View_Friends(); break;
            case 4: Create_Post(); break;
            case 5: View_Feed(); break;
            case 6: Logout(); break;
            case 7: Admin_Database(); break;
            default: cout << "\033[1;31mInvalid Option.\033[0m" << endl; break;
        }
    }
}

// Add Friend Function (using a stack)
void Add_Friend() {
    cout << "\n\033[1;36mEnter the User ID or Name to send a friend request: \033[0m";
    string input;
    cin.ignore();
    getline(cin, input);

    int friendId = -1;
    // Check if input is a number (User ID)
    if (isdigit(input[0])) {
        friendId = stoi(input);
    } else {
        // Search for user by name
        for (const auto &user : users) {
            if (user.second.name == input) {
                friendId = user.first;
                break;
            }
        }
    }

    if (friendId != -1 && friendId != currentUserId) {
        // Add friend request to queue
        friendRequests.push({currentUserId, friendId});
        cout << "\033[1;32mFriend request sent successfully.\033[0m" << endl;
    } else if (friendId == currentUserId) {
        cout << "\033[1;31mYou cannot send a friend request to yourself.\033[0m" << endl;
    } else {
        cout << "\033[1;31mUser not found.\033[0m" << endl;
    }
}

// Pending Friends function
void Pending_Friends() {
    cout << "\033[1;36mPending Friend Requests:\033[0m" << endl;
    bool hasPending = false;

    // Check all pending requests
    queue<FriendRequest> tempQueue = friendRequests;
    while (!tempQueue.empty()) {
        FriendRequest request = tempQueue.front();
        tempQueue.pop();

        if (request.receiverId == currentUserId) {
            hasPending = true;
            cout << "\033[1;33mRequest from user " << request.senderId << ".\033[0m" << endl;
            cout << "\033[1;32m1. Accept\033[0m / \033[1;31m2. Reject\033[0m: ";
            int action;
            cin >> action;

            if (action == 1) {
                // Accept request
                users[currentUserId].friends.push_back(request.senderId);
                users[request.senderId].friends.push_back(currentUserId);
                cout << "\033[1;32mFriend request accepted!\033[0m" << endl;
            } else {
                cout << "\033[1;31mFriend request rejected.\033[0m" << endl;
            }
        }
    }

    if (!hasPending) {
        cout << "\033[1;31mNo pending requests.\033[0m" << endl;
    }
}

// View Friends Function
void View_Friends() {
    if (users[currentUserId].friends.empty()) {
        cout << "\033[1;31mNo friends yet.\033[0m" << endl;
    } else {
        cout << "\033[1;36mYour Friends:\033[0m" << endl;
        for (int friendId : users[currentUserId].friends) {
            cout << "User ID: " << friendId << " - " << users[friendId].name << endl;
        }
    }
}

// Create Post Function
void Create_Post() {
    cout << "\033[1;36mEnter the content of your post: \033[0m";
    string content;
    cin.ignore();
    getline(cin, content);

    // Save post
    posts[postIdCounter++] = {postIdCounter, content, currentUserId, time(0)};
    cout << "\033[1;32mPost created successfully.\033[0m" << endl;
}

// View Feed Function
void View_Feed() {
    cout << "\033[1;36mYour News Feed:\033[0m" << endl;
    for (const auto &post : posts) {
        if (post.second.userId == currentUserId || find(users[currentUserId].friends.begin(), users[currentUserId].friends.end(), post.second.userId) != users[currentUserId].friends.end()) {
            cout << "\n\033[1;34mPost ID: " << post.second.postId << "\033[0m" << endl;
            cout << "\033[1;33mContent: " << post.second.content << "\033[0m" << endl;
            cout << "\033[1;32mPosted by: " << users[post.second.userId].name << "\033[0m" << endl;
            cout << "\033[1;36mTimestamp: " << ctime(&post.second.timestamp);
        }
    }
}

// Logout Function
void Logout() {
    cout << "\033[1;36mYou are now logged out.\033[0m" << endl;
    currentUserId = -1;
    loggedInUsers.erase(currentUserId);
    Welcome_Interface();
}

// Admin Database Function (Restricted to Admin)
void Admin_Database() {
    int adminId = 99;  // Assuming Admin has user ID 99
    string adminPassword = "admin99";  // Hardcoded admin password

    cout << "\033[1;36mEnter Admin User ID: \033[0m";
    int adminInputId;
    cin >> adminInputId;

    cout << "\033[1;36mEnter Admin Password: \033[0m";
    string adminInputPassword;
    cin >> adminInputPassword;

    if (adminInputId == adminId && adminInputPassword == adminPassword) {
        cout << "\033[1;32mAdmin login successful.\033[0m" << endl;
        cout << "\033[1;36mDisplaying all user information:\033[0m" << endl;
        for (const auto &user : users) {
            cout << "\nUser ID: " << user.second.userId << endl;
            cout << "Name: " << user.second.name << endl;
            cout << "Country: " << user.second.country << endl;
            cout << "Gender: " << user.second.gender << endl;
            cout << "Age: " << user.second.age << endl;
        }
    } else {
        cout << "\033[1;31mInvalid Admin credentials.\033[0m" << endl;
    }
}

int main() {
    Welcome_Interface();
    return 0;
}
