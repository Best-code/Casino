// Casino.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "headers/Commons.h"


using std::cout;
using std::cin;

bool changeName = false;
bool grantAccess = true;
bool userExist = false;

static int callback(void* NotUsed, int argc, char** argv, char** azColName);
void runSQL(String& sql);

User newUser;

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {

    if (argv[0] == newUser.getPass()) {
        grantAccess = true;
    }
    else {
        grantAccess = false;
    }
    

    if (argv[0] == newUser.username) {
        userExist = true;
    }
    
    if (argv[0] == newUser.username) {
        changeName = true;
    }

    printf("\n");
    return 0;
}

void runSQL(String& sql) {
    sqlite3* DB;
    char* errMsg = 0;

    int exit = sqlite3_open("src/db/casino.db", &DB);

    sqlite3_exec(DB, sql.c_str(), callback, 0, &errMsg);
    sqlite3_close(DB);
}

void welcome()
{
    String welcome = R"(Welcome to Colin's Casino!


Login to my account > 1

Register an account > 2

)";

    cout << welcome;

    int n;
    cin >> n;
    ((n == 1) ? newUser.Login() : newUser.Register());
}

int main()
{
    welcome();
    cin.get();
}
