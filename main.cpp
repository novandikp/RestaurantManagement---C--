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
        Table *tableA = new Table();
        this->table = table;
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
        total = 0;
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
                if (!listTable[i].getIsOccupied())
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

class View : Restaurant
{
private:
    Waiter user;

public:
    void start()
    {
        system("cls");
        loginPage(1);
    }

    void loginPage(int i)
    {
        string email;
        string password;
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
        getline(cin, email);
        cout << "Password: ";
        getline(cin, password);
        if (i > 3)
        {
            cout << "You have tried too many times" << endl;
            system("pause");
            exitApp();
        }
        else if (!checkLogin(email, password))
        {
            cout << "Wrong email or password" << endl;
            system("pause");
            system("cls");
            loginPage(i + 1);
        }

        else
        {
            user = getUser(email, password);
            mainPage();
        }
    }

    void editprofileRestaurantPage()
    {
        system("cls");
        // Input name and address
        string name;
        string address;
        cout << "==========================================================" << endl;
        cout << "Edit Profile Restaurant" << endl;
        cout << "==========================================================" << endl;
        showIdentity();
        cout << "Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Address: ";
        getline(cin, address);
        setIdentity(name, address);
    }

    void mainPage()
    {
        int pilihan;
        do
        {
            system("cls");
            cout << "==========================================================" << endl;
            cout << "Welcome to Restaurant" << endl;
            cout << "==========================================================" << endl;
            showIdentity();
            cout << "Income : Rp. " << getIncome() << endl;
            cout << "Order Count : " << Bill::countBill << endl;
            cout << "0. Profile Restaurant" << endl;
            cout << "1. Menu" << endl;
            cout << "2. Table" << endl;
            cout << "3. Order" << endl;
            cout << "4. Exit" << endl;
            cout << "==========================================================" << endl;
            cout << "Pilihan : ";
            cin >> pilihan;
            switch (pilihan)
            {
            case 0:
                editprofileRestaurantPage();
                break;
            case 1:
                menuPage();
                break;
            case 2:
                tablePage();
                break;
            case 3:
                orderPage();
                break;
            case 4:
                exitApp();
                break;
            default:
                cout << "Wrong input" << endl;
                system("pause");
                break;
            }
        } while (pilihan != 4);
    }

    void addMenuPage()
    {
        string name;
        int price;
        string sku;
        int pilihan;
        string description;
        system("cls");
        cout << "==========================================================" << endl;
        cout << "Add Menu" << endl;
        cout << "==========================================================" << endl;
        cin.ignore();
        cout << "Sku : ";
        getline(cin, sku);
        cout << "Name : ";
        getline(cin, name);
        cout << "Description : ";
        getline(cin, description);
        cout << "Price : ";
        cin >> price;
        addMenu(Menu(sku, name, description, price));
    }

    void removeMenuPage()
    {

        system("cls");
        string sku;
        cout << "==========================================================" << endl;
        cout << "Remove Menu" << endl;
        cout << "==========================================================" << endl;
        cin.ignore();
        cout << "Input Sku want to remove : ";
        getline(cin, sku);
        removeMenu(sku);
    }

    void editMenuPage()
    {
        system("cls");
        string name;
        int price;
        string sku;
        int pilihan;
        string description;
        cout << "==========================================================" << endl;
        cout << "Edit Menu" << endl;
        cout << "==========================================================" << endl;
        cin.ignore();
        cout << "Sku : ";
        getline(cin, sku);

        // check data
        if (!isExistMenu(sku))
        {
            cout << "Menu not found" << endl;
            system("pause");
            return;
        }

        Menu menu = getMenu(sku);
        cout << endl
             << "Last Data : " << endl;
        menu.showMenu();
        cout << endl
             << "New Data : " << endl;
        cout
            << "Name : ";
        getline(cin, name);
        cout << "Description : ";
        getline(cin, description);
        cout << "Price : ";
        cin >> price;
        editMenu(sku, Menu(sku, name, description, price));
    }

    void menuPage()
    {
        int pilihan;
        do
        {
            system("cls");
            cout << "==========================================================" << endl;
            cout << "Welcome to Restaurant" << endl;
            cout << "==========================================================" << endl;
            cout << "1. Add Menu" << endl;
            cout << "2. Remove Menu" << endl;
            cout << "3. Edit Menu" << endl;
            cout << "4. Show Menu" << endl;
            cout << "5. Back" << endl;
            cout << "==========================================================" << endl;
            cout << "Pilihan : ";
            cin >> pilihan;
            switch (pilihan)
            {
            case 1:
                addMenuPage();
                break;
            case 2:
                removeMenuPage();
                break;
            case 3:
                editMenuPage();
                break;
            case 4:
                system("cls");
                cout << "Menu in Our Restaurant" << endl;
                showMenu();
                system("pause");
                break;
            case 5:
                mainPage();
                break;
            default:
                cout << "Wrong input" << endl;
                system("pause");
                break;
            }
        } while (pilihan != 5);
    }

    void addTablePage()
    {
        system("cls");
        int number;
        int seats;
        cout << "==========================================================" << endl;
        cout << "Add Table" << endl;
        cout << "==========================================================" << endl;
        cin.ignore();
        cout << "Number : ";
        cin >> number;
        cout << "Seats : ";
        cin >> seats;
        addTable(Table(number, seats));
    }

    void removeTablePage()
    {
        system("cls");
        int number;
        cout << "==========================================================" << endl;
        cout << "Remove Table" << endl;
        cout << "==========================================================" << endl;

        cout << "Number : ";
        cin >> number;
        removeTable(number);
    }

    void tablePage()
    {
        int pilihan;
        do
        {
            system("cls");
            cout << "==========================================================" << endl;
            cout << "Welcome to Restaurant" << endl;
            cout << "==========================================================" << endl;
            cout << "1. Add Table" << endl;
            cout << "2. Remove Table" << endl;
            cout << "3. Show Available Table" << endl;
            cout << "4. Back" << endl;
            cout << "==========================================================" << endl;
            cout << "Pilihan : ";
            cin >> pilihan;
            switch (pilihan)
            {
            case 1:
                addTablePage();
                break;
            case 2:
                removeTablePage();
                break;
            case 3:
                system("cls");
                showAvailableTable();
                system("pause");
                break;
            case 4:
                mainPage();
                break;
            default:
                cout << "Wrong input" << endl;
                system("pause");
                break;
            }
        } while (pilihan != 4);
    }

    void addOrderPage()
    {
        // Question about customer ,table
        string customer;
        int table;
        int pilihan;
        do
        {
            system("cls");
            cout << "==========================================================" << endl;
            cout << "Add Order" << endl;
            cout << "==========================================================" << endl;
            cout << "1. Add Order" << endl;
            cout << "2. Back" << endl;
            cout << "==========================================================" << endl;
            cout << "Pilihan : ";
            cin >> pilihan;
            switch (pilihan)
            {
            case 1:
                cin.ignore();
                cout << "Customer : ";
                getline(cin, customer);
                cout << "Table : ";
                cin >> table;
                if (isAvailableTable(table))
                {
                    detailOrderPage(Bill(getTable(table), user, customer));
                }
                else
                {
                    cout << "Table is not available" << endl;
                    system("pause");
                }
                break;
            case 2:
                break;
            default:
                cout << "Wrong input" << endl;
                system("pause");
                break;
            }
        } while (pilihan != 2);
    }

    void addDetailBill(Bill *bill)
    {
        system("cls");
        // add detail bill from sku and quantity
        string sku;
        int quantity;
        cout << "==========================================================" << endl;
        cout << "Add Detail Bill" << endl;
        cout << "==========================================================" << endl;
        // Input sku and quantity
        cin.ignore();
        cout << "Input SKU Menu : ";
        getline(cin, sku);
        // Check sku menu if exist
        if (!isExistMenu(sku))
        {
            cout << "Sku not found" << endl;
            system("pause");
            return;
        }
        cout << "Input Quantity : ";
        cin >> quantity;
        bill->addMenu(getMenu(sku), quantity);
    }

    void removeDetailBill(Bill *bill)
    {
        system("cls");
        string sku;
        int quantity;
        cin.ignore();
        cout << "Input SKU Menu : ";
        getline(cin, sku);
        bill->removeMenu(sku);
    }

