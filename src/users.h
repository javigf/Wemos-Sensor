// File to define users and roles in the DINAMIGO
#define MAX_USERS 5
#define MAX_BLACKLIST 10

//USER STRUCTURE DEFINITION
struct user {

        String chatId;
        String userName;
        String userRole;
        bool userValidated;
        String userPassword;
        String userStatus;
        String userLastAccess;
        String userAddedBy;
        String userCreationDate;

} users [MAX_USERS];

//BLACKLIST STRUCTURE DEFINITION
struct blackList {

        String chatId;
        String userName;
        String lastdate;
        int count;

} blacklist [MAX_BLACKLIST];

enum role {soporte, admin, user};

int init_users_db (void);
int count_users (void);
int add_user (String, String);
int add_user (String, String);
int del_user (String);
int search_user_by_name (String);
int search_user_by_chatId (String);
int find_first_free_user_space (void);
int check_full_user_table (void);
int arrange_user_table (void);
int find_next_user (int position);

///////////////////////////////////////////////////////////////////////////////////
// Init users table -> Truncate Table
// Parameter :
// Returns : 0
///////////////////////////////////////////////////////////////////////////////////
int init_users_db (void){
        int i = 0, user_count = 0;

        users[i].chatId           = "309075155";
        users[i].userName         = "Javier";
        users[i].userRole         = "soporte";
        users[i].userValidated    = 1;
        users[i].userPassword     = "soporte";
        users[i].userStatus       = "activo";
        users[i].userLastAccess   = "1488937184";
        users[i].userAddedBy      = "soporte";
        users[i].userCreationDate = "1488937184";

        users[1].chatId           = "-202456688";
        users[1].userName         = "GRUPO";
        users[1].userRole         = "grupo";
        users[1].userValidated    = 1;
        users[1].userPassword     = "grupo";
        users[1].userStatus       = "activo";
        users[1].userLastAccess   = "1488937184";
        users[1].userAddedBy      = "soporte";
        users[1].userCreationDate = "1488937184";
//-202456688
        for (i = 2; i < MAX_USERS; i++) {
                users[i].chatId           = "";
                users[i].userName         = "";
                users[i].userRole         = "";
                users[i].userValidated    =  0;
                users[i].userPassword     = "";
                users[i].userStatus       = "";
                users[i].userLastAccess   = "";
                users[i].userAddedBy      = "";
                users[i].userCreationDate = "";
        }

        return 0;
}

///////////////////////////////////////////////////////////////////////////////////
// Count / Display users
// Parameter :
// Returns : Count of users
///////////////////////////////////////////////////////////////////////////////////
int count_users (void) {
        int i, user_count = 0;

        for (i = 0; i < MAX_USERS; i++) {
                String str = String(users[i].chatId);
                if (str != NULL)
                        user_count++;
        }

        return user_count;
}

///////////////////////////////////////////////////////////////////////////////////
// Add user
// Parameter : String chatId , String userName, ???String userRole, ???String userStatus
// Returns 0: Success, -1 Error
///////////////////////////////////////////////////////////////////////////////////
int add_user (String chatId, String userName){
        int status = 0, i;

        i = find_first_free_user_space ();
        Serial.print ("I:");
        Serial.println (i);
        if (i > 0) {
                //update_clk (); //TODO

                users[i].chatId           = chatId;
                users[i].userName         = userName;
                //users[i].userRole = userRole;
                users[i].userValidated    = 1;
                users[i].userPassword     = userName;
                users[i].userStatus       = "activo";
                users[i].userLastAccess   = local_epoch;
                users[i].userAddedBy      = "admin";
                users[i].userCreationDate = local_epoch;
        }
        else
                status = -1;

        return status;
}

///////////////////////////////////////////////////////////////////////////////////
// Add user blackList
// Parameter : String chatId , String userName, String userRole, String userStatus
// Returns 0: Success, -1 Error
///////////////////////////////////////////////////////////////////////////////////
/*int add_user (String chatId, String userName){
        int status = 0;

        return status;
   }*/

///////////////////////////////////////////////////////////////////////////////////
// Delete user by chatId
// Parameter : String userName
// Returns : 0 Success / -1 Error
///////////////////////////////////////////////////////////////////////////////////
int del_user (String chatId){
        int status = 0, i;

        i = search_user_by_chatId (chatId);

        if ((i < 0) && (i >= MAX_USERS))
                users[i].chatId ="";
        else
                status = -1;

        return status;
}

///////////////////////////////////////////////////////////////////////////////////
// Search users by Name
// Parameter : String userName
// Returns : 0 Success / -1 Error
///////////////////////////////////////////////////////////////////////////////////
int search_user_by_name (String userName){
        int i, position = 0;
        String str;
        for (i = 0; (( i < MAX_USERS ) && (str != userName)); i++)
                str = String(users[i].userName);
        if (i < MAX_USERS)
                position = i;

        return position;
}

///////////////////////////////////////////////////////////////////////////////////
// Search users by Chat ID
// Parameter : String userName
// Returns : 0/MAX_USERS Success / -1 NOT FOUND
///////////////////////////////////////////////////////////////////////////////////
// TODO : Support Account in Position 0
int search_user_by_chatId (String chatId){
        int i, position = -1;
        String str;

        for (i = 0; (( i < MAX_USERS ) && ( str != chatId )); i++)
                str = String(users[i].chatId);
        if (i < MAX_USERS)
                position = i;

        return position;
}

///////////////////////////////////////////////////////////////////////////////////
// Search last user added or first space available on user table
// Parameter : NONE
// Returns : first free position or end of table
///////////////////////////////////////////////////////////////////////////////////
int find_first_free_user_space (void){
        int i, position = 0;

        String str = "*";

        for (i = 0; ((i < MAX_USERS) && (str != NULL)); i++)
                str = String(users[i].chatId);

        position = i;
        //Serial.println (position);

        if (i >= MAX_USERS)
                position = -1;

        return position;
}

///////////////////////////////////////////////////////////////////////////////////
// Looks for available space on user table
// Parameter : NONE
// Returns : full -1 / free space 0
///////////////////////////////////////////////////////////////////////////////////
int check_full_user_table (void){
        int status = 0;

        if (MAX_USERS <= find_first_free_user_space ())
                status = 1;

        return status;
}

///////////////////////////////////////////////////////////////////////////////////
// Looks for available space on user table
// Parameter : NONE
// Returns : full -1 / free space 0
///////////////////////////////////////////////////////////////////////////////////
int arrange_user_table (void){
        int status = 0;

        status = find_first_free_user_space ();
        if (!status) // Table is full
                status = -1;
        else
                find_next_user (status);


        return status;
}

///////////////////////////////////////////////////////////////////////////////////
// Looks for available space on user table
// Parameter : NONE
// Returns : full -1 / free space 0
///////////////////////////////////////////////////////////////////////////////////
int find_next_user (int position){

        while ((String)users[position++].chatId != NULL) ;

        return position;
}
