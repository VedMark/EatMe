#pragma once

#include <iterator>
#include <iostream>
#include <string>
#include <vector>

#include "menu.h"
#include "order.h"

const enum UserType{ ADMIN, CUSTOMER };

class InputError {
public:
	std::string message = "\n\t\tWRONG VALUE!\n";
};



class User
{
public:
	explicit User(std::string name = "", std::string aPassword = "");
	User(const User&);

	virtual void addDishInMenu(Menu* menu);
	virtual void deleteDishes(Menu* menu);
	virtual void parseOrders(Orders* currentOrders, History archive);

	virtual void addInBasket(const Dish&);
	virtual void replenishWallet();

	inline unsigned int getID() const { return aID; }
	inline void setId(unsigned int id) { aID = id; }

	inline std::string getName() const { return aName; }
	inline void setName(std::string name) { aName = name; }

	inline std::string getPassword() const { return aPassword; }
	inline void setPassword(std::string password) { aPassword = password; }

	inline Basket* getBasket() const { return pBuyings; }
	inline void setBasket(Basket* buyings) { pBuyings = new Basket(*buyings); }

	virtual int getMoney() const;
	virtual void setMoney(float money_);

protected:
	static unsigned int ID;

	unsigned int aID;
	std::string aName;
	std::string aPassword;
	Basket *pBuyings;
};



class Admin : public User
{
public:
	explicit Admin(std::string aName = "", std::string password = "");
	Admin(const Admin&);

	void addDishInMenu(Menu* menu);
	void deleteDishes(Menu* menu);
	void parseOrders(CurrentOrders currentOrders, History archive);
};


class Customer : public User
{
public:
	explicit Customer(std::string FIO = "",
					std::string password = "",
					std::string address = "",
					unsigned int money = 0);

	explicit Customer(const Customer&);

	int getMoney() const { return aMoney; }
	void setMoney(int money_) { aMoney = money_; }

	void replenishWallet();

protected:
	std::string aAddress;
	unsigned int aMoney;
};
