// import
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

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
    string status;

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
        this->status = "Waiting";
        this->total = 0;
        this->pay = 0;
        this->change = 0;
        // Set faktur
        this->faktur = "";
        this->faktur += to_string(table->getTableNumber());
        this->faktur += ".";
        this->faktur += to_string(countBill);
    }

    Bill()
    {
        this->customer_name = "";
        this->table = nullptr;
        this->waiter = Waiter();
        this->isPayed = false;
        this->status = "Waiting";
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
        cout << "Status : " << status << endl;
        cout << "Total : " << total << endl;
    }

    void servingMenu()
    {
        if (status == "Waiting")
        {
            status = "Serving";
        }
        else
        {
            cout << "Bill is already serving" << endl;
            system("pause");
        }
    }

    void payBill(double pay)
    {
        system("cls");
        if (status == "Serving")
        {
            if (pay < total)
            {
                cout << "Payment is not enough" << endl;
            }
            else
            {
                this->pay = pay;
                this->change = pay - total;
                this->isPayed = true;
                this->status = "Payed";
                this->table->setOccupy();

                this->printReceipt();
            }
        }
        else
        {
            cout << "Bill is not serving" << endl;
        }
        system("pause");
    }

    void printReceipt()
    {

        cout << "==========================================================" << endl;
        cout << "Receipt" << endl;
        cout << "==========================================================" << endl;
        cout << "Table Number: " << table->getTableNumber() << endl;
        cout << "Customer Name: " << customer_name << endl;
        cout << "Faktur: " << faktur << endl;
        cout << "==========================================================" << endl;
        cout << "Menu" << endl;
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

public:
    Restaurant()
    {
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
            cout << listMenu[i].getSku() << ". " << listMenu[i].getName() << endl
                 << listMenu[i].getDescription() << endl
                 << listMenu[i].getPrice() << endl;
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

    void addBill(Bill bill)
    {
        listBill.push_back(bill);
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
        cin.ignore();
        cout << "==========================================================" << endl;
        cout << "Main Menu" << endl;
        cout << "==========================================================" << endl;
        cout << "1. Order" << endl;
        cout << "2. Show All Order" << endl;
        cout << "3. Serving Menu" << endl;
        cout << "4. Pay Bill" << endl;
        cout << "5. List Available Table" << endl;
        cout << "6. Exit" << endl;
        cout << "==========================================================" << endl;
        cout << "Please choose: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            // Make Order
            system("cls");
            cout << "==========================================================" << endl;
            cout << "Make New Order" << endl;
            cout << "==========================================================" << endl;

            bool tableCheck = false;
            int tableNumber;
            while (!tableCheck)
            {
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
            cin >> customer;
            Bill bill = Bill(restaurant.getTable(tableNumber), user, customer);
            bool isOrder = true;
            while (isOrder)
            {
                system("cls");
                bill.shortInformation();
                cout << "==========================================================" << endl;
                cout << "Choose :" << endl;
                cout << "1. Add Menu" << endl;
                cout << "2. Remove Menu" << endl;
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
        case 2:
            system("cls");
            cout << "==========================================================" << endl;
            cout << "List All Order" << endl;
            cout << "==========================================================" << endl;
            restaurant.showOrder();
            system("pause");
            break;
        case 3:
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
        case 4:
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

                bill->payBill(payment);
            }
            else
            {
                cout << "Bill not found" << endl;
                system("pause");
            }
            break;
        }
        case 5:
            system("cls");
            restaurant.showAvailableTable();
            system("pause");
            break;
        case 6:
            cout << "Good Bye !" << endl;
            exitApp = true;
            break;
        default:
            break;
        }
    }

    return 0;
}