#pragma once

#include <string>
#include <iostream>
#include <iterator>
#include <vector>


class dish;
class Menu;

class Orders;
typedef Menu Basket;
typedef Orders History;

const enum UserType{ ADMIN, CUSTOMER };

class User
{
public:
	explicit User(std::string name = "", std::string aPassword = "");
	User(const User&);

	virtual void addDishInMenu(Menu* menu);
	virtual void deleteDishes(Menu* menu);
	virtual void parseOrders(Orders *currentOrders, Orders *archive);

	virtual void addInBasket(const dish&);
	virtual void replenishWallet();

	inline unsigned int getID() const { return aID; }
	inline void setId(unsigned int id) { aID = id; }

	inline std::string getName() const { return aName; }
	inline void setName(std::string name) { aName = name; }

protected:
	Basket *pBuyings;
	static unsigned int ID;

	unsigned int aID;
	std::string aName;
	std::string aPassword;
};


class Admin : public User
{
public:
	explicit Admin(std::string aName = "", std::string password = "");
	Admin(const Admin&);

	void addDishInMenu(Menu* menu);
	void deleteDishes(Menu* menu);
	inline void A();
	void parseOrders(Basket* currentOrders, History* archive);
};


class Customer : public User
{
public:
	explicit Customer(std::string FIO = "",
					std::string password = "",
					std::string address = "",
					unsigned int money = 0);

	explicit Customer(const Customer&);
	
	void replenishWallet();

protected:
	std::string aAddress;
	unsigned int aMoney;
};
