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
        changeName = true;
    }

    printf("\n");
    return 0;
}

static int ueCall(void* NotUsed, int argc, char** argv, char** azColName) {

    printf("\n");
    return 0;
};



void runSQL(String& sql, int n) {
    sqlite3* DB;
    char* errMsg = 0;

    sqlite3_stmt* stmt2;

    int exit = sqlite3_open("src/db/casino.db", &DB);
    if(n == 1)
        sqlite3_exec(DB, sql.c_str(), callback, 0, &errMsg);
    if (n == 2) {
        sqlite3_prepare(DB, sql.c_str(), -1, &stmt2, NULL);
        int x = sqlite3_step(stmt2);
        if (x == SQLITE_DONE) {
            userExist = false;
            grantAccess = true;
        }
        else {
            userExist = true;
        }
    }

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
