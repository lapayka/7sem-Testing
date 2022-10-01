#pragma once
#include "BaseInterface.h"
#include "Facade.h"
#include "Config.h"
#include "View.h"

class UserInterface :
    public BaseInterface
{
private:
    Facade facade;
    string self_id;
public:
    UserInterface(shared_ptr<Config> config, const string& email, const string& password)
        :
        facade(config, email, password, USER_CONNECT),
        self_id(email)
    {

    }

    virtual void work() override
    {
        bool end = false;
        while (!end)
        {
            system("cls");
            std::cout << "1. Music by name\n"
                "2. Music by album\n"
                "3. Music by artist\n"
                "4. My Playlists\n" 
                "5. Create request to become an artist\n"
                "0. Exit"
                << std::endl;
            int choice;
            cout << "Your choice: " << std::ends;
            std::cin >> choice;

            switch (choice)
            {
            case 1:
            {
                string tmp;
                cout << "Input compostion name:" << std::endl;
                cin >> tmp;
                subwork(facade.getMusicByName(tmp));
                break;
            }
            case 2:
            {
                string tmp;
                cout << "Input album name:" << std::endl;
                cin >> tmp;
                subwork(facade.getMusicByAlbum(tmp));
                break;
            }
            case 3:
            {
                string tmp;
                cout << "Input artist name:" << std::endl;
                cin >> tmp;
                subwork(facade.getMusicByArtist(tmp));
                break;
            }
            case 4:
            {
                subwork(facade.getPlstByUser(self_id));
                break;
            }
            case 5:
            {
                string tmp;
                cout << "Input artist name:" << std::endl;
                cin >> tmp;

                facade.createRequest(self_id, tmp);
                break;
            }
            case 0:
            {
                end = true;
                break;
            }
            default:
                cout << "No such choice" << std::endl;
                break;
            }
        }

    }

    ~UserInterface() = default;

private:
    void subwork(const vector<MusItem>& items);
    
    void subwork(const vector<PlstItem>& items);
};

