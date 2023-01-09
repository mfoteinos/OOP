#include <windef.h>
#include <winbase.h>
#include <wincon.h>
#include <iostream>
#include<string>
#include <exception>
#include <time.h>
#include<vector>




using namespace std;

//CLASS DECLARATIONS
class Wall;
class User;
class ReplyMessage;
class Message;
class Exceptions;
class FriendRequest;
int findUserNo(string n);

vector <User> UserList;
vector<vector<User>> friendrequests;
vector<vector<User>> friends;
vector<vector<vector<User>>> whoLiked;
vector<vector<string>> ftime;


int getStringHeight(string s){
   string pat = "\n";
   int M = pat.length();
    int N = s.length();
    int res = 0;

    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++)
    {
        /* For current index i, check for
           pattern match */
        int j;
        for (j = 0; j < M; j++)
            if (s[i+j] != pat[j])
                break;

        // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
        if (j == M)
        {
           res++;
           j = 0;
        }
    }
    return res;
}

int cursorX() {
    CONSOLE_SCREEN_BUFFER_INFO consoleinfo;
    int cursorx;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleinfo);
  cursorx = consoleinfo.dwCursorPosition.X;
  return cursorx;
}



int cursorY() {
    CONSOLE_SCREEN_BUFFER_INFO consoleinfo;
    int cursory;
 GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleinfo);
  cursory = consoleinfo.dwCursorPosition.Y;
  return cursory;
}

void SetColor(int ForgC)
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}

void cursorJump(short x,short y, bool clearLine)
{
    //move to desired position
    COORD cursor={x,y};
    HANDLE console=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console,cursor);
    //clear remaining line when desired
    if (clearLine==true)
    {
        for (int i=x;i<80;i++)
        cout<<" ";
        //return to desired position
        cursorJump(x,y,false);
    }
}
//Function for creating borders
void border(int x1,int y1,int width,int height)
{
 for (int i=x1;i<=x1+width+2;i++) // top
    {
        cursorJump(i,y1,false);
        cout<<char(220);
        Sleep(10);
    }
    for (int j=y1+1;j<=y1+height+2;j++) // left
    {
        cursorJump(x1,j,false);
        cout<<char(221);
        Sleep(10);
    }
    for (int k=x1;k<=x1+width+2;k++) //bottom
    {
        cursorJump(k,y1+height+2,false);
        cout<<char(223);
        Sleep(10);
    }
    for (int l=y1+height+1; l>=y1+1; l--) // right
    {
        cursorJump(x1+width+2,l,false);
        cout<<char(222);
        Sleep(10);
    }

  }

//Function for welcoming users
void Welcome2Emerald (string n) {
    SetColor(2);
    cout<<endl;
    int i,j,space1,space2;
        for(i=11; i>=1; i--) {

             for(space1 = i; space1 < 11 ; space1++)
         cout << " ";
      for(j = 1; j <= (2 * i - 1); j++) {
         cout << "*";
         Sleep(8);
      }
         for (space2=i; space2<48-i; space2++)
            cout<<" ";
        for(j = 1; j <= (2 * i - 1); j++) {
                cout << "*";
                    Sleep(8);
      }
      cout << "\n";
}
            cursorJump(25,3,false);
        char text[] = "Welcome to Emerald.";
             char user[n.length()];
             for(unsigned k=0; k<sizeof(user); k++){
                user[k] = n[k];
             }
             char choose[] =  "Choose what you wish to do! ";
        int textl = sizeof(text) / sizeof(text[0]);
        int userl = sizeof(user) / sizeof(user[0]);
        int choosel = sizeof(choose) / sizeof(choose[0]);
         SetColor(10);
             for(i=0; i < textl; i++){
                cout<<text[i];
                Sleep(80);
            }
            cout<<endl;
            cursorJump(30,4,false);
      for(i=0; i < userl; i++){
           cout<<user[i];
            Sleep(80);
            }
            cursorJump(2,15,false);

            for(i=0; i < choosel; i++){
           cout<<choose[i];
            Sleep(80);
            }
            cout<<endl;
         SetColor(15);
}

//Function about printing out the user main choices
void startMenu(){
    string menu1[7]{"1: See your wall.","2: See friend's wall." , "3: Send friend request.","4: Manage friend requests.","5: See my friends." ,"6: Log out.","7: Exit."};
        SetColor(2);
        border(cursorX(),cursorY(),26,6);
        cursorJump(cursorX()-28,cursorY(),false);
        SetColor(10);
         cout<<menu1[0]<<endl;
        for (int i=1; i<7;i++) {
        cursorJump(cursorX()+1,cursorY(),false);
         cout<<menu1[i]<<endl;
         Sleep(100);
        }
        cout<<endl;
        cout<<endl;
}

