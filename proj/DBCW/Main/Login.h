#pragma once

#include "Facade.h"
#include "AdminInterface.h"
#include "UserInterface.h"
#include "ArtistInterface.h"
#include "ConnectException.h"
#include "LoginException.h"

class Login
{
private:
	Config& config;
public:
	Login() = delete;
	Login(Config& conf) : config(conf) {}

	shared_ptr<BaseInterface> create()
	{
		while (true)
		{
			system("cls");
			cout << "Login as\n"
				"1. User\n"
				"2. Artist\n"
				"3. Admin\n" << std::endl;

			int num;

			cin >> num;

			switch (num)
			{
			case 1:
			{
				return subwork();
				break;
			}
			case 2:
			{
				cout << "email" << std::endl;
				string email;
				cin >> email;

				cout << "password" << std::endl;
				string pass;
				cin >> pass;

				try
				{
					return shared_ptr<BaseInterface>(new ArtistInterface(config, email, pass));
				}
				catch (const ConnectException& e)
				{
					cout << "\nError while connecting db\n" << std::endl;
					break;
				}
				catch (const LoginException& e)
				{
					cout << "\nWrong login or email\n" << std::endl;
				}
				break;
			}
			case 3:
			{
				cout << "password" << std::endl;
				string pass;
				cin >> pass;
		
				try
				{
					return shared_ptr<BaseInterface>(new AdminInterface(config, "", pass));
				}
				catch (const ConnectException&)
				{
					cout << "\nError while connecting db (maybe wrong password)\n" << std::endl;
					break;
				}
				break;
			}
			default:
				break;
			}
		}
	}
private:
	shared_ptr<BaseInterface> subwork() 
	{
		while (true)
		{
			cout << "1. Login\n"
				"2. Register\n" << std::endl;

			int num;

			cin >> num;

			switch (num)
			{
			case 1:
			{
				cout << "email" << std::endl;
				string email;
				cin >> email;

				cout << "password" << std::endl;
				string pass;
				cin >> pass;

				try
				{
					return shared_ptr<BaseInterface>(new UserInterface(config, email, pass));
				}
				catch (const ConnectException & e)
				{
					cout << "\nError while connecting db\n" << std::endl;
					break;
				}
				catch (const LoginException& e)
				{
					cout << "\nWrong login or email\n" << std::endl;
				}
				catch (...)
				{
					cout << "\nShit happens\n" << std::endl;
				}
				break;
			}
			case 2:
			{
				cout << "Input your register email" << std::endl;
				string email;
				cin >> email;

				cout << "Input your register password" << std::endl;
				string password;
				cin >> password;

				if (Facade(config, "", "4Nikarulez_7", ADMIN_CONNECT).loginUser(email, password))
				{
					cout << "\nSuccess login\n" << std::endl;
				}
				else
				{
					cout << "\nUser with same email already exists\n" << std::endl;
				}
			}
			default:
				break;
			}
		}
	}
};

