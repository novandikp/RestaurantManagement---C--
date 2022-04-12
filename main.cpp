// import
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>

// Nama :Novandi Kevin Pratama
// NPM : 20081010005
// Kelas : PBO (C081)

using namespace std;
// Restaurant OOP
// Menu Class
class Menu
{
private:
    string sku;
    string name;
    string description;
    double price;

public:
    Menu(string sku, string name, string description, double price)
    {
        this->sku = sku;
        this->name = name;
        this->description = description;
        this->price = price;
    }
    string getSku()
    {
        return sku;
    }
    string getName()
    {
        return name;
    }
    string getDescription()
    {
        return description;
    }
    double getPrice()
    {
        return price;
    }

    void showMenu()
    {
        cout << "Sku: " << sku << endl;
        cout << "Name: " << name << endl;
        cout << "Description: " << description << endl;
        cout << "Price: " << price << endl;
    }
};

// Table Class
class Table
{
private:
    int tableNumber;
    int numberOfSeats;
    bool isOccupied;

public:
    Table()
    {
        this->tableNumber = 0;
        this->numberOfSeats = 0;
        this->isOccupied = false;
    }
    Table(int tableNumber, int numberOfSeats)
    {
        this->tableNumber = tableNumber;
        this->numberOfSeats = numberOfSeats;
        this->isOccupied = true;
    }
    int getTableNumber()
    {
        return tableNumber;
    }
    int getNumberOfSeats()
    {
        return numberOfSeats;
    }
    bool getIsOccupied()
    {
        return isOccupied;
    }
    void setOccupy()
    {
        this->isOccupied = true;
    }

    void setOnOccupy()
    {
        this->isOccupied = false;
    }
};

// Waiter Class
class Waiter
{
private:
    string name;
    string phonenumber;
    string email;
    string password;

public:
    Waiter()
    {
        this->name = "";
        this->phonenumber = "";
        this->email = "";
        this->password = "";
    }
    Waiter(string name, string phonenumber, string email, string password)
    {
        this->name = name;
        this->phonenumber = phonenumber;
        this->email = email;
        this->password = password;
    }
    string getName()
    {
        return name;
    }
    string getPhonenumber()
    {
        return phonenumber;
    }
    string getEmail()
    {
        return email;
    }
    string getPassword()
    {
        return password;
    }
};

// Detail Bill Class
class DetailBill : public Menu
{
private:
    int quantity;
    double totalPrice;

public:
    DetailBill(string sku, string name, string description, double price, int quantity) : Menu(sku, name, description, price)
    {
        this->quantity = quantity;
        this->totalPrice = price * quantity;
    }

    void addQuantity(int quantity)
    {
        this->quantity += quantity;
        this->totalPrice = getPrice() * quantity;
    }

    int getQuantity()
    {
        return quantity;
    }
    double getTotalPrice()
    {
        return totalPrice;
    }
};

enum StatusOrder
{
    Waiting,
    Served,
    Paid,
};

const string StatusStr[] = {
    "Waiting",
    "Served",
    "Paid"};

// Bill Class
class Bill
{
private:
    double total;
    double pay;
    double change;
    string customer_name;
    string faktur;
    vector<DetailBill> detail;
    Table *table;
    Waiter waiter;
    bool isPayed;
    StatusOrder status;

public:
    static int countBill;
    Bill(Table *table, Waiter waiter, string customer_name)
    {
        countBill++;
        this->customer_name = customer_name;
        this->table = table;
        this->table->setOnOccupy();
        this->waiter = waiter;
        this->isPayed = false;
        this->status = Waiting;
        this->total = 0;
        this->pay = 0;
        this->change = 0;

        // Set faktur
        faktur = "";
        for (int i = 0; i < 6 - floor(countBill / 10); i++)
        {
            faktur += "0";
        }
        faktur += to_string(countBill);
    }

    Bill()
    {
        this->customer_name = "";
        this->table = nullptr;
        this->waiter = Waiter();
        this->isPayed = false;
        this->status = Waiting;
        this->total = 0;
        this->pay = 0;
        this->change = 0;
        // Set faktur
        this->faktur = "";
    }

    string getFaktur()
    {
        return faktur;
    }

    double getTotal()
    {
        return total;
    }

    bool isEmptyCart()
    {
        return detail.empty();
    }

    void shortInformation()
    {
        cout << "Faktur : " << faktur << endl;
        cout << "Customer Name : " << customer_name << endl;
        cout << "Table Number : " << table->getTableNumber() << endl;
        cout << "Number of Seats : " << table->getNumberOfSeats() << endl;
        cout << "Waiter Name : " << waiter.getName() << endl;
        cout << "Status : " << StatusStr[status] << endl;
        cout << "Total : " << total << endl;
    }

    void servingMenu()
    {
        system("cls");
        if (status == Waiting)
        {
            status = Served;

            cout << "Faktur : " << faktur << endl;
            cout << "Success!!" << endl;
            cout << "Order is served" << endl;
        }
        else
        {
            cout << "Faktur : " << faktur << endl;
            cout << "Failed!!" << endl;
            cout << "Bill is already serving" << endl;
        }
        system("pause");
    }

    void payBill(double pay)
    {

        if (status == Served)
        {
            if (pay < total)
            {
                system("cls");
                cout << "Faktur : " << faktur << endl;
                cout << "Failed!!" << endl;
                cout << "Payment is not enough" << endl;
            }
            else
            {
                this->pay = pay;
                this->change = pay - total;
                this->isPayed = true;
                this->status = Paid;
                this->table->setOccupy();

                this->printReceipt();
            }
        }
        else
        {
            system("cls");
            cout << "Faktur : " << faktur << endl;
            cout << "Failed!!" << endl;
            cout << "Bill is not serving" << endl;
        }
        system("pause");
    }

    void printReceipt()
    {
        cout << "Table Number: " << table->getTableNumber() << endl;
        cout << "Customer Name: " << customer_name << endl;
        cout << "Faktur: " << faktur << endl;
        cout << "==========================================================" << endl;
        cout << "Menu Ordered" << endl;
        cout << "==========================================================" << endl;
        for (int i = 0; i < detail.size(); i++)
        {
            cout << detail[i].getName() << " x" << detail[i].getQuantity() << " = " << detail[i].getTotalPrice() << endl;
        }
        cout << "==========================================================" << endl;
        cout << "Total: " << total << endl;
        cout << "Pay: " << pay << endl;
        cout << "Change: " << change << endl;
        cout << "==========================================================" << endl;
    }

    void setTotal()
    {
        for (int i = 0; i < detail.size(); i++)
        {
            total += detail[i].getTotalPrice();
        }
    }

    void addMenu(Menu menu, int quantity)
    {
        // Check if exists in detail bill
        bool isExist = false;
        for (int i = 0; i < detail.size(); i++)
        {
            if (detail[i].getSku() == menu.getSku())
            {
                isExist = true;
                detail[i].addQuantity(quantity);
            }
        }

        if (!isExist)
        {
            detail.push_back(DetailBill(menu.getSku(), menu.getName(), menu.getDescription(), menu.getPrice(), quantity));
        }
        this->setTotal();
    }

    void removeMenu(string sku)
    {
        bool isExist = false;
        for (int i = 0; i < detail.size(); i++)
        {
            if (detail[i].getSku() == sku)
            {
                detail.erase(detail.begin() + i);
                isExist = true;
            }
        }

        if (isExist)
        {
            this->setTotal();
        }
        else
        {
            cout << "Menu not found in cart" << endl;
            system("pause");
        }
    }

    void showCart()
    {
        for (int i = 0; i < detail.size(); i++)
        {
            cout << detail[i].getName() << " x" << detail[i].getQuantity() << " " << detail[i].getPrice() << " = " << detail[i].getTotalPrice() << endl;
        }
    }
};

//  Restaurant Class
class Restaurant
{
private:
    vector<Menu> listMenu;
    vector<Table> listTable;
    vector<Waiter> listWaiter;
    vector<Bill> listBill;