    void detailOrderPage(Bill bill)
    {
        // add detailbill, remove detaill bill, show menu, show cart, done
        int pilihan;
        do
        {
            system("cls");
            bill.shortInformation();
            cout << "==========================================================" << endl;
            cout << "Detail Order" << endl;
            cout << "==========================================================" << endl;
            cout << "1. Add Detail Bill" << endl;
            cout << "2. Remove Detail Bill" << endl;
            cout << "3. Show Menu" << endl;
            cout << "4. Show Cart" << endl;
            cout << "5. Done" << endl;
            cout << "==========================================================" << endl;
            cout << "Pilihan : ";
            cin >> pilihan;
            switch (pilihan)
            {
            case 1:
                addDetailBill(&bill);
                break;
            case 2:
                removeDetailBill(&bill);
                break;
            case 3:
                system("cls");
                cout << "Our Menu" << endl;
                showMenu();
                system("pause");
                break;
            case 4:
                system("cls");
                cout << "Your cart : " << endl;
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
                    pilihan = 0;
                }
                else
                {
                    addBill(bill);
                    system("cls");
                    cout << "==========================================================" << endl;
                    cout << "Success Order Saved" << endl;
                    cout << "==========================================================" << endl;
                    system("pause");
                }
                break;
            default:
                cout << "Wrong input" << endl;
                system("pause");
                break;
            }
        } while (pilihan != 5);
    }

    void serveOrderPage()
    {
        int pilihan;
        do
        {
            system("cls");
            cout << "==========================================================" << endl;
            cout << "Serve Order" << endl;
            cout << "==========================================================" << endl;
            cout << "1. Serve Order" << endl;
            cout << "2. Back" << endl;
            cout << "==========================================================" << endl;
            cout << "Pilihan : ";
            cin >> pilihan;
            switch (pilihan)
            {
            case 1:
            {
                string faktur;
                cout << "Please Input Faktur: ";
                cin >> faktur;
                if (isExistBill(faktur))
                {
                    Bill *bill = getBill(faktur);
                    bill->servingMenu();
                }
                else
                {
                    cout << "Bill not found" << endl;
                    system("pause");
                }
                break;
            }
            case 2:
                break;
            default:
                cout << "Wrong input" << endl;
                system("pause");
                break;
            }
        } while (pilihan != 2);
    }

    void payOrderPage()
    {
        int pilihan;
        do
        {
            system("cls");
            cout << "==========================================================" << endl;
            cout << "Pay Order" << endl;
            cout << "==========================================================" << endl;
            cout << "1. Pay Order" << endl;
            cout << "2. Back" << endl;
            cout << "==========================================================" << endl;
            cout << "Pilihan : ";
            cin >> pilihan;
            switch (pilihan)
            {
            case 1:
            {
                string faktur;
                cout << "Please Input Faktur: ";
                cin >> faktur;
                if (isExistBill(faktur))
                {
                    system("cls");
                    Bill *bill = getBill(faktur);
                    bill->shortInformation();
                    // Input payment
                    double payment;
                    cout << "Input Payment : ";
                    cin >> payment;
                    system("cls");
                    showIdentity();
                    bill->payBill(payment);
                }
                else
                {
                    cout << "Bill not found" << endl;
                    system("pause");
                }
                break;
            }
            case 2:
                break;
            default:
                cout << "Wrong input" << endl;
                system("pause");
                break;
            }
        } while (pilihan != 2);
    }

    void orderPage()
    {
        // Show order , add order, serve order, pay order
        int pilihan;
        do
        {
            system("cls");
            cout << "==========================================================" << endl;
            cout << "Welcome to Restaurant" << endl;
            cout << "==========================================================" << endl;
            cout << "1. Show Order" << endl;
            cout << "2. Add Order" << endl;
            cout << "3. Serve Order" << endl;
            cout << "4. Pay Order" << endl;
            cout << "5. Back" << endl;
            cout << "==========================================================" << endl;
            cout << "Pilihan : ";
            cin >> pilihan;
            switch (pilihan)
            {
            case 1:
                system("cls");
                cout << "==========================================================" << endl;
                cout << "List Order" << endl;
                cout << "==========================================================" << endl;
                showOrder();
                system("pause");
                break;
            case 2:
                addOrderPage();
                break;
            case 3:
                serveOrderPage();
                break;
            case 4:
                payOrderPage();
                break;
            case 5:
                mainPage();
                break;
            default:
                cout << "Wrong input" << endl;
                system("pause");
                break;
            }
        } while (pilihan != 5);
    }

    void exitApp()
    {
        system("cls");
        cout << "Thank you for using our application" << endl;
        system("pause");
        exit(0);
    }
};

int main(int argc, const char **argv)
{
    // Clear screen
    system("cls");
    View view;
    view.start();
    return 0;
}