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
	shared_ptr<Config> config;
public:
	Login() = delete;
	Login(shared_ptr<Config> conf) : config(conf) {}

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
			cout << "Your choice: " << std::ends;

			cin >> num;

			system("cls");

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

				system("cls");
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
			
				system("cls");
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
				cout << "No such choice" << std::endl;
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
			cout << "Your choice: " << std::ends;
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

				system("cls");
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

				system("cls");
				if (Facade(config, "", "4Nikarulez_7", ADMIN_CONNECT).loginUser(email, password))
				{
					cout << "\nSuccessful login\n" << std::endl;
				}
				else
				{
					cout << "\nUser with the same email already exists\n" << std::endl;
				}
			}
			default:
				break;
			}
		}
	}
};

