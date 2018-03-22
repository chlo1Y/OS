/*  This is where you define the structs needed to 
    solve this problem.  You can define constants, global
    variables, and function signatures here as well. 
    By <Zesun Yang>, <Nov 30 2017>
*/
struct Inventory{
    int itemNumber;
    int quantityOnHand;
    float price;
    struct expireDtae {
        int month;
        int year;
    }expireDate;
};
