#include <String.h>

#define HOME_PAGE "www.tatu.la"
#define COMPANY_NAME "TATU.LA"
#define DEVICE_NAME "DINAMIGO"
#define SOFT_VERSION "1.0"
#define MOBILE "5491155093681"

// TODO: MAKE THEM UPDATABLE VIA Telegram

struct data {

        String device_name;
        String email;
// Social Networks
        String tweeter;
        String telegram;
        String instagram;
        String facebook;
        String snapchat;
// END Social Networks
        String mobile;
        String website;
        String product_link;
        String extra;

} contact_info;

int init_data (void);

///////////////////////////////////////////////////////////////////////////////////
// Load Data to the Support Screen - Modifiable from Menu
///////////////////////////////////////////////////////////////////////////////////
int init_data (void){

        contact_info.device_name = DEVICE_NAME;
        contact_info.email = "tatulaiot@gmail.com";
        contact_info.tweeter ="@tatulaiot";
        contact_info.telegram = "@tatulaiot";
        contact_info.mobile = MOBILE;
        contact_info.website = HOME_PAGE;
        contact_info.product_link = HOME_PAGE;
        contact_info.extra,"";

        return 0;
}
