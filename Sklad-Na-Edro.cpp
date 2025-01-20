#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

// ========================== Клас: Стоки ==========================
class Goods {
private:
    string productName;
    double unitPrice;
    int quantity;
    double amount;

public:
    Goods(string name, double price, int qty)
        : productName(name), unitPrice(price), quantity(qty) {
        calculateAmount();
    }

    void calculateAmount() {
        amount = unitPrice * quantity;
    }

    void printInfo() const {
        cout << "Product: " << productName
            << ", Unit Price: " << unitPrice
            << ", Quantity: " << quantity
            << ", Amount: " << amount << endl;
    }

    string getName() const { return productName; }
    double getAmount() const { return amount; }
    int getQuantity() const { return quantity; }
};

// ========================== Клас: Person ==========================
class Person {
protected:
    string name;
    string surname;
    string phoneNumber;
    string email;

public:
    Person(string n, string s, string phone, string mail)
        : name(n), surname(s), phoneNumber(phone), email(mail) {}

    void printInfo() const {
        cout << "Name: " << name << " " << surname
            << ", Phone: " << phoneNumber
            << ", Email: " << email << endl;
    }

    string getName() const { return name; }
};

// ========================== Клас: Клиент (Наследява Person) ==========================
class Customer : public Person {
private:
    string companyName;
    string deliveryAddress;
    vector<Goods> goodsList;
    double totalPayment;

public:
    Customer(string n, string s, string phone, string mail, string company, string address)
        : Person(n, s, phone, mail), companyName(company), deliveryAddress(address), totalPayment(0) {}

    void addGoods(const Goods& goods) {
        goodsList.push_back(goods);
        totalPayment += goods.getAmount();
    }

    void printInfo() const {
        Person::printInfo();
        cout << "Company: " << companyName
            << ", Delivery Address: " << deliveryAddress
            << ", Total Payment: " << totalPayment << endl;

        cout << "Goods requested: " << endl;
        for (const auto& goods : goodsList) {
            goods.printInfo();
        }
    }

    double getTotalPayment() const { return totalPayment; }
};

// ========================== Клас: Представител ==========================
class SalesRepresentative {
private:
    vector<Customer*> customers;

public:
    void addCustomer(Customer* customer) {
        customers.push_back(customer);
    }

    void printCustomersInfo() const {
        for (const auto& customer : customers) {
            customer->printInfo();
        }
    }

    double calculateDailyTurnover() const {
        double turnover = 0;
        for (const auto& customer : customers) {
            turnover += customer->getTotalPayment();
        }
        return turnover;
    }
};

// ========================== Клас: Склад ==========================
class Warehouse {
private:
    string name;
    vector<SalesRepresentative> representatives;
    vector<Customer> customers;
    unordered_map<string, Goods> goods;

public:
    Warehouse(string n) : name(n) {}

    void addCustomer(const Customer& customer) {
        customers.push_back(customer);
    }

    void addGoods(const Goods& good) {
        goods[good.getName()] = good;
    }

    Goods* searchGoods(const string& productName) {
        if (goods.find(productName) != goods.end()) {
            return &goods[productName];
        }
        return nullptr;
    }

    Customer* findCustomerByName(const string& customerName) {
        for (auto& customer : customers) {
            if (customer.getName() == customerName) {
                return &customer;
            }
        }
        return nullptr;
    }

    void printAllCustomersInfo() const {
        for (const auto& customer : customers) {
            customer.printInfo();
        }
    }

    double calculateTurnover() const {
        double totalTurnover = 0;
        for (const auto& customer : customers) {
            totalTurnover += customer.getTotalPayment();
        }
        return totalTurnover;
    }
};

// ========================== Главна Програма ==========================
int main() {
    Warehouse warehouse("Main Warehouse");

    int choice;
    while (true) {
        cout << "\nMenu:\n"
            << "1. Add Goods\n"
            << "2. Add Customer\n"
            << "3. Implement a Request\n"
            << "4. Print Information\n"
            << "5. Exit\n"
            << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string productName;
            double unitPrice;
            int quantity;

            cout << "Enter product name: ";
            cin >> productName;
            cout << "Enter unit price: ";
            cin >> unitPrice;
            cout << "Enter quantity: ";
            cin >> quantity;

            Goods goods(productName, unitPrice, quantity);
            warehouse.addGoods(goods);
            cout << "Goods added successfully!" << endl;
            break;
        }

        case 2: {
            string name, surname, phone, email, company, address;

            cout << "Enter customer name: ";
            cin >> name;
            cout << "Enter customer surname: ";
            cin >> surname;
            cout << "Enter phone: ";
            cin >> phone;
            cout << "Enter email: ";
            cin >> email;
            cout << "Enter company name: ";
            cin >> company;
            cout << "Enter delivery address: ";
            cin >> address;

            Customer customer(name, surname, phone, email, company, address);
            warehouse.addCustomer(customer);
            cout << "Customer added successfully!" << endl;
            break;
        }

        case 3: {
            string customerName, productName;
            int quantity;

            cout << "Enter customer name: ";
            cin >> customerName;
            cout << "Enter product name: ";
            cin >> productName;
            cout << "Enter quantity: ";
            cin >> quantity;

            Goods* goods = warehouse.searchGoods(productName);
            if (goods) {
                Goods requestedGoods(productName, goods->getAmount() / goods->getQuantity(), quantity);

                Customer* customer = warehouse.findCustomerByName(customerName);
                if (customer) {
                    customer->addGoods(requestedGoods);
                    cout << "Request successfully processed!" << endl;
                }
                else {
                    cout << "Customer not found!" << endl;
                }
            }
            else {
                cout << "Product not found!" << endl;
            }
            break;
        }


        case 4: {
            warehouse.printAllCustomersInfo();
            break;
        }

        case 5:
            cout << "Exiting program." << endl;
            return 0;

        default:
            cout << "Invalid choice! Try again." << endl;
        }
    }
    return 0;
}