//Function for printing out choices about what the users wants to do with posts
 void menu2() {

         system("cls");
         char choose[] =  "Choose what you wish to do! ";
         int choosel = sizeof(choose) / sizeof(choose[0]);
         SetColor(10);
            for(int i=0; i < choosel; i++){
           cout<<choose[i];
            Sleep(80);
            }
            cout<<endl<<endl;
         string menu2[5]{"1: Create a post.","2: Create a comment at a post." , "3: Like a post.","4: Go back."};
        border(cursorX(),cursorY(),29,3);
        cursorJump(cursorX()-31,cursorY(),false);
        SetColor(10);
         cout<<menu2[0]<<endl;
        for (int i=1; i<4;i++) {
        cursorJump(cursorX()+1,cursorY(),false);
         cout<<menu2[i]<<endl;
         Sleep(100);
        }
        SetColor(15);
}


void printMultilinedPost(string p) {
    SetColor(2);
    border(cursorX(),cursorY(),64,p.length()/58+1);
    cursorJump(cursorX()-66,cursorY(),false);
    SetColor(10);
        for (unsigned i = 0; i < p.length(); i += 58) {
        cursorJump(cursorX()+1,cursorY(),false);
        cout<<p.substr(i,58 )<<endl;
    }

 }

void printOneLinePost(string p){
    SetColor(2);
            border(cursorX(),cursorY(),p.size(),getStringHeight(p));
            cursorJump(cursorX()-p.size()-2,cursorY(),false);
            SetColor(10);
            cout<<p;

}

void PrintPost(string p) {

    if (p.length() <=32)
        printOneLinePost(p);
    else
        printMultilinedPost(p);
}

string getTime(){
    time_t     now = time(0); //gets current time
    struct tm  tstruct;
    char       buf[80]; //buf:pointer sto prwto stoixeio tou output , [80]:max number of bytes
    tstruct = *localtime(&now); //Metatrepei to tstruct  sto local timezone
    strftime(buf, sizeof(buf), "%d-%m-%Y %X", &tstruct); //%d -> day, %m->month, %Y ->year,%X->local time representation

        return buf;

}






class ReplyMessage {
    public:
        ReplyMessage(string c){
        comment = c;
        }
        string getComments(){
        return comment;
    }

    private:
        string comment;


};

class Message {
public:

    Message (string p){
            post=p;
            likes =0;
    }

     void  addLike() {
        likes= likes+1;

    }

    string getPost(){
        return post;
    }

   int getLikes(){
        return likes;
    }

private:
    string post;
    int likes;
};
class Wall {
public:



    vector<Message> posts;
    vector<vector<ReplyMessage> > comments;

};

class User : public Wall{


public:

//Function for showing posts on the users own wall
        void showPosts(string n){
    for (int i=UserList[findUserNo(n)].posts.size()-1; i>=0; i--){

        PrintPost(UserList[findUserNo(n)].posts[i].getPost() + " | Likes:" + to_string(UserList[findUserNo(n)].posts[i].getLikes()));
        cout<<endl<<endl<<endl;
        cout<<"\tComments:"<<endl;
        Sleep(200);
            for (unsigned int j=0; j<UserList[findUserNo(n)].comments[i].size(); j++){
                cout<<"\t"<< UserList[findUserNo(n)].comments[i][j].getComments()<<endl;
                Sleep(200);
                }
            cout<<endl;
            }
        Sleep(400);
    }
//Function for creating posts on the users own wall
    void createPost(string n){
            string y;
            string t;
            User zero(" "," ");
            vector<User> temp;
            Sleep(200);
            cout << "Type what you want to post! (Type 'back' to go back)"<<endl;
            cin >> t;
            if(t == "back"){
                return;
            }
            y = to_string(UserList[findUserNo(n)].posts.size()+ 1);
            UserList[findUserNo(n)].posts.push_back(Message(y + ": | " + name + ": " + t + " | Posted at: " + getTime()));
            vector<ReplyMessage> temp2;
            temp2.push_back(ReplyMessage (" "));
            UserList[findUserNo(n)].comments.push_back(temp2);
            temp.push_back(zero);
            whoLiked[findUserNo(n)].push_back(temp);
            Sleep(200);
            cout << "Post created."<<endl;
    }
    //Function for creating comments on the posts of the users own wall
    void createComment(int i,string n){
            string y;
            string t;
            Sleep(200);
            cout << "Type what you want to comment! (Type 'back' to go back)"<<endl;
            cin >> t;
            if(t == "back"){
                return;
            }
            y = to_string(UserList[findUserNo(n)].comments[i-1].size()+ 1);
            vector<ReplyMessage> temp;
            if(UserList[findUserNo(n)].comments[i-1].size()== 1){
                    temp.push_back(ReplyMessage(y + ": | " + name + ": " + t + " | Posted at: " + getTime()));
                    UserList[findUserNo(n)].comments[i-1] = temp;
                }else {
                        UserList[findUserNo(n)].comments[i-1].push_back(ReplyMessage (y + ": | " + name + ": " + t + " | Posted at: " + getTime()));
                }
                Sleep(200);
                cout << "Comment created."<<endl;
    }
    //Function for finding user position in user storing vector
       int findUserNo (string n) {
for (unsigned int i=0; i<UserList.size(); i++)
if  (UserList[i].getName() == n)
return i;
    }


     User(string e,string n){
         email=e;
         name=n;
     }
     string getName (){
        return name;
}
//Function for sending friend requests
    void addFriend(string n) {

        bool alfriend = false;
        string nof;
        int thesi;
        bool flag = false;
        User zero(" "," ");
     //Userlist show:
        cout<<"Available users to add: "<<endl;
        for(unsigned int i=0; i<UserList.size(); i++) {
            for(unsigned int k = 0; k < friends[findUserNo(n)].size(); k++){
                if(friends[findUserNo(n)][k].getName() == UserList[i].getName()){
                    alfriend = true;
                }
            }
            if(alfriend == false ){
                cout<<UserList[i].getName()<<endl;
            }
            alfriend = false;
        }
        Sleep(200);
        cout<<"Give name of user you want to add or type 'back' to go back."<<endl;
        cin>>nof;
        if(nof == "back"){
            return;
        }

        for (unsigned int j=0; j<UserList.size(); j++){
            if (UserList[j].getName() == nof){
                   thesi = j;
                   flag = true;

            }
            }
           if (flag == false){
                Sleep(200);
                cout << "The given name is not registered.Try again"<<endl;
                Sleep(1000);
                addFriend(n );
                return;
            }
            if(UserList[findUserNo(n)].getName()== nof){
                Sleep(200);
                cout<<"You can't add yourself"<<endl;
                Sleep(1000);
                addFriend(n);
                return;
            }
            for(unsigned int i=0; i<UserList.size(); i++) {
                for(unsigned int k = 0; k < friends[findUserNo(n)].size(); k++){
                    if(friends[findUserNo(n)][k].getName() == UserList[i].getName()){
                        cout<<"You already are friends with this user"<<endl;
                        Sleep(1000);
                        addFriend(n);
                        return;
                    }
                }
            }

            for (unsigned int k=0; k< friendrequests[thesi].size(); k++){
                if (friendrequests[thesi] [k].getName() == n){
                        Sleep(200);
                    cout<<"The user you selected already has a request"<<endl;
                    Sleep(1000);
                    addFriend(n );
                    return;
                }
            }
            for(unsigned int i=0; i<UserList.size(); i++) {
                for(unsigned int k = 0; k < friendrequests[findUserNo(n)].size(); k++){
                    if(friendrequests[findUserNo(n)][k].getName() == UserList[i].getName()){
                        cout<<"You already have a friend request from that user"<<endl;
                        Sleep(1000);
                        addFriend(n);
                        return;
                    }
                }
            }
            Sleep(200);
            cout<<"User "<<nof<<" has received your friend request."<<endl;

            if(friendrequests[thesi][0].getName()== zero.getName() ){
                friendrequests[thesi][0] = UserList[findUserNo(n)];
                ftime[thesi][0] = getTime();
            }
            else {
                friendrequests[thesi].push_back(UserList[findUserNo(n)]);
                ftime[thesi].push_back(getTime());
            }
    }

    //Function for managing friend requests
    void manageFriendRequests(string n){

        User zero(" "," ");

        if(friendrequests[findUserNo(n)][0].getName() == zero.getName()){
            Sleep(200);
            cout<<"There are no pending friend requests"<<endl;
            Sleep(1000);
            return;
        }
        for(unsigned i = 0; i < friendrequests[findUserNo(n)].size();i++){
            cout<<i + 1<<" :"<<friendrequests[findUserNo(n)][i].getName()<<" Sent at: "<<ftime[findUserNo(n)][i]<<endl;

        }
        Sleep(200);
        cout<<"Select a name to manage their request or type 'back' to go back."<<endl;
        string nof;
        string dec;
        cin>>nof;
        if (nof == "back"){
            return;
        }
        bool flag = false;
        int thesi;
        for (unsigned int k=0; k< friendrequests[thesi].size(); k++){
            if (friendrequests[findUserNo(n)] [k].getName() == nof){
                   flag = true;
                   thesi = k;
            }
        }
            if(flag == false){
                Sleep(200);
                cout<<"No friend request from that user. Try again."<<endl;
                Sleep(1000);
                manageFriendRequests(n);
                return;
            }
            Sleep(200);
            cout<<"Accept or deny this request? (type 'accept', 'deny' or 'back' to go back.) "<<endl;
            cin>>dec;
            if(dec == "accept"){

                if(friends[findUserNo(n)][0].getName() == zero.getName() ){
                    friends[findUserNo(n)][0] = UserList[findUserNo(nof)];
                    if(friends[findUserNo(nof)][0].getName() == zero.getName()){
                        friends[findUserNo(nof)][0] = UserList[findUserNo(n)];
                    }else{
                        friends[findUserNo(nof)].push_back(UserList[findUserNo(n)]);
                    }

                    if(friendrequests[findUserNo(n)].size() == 1){
                        friendrequests[findUserNo(n)][0] = zero;
                    } else{
                        friendrequests[findUserNo(n)].erase(friendrequests[findUserNo(n)].begin() + thesi);
                        }

                } else {
                    friends[findUserNo(n)].push_back(UserList[findUserNo(nof)]);
                    if(friends[findUserNo(nof)][0].getName() == zero.getName()){
                        friends[findUserNo(nof)][0] = UserList[findUserNo(n)];
                    }else{
                        friends[findUserNo(nof)].push_back(UserList[findUserNo(n)]);
                    }
                    if(friendrequests[findUserNo(n)].size() == 1){
                        friendrequests[findUserNo(n)][0] = zero;
                    } else{
                        friendrequests[findUserNo(n)].erase(friendrequests[findUserNo(n)].begin() + thesi);
                        }
                }}

            else if(dec == "deny"){
                if(friendrequests[findUserNo(n)].size() == 1){
                        friendrequests[findUserNo(n)][0] = zero;
                    } else{
                        friendrequests[findUserNo(n)].erase(friendrequests[findUserNo(n)].begin() + thesi);
                        }
            }
            else{
                manageFriendRequests(n);
                return;
            }

    }

    //Function for showing posts on a friends wall
    string showFriendPosts(string n){
        string nof;
        printFriends(n);

        if(friends[findUserNo(n)][0].getName() == " "){
            return " ";
        }
        Sleep(200);
        cout<<"Choose which friend's wall to show by typing their name"<<endl;
        cin>>nof;
        for (int i=UserList[findUserNo(nof)].posts.size()-1; i>=0; i--){
        PrintPost(UserList[findUserNo(nof)].posts[i].getPost() + " | Likes:" + to_string(UserList[findUserNo(nof)].posts[i].getLikes()));
        cout<<endl<<endl<<endl;
        cout<<"\tComments:"<<endl;
        Sleep(200);
            for (unsigned int j=0; j<UserList[findUserNo(nof)].comments[i].size(); j++){
                cout<<"\t"<< UserList[findUserNo(nof)].comments[i][j].getComments()<<endl;
                Sleep(200);
                }
            cout<<endl;
            }
            Sleep(400);
            return nof;
    }
    //Function for creating posts on a friends wall
    void createFriendPost(string nof){
            User zero(" "," ");
            vector<User> temp;
            string y;
            string t;
            Sleep(200);
            cout << "Type what you want to post! (Type 'back' to go back)"<<endl;
            cin >> t;
            if(t == "back"){
                return;
            }
            y = to_string(UserList[findUserNo(nof)].posts.size()+ 1);
            UserList[findUserNo(nof)].posts.push_back(Message(y + ": | " + name + ": " + t + " | Posted at: " + getTime()));
            vector<ReplyMessage> temp2;
            temp2.push_back(ReplyMessage (" "));
            UserList[findUserNo(nof)].comments.push_back(temp2);
            temp.push_back(zero);
            whoLiked[findUserNo(nof)].push_back(temp);
            Sleep(200);
            cout<<"Post created."<<endl;
    }
        //Function for creating comments on a friends wall
        void createFriendComment(int i,string nof){
            string y;
            string t;
            Sleep(200);
            cout << "Type what you want to comment! (Type 'back' to go back)"<<endl;
            cin >> t;
            if(t == "back"){
                return;
            }
            y = to_string(UserList[findUserNo(nof)].comments[i-1].size()+ 1);
            vector<ReplyMessage> temp;
            if(UserList[findUserNo(nof)].comments[i-1].size()== 1){
                    temp.push_back(ReplyMessage(y + ": | " + name + ": " + t + " | Posted at: " + getTime()));
                    UserList[findUserNo(nof)].comments[i-1] = temp;
                }else {
                        UserList[findUserNo(nof)].comments[i-1].push_back(ReplyMessage (y + ": | " + name + ": " + t + " | Posted at: " + getTime()));
                }
                Sleep(200);
                cout<<"Comment created."<<endl;
    }
    //Function for removing friends
    void removeFriend(string n) {

        if(friends[findUserNo(n)][0].getName() == " "){
            return;
        }
        bool flag = false;
        string nof;
        int thesi;

     //Userlist show:
        Sleep(200);
        cout<<"Select friend to remove or type 'back' to go back"<<endl;
        cin >>nof;

        if(nof == "back"){
            return;
        }
       for (unsigned int j=0; j<friends[findUserNo(n)].size(); j++){
            if (friends[findUserNo(n)][j].getName() == nof){

                   thesi = j;
                   flag = true;

            }

       }
       if(flag == false){
            Sleep(200);
            cout << "The given name is not registered.Try again"<<endl;
            Sleep(1000);
            removeFriend(n);
            return;
       }
           friends[findUserNo(n)].erase(friends[findUserNo(n)].begin()+thesi);
    }

    void printFriends(string n){
        if(friends[findUserNo(n)][0].getName() == " "){
            Sleep(200);
            cout<<"You have no friends :( Go add some!"<<endl;
            Sleep(1000);
            return;
        }
        for(unsigned int i = 0; i < friends[findUserNo(n)].size(); i++){
            Sleep(200);
            cout<<i + 1<<": "<<friends[findUserNo(n)][i].getName()<<endl;
        }

    }

    vector<vector<User> > getFriendrequests(){
    return friendrequests;
    }

private:
    string email;
    string name;



};

class Network  {
public:

void searchForMutuals(string n1,string n2){

    for(unsigned int i = 0; i < friends[UserList[0].findUserNo(n1)].size(); i++){
        for(unsigned int j = 0; j <friends[UserList[0].findUserNo(n2)].size(); j++){
            if(friends[UserList[0].findUserNo(n1)][i].getName() == friends[UserList[0].findUserNo(n2)][j].getName()){
                cout<<friends[UserList[0].findUserNo(n1)][i].getName()<<endl;
            }
        }
    }
}
bool friendsOrNot (string u1 , string u2) {

    int ok1,ok2;

        for (unsigned int j=0; j<friends[findUserNo(u1)].size(); j++){
                if (u2 == friends[findUserNo(u1)][j].getName())
                    ok1 = 1;
        }

        for (unsigned int i=0; i<friends[findUserNo(u2)].size(); i++) {
            if ( u1 == friends[findUserNo(u2)][i].getName())
                ok2=1;

        }

        if (ok1 == 1 && ok2 == 1)
            return true;
        else return false;
}

void printNetFriends(string n){
    for(unsigned int i = 0; i < friends[UserList[0].findUserNo(n)].size(); i++){
        cout<<friends[UserList[0].findUserNo(n)][i].getName()<<endl;
    }
}




    };


int main()
{


//Initializing useful variables,vectors and users for "stored" users
    bool logtest = false;
    vector<string> timeless;
    timeless.push_back(" ");
    User lognow(" "," ");
    User zero (" "," ");
    vector<User> temp;
    vector<vector<User>> supertemp;
    temp.push_back(zero);
    //Stored users
    User user1("manolisf47@hotmail.com" , "Manolis");
    User user2("mike12@hotmail.com", "Mixalis");
    User user3("panos25@hotmail.com ", "Panagiotis");
    User user4("arouri@gmail.com","Aristea");
    User user5("darkness@gmail.com","Maura");
    User user6("x_angie_x@gmail.com","Aggeliki");
    //Avoiding exceptions by push_back in the needed vectors
    UserList.push_back(user1);
    UserList.push_back(user2);
    UserList.push_back(user3);
    UserList.push_back(user4);
    UserList.push_back(user5);
    UserList.push_back(user6);
    friendrequests.push_back(temp);
    friendrequests.push_back(temp);
    friendrequests.push_back(temp);
    friendrequests.push_back(temp);
    friendrequests.push_back(temp);
    friendrequests.push_back(temp);
    ftime.push_back(timeless);
    ftime.push_back(timeless);
    ftime.push_back(timeless);
    ftime.push_back(timeless);
    ftime.push_back(timeless);
    ftime.push_back(timeless);
    friends.push_back(temp);
    friends.push_back(temp);
    friends.push_back(temp);
    friends.push_back(temp);
    friends.push_back(temp);
    friends.push_back(temp);
    friends[0][0] = user2;
    friends[0].push_back(user3);
    friends[0].push_back(user4);
    friends[0].push_back(user5);
    friends[1][0] = user1;
    friends[2][0] = user1;
    friends[3][0] = user1;
    friends[4][0] = user1;
    supertemp.push_back(temp);
    supertemp.push_back(temp);
    supertemp.push_back(temp);
    whoLiked.push_back(supertemp);
    supertemp.clear();
    supertemp.push_back(temp);
    supertemp.push_back(temp);
    supertemp.clear();
    supertemp.push_back(temp);
    whoLiked.push_back(supertemp);
    whoLiked.push_back(supertemp);
    whoLiked.push_back(supertemp);
    whoLiked.push_back(supertemp);
    whoLiked.push_back(supertemp);



    //Stored Comments
    ReplyMessage comment111("1: | Aggeliki: Kalo mina!!!!!! | Posted at: " + getTime());
    ReplyMessage comment112("2: | Aristea: Episis :))))))))))))))))))))))))))))))))) | Posted at: " + getTime());
    ReplyMessage comment113("3: | Panagiotis: oxi | Posted at: " + getTime());
    ReplyMessage comment114("4: | Mixalis: WOOOOOOOOOOOOO!!!!!! | Posted at: " + getTime());
    ReplyMessage comment115("5: | Maura: Kalo mina Manoli hehehe | Posted at: " + getTime());
    ReplyMessage comment121("1: | Manolis: Euxaristooooo! | Posted at: " + getTime());
    ReplyMessage emptycomment(" ");


    //Storing posts
    UserList[0].posts.push_back(Message ("1: | Manolis: Kalo mina se olous :)))))))))))  | Posted at: " + getTime()));
    UserList[0].posts.push_back(Message("2: | Aristea: Xronia polla!!!!! | Posted at: " + getTime()));
    UserList[0].posts.push_back(Message("3: | Panagiotis: Den to pisteuo oti o Bran anevike ston throno | Posted at: " + getTime()));
    UserList[1].posts.push_back(Message("1: | Aggeliki: https://www.youtube.com/watch?v=ecIphyKtQl0 | Posted at: " + getTime()));
    UserList[1].posts.push_back(Message("2: | Maura: Katalathos se ekana add | Posted at: " + getTime()));
    UserList[4].posts.push_back(Message("1: | Mixalis: MORI KAMPIA | Posted at: " + getTime()));
    UserList[3].posts.push_back(Message("1: | Manolis:  Agapame Melisandre | Posted at: " + getTime()));


// Storing cpmments
    vector<ReplyMessage> temp2;
    temp2.push_back(comment111);
    temp2.push_back(comment112);
    temp2.push_back(comment113);
    temp2.push_back(comment114);
    temp2.push_back(comment115);
    UserList[0].comments.push_back(temp2);
    temp2.clear();
    temp2.push_back(comment121);
    UserList[0].comments.push_back(temp2);
    temp2.clear();
    temp2.push_back(emptycomment);
    UserList[0].comments.push_back(temp2);
    UserList[1].comments.push_back(temp2);
    UserList[1].comments.push_back(temp2);
    UserList[0].comments.push_back(temp2);
    UserList[4].comments.push_back(temp2);
    UserList[3].comments.push_back(temp2);
    temp2.clear();

    //Login process
    string username=" ";
    while (logtest == false) {
        for(unsigned l = 0; l < UserList.size(); l++){
            cout<< l + 1<<": "<<UserList[l].getName()<<endl;
        }

        cout << "Give username" << endl;
        cin >>username;

            for (unsigned int i=0;  i<UserList.size(); i++){

                if (username == UserList[i].getName()) {

                lognow = UserList[i];
                    }
            }
        logtest = true;
        if (lognow.getName() == " "){
            Sleep(200);
            cout<<"No user found with that name. Try again."<<endl;
            Sleep(1000);
            logtest = false;
        }
}
// Login Success
int choice1 = 0;
int choice2;
string s;
unsigned int whichpost;
bool alreadyLiked;
bool nopost;
bool enditall = false;
bool exflag = true;
bool bck;
string nof;
system("cls");
Welcome2Emerald(lognow.getName());
while (enditall == false){
    if(choice1 == 6){
        system("cls");
    Welcome2Emerald(lognow.getName());
    }
    while(exflag == true){
        startMenu();



        try{
            exflag = false;
            cin >> s;
            choice1 = stoi(s);
        } catch(exception e){
            Sleep(200);
            cout<<"You choose by typing numbers!"<<endl;
            Sleep(1000);
            exflag = true;
        }

        }
        exflag = true;

    //Handling main choices
    switch (choice1)
    {
    case 1:
        while (exflag == true){
            while (choice2 != 4){
                system("cls");
                lognow.showPosts(lognow.getName());
                Sleep(200);
                cout<<endl;
                cout<< "Choose what you wish to do! "<<endl;
                cout << endl;
                cout << "1: Create a post." << endl;
                Sleep(200);
                cout << "2: Create a comment at a post." << endl;
                Sleep(200);
                cout << "3: Like a post." << endl;
                Sleep(200);
                cout << "4: Go back."<<endl;

                try{
                    exflag = false;
                    cin >> s;
                    choice2 = stoi(s);
                } catch(exception e){
                    Sleep(200);
                    cout<<"You choose by typing numbers!"<<endl;
                    Sleep(1000);
                    exflag = true;
                    choice2=0;
                }



            switch (choice2)
            {

                case 1:
                    lognow.createPost(lognow.getName());
                break;
                case 2:
                    nopost = false;
                    while (nopost == false){
                        bck = false;
                        Sleep(200);
                        cout<<endl;
                        cout<< "Create a comment at which post? (Type 0 to go back) "<<endl;
                        cout<<endl;
                        try{
                            cin >> s;
                            whichpost = stoi(s);
                        } catch(exception e){
                            Sleep(200);
                            cout<<"You choose by typing numbers!"<<endl;
                            Sleep(1000);
                            whichpost = 0;
                        }
                        if(whichpost == 0){
                                bck = true;
                        }
                        nopost = true;
                        if ((whichpost > UserList[lognow.findUserNo(lognow.getName())].posts.size() || whichpost < 1) && (bck == false )){
                            Sleep(200);
                            cout<<"You selected a post that doesn't exist!"<<endl;
                            Sleep(1000);
                            nopost = false;
                        }
                    }
                    if(bck == false){
                        lognow.createComment(whichpost, lognow.getName());
                    }

                break;
                case 3:
                    alreadyLiked = false;
                    nopost = false;
                    while (nopost == false){
                        bck = false;
                        Sleep(200);
                        cout<<endl;
                        cout<< "Like which post? (Type 0 to go back) "<<endl;
                        cout<<endl;
                        try{
                            cin >> s;
                            whichpost = stoi(s);
                        } catch(exception e){
                            Sleep(200);
                            cout<<"You choose by typing numbers!"<<endl;
                            Sleep(1000);
                            whichpost = 0;
                        }
                        if(whichpost == 0){
                            bck = true;
                            alreadyLiked = true;
                        }
                        nopost = true;
                        if ((whichpost > UserList[lognow.findUserNo(lognow.getName())].posts.size() || whichpost < 1) && (bck == false )){
                            Sleep(200);
                            cout<<"You selected a post that doesn't exist!"<<endl;
                            Sleep(1000);
                            nopost = false;
                            alreadyLiked = true;
                        }
                        if(alreadyLiked == false){
                            for(unsigned int h = 0; h < whoLiked[lognow.findUserNo(lognow.getName())][whichpost-1].size(); h++){
                                if(whoLiked[lognow.findUserNo(lognow.getName())][whichpost-1][h].getName() == lognow.getName()){
                                    Sleep(200);
                                    cout<<"You have already liked this post!"<<endl;
                                    Sleep(1000);
                                    alreadyLiked = true;
                                }
                            }
                        }
                        if(alreadyLiked == false){
                            UserList[lognow.findUserNo(lognow.getName())].posts[whichpost-1].addLike();
                            if(whoLiked[lognow.findUserNo(lognow.getName())][whichpost-1][0].getName() == " "){
                                whoLiked[lognow.findUserNo(lognow.getName())][whichpost-1][0] = UserList[lognow.findUserNo(lognow.getName())];
                            } else{
                                    whoLiked[lognow.findUserNo(lognow.getName())][whichpost-1].push_back(UserList[lognow.findUserNo(lognow.getName())]);
                            }
                        }
                    }

                break;
                case 4:
                break;
                default:
                    Sleep(200);
                    cout << "Wrong choice, try again!" << endl;
                    Sleep(1000);
        }
        }
        }
        exflag = true;
    choice2 = 0;
    break;
    case 2:
        while(exflag == true){
            while (choice2 != 4){
                nof = lognow.showFriendPosts(lognow.getName());

                if(nof != " "){
                    Sleep(200);
                    system("cls");
                    cout<<endl;
                    cout<< "Choose what you wish to do! "<<endl;
                    cout << endl;
                    Sleep(200);
                    cout << "1: Create a post." << endl;
                    Sleep(200);
                    cout << "2: Create a comment at a post." << endl;
                    Sleep(200);
                    cout << "3: Like a post." << endl;
                    Sleep(200);
                    cout << "4: Go back."<<endl;

                    try{
                        exflag = false;
                        cin >> s;
                        choice2 = stoi(s);
                    } catch(exception e){
                        Sleep(200);
                        cout<<"You choose by typing numbers!"<<endl;
                        Sleep(1000);
                        exflag = true;
                        choice2=0;
                    }

                    switch (choice2)
                    {

                        case 1:
                            lognow.createFriendPost(nof);
                        break;
                        case 2:
                                nopost = false;
                            while (nopost == false){
                                bck = false;
                                Sleep(200);
                                cout<<endl;
                                cout<< "Create a comment at which post? (Type 0 to go back) "<<endl;
                                cout<<endl;
                                try{
                                    cin >> s;
                                    whichpost = stoi(s);
                                } catch(exception e){
                                    Sleep(200);
                                    cout<<"You choose by typing numbers!"<<endl;
                                    Sleep(1000);
                                    whichpost = 0;
                                }
                                if(whichpost == 0){
                                    bck = true;
                                }
                                nopost = true;
                                if ((whichpost > UserList[lognow.findUserNo(nof)].posts.size() || whichpost < 1) && (bck == false )){
                                    Sleep(200);
                                    cout<<"You selected a post that doesn't exist!"<<endl;
                                    Sleep(1000);
                                    nopost = false;
                                }
                                if(bck == false){
                                lognow.createFriendComment(whichpost, nof);
                                }
                        }

                        break;
                        case 3:
                            alreadyLiked = false;
                            nopost = false;
                                while (nopost == false){
                                    bck = false;
                                    Sleep(200);
                                    cout<<endl;
                                    cout<< "Like which post? (type 0 to go back) "<<endl;
                                    cout<<endl;
                                    try{
                                        cin >> s;
                                        whichpost = stoi(s);
                                        } catch(exception e){
                                        Sleep(200);
                                        cout<<"You choose by typing numbers!"<<endl;
                                        Sleep(1000);
                                        whichpost = 0;
                                    }
                                    if(whichpost == 0){
                                        alreadyLiked = true;
                                        bck = true;
                                    }
                                    nopost = true;
                                    if ((whichpost > UserList[lognow.findUserNo(nof)].posts.size() || whichpost < 1) && (bck == false )){
                                        Sleep(200);
                                        cout<<"You selected a post that doesn't exist!"<<endl;
                                        Sleep(1000);
                                        nopost = false;
                                        alreadyLiked = true;
                                    }
                                    if(alreadyLiked == false){
                                        for(unsigned h = 0; h < whoLiked[lognow.findUserNo(nof)][whichpost-1].size(); h++){
                                            if(whoLiked[lognow.findUserNo(nof)][whichpost-1][h].getName() == lognow.getName()){
                                                Sleep(200);
                                                cout<<"You have already liked this post!"<<endl;
                                                Sleep(1000);
                                                alreadyLiked = true;
                                            }
                                        }
                                    }
                                    if(alreadyLiked == false){
                                        UserList[lognow.findUserNo(nof)].posts[whichpost-1].addLike();
                                        if(whoLiked[lognow.findUserNo(nof)][whichpost-1][0].getName() == " "){
                                            whoLiked[lognow.findUserNo(nof)][whichpost-1][0] = UserList[lognow.findUserNo(lognow.getName())];
                                        } else{
                                            whoLiked[lognow.findUserNo(nof)][whichpost-1].push_back(UserList[lognow.findUserNo(lognow.getName())]);
                                        }
                                    }
                                }

                        break;
                        case 4:
                        break;
                        default:
                            Sleep(200);
                            cout << "Wrong choice, try again!" << endl;
                            Sleep(1000);
                    }
                } else{
                    choice2 = 4;
                }
            }
        }
        exflag = true;
        choice2 = 0;

    break;
    case 3:
        lognow.addFriend(lognow.getName());
    break;
    case 4:
        lognow.manageFriendRequests(lognow.getName());
    break;
    case 5:
        lognow.printFriends(lognow.getName());
        Sleep(200);
        cout<<"Type 1 to remove a friend or 2 to go back"<<endl;
        try{
            cin >> s;
            choice2 = stoi(s);
        } catch(exception e){
            Sleep(200);
            cout<<"You choose by typing numbers!"<<endl;
            Sleep(1000);
            choice2=0;
        }
            if(choice2 == 1){
                lognow.printFriends(lognow.getName());
                lognow.removeFriend(lognow.getName());
                Sleep(200);
                cout<<"Friend removed"<<endl;
                choice2 = 2;
            } else if (choice2 == 2){
            }else{
                Sleep(200);
                cout<<"Wrong choice! Try again."<<endl;
                Sleep(1000);
            }

        choice2 = 0;

    break;
    case 6:
        system("cls");
        lognow = zero;
        logtest = false;
        while (logtest == false) {
            Sleep(200);
            cout << "Give username" << endl;
            cin >>username;

        for (unsigned int i=0;  i<UserList.size(); i++){

                if (username == UserList[i].getName()) {

                lognow = UserList[i];
                    }
            }
        logtest = true;
        if (lognow.getName() == " "){


            cout<<"No user found with that name. Try again."<<endl;
            Sleep(1000);
            logtest = false;

            }
    }

    break;
    case 7:
        enditall = true;
        Sleep(200);
        cout<<"Exiting..."<<endl;
        Sleep(1000);
    break;
    default:
        Sleep(200);
        cout << "Wrong choice, try again!" << endl;

    }
    system("cls");

}
    return 0;
}


