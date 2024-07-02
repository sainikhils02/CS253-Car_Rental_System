# **CAR RENTAL SYSTEM**

## BASIC DESCRIPTION
This Project implements Car Rental System in an efficient manner.The system uses OOPS concepts and filehandling of c++.It contains six parts.
1. main.cpp
2. cars.txt
3. managers.txt
4. customers.txt
5. employees.txt
6. managers.txt

The First part contains c++ code necessary for the system to run.Other parts are used as Databases for the system.

## INSTALLATION
To run the system, all the files are required to be in the same directory and presence of c++ compiler is a must.

## USAGE
The system is Designed for 3 types of users.
1. Manager
2. Employee
3. Customer

Each user is required to enter their login credentials and the system will automatically guide them through their performable actions and functions.The system assumes today's date to be 1 and does not allow advance bookings.The system offers an exclusive discount of 15% for its employees and fine of INR500 will be imposed per day if the cars are returned late.

## DATABASES

### cars.txt
This file contains data of all cars on the below format.
id name cost_per_day Availability Retrn_date(If car is not available else is 0)

### customers.txt
This file contains data of all customers which used/are using the system in the below format,
id name password fine_due record number_of_cars_rented ids_of_cars_rented

### employees.txt
This file contains data of all epmloyees which used/are using the system in the below format,
id name password fine_due record number_of_cars_rented ids_of_cars_rented

### managers.txt
This file contains data of managers of the system in the below format,
id name password