    string restaurant_name;
    string address;
    double income;

public:
    Restaurant()
    {
        this->income = 0;
        // Dummy Menu
        this->listMenu.push_back(Menu("1", "Nasi Goreng Kambing", "Nasi goreng dengan daging kambing muda", 10000));
        this->listMenu.push_back(Menu("2", "Nasi Uduk", "Nasi uduk enak", 10000));
        this->listMenu.push_back(Menu("3", "Nasi Ayam", "Nasi ayam krispi yang gurih dan enak", 10000));
        this->listMenu.push_back(Menu("4", "Nasi Goreng", "Nasi goreng Ayam", 10000));

        // Dummy Waiter
        this->listWaiter.push_back(Waiter("Budi", "0812345678", "admin@gmail.com", "admin"));
        this->listWaiter.push_back(Waiter("Andi", "0812345679", "andi@gmail.com", "andi"));

        // Dummy Table
        this->listTable.push_back(Table(1, 10));
        this->listTable.push_back(Table(2, 10));
        this->listTable.push_back(Table(3, 10));
        this->listTable.push_back(Table(4, 10));
        this->listTable.push_back(Table(5, 10));
        this->listTable.push_back(Table(6, 10));
        this->listTable.push_back(Table(7, 10));
        this->listTable.push_back(Table(8, 10));
        this->listTable.push_back(Table(9, 10));
        this->listTable.push_back(Table(10, 10));

        address = "Rungkut Madya, Surabaya";
        restaurant_name = "Warung Nasi";
    }

    void setIdentity(string restaurant_name, string address)
    {
        this->restaurant_name = restaurant_name;
        this->address = address;
    }

    void showIdentity()
    {
        cout << "Restaurant Name : " << restaurant_name << endl;
        cout << "Address : " << address << endl;
        cout << "==========================================================" << endl;
    }

    void showOrder()
    {
        for (int i = 0; i < listBill.size(); i++)
        {
            listBill[i].shortInformation();
            cout << endl;
        }
    }

    void showMenu()
    {
        for (int i = 0; i < listMenu.size(); i++)
        {
            cout << "SKU :" << listMenu[i].getSku() << endl
                 << listMenu[i].getName() << endl
                 << listMenu[i].getDescription() << endl
                 << "Harga : " << listMenu[i].getPrice() << endl
                 << endl;
        }
    }

    bool isExistMenu(string sku)
    {
        for (int i = 0; i < listMenu.size(); i++)
        {
            if (listMenu[i].getSku() == sku)
            {
                return true;
            }
        }
        return false;
    }

    Menu getMenu(string sku)
    {
        for (int i = 0; i < listMenu.size(); i++)
        {
            if (listMenu[i].getSku() == sku)
            {
                return listMenu[i];
            }
        }
        return Menu("", "", "", 0);
    }

    void addMenu(Menu menu)
    {
        if (isExistMenu(menu.getSku()))
        {
            cout << "Failed !" << endl;
            cout << "Menu already exist" << endl;
            system("pause");
        }
        else
        {
            listMenu.push_back(menu);
        }
    }

    void removeMenu(string sku)
    {
        for (int i = 0; i < listMenu.size(); i++)
        {
            if (listMenu[i].getSku() == sku)
            {
                listMenu.erase(listMenu.begin() + i);
            }
        }
    }

    void editMenu(string sku, Menu menu)
    {
        for (int i = 0; i < listMenu.size(); i++)
        {
            if (listMenu[i].getSku() == sku)
            {
                listMenu[i] = menu;
            }
        }
    }

    bool isExistTable(int table_number)
    {
        for (int i = 0; i < listTable.size(); i++)
        {
            if (listTable[i].getTableNumber() == table_number)
            {
                return true;
            }
        }
        return false;
    }

    bool isAvailableTable(int tableNumber)
    {
        for (int i = 0; i < listTable.size(); i++)
        {
            if (listTable[i].getTableNumber() == tableNumber && listTable[i].getIsOccupied())
            {
                return true;
            }
        }
        return false;
    }

    void addTable(Table table)
    {
        if (isExistTable(table.getTableNumber()))
        {
            cout << "Failed !" << endl;
            cout << "Table already exist" << endl;
            system("pause");
        }
        else
        {
            listTable.push_back(table);
        }
    }

    void removeTable(int tableNumber)
    {
        for (int i = 0; i < listTable.size(); i++)
        {
            if (listTable[i].getTableNumber() == tableNumber)
            {
                if (listTable[i].getIsOccupied())
                {
                    cout << "Failed !" << endl;
                    cout << "Table is occupied" << endl;
                    system("pause");
                }
                else
                {
                    listTable.erase(listTable.begin() + i);
                }
                break;
            }
        }
    }

