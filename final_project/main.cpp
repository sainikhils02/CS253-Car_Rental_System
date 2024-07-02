#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int findEmployeeId(int& userid,string& password);
int findCustomerId(int& userid,string& password);
int findManagerId(int& userid,string& password);
int findAverageRating(const string& filename);
bool check_car_id(int car_id);
int getCarAvailability(int carId);
bool editCarAvailability(int carId, int newCarAvailability, int newReturnDate);
int getReturnDate(int carId);
int find_car_price(int car_id);
string getCarName(int carId);
bool findManagerInfo(int idTosearch, string& name, string& password);
bool fillEmployeeInfo(int idToSearch,
                      string& foundName, string& foundPassword,
                      int& foundFineDue, int& foundEmployeeRecord,
                      int& foundNumOfCars, vector<int>& foundCars);
bool fillCustomerInfo(int idToSearch,
                      string& foundName, string& foundPassword,
                      int& foundFineDue, int& foundCustomerRecord,
                      int& foundNumOfCars, vector<int>& foundCars);
class user{
    protected:
    string name;
    int id;
    string password;
    public:
    void available_cars(){
        ifstream file("cars.txt");
        if (!file.is_open()) {
            cout << "Error opening file: " << "cars.txt" << endl;
            return;
        }
        string line;
        int car_id, car_cost, car_availability;
        string car_name;
    
        while (getline(file, line)) {
            istringstream iss(line);

            if (iss >> car_id >> car_name >> car_cost >> car_availability) {
                 // Check if the car is available (car_availability == 1)
                if (car_availability == 1) {
                 // Print details of the available car
                    cout << "Car ID: " << car_id << ", Name: " << car_name << ", Cost: " << car_cost << endl;
                }
            }
        }

        file.close();
    }
    
};
class customer: public user{
    protected:
    
    int customer_record;
    int num_of_cars;
    vector<int> cars;
    public:
    customer(int id, string name, string password, int fine_due,int customer_rec, int num_of_cars, vector<int>cars){
        this->id=id;
        this->name=name;
        this->password=password;
        this->fine_due=fine_due;
        this->customer_record=customer_rec;
        this->num_of_cars=num_of_cars;
        this->cars=cars;
        //  cout<<"In customer";
        // for(int i=0; i<this->num_of_cars; i++){
        //     this->cars[i]=cars[i];
        // }
    }
    
    public:
    int fine_due;
    bool rent_request(int car_id, int exp_return_date, int cost, int payment){
            if(!check_car_id(car_id)){
                cout<<"Invalid Car Number"<<endl;
                return false;
            }
            else if(customer_record<3){
                cout<<"Car could not be rented due to low record"<<endl;
                return false;
            }
            else if(cost>payment){
                cout<<"Car could not be rented due to Insufficient payment"<<endl;
                return false;
            }
            else if(getCarAvailability(car_id)!=1){
                return false;
                cout<<"Car is not available"<<endl;
            }
            else{
                editCarAvailability(car_id, 0, exp_return_date);
                this->fine_due=cost-payment;
                return true;
            }
    }
    bool return_request(int car_id, int damage, int return_date){
        if(!check_car_id(car_id)){
            cout<<"Invalid car Id"<<endl;
            return false;
        }
        if(damage)this->customer_record=this->customer_record-1;
        int exp_return_date=getReturnDate(car_id);
        if(exp_return_date>=return_date){
            editCarAvailability(car_id, 1, 1);return true;
        }
        else{
            this->fine_due=this->fine_due+((return_date-exp_return_date)*(find_car_price(car_id)+500));
            editCarAvailability(car_id, 1, 1);return true;
        }
    }
    void rented_cars(){
        for(int i=0; i<cars.size(); i++){
            cout<<"Car Id:"<<cars[i]<<" "<<"Car Name:"<<getCarName(cars[i])<<" "<<"Car Return Date:"<<getReturnDate(cars[i])<<endl;
        }
    }
    friend class manager;
};
class employee: public user{
    protected:
    
    int employee_record;
    int num_of_cars;
    vector<int> cars;
    public:
    employee(int id, string name, string password, int fine_due, int employee_rec, int num_of_cars, vector<int>cars){
        this->id=id;
        this->name=name;
        this->password=password;
        this->fine_due=fine_due;
        this->employee_record=employee_rec;
        this->num_of_cars=num_of_cars;
        this->cars=cars;
    }
    
    public:
    int fine_due;
    bool rent_request(int car_id, int exp_return_date, int cost, int payment){
            if(!check_car_id(car_id)){
                cout<<"Invalid Car Number"<<endl;
                return false;
            }
            else if(employee_record<3){
                cout<<"Car could not be rented due to low record"<<endl;
                return false;
            }
            else if(cost>payment){
                cout<<"Car could not be rented due to Insufficient payment"<<endl;
                return false;
            }
            else if(getCarAvailability(car_id)!=1){
                return false;
                cout<<"Car is not available"<<endl;
            }
            else{
                editCarAvailability(car_id, 0, exp_return_date);
                this->fine_due=cost-payment;
                return true;
            }
    }
    bool return_request(int car_id, int damage, int return_date){
        if(!check_car_id(car_id)){
            cout<<"Invalid car Id"<<endl;
            return false;
        }
        if(damage)this->employee_record=this->employee_record-1;
        int exp_return_date=getReturnDate(car_id);
        if(exp_return_date>=return_date){
            editCarAvailability(car_id, 1, 1);return true;
        }
        else{
            this->fine_due=this->fine_due+((return_date-exp_return_date)*(find_car_price(car_id)+500)*0.85);
            editCarAvailability(car_id, 1, 1);return true;
        }
    }
    void rented_cars(){
        for(int i=0; i<cars.size(); i++){
            cout<<"Car Id:"<<cars[i]<<" "<<"Car Name:"<<getCarName(cars[i])<<" "<<"Car Return Date:"<<getReturnDate(cars[i])<<endl;
        }
    }
    friend class manager;
};
class manager: public user{
    public:
    manager(int id, string name, string password){
        this->id=id;
        this->name=name;
        this->password=password;
        // cout<<"In manager    ";
    }
    public:
    void all_cars(){
         ifstream file("cars.txt");

        if (!file.is_open()) {
            cerr << "Error opening file: " << "cars.txt" << endl;
            return;
        }

        int carId, carRating, carCost, carAvailability, returnDate;
        string carName;

        

        while (file >> carId >> carName >> carCost >> carAvailability >> returnDate) {
            // Assuming the file format is: car_id car_name car_rating car_cost car_availability return_date
            cout << "carId: " << carId << "\t" << "Name: " << carName << "\tCost: " << carCost << "\tAvailability: " << carAvailability << "\tReturn Date: " << returnDate << endl;
        }

        file.close();
    }
    bool add_customer(int newId, const string& newName, const string& newPassword, int newRating) {
        fstream file("customers.txt", ios::in | ios::out | ios::app);

        if (!file.is_open()) {
            cerr << "Error opening file: " << "customers.txt" << endl;
            return false;
        }

        // Set default values for num_of_cars_rented and car_ids
        int numCarsRented = 0;

        // Write the new customer information to the file
        file << newId << " " << newName << " " << newPassword << " 0 " << newRating << " " << numCarsRented << endl;

        file.close();
        return true;
    }
    bool add_employee(int newId, const string& newName, const string& newPassword, int newRating) {
        fstream file("employees.txt", ios::in | ios::out | ios::app);

        if (!file.is_open()) {
            cerr << "Error opening file: " << "employees.txt" << endl;
            return false;
        }

        // Set default values for num_of_cars_rented and car_ids
        int numCarsRented = 0;

        // Write the new customer information to the file
        file << newId << " " << newName << " " << newPassword << " 0 " << newRating << " " << numCarsRented << endl;

        file.close();
        return true;
    }
    bool delete_customer(int customerId) {
        ifstream inFile("customers.txt");
        ofstream tempFile("temp.txt");

        if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Error opening files." << endl;
        return false;
        }

            int currentCustomerId;
        string line;

        while (getline(inFile, line)) {
        istringstream iss(line);

        // Assuming the file format is: employee_id employee_name employee_userid employee_password employee_fine_due employee_rating num_of_cars_rented [car_ids]
        if (iss >> currentCustomerId) {
            // Check if the current line matches the given employee_id
            if (currentCustomerId != customerId) {
                tempFile << line << endl;  // Write the line to the temporary file
            }
        }
        }

        inFile.close();
        tempFile.close();

        // Remove the original file
        remove("customers.txt");

            // Rename the temporary file to the original file
        if (rename("temp.txt", "customers.txt") != 0) {
        cerr << "Error renaming file." << endl;
        return false;
        }

        cout << "Customer with ID " << customerId << " deleted successfully." << endl;

        return true;
    }
    bool delete_employee(int employeeId) {
        ifstream inFile("employees.txt");
        ofstream tempFile("temp.txt");

        if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Error opening files." << endl;
        return false;
        }

            int currentEmployeeId;
        string line;

        while (getline(inFile, line)) {
        istringstream iss(line);

        // Assuming the file format is: employee_id employee_name employee_userid employee_password employee_fine_due employee_rating num_of_cars_rented [car_ids]
        if (iss >> currentEmployeeId) {
            // Check if the current line matches the given employee_id
            if (currentEmployeeId != employeeId) {
                tempFile << line << endl;  // Write the line to the temporary file
            }
        }
        }

        inFile.close();
        tempFile.close();

        // Remove the original file
        remove("employees.txt");

            // Rename the temporary file to the original file
        if (rename("temp.txt", "employees.txt") != 0) {
        cerr << "Error renaming file." << endl;
        return false;
        }

        cout << "Employee with ID " << employeeId << " deleted successfully." << endl;

        return true;
    }
    bool update_customer_fine(int customerId, int newFineDue) {
        ifstream inFile("customers.txt");
        ofstream tempFile("temp.txt");

        if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Error opening files." << endl;
        return false;
        }

        int currentCustomerId, fineDue;
        string line, customerName, customerPassword, customerRating;
        int numCarsRented;
        vector<int> carIds;

        while (getline(inFile, line)) {
        istringstream iss(line);

        // Assuming the file format is: employee_id employee_name employee_password employee_fine_due employee_rating num_of_cars_rented [car_ids]
        if (iss >> currentCustomerId >> customerName >> customerPassword >> fineDue >> customerRating >> numCarsRented) {
            // Check if the current line matches the given employee_id
            if (currentCustomerId == customerId) {
                // Update employee fine_due in memory
                fineDue = newFineDue;
            }
            tempFile << currentCustomerId << " " << customerName << " " << customerPassword << " "
                     << fineDue << " " << customerRating << " " << numCarsRented;

            // Read car IDs
            carIds.clear();
            for (int i = 0; i < numCarsRented; ++i) {
                int carId;
                if (iss >> carId) {
                    carIds.push_back(carId);
                    tempFile << " " << carId;
                }
            }
            tempFile << endl;
        }
        }

            inFile.close();
        tempFile.close();

        // Remove the original file
        remove("customers.txt");

        // Rename the temporary file to the original file
        if (rename("temp.txt", "customers.txt") != 0) {
        cerr << "Error renaming file." << endl;
        return false;
        }

        cout << "Customer fine_due for ID " << customerId << " updated successfully." << endl;

        return true;
    }    
    bool update_customer_record(int customerId, int newRecord) {
        ifstream inFile("customers.txt");
        ofstream tempFile("temp.txt");

        if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Error opening files." << endl;
        return false;
        }

        int currentCustomerId, fineDue;
        string line, customerName, customerPassword, customerRating;
        int numCarsRented;
        vector<int> carIds;

        while (getline(inFile, line)) {
        istringstream iss(line);

        // Assuming the file format is: employee_id employee_name employee_password employee_fine_due employee_rating num_of_cars_rented [car_ids]
        if (iss >> currentCustomerId >> customerName >> customerPassword >> fineDue >> customerRating >> numCarsRented) {
            // Check if the current line matches the given employee_id
            if (currentCustomerId == customerId) {
                // Update employee fine_due in memory
                customerRating = to_string(newRecord);
            }
            tempFile << currentCustomerId << " " << customerName << " " << customerPassword << " "
                     << fineDue << " " << customerRating << " " << numCarsRented;

            // Read and write car IDs
            carIds.clear();
            for (int i = 0; i < numCarsRented; ++i) {
                int carId;
                if (iss >> carId) {
                    carIds.push_back(carId);
                    tempFile << " " << carId;
                }
            }
            tempFile << endl;
        }
        }

        inFile.close();
        tempFile.close();

        // Remove the original file
        remove("customers.txt");

        // Rename the temporary file to the original file
        if (rename("temp.txt", "customers.txt") != 0) {
        cerr << "Error renaming file." << endl;
        return false;
        }

        cout << "Customer Record for ID " << customerId << " updated successfully." << endl;

        return true;
    }
    bool update_employee_fine(int employeeId, int newFineDue) {
        ifstream inFile("employees.txt");
        ofstream tempFile("temp.txt");

        if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Error opening files." << endl;
        return false;
        }

        int currentEmployeeId, fineDue;
        string line, employeeName, employeePassword, employeeRating;
        int numCarsRented;
        vector<int> carIds;

        while (getline(inFile, line)) {
        istringstream iss(line);

        // Assuming the file format is: employee_id employee_name employee_password employee_fine_due employee_rating num_of_cars_rented [car_ids]
        if (iss >> currentEmployeeId >> employeeName >> employeePassword >> fineDue >> employeeRating >> numCarsRented) {
            // Check if the current line matches the given employee_id
            if (currentEmployeeId == employeeId) {
                // Update employee fine_due in memory
                fineDue = newFineDue;
            }
            tempFile << currentEmployeeId << " " << employeeName << " " << employeePassword << " "
                     << fineDue << " " << employeeRating << " " << numCarsRented;

            // Read car IDs
            carIds.clear();
            for (int i = 0; i < numCarsRented; ++i) {
                int carId;
                if (iss >> carId) {
                    carIds.push_back(carId);
                    tempFile << " " << carId;
                }
            }
            tempFile << endl;
        }
        }

            inFile.close();
        tempFile.close();

        // Remove the original file
        remove("employees.txt");

        // Rename the temporary file to the original file
        if (rename("temp.txt", "employees.txt") != 0) {
        cerr << "Error renaming file." << endl;
        return false;
        }

        cout << "Employee fine_due for ID " << employeeId << " updated successfully." << endl;

        return true;
    }   
    bool update_employee_record(int employeeId, int newRecord) {
        ifstream inFile("employees.txt");
        ofstream tempFile("temp.txt");

        if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Error opening files." << endl;
        return false;
        }

        int currentEmployeeId, fineDue;
        string line, employeeName, employeePassword, employeeRating;
        int numCarsRented;
        vector<int> carIds;

        while (getline(inFile, line)) {
        istringstream iss(line);

        // Assuming the file format is: employee_id employee_name employee_password employee_fine_due employee_rating num_of_cars_rented [car_ids]
        if (iss >> currentEmployeeId >> employeeName >> employeePassword >> fineDue >> employeeRating >> numCarsRented) {
            // Check if the current line matches the given employee_id
            if (currentEmployeeId == employeeId) {
                // Update employee fine_due in memory
                employeeRating = to_string(newRecord);
            }
            tempFile << currentEmployeeId << " " << employeeName << " " << employeePassword << " "
                     << fineDue << " " << employeeRating << " " << numCarsRented;

            // Read and write car IDs
            carIds.clear();
            for (int i = 0; i < numCarsRented; ++i) {
                int carId;
                if (iss >> carId) {
                    carIds.push_back(carId);
                    tempFile << " " << carId;
                }
            }
            tempFile << endl;
        }
        }

        inFile.close();
        tempFile.close();

        // Remove the original file
        remove("employees.txt");

        // Rename the temporary file to the original file
        if (rename("temp.txt", "employees.txt") != 0) {
        cerr << "Error renaming file." << endl;
        return false;
        }

        cout << "Employee Record for ID " << employeeId << " updated successfully." << endl;

        return true;
    }
    bool add_car(int carId, const string& carName, int carCost) {
    // Open the file in append mode
    fstream file("cars.txt", ios::in | ios::out | ios::app);

    if (!file.is_open()) {
        cerr << "Error opening file: " << "cars.txt" << endl;
        return false;
    }

    // Set default values for car_availability and return_date
    int carAvailability = 1;
    int returnDate = 1;

    // Move to the end of the file
    file.seekp(0, ios::end);

    // Write the new car information to the file
    file << carId << " " << carName << " " << carCost << " " << carAvailability << " " << returnDate << endl;

    // Close the file
    file.close();

    return true;
    }
    // bool delete_car(int carId) {
    //     fstream file("cars.txt", ios::in | ios::out);

    //     if (!file.is_open()) {
    //         cerr << "Error opening file: " << "cars.txt" << endl;
    //         return false;
    //     }

    //     streampos lastPos = file.tellg();  // To remember the position of the last line read

    //     int currentCarId;
    //     string line;

    //     while (getline(file, line)) {
    //         istringstream iss(line);

    //         // Assuming the file format is: car_id car_name car_cost car_availability return_date
    //         if (iss >> currentCarId) {
    //             if (currentCarId != carId) {
    //                 // Move back to the beginning of the line and overwrite it
    //                 file.seekp(lastPos);
    //                 file << line << endl;
    //             }
    //         }

    //         lastPos = file.tellg();  // Remember the position before reading the next line
    //     }

    //     file.close();
    //     // Truncate the file to remove any remaining content after the last line
    //     file.open("cars.txt", ios::out | ios::trunc);
    //     file.close();
    //         return true;
    // }
    bool delete_car(int carId) {
    ifstream inFile("cars.txt");
    ofstream outFile("temp.txt");

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error opening file." << endl;
        return false;
    }

    int currentCarId;
    string line;

    while (getline(inFile, line)) {
        istringstream iss(line);

        if (iss >> currentCarId) {
            if (currentCarId != carId) {
                outFile << line << endl;
            }
        }
    }

    inFile.close();
    outFile.close();

    // Remove the original file
    remove("cars.txt");

    // Rename the temporary file to the original file
    if (rename("temp.txt", "cars.txt") != 0) {
        cerr << "Error renaming file." << endl;
        return false;
    }

    return true;
    }
    bool update_car_availability(int carId) {
        ifstream inFile("cars.txt");
        ofstream tempFile("temp.txt");

        if (!inFile.is_open() || !tempFile.is_open()) {
            cerr << "Error opening files." << endl;
            return false;
        }

        int currentCarId, carCost, carAvailability, returnDate;
        string carName;

        while (inFile >> currentCarId >> ws >> carName >> carCost >> carAvailability >> returnDate) {
            if (currentCarId == carId) {
                carAvailability=1-carAvailability;
            }
            tempFile << currentCarId << " " << carName << " " << setw(5) << carCost << " " << carAvailability << " " << returnDate << endl;
        }

        inFile.close();
        tempFile.close();

        // Remove the original file
            remove("cars.txt");

        // Rename the temporary file to the original file
        if (rename("temp.txt", "cars.txt") != 0) {
            cerr << "Error renaming file." << endl;
            return false;
        }

        cout << "Car cost for ID " << carId << " updated successfully." << endl;

        return true;
    }
    // void update_car_rating(){

    // }
    bool update_car_cost(int carId, int newCarCost) {
        ifstream inFile("cars.txt");
        ofstream tempFile("temp.txt");

        if (!inFile.is_open() || !tempFile.is_open()) {
            cerr << "Error opening files." << endl;
            return false;
        }

        int currentCarId, carCost, carAvailability, returnDate;
        string carName;

        while (inFile >> currentCarId >> ws >> carName >> carCost >> carAvailability >> returnDate) {
            if (currentCarId == carId) {
                carCost = newCarCost;
            }
            tempFile << currentCarId << " " << carName << " " << setw(5) << carCost << " " << carAvailability << " " << returnDate << endl;
        }

        inFile.close();
        tempFile.close();

        // Remove the original file
            remove("cars.txt");

        // Rename the temporary file to the original file
        if (rename("temp.txt", "cars.txt") != 0) {
            cerr << "Error renaming file." << endl;
            return false;
        }

        cout << "Car cost for ID " << carId << " updated successfully." << endl;

        return true;
    }
};
int findEmployeeId(int& userid,string& password) {
    ifstream file("employees.txt");

    if (!file.is_open()) {
        cout << "Error opening file: " << "employees.txt" << endl;
        return 0;
    }

    int id, fine_due, employee_record, num_of_cars;
    string name, line, file_password;
    vector<int> ids_of_cars_rented;

    while (getline(file, line)) {
        istringstream iss(line);

        if (iss >> id >> name >> file_password
            >> fine_due >> employee_record >> num_of_cars) {

            // Read the IDs of rented cars
            ids_of_cars_rented.clear();  // Clear the vector for each employee
            int car_id;
            for (int i = 0; i < num_of_cars; ++i) {
                if (iss >> car_id) {
                    ids_of_cars_rented.push_back(car_id);
                }
            }

            // Check if userid and password match
            if (id == userid && file_password == password) {
                file.close();
                return id; // Return the id of the matched employee
            }
        }
    }

    file.close();
    return 0; // Return 0 if not matched
}
int findCustomerId(int& userid,string& password) {
    ifstream file("customers.txt");

    if (!file.is_open()) {
        cout << "Error opening file: " << "customers.txt" << endl;
        return 0;
    }

    int id, fine_due, customer_record, num_of_cars;
    string name, line, file_password;
    vector<int> ids_of_cars_rented;

    while (getline(file, line)) {
        istringstream iss(line);

        if (iss >> id >> name >> file_password
            >> fine_due >> customer_record >> num_of_cars) {

            // Read the IDs of rented cars
            ids_of_cars_rented.clear();  // Clear the vector for each employee
            int car_id;
            for (int i = 0; i < num_of_cars; ++i) {
                if (iss >> car_id) {
                    ids_of_cars_rented.push_back(car_id);
                }
            }

            // Check if userid and password match
            if (id == userid && file_password == password) {
                file.close();
                return id; // Return the id of the matched employee
            }
        }
    }

    file.close();
    return 0; // Return 0 if not matched
}
int findManagerId(int& userid,string& password){
    ifstream file("managers.txt");

    if (!file.is_open()) {
        cout << "Error opening file: " << "managers.txt" << endl;
        return 0;
    }
    int id;
    string name, file_password;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);

        if (iss >> id >> name >> file_password) {

            // Read the IDs of rented cars
            // Check if userid and password match
            if (id == userid && file_password == password) {
                file.close();
                return id; // Return the id of the matched manager
            }
        }
    }
}
int findAverageRating(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return 0;
    }

    int totalCustomers = 0;
    int totalRating = 0;

    int currentCustomerId, fineDue, rating, numCarsRented;
    string line, customerName, customerPassword;

    while (getline(file, line)) {
        istringstream iss(line);

        // Assuming the file format is: customer_id customer_name customer_password customer_fine_due customer_rating num_of_cars_rented [car_ids]
        if (iss >> currentCustomerId >> customerName >> customerPassword >> fineDue >> rating >> numCarsRented) {
            totalCustomers++;
            totalRating += rating;
        }
    }

    file.close();

    if (totalCustomers == 0) {
        cerr << "No customers found in the file." << endl;
        return 0;
    }

    int averageRating = totalRating / totalCustomers;
    return averageRating;
}
bool fillEmployeeInfo(int idToSearch,string& foundName, string& foundPassword,int& foundFineDue, int& foundEmployeeRecord,int& foundNumOfCars, vector<int>& foundCars) {
    ifstream file("Employees.txt");

    if (!file.is_open()) {
        cout << "Error opening file: " << "Employees.txt" << endl;
        return false;
    }

    string line;
    foundCars.clear(); // Clear the vector before filling

    while (getline(file, line)) {
        istringstream iss(line);
        int id, fine_due, employee_record, num_of_cars;
        string name, password;
        vector<int> cars;
        if (iss >> id >> name >> password >> fine_due >> employee_record >> num_of_cars) {
            // Read the IDs of rented cars
            int car_id;
            for (int i = 0; i < num_of_cars; ++i) {
                if (iss >> car_id) {
                    cars.push_back(car_id);
                }
            }
            // Check if the ID matches
            if (id == idToSearch) {
                // Fill the individual variables
                foundName = name;
                foundPassword = password;
                foundFineDue = fine_due;
                foundEmployeeRecord = employee_record;
                foundNumOfCars = num_of_cars;
                foundCars = cars;

                file.close();
                return true; // Employee found and information filled
            }
        }
    }
    file.close();
    return false; // Employee not found
}
bool fillCustomerInfo(int idToSearch, string& foundName, string& foundPassword,int& foundFineDue, int& foundCustomerRecord, int& foundNumOfCars, vector<int>& foundCars) {
    ifstream file("customers.txt");

    if (!file.is_open()) {
        cout << "Error opening file: " << "customers.txt" << endl;
        return false;
    }

    string line;
    foundCars.clear(); // Clear the vector before filling

    while (getline(file, line)) {
        istringstream iss(line);

        int id, fine_due, customer_record, num_of_cars;
        string name, password;
        vector<int> cars;

        if (iss >> id >> name >> password >> fine_due >> customer_record >> num_of_cars) {
            // Read the IDs of rented cars
            int car_id;
            for (int i = 0; i < num_of_cars; ++i) {
                if (iss >> car_id) {
                    cars.push_back(car_id);
                }
            }
            // Check if the ID matches
            if (id == idToSearch) {
                // Fill the individual variables
                foundName = name;
                foundPassword = password;
                foundFineDue = fine_due;
                foundCustomerRecord = customer_record;
                foundNumOfCars = num_of_cars;
                foundCars = cars;
                file.close();
                return true; // Employee found and information filled
            }
        }
    }
    file.close();
    return false; // Employee not found
}
bool findManagerInfo(int idTosearch, string& name, string& password){
    ifstream file("managers.txt");

    if (!file.is_open()) {
        cout << "Error opening file: " << "managers.txt" << endl;
        return false;
    }
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int foundid;
        string foundname, foundpassword;
        if (iss >> foundid >> foundname >> foundpassword) {
            // Read the IDs of rented cars
            // Check if the ID matches
            if (foundid == idTosearch) {
                // Fill the individual variables
                name = foundname;
                password = foundpassword;
                file.close();
                return true; // Employee found and information filled
            }
        }
    }
    file.close();
    return false;
}

int find_car_price(int car_id){
    ifstream file("cars.txt");

    if (!file.is_open()) {
        cerr << "Error opening file: " << "cars.txt" << endl;
        return -1;  // Return -1 to indicate an error
    }

    int currentCarId, carPrice;
    string line, carName;

    while (getline(file, line)) {
        istringstream iss(line);

        // Assuming the file format is: car_id car_name car_price ...
        if (iss >> currentCarId >> carName >> carPrice) {
            // Check if the current line matches the given car_id
            if (currentCarId == car_id) {
                file.close();
                return carPrice;  // Return the car price if found
            }
        }
    }

    file.close();
    return -1;
}
int getCarAvailability(int carId) {
    ifstream file("cars.txt");

    if (!file.is_open()) {
        cerr << "Error opening file: " << "cars.txt" << endl;
        return -1;  // Return -1 to indicate an error
    }

    int currentCarId, carAvailability;
    string line, carName;
    //int carRating;
    int carCost;

    while (getline(file, line)) {
        istringstream iss(line);

        // Assuming the file format is: car_id car_name car_rating car_cost car_availability
        if (iss >> currentCarId >> carName >> carCost >> carAvailability) {
            // Check if the current line matches the given car_id
            if (currentCarId == carId) {
                file.close();
                return carAvailability;  // Return the car availability if found
            }
        }
    }

    file.close();
    return -1;  // Return -1 if car_id not found
}
bool editCarAvailability(int carId, int newCarAvailability, int newReturnDate) {
    ifstream inputFile("cars.txt");
    ofstream tempFile("temp_cars.txt");

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cerr << "Error opening files." << endl;
        return false;
    }

    int currentCarId, carCost, carAvailability, returnDate;
    string line, carName;

    while (getline(inputFile, line)) {
        istringstream iss(line);

        if (iss >> currentCarId >> carName >> carCost >> carAvailability >> returnDate) {
            if (currentCarId == carId) {
                // Modify the line in memory
                stringstream modifiedLine;
                modifiedLine << carId << " " << carName << " " << carCost << " " << newCarAvailability << " " << newReturnDate;

                // Write the modified line to the temporary file
                tempFile << modifiedLine.str() << endl;
            } else {
                // Write unchanged lines to the temporary file
                tempFile << line << endl;
            }
        }
    }

    // Close both files
    inputFile.close();
    tempFile.close();

    // Remove the original file
    if (remove("cars.txt") != 0) {
        cerr << "Error removing the original file." << endl;
        return false;
    }

    // Rename the temporary file to the original file
    if (rename("temp_cars.txt", "cars.txt") != 0) {
        cerr << "Error renaming the temporary file." << endl;
        return false;
    }

    return true;
}
int getReturnDate(int carId) {
    ifstream file("cars.text");

    if (!file.is_open()) {
        cerr << "Error opening file: " << "cars.txt" << endl;
        return -1;  // Return -1 to indicate an error
    }

    int currentCarId, carRating, carCost, carAvailability, returnDate;
    string line, carName;

    while (getline(file, line)) {
        istringstream iss(line);

        // Assuming the file format is: car_id car_name car_rating car_cost car_availability return_date
        if (iss >> currentCarId >> carName >> carRating >> carCost >> carAvailability >> returnDate) {
            // Check if the current line matches the given car_id
            if (currentCarId == carId) {
                file.close();
                return returnDate;  // Return the return_date if found
            }
        }
    }

    file.close();
    return -1;  // Return -1 if car_id not found
}
bool check_car_id(int car_id) {
    ifstream file("cars.txt");

    if (!file.is_open()) {
        cerr << "Error opening file: cars.txt" << endl;
        return false;
    }

    int currentCarId;
    string line;

    while (getline(file, line)) {
        istringstream iss(line);

        if (iss >> currentCarId) {
            if (currentCarId == car_id) {
                file.close();
                return true;  // Car ID found
            }
        }
    }

    file.close();
    return false;  // Car ID not found
}
string getCarName(int carId) {
    ifstream file("cars.txt");

    if (!file.is_open()) {
        cerr << "Error opening file: " << "cars.txt" << endl;
        return "";  // Return an empty string to indicate an error
    }

    int currentCarId;
    string line, carName;
    int carRating, carCost, carAvailability, returnDate;

    while (getline(file, line)) {
        istringstream iss(line);

        // Assuming the file format is: car_id car_name car_rating car_cost car_availability return_date
        if (iss >> currentCarId >> carName >> carRating >> carCost >> carAvailability >> returnDate) {
            // Check if the current line matches the given car_id
            if (currentCarId == carId) {
                file.close();
                return carName;  // Return the car_name if found
            }
        }
    }

    file.close();
    return "";  // Return an empty string if car_id not found
}
int Login(int userid, string password, int &type/*, customer* &cust, employee* &emp, manager* &manage*/){

        if(findCustomerId(userid, password)){
            // int id, fine_due, customer_record, num_of_cars;
            // vector<int> cars;
            // string name, password;
            //fillCustomerInfo(id, name, password, fine_due, customer_record, num_of_cars, cars);
            //cust = new customer(id, name, password, fine_due, customer_record, num_of_cars, cars);
            type=0;
            return 1;
        }
        else if(findEmployeeId(userid, password)){
            // int id, fine_due, employee_record, num_of_cars;
            // vector<int> cars;
            // string name, password;
            // fillEmployeeInfo(id, name, password, fine_due, employee_record, num_of_cars, cars); 
            // emp = new employee (id, name, password, fine_due, employee_record, num_of_cars, cars);
            
            type=1;
            return 1;
        }
        else if(findManagerId(userid, password)){
            // int id;
            // string name, password;
            // findManagerInfo(id, name, password);
            // // manager m1(id, name, password);
            // // manage = &m1;
            // manage = new manager(id, name, password);
            type=2;
            return 1;
        }
        
        //cust: 0, emp: 1, manag: 2;

        return 0;
    
}
// fstream cars("cars.txt", ios::cin, ios::cout, ios::app);
// fstream customers("customers.txt", ios::cin, ios::cout, ios::app);
// fstream employees("employees.txt", ios::cin, ios::cout, ios::app);
    
int main(){
    int today_date=1;
    // customer* cust=NULL;
    // employee* emp=NULL;
    // manager* manage=NULL;
    
    cout<<"Enter user ID: "<<endl;
    int userid;
    string password;
    int type;
    // customer* cust=NULL;
    // employee* emp=NULL;
    // manager* manage=NULL;
    cin>>userid;
    cout<<"Enter password: "<<endl;
    cin>>password;
    Login(userid, password, type/*, cust, emp, manage*/);
    if(!Login(userid, password, type/*, cust, emp, manage*/)){
        do{
            cout<<"Incorrect user ID or password"<<endl;
            cout<<"Re-enter user ID "<<endl;
            cin>>userid;
            cout<<"Enter password"<<endl;
            cin>>password;
            Login(userid, password, type/*, cust, emp, manage*/);
        }while(!Login(userid, password, type/*, cust, emp, manage*/));
    }
    int n;
    int id;
    int car_id;
    int damage;
    int m;
    int new_fine_due;
    int new_record;
    int new_id;
    int rating;
    int price;
    string new_name;
    // int new_rating;
    int new_cost;
    int exp_return_date;
    int return_date;
    int payment;
    int cost;
    string new_password;
    string model;
     int cons_id, con_fine_due, cons_customer_record, cons_num_of_cars;
             vector<int> cons_cars;
             string cons_name, cons_password;
    if(type==0){
        fillCustomerInfo(userid, cons_name, cons_password, con_fine_due, cons_customer_record, cons_num_of_cars, cons_cars);
        customer* cust = new customer(userid, cons_name, cons_password, con_fine_due, cons_customer_record, cons_num_of_cars, cons_cars);
        cout<<"0: exit"<<endl;
        cout<<"1: See available cars"<<endl;
        cout<<"2: See Rented cars"<<endl;
        cout<<"3: Rent a car"<<endl;
        cout<<"4: Return a car"<<endl;
        cin>>n;
        while(n!=0){
            switch(n){
                case 1:
                    cust->available_cars();
                break;
                case 2:
                    cust->rented_cars();
                break;
                case 3:
                    cout<<"Enter Id of car you want to rent"<<endl;
                    cin>>car_id;
                    cout<<"Enter expected return date"<<endl;
                    cin>>exp_return_date;
                    cost=(exp_return_date-today_date)*find_car_price(car_id);
                    cost+=cust->fine_due;
                    cout<<"Net cost including previous fines is: "<<cost<<endl;
                    cout<<"Enter payable amount"<<endl;
                    cin>>payment;
                    if(cust->rent_request(car_id, exp_return_date, cost, payment)){
                        cout<<"car rented successfully"<<endl;
                    }
                break;
                case 4:
                    cout<<"Enter Id of car to be returned"<<endl;
                    cin>>car_id;
                    cout<<"Enter 1 if the car is damaged else 0";
                    cin>>damage;
                    cout<<"Enter return date"<<endl;
                    cin>>return_date;
                    if(cust->return_request(car_id, damage, return_date)){
                        cout<<"car returned successfully"<<endl;
                    }
                    else{
                        cout<<"car could not be returned"<<endl;
                    }
                break;
            }
            cin>>n;
        }
    }
    else if(type==1){
        fillEmployeeInfo(userid, cons_name, cons_password, con_fine_due, cons_customer_record, cons_num_of_cars, cons_cars);
        employee* emp = new employee(userid, cons_name, cons_password, con_fine_due, cons_customer_record, cons_num_of_cars, cons_cars);
        cout<<"0: exit"<<endl;
        cout<<"1: See available cars"<<endl;
        cout<<"2: See Rented cars"<<endl;
        cout<<"3: Rent a car"<<endl;
        cout<<"4: Return a car"<<endl;
        cin>>n;
        while(n!=0){
            switch(n){
                case 1:
                    emp->available_cars();
                break;
                case 2:
                    emp->rented_cars();
                break;
                case 3:
                    cout<<"Enter Id of car you want to rent"<<endl;
                    cin>>car_id;
                    cout<<"Enter expected return date"<<endl;
                    cin>>exp_return_date;
                    cost=(exp_return_date-today_date)*find_car_price(car_id)*0.85;
                    cost+=emp->fine_due;
                    cout<<"Net cost including previous fines is: "<<cost<<endl;
                    cout<<"Enter payable amount"<<endl;
                    cin>>payment;
                    if(emp->rent_request(car_id, exp_return_date, cost, payment)){
                        cout<<"car rented successfully"<<endl;
                    }
                break;
                case 4:
                    cout<<"Enter Id of car to be returned"<<endl;
                    cin>>car_id;
                    cout<<"Enter 1 if the car is damaged else 0";
                    cin>>damage;
                    cout<<"Enter return date"<<endl;
                    cin>>return_date;
                    if(emp->return_request(car_id, damage, return_date)){
                        cout<<"car returned successfully"<<endl;
                    }
                    else{
                        cout<<"car could not be returned"<<endl;
                    }
                break;
            }
            cin>>n;
        }
    }
    else if(type==2){
        findManagerInfo(userid, cons_name, cons_password);
        manager* manage = new manager(userid, cons_name, cons_password);
        cout<<"0: exit"<<endl;
        cout<<"1: Add customer"<<endl;
        cout<<"2: Update customer"<<endl;
        cout<<"3: Delete customer"<<endl;
        cout<<"4: Add employee"<<endl;
        cout<<"5: Update employee"<<endl;
        cout<<"6: Delete employee"<<endl;
        cout<<"7: Add car"<<endl;
        cout<<"8: Update car"<<endl;
        cout<<"9: Delete car"<<endl;
        cout<<"10: See all cars"<<endl;
        cout<<"11: See Available cars"<<endl;
        cin>>n;
        while(n!=0){
        switch(n){
            case 1:
                cout<<"Enter New User Id"<<endl;
                cin>>new_id;
                cout<<"Enter New password"<<endl;
                cin>>new_password;
                cout<<"Enter name(without spaces)"<<endl;
                cin>>new_name;
                manage->add_customer(new_id, new_name, new_password, findAverageRating("customers.txt"));
            break;
            case 2:
                cout<<"Enter Id of customer:"<<endl;
                cin>>id;
                // customer* up_customer=manage->find_customer(id);
                cout<<"1: Update fine_due"<<endl;
                cout<<"2: Update customer record"<<endl;
                // cout<<"3: Update cars rented by customer";
                cin>>m;
                switch(m){
                    case 1:
                        // cout<<"Enter id of customer";
                        // cin>>id;
                        cout<<"Enter new fine due:"<<endl;
                        cin>>new_fine_due;
                        manage->update_customer_fine(id, new_fine_due);
                    break;
                    case 2:
                        // cout<<"Enter id of customer";
                        // cin>>id;
                        cout<<"Enter new record:"<<endl;
                        cin>>new_record;
                        manage->update_customer_record(id, new_record);
                    break;
                    // case 3:

                    // break;
                }
            break;
            case 3:
                cout<<"Enter Id of customer to be deleted:"<<endl;
                cin>>id;
                manage->delete_customer(id);
            break;
            case 4:
                cout<<"Enter New User Id"<<endl;
                cin>>new_id;
                cout<<"Enter password"<<endl;
                cin>>new_password;
                cout<<"Enter name"<<endl;
                cin>>new_name;
                manage->add_employee(new_id, new_name, new_password, findAverageRating("employees.txt"));
            break;
            case 5:
                cout<<"Enter Id of employee:"<<endl;
                cin>>id;
                //customer* up_employee=manage->find_employee(id);
                cout<<"1: Update fine_due"<<endl;
                cout<<"2: Update employee record"<<endl;
                // cout<<"3: Update cars rented by employee";
                cin>>m;
                switch(m){
                    case 1:
                        // cout<<"Enter id of employee";
                        // cin>>id;
                        cout<<"Enter new fine due:"<<endl;
                        cin>>new_fine_due;
                        manage->update_employee_fine(id, new_fine_due);
                    break;
                    case 2:
                        // cout<<"Enter id of employee";
                        // cin>>id;
                        cout<<"Enter new record:"<<endl;
                        cin>>new_record;
                        manage->update_employee_record(id, new_record);
                    break;
                    // case 3:

                    // break;
                }
            break;
            case 6:
                cout<<"Enter Id of employee to be deleted"<<endl;
                cin>>id;
                manage->delete_employee(id);
            break;
            case 7:
                cout<<"Enter model of car"<<endl;
                cin>>model;
                cout<<"Enter Id"<<endl;
                cin>>car_id;
                // cout<<"Enter rating of car"<<endl;
                // cin>>rating;
                cout<<"Enter price of car"<<endl;
                cin>>price;
                if(manage->add_car(car_id, model, price)){
                    cout<<"Car with Id: "<<car_id<<"successfully"<<endl;
                };
            break;
            case 8:
                cout<<"Enter car Id"<<endl;
                cin>>car_id;
                cout<<"1: Update car Availability"<<endl;
                cout<<"2: Update car cost"<<endl;
                // cout<<"2: Update car rating";
                cin>>m;
                switch(m){
                    case 1:
                        manage->update_car_availability(car_id);
                    break;
                    case 2:
                        cout<<"Enter new cost: "<<endl;
                        cin>>new_cost;
                        manage->update_car_cost(car_id, new_cost);
                    break;
                    // case 3:
                    //     cin>>new_rating;
                    //     manage->update_car_rating(car_id, new_rating);
                    // break;
                }
            break;
            case 9:
                cout<<"Enter the Id of the car to be deleted"<<endl;
                cin>>car_id;
                if(manage->delete_car(car_id)){
                    cout<<"Deleted car with ID: "<<car_id<<"successfully"<<endl;
                };
            break;
            case 10:
                manage->all_cars();
            break;
            case 11:
            manage->available_cars();
            break;
        }
        cin>>n;
        }
    }
    return 0;
}
