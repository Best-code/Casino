#pragma once

#define cls system("CLS")
#define String std::string

extern bool grantAccess;
extern bool changeName;
extern bool noMatch;
extern bool userExist;

#include <iostream>
#include <string>
#include <sqlite3.h>
#include "casinoGames.h"
#include "Users.h"

static int callback(void* NotUsed, int argc, char** argv, char** azColName);
void runSQL(String&, int);

using std::cout;
using std::cin;