    void showAvailableTable()
    {
        cout << "Available Table :" << endl;
        for (int i = 0; i < listTable.size(); i++)
        {
            if (listTable[i].getIsOccupied())
            {
                // Write detail table
                cout << "Table Number: " << listTable[i].getTableNumber() << endl;
                cout << "Seat Capacity: " << listTable[i].getNumberOfSeats() << endl;
                cout << "==========================================================" << endl;
            }
        }
    }

    Table *getTable(int tableNumber)
    {
        Table *table = new Table;
        for (int i = 0; i < listTable.size(); i++)
        {
            if (listTable[i].getTableNumber() == tableNumber)
            {
                delete table;
                return &listTable[i];
            }
        }

        return table;
    }

    bool checkLogin(string email, string password)
    {
        for (int i = 0; i < listWaiter.size(); i++)
        {
            if (listWaiter[i].getEmail() == email && listWaiter[i].getPassword() == password)
            {
                return true;
            }
        }
        return false;
    }

    Waiter getUser(string email, string password)
    {
        for (int i = 0; i < listWaiter.size(); i++)
        {
            if (listWaiter[i].getEmail() == email && listWaiter[i].getPassword() == password)
            {
                return listWaiter[i];
            }
        }
        return Waiter();
    }

    bool isExistBill(string faktur)
    {
        for (int i = 0; i < listBill.size(); i++)
        {
            if (listBill[i].getFaktur() == faktur)
            {
                return true;
            }
        }
        return false;
    }

    Bill *getBill(string faktur)
    {
        Bill *temp = new Bill;
        for (int i = 0; i < listBill.size(); i++)
        {
            if (listBill[i].getFaktur() == faktur)
            {
                delete temp;
                return &listBill[i];
            }
        }
        return temp;
    }

    void addBill(Bill bill)
    {
        income += bill.getTotal();
        listBill.push_back(bill);
    }

    double getIncome()
    {
        return income;
    }
};

// Count Bill
int Bill::countBill = 0;

