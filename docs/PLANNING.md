# :pager: Planning process guide
***
The Bank Account Management System is a console-based application developed in C, designed to simulate the basic operations of a bank account such as creating new accounts, 
updating existing accounts, conducting transactions (deposits and withdrawals), viewing account details, and facilitating transactions between users. This project emphasizes 
the use of file handling in C to store and manage user data persistently across sessions.

Knowing this, we can divide the planning into four aspects:
- Define what the project interface will look like.
- Define what functionalities the bank will have
- Define how we will store customer data
- Define how we will secure the information 
***
## :computer: Interface
For this console-based project we will not need a complicated interface, we will use several menus that present options and the user will choose the option by simply entering its number.

![Example image of a menu](https://github.com/vilan54/Bank-Management-C/assets/79419009/3d6fd620-b50d-4253-9337-4ab7a850ca4a)

***
## :bookmark_tabs: Functionalities
As described above, the system will have 5 functionalities: create an account, login to an account, deposit or withdraw money and make transactions between accounts.

### Create an account
The system must give the option to create an account as long as the user does not have an account associated with his or her ID.
To create an account, the system will need the following information from the user:
```
- Dni
- User's name
- Password
- Date of birth 
```
This information must be provided by the user and the system must process and store it as described below.

### Log in
The user must be able to log in as long as he/she has created an account. To do so, the user must enter 
```
- His/Her Dni
- His/Her password
```

### Manage account's monney
The system must provide a way to manage the money in the account, this can be either depositing money or withdrawing money.
We will assume that there is no upper limit to the amount of money that can be deposited, but, obviously, it is not possible to withdraw more money than is available in the account.

### Make a transaction
As well as managing money, the system must allow transactions between existing accounts. 
To do this, the user will be prompted:
```
- Dni of the recipient
- Amount of money
```
The system must check that the recipient exists and that there is enough money in the account. 
It must also save the information of the transaction together with the date and time of the transaction in both users (sender and recipient) and in each one if it was sent or received.

