/*  
By <zesun Yang> Dec 9 2017
*/
typedef struct {
    int itemNumber;
    int quantityOnHand;
    float price;
    struct expireDtae {
        int month;
        int year;
    }expireDate;
}Inventory;