int main(int argc, const char **argv)
{
    // Clear screen
    system("cls");

    Restaurant restaurant;
    Waiter user;

    // Login page
    string email;
    string password;
    bool isLogin = false;
    while (!isLogin)
    {

        cout << "==========================================================" << endl;
        cout << "Welcome to Restaurant" << endl;
        cout << "==========================================================" << endl;
        cout << "Nama : Novandi Kevin Pratama" << endl;
        cout << "NPM : 20081010005" << endl;
        cout << "Kelas : PBO (C081)" << endl
             << endl;
        cout << "Default Email : admin@gmail.com" << endl;
        cout << "Default Password : admin" << endl
             << endl;
        cout << "Please login to continue" << endl;
        cout << "Email: ";
        cin >> email;
        cout << "Password: ";
        cin >> password;
        isLogin = restaurant.checkLogin(email, password);
        if (!isLogin)
        {
            cout << "Wrong email or password" << endl;
            system("pause");
            system("cls");
        }
        else
        {
            user = restaurant.getUser(email, password);
        }
    }

    // Main Menu
    int choice;
    bool exitApp = false;
    while (!exitApp)
    {
        system("cls");
        cout << "==========================================================" << endl;
        cout << "Main Menu" << endl;
        cout << "==========================================================" << endl;
        restaurant.showIdentity();
        cout << "Total Order : " << Bill::countBill << endl;
        cout << "Total Income : " << restaurant.getIncome() << endl;

        cout << "==========================================================" << endl;
        cout << "1.\tSet Profile Restaurant" << endl;
        cout << "2.\tShow Menu Restaurant" << endl;
        cout << "3.\tAdd Menu Restaurant" << endl;
        cout << "4.\tEdit Menu Restaurant" << endl;
        cout << "5.\tRemove Menu Restaurant" << endl;
        cout << "6.\tAdd Order" << endl;
        cout << "7.\tShow All Order" << endl;
        cout << "8.\tServing Menu" << endl;
        cout << "9.\tPay Bill" << endl;
        cout << "10.\tShow Available Table" << endl;
        cout << "11.\tAdd Table" << endl;
        cout << "12.\tRemove Table" << endl;
        cout << "13.\tExit" << endl;
        cout << "==========================================================" << endl;
        cout << "Please choose: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {

            system("cls");
            cout << "==========================================================" << endl;
            cout << "Profile Restaurant" << endl;
            cout << "==========================================================" << endl;
            string name, address;
            cin.ignore();
            cout << "Name Restaurant : ";
            getline(cin, name);
            cout << "Address Restaurant : ";
            getline(cin, address);
            restaurant.setIdentity(name, address);
            break;
        }
        case 2:
        {
            system("cls");
            cout << "==========================================================" << endl;
            cout << "List Menu Our Restaurant" << endl;
            cout << "==========================================================" << endl;
            restaurant.showMenu();
            system("pause");
            break;
        }
        case 3:
        {
            system("cls");
            cout << "==========================================================" << endl;
            cout << "Add Menu" << endl;
            cout << "==========================================================" << endl;
            string name, description, sku;
            double price;
            cin.ignore();
            cout << "SKU Menu : ";
            getline(cin, sku);
            cout << "Name Menu : ";
            getline(cin, name);
            cout << "Description Menu : ";
            getline(cin, description);
            cout << "Price Menu : ";
            cin >> price;
            restaurant.addMenu(Menu(sku, name, description, price));
            break;
        }
        case 4:
        {
            system("cls");
            cout << "==========================================================" << endl;
            cout << "Edit Menu" << endl;
            cout << "==========================================================" << endl;

            string sku;
            cin.ignore();
            cout << "SKU Menu : ";
            getline(cin, sku);
            if (restaurant.isExistMenu(sku))
            {
                cout << "Last Menu :" << endl;
                restaurant.getMenu(sku).showMenu();
                cout << "==========================================================" << endl;
                cout << "New Menu :" << endl;
                string name, description;
                double price;
                cout << "Name Menu : ";
                getline(cin, name);
                cout << "Description Menu : ";
                getline(cin, description);
                cout << "Price Menu : ";
                cin >> price;
                restaurant.editMenu(sku, Menu(sku, name, description, price));
            }
            else
            {
                cout << "Menu not found" << endl;
                system("pause");
            }

            break;
        }
        case 5:
        {
            system("cls");
            cout << "==========================================================" << endl;
            cout << "Remove Menu" << endl;
            cout << "==========================================================" << endl;

            string sku;
            cin.ignore();
            cout << "SKU Menu : ";
            getline(cin, sku);
            if (restaurant.isExistMenu(sku))
            {
                restaurant.removeMenu(sku);
            }
            else
            {
                cout << "Menu not found" << endl;
                system("pause");
            }
            break;
        }
        case 6:
        {
            // Make Order
            system("cls");

            bool tableCheck = false;
            int tableNumber;
            while (!tableCheck)
            {
                cout << "==========================================================" << endl;
                cout << "Make New Order" << endl;
                cout << "==========================================================" << endl;
                cout << "Please choose table number: ";
                cin >> tableNumber;
                if (restaurant.isAvailableTable(tableNumber))
                {
                    tableCheck = true;
                }
                else
                {
                    system("cls");
                    cout
                        << "Table not available or not found" << endl;
                    system("pause");
                    system("cls");
                }
            }

            string customer = "";
            cout << "Please enter customer name: ";
            cin.ignore();
            getline(cin, customer);
            Bill bill = Bill(restaurant.getTable(tableNumber), user, customer);
            bool isOrder = true;
            while (isOrder)
            {
                system("cls");
                bill.shortInformation();
                cout << "==========================================================" << endl;
                cout << "Choose :" << endl;
                cout << "1. Add Menu in Cart" << endl;
                cout << "2. Remove Menu in Cart" << endl;
                cout << "3. Show Menu" << endl;
                cout << "4. Show Cart" << endl;
                cout << "5. Done" << endl;
                cout << "==========================================================" << endl;
                cout << "Please choose: ";
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    // Add detail Bill
                    system("cls");

                    cout
                        << "Please Input SKU Menu" << endl;
                    string sku;
                    cin >> sku;
                    if (restaurant.isExistMenu(sku))
                    {
                        Menu menu = restaurant.getMenu(sku);
                        int quantity;
                        cout << "Please Input Quantity" << endl;
                        cin >> quantity;
                        bill.addMenu(menu, quantity);
                    }
                    else
                    {
                        cout << "Menu not found" << endl;
                        system("pause");
                    }
                    break;
                }
                case 2:
                {
                    // Remove detail Bill
                    system("cls");
                    cout << "Please Input SKU Menu in Cart to remove" << endl;
                    string sku;
                    cin >> sku;
                    bill.removeMenu(sku);
                    break;
                }
                case 3:
                    // Show Menu
                    system("cls");
                    cout << "==========================================================" << endl;
                    cout << "List Menu Our Restaurant" << endl;
                    cout << "==========================================================" << endl;
                    restaurant.showMenu();
                    system("pause");
                    break;
                case 4:
                    system("cls");
                    cout << "==========================================================" << endl;
                    cout << "Your Cart" << endl;
                    cout << "==========================================================" << endl;
                    bill.showCart();
                    system("pause");
                    break;
                case 5:
                    if (bill.isEmptyCart())
                    {
                        system("cls");
                        cout << "==========================================================" << endl;
                        cout << "Your Cart is Empty Please Add Minimal 1 Menu" << endl;
                        cout << "==========================================================" << endl;
                        system("pause");
                    }
                    else
                    {
                        system("cls");
                        cout << "==========================================================" << endl;
                        cout << "Success Order Saved" << endl;
                        cout << "==========================================================" << endl;
                        system("pause");
                        isOrder = false;
                    }

                    break;
                default:
                    system("cls");
                    cout << "==========================================================" << endl;
                    cout << "Wrong Input" << endl;
                    cout << "==========================================================" << endl;
                    system("pause");
                    break;
                }
            }

            restaurant.addBill(bill);

            break;
        }
        case 7:
        {
            system("cls");
            cout << "==========================================================" << endl;
            cout << "List All Order" << endl;
            cout << "==========================================================" << endl;
            restaurant.showOrder();
            system("pause");
            break;
        }
        case 8:
        {
            system("cls");
            cout << "==========================================================" << endl;
            cout << "Serving Menu" << endl;
            cout << "==========================================================" << endl;
            string faktur;
            cout << "Please Input Faktur: ";
            cin >> faktur;
            if (restaurant.isExistBill(faktur))
            {
                Bill *bill = restaurant.getBill(faktur);
                bill->servingMenu();
            }
            else
            {
                cout << "Bill not found" << endl;
                system("pause");
            }

            break;
        }
        case 9:
        {
            // Pay Bill
            system("cls");
            cout << "==========================================================" << endl;
            cout << "Pay Bill" << endl;
            cout << "==========================================================" << endl;
            cout << "Please Input Faktur: ";
            string faktur;
            cin >> faktur;
            if (restaurant.isExistBill(faktur))
            {
                Bill *bill = restaurant.getBill(faktur);
                bill->shortInformation();
                double payment;
                cout << "Please Input Payment: ";
                cin >> payment;
                system("cls");
                restaurant.showIdentity();
                bill->payBill(payment);
            }
            else
            {
                cout << "Bill not found" << endl;
                system("pause");
            }
            break;
        }
        case 10:
        {
            system("cls");
            restaurant.showAvailableTable();
            system("pause");
            break;
        }
        case 11:
        {
            system("cls");
            // Add table
            cout << "==========================================================" << endl;
            cout << "Add Table" << endl;
            cout << "==========================================================" << endl;
            int tableNumber;
            int seatNumber;
            cout << "Please Input Table Number: ";
            cin >> tableNumber;
            cout << "Please Input Seat Number: ";
            cin >> seatNumber;
            restaurant.addTable(Table(tableNumber, seatNumber));
            break;
        }
        case 12:
        {
            system("cls");
            cout << "==========================================================" << endl;
            cout << "Remove Table" << endl;
            cout << "==========================================================" << endl;
            int tableNumber;
            cout << "Please Input Table Number: ";
            cin >> tableNumber;
            if (restaurant.isExistTable(tableNumber))
            {
                restaurant.removeTable(tableNumber);
            }
            else
            {
                cout << "Table not found" << endl;
                system("pause");
            }
            break;
        }
        case 13:
        {
            cout << "Good Bye !" << endl;
            exitApp = true;
            break;
        }
        default:
            system("cls");
            cout << "==========================================================" << endl;
            cout << "Wrong Input" << endl;
            cout << "==========================================================" << endl;
            system("pause");
            break;
        }
    }

    return 0;
}