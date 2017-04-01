#ifndef EAT_ME
#define EAT_ME

#include <fstream>
#include <string>
#include <vector>

#include "user.h"
#include "menu.h"
#include "order.h"
#include "ciphers/RC5Simple.h"

typedef fstream *Storage;

class EatMe
{
public:
	explicit EatMe();
	~EatMe();

	inline void run();

private:
	const string KEY_FILE_NAME = "storage/key.txt";
	const string ORDER_FILE_NAME = "storage/orders.txt";
	const string PASSWORDS_FILE_NAME = "storage/passwords.txt";

	RC5Simple *pRC5;
	Menu *pMenu;
	Basket *customerBasker;
	User *pCurrentUser;
};

#endif // EAT_ME