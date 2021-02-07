#include "headers/Commons.h"

//if password and password confirmation dont match on registration
bool noMatch = false;

String User::getPass() {
    return password;
}

void User::gamesMenu() {
    cls;
    cout << "Colins Casino - Home Page\n" << std::endl;
    cout << "Welcome - " + username + ".\n\n";

    cout << "Games Here";
}

int x = -1;
void User::Login() {
    x += 1;
    cls;
    cout << "Colins Casino - Login Page\n\n";
    //if given password doesnt match the users password
    if (!grantAccess) {
        if(x>0){
            cout << "Your Password was Incorrect.\nPlease Try Again.\n\n";
        }
    }
    if (!userExist) {
        if (x > 0) {
            cout << "That Username does not Exist.\nPlease Try Again.\n\n";
        }
    }
    cout << "Please Enter your Username > ";
    cin >> username;
    cout << std::endl << "Please Enter your Password > ";
    cin >> password;

    //Checks if the user exist
    String sql = "SELECT username FROM user WHERE username = '" + username + "';";
    runSQL(sql,2);

    //if he does exist check if his password is correct
    if (userExist) {
        String sql = "SELECT password FROM user WHERE username = '" + username + "';";
        runSQL(sql,1);

        //if he exist and his password is correct goto gamesMenu
        if (grantAccess)
            gamesMenu();

        //if he exist and his password isnt correct login again.
        else
            Login();
    }
    else {
        Login();
    }

    
    
}

void User::Register() {

    //Sets back to empty string
    username, password = "";
    cls;
    cout << "Colins Casino - Register Page\n" << std::endl;

    //If someone already has that name
    if (changeName) {
        cout << "Someone has already chosen that Username.\nPlease try again\n" << std::endl;
        changeName = false;
    }
    //If you failed password confirmation
    if (noMatch) {
        cout << "Your Password Confirmation Failed.\nPlease try again.\n" << std::endl << std::endl;
        noMatch = false;
    }

    cout << "Please Create a Username > ";
    cin >> username;
    cout << std::endl << "Please Create a Password > ";
    cin >> password;
    cout << std::endl << "Plase Retype to Confirm Password > ";
    String conf;
    cin >> conf;


    //If the username and password match
    if (!strcmp(conf.c_str(), password.c_str())) {

        //Check if there is someone already with that name and if so set bool changeName to true
        String sql = "SELECT username FROM user WHERE username = '" + username + "'";
        runSQL(sql,1);

        //if no one has the name, change name will be false and you will be added to the database
        //with a base balance of 500
        if (!changeName) {
            sql = "INSERT INTO user(username,password,balance) VALUES('" + username + "','" + password + "', 500)";
            runSQL(sql,1);

            gamesMenu();
        }
        //If someone does have the name it will just take you back to the register page
        else {
            Register();
        }
    }
    //if your username and passwords dont match register again.
    else {
        noMatch = true;
        Register();
    }


}

