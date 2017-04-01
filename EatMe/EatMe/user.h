#ifndef USERS_H
#define USERS_H

#include <string>
#include <iostream>


class User
{
	friend class Orders;
public:
	inline virtual void seeMenu();

	inline void logIn();
	inline void seeDishes();
	inline void addInBasket(unsigned int choise);
	
};



class LogedInUser : public User
{
public:
	explicit LogedInUser(std::string aName = "", std::string password = "");
	explicit LogedInUser(const LogedInUser&);

private:
	static unsigned int ID;

	unsigned int aId;
	std::string aName;
	std::string aPassword;
};



class Admin : public LogedInUser
{
public:
	explicit Admin(std::string aName = "", std::string password = "");
	explicit Admin(const Admin&);

	void seeMenu();

	inline void addDishInMenu();
	inline void deleteDish();
	inline void seeOrders();

private:

};



class Customer : public LogedInUser
{
public:
	explicit Customer(std::string FIO = "", std::string password = "");
	explicit Customer(const Customer&);

	inline void seeMenu();

private:

};

#endif //USERS_H
