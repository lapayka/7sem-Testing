#pragma once
#include "BaseInterface.h"
#include "Facade.h"
#include "ConConfig.h"

class ArtistInterface :
    public BaseInterface
{
private:
    Facade facade;
    string self_id;
public:

    ArtistInterface(Config & config, const string& email, const string& password)
        :
        facade(config, email, password, ARTIST_CONNECT),
        self_id(email)
    {

    }

    virtual void work() override
    {
        bool end = false;
        while (!end)
        {
            system("cls");
            cout << "1. Add album\n"
                "0. Exit\n" << std::endl;

            int choice;

            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                cout << "Input name of album" << std::endl;
                string name;
                cin >> name;

                vector<MusItem> toAdd = inputMusItems(name);

                facade.createAlbum(self_id, name, toAdd);

                break;
            }
            case 0:
                end = true;
                break;
            default:
                cout << "No such choice" << std::endl;
                break;
            }
            

        }
    }

    ~ArtistInterface() = default;

private:
    vector<MusItem> inputMusItems(const string & aname)
    {
        cout << "Input count of compositions" << std::endl;
        int n;
        cin >> n;

        cout << "Input compositions in format\nname duration" << std::endl;
        vector<MusItem> res;
        while (n--)
        {
            string name;
            string duration;

            cin >> name >> duration;

            res.push_back(MusItem(0, name, duration, aname, self_id));
        }

        return res;
    }
};

