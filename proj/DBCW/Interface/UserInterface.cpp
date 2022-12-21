#include "UserInterface.h"

void UserInterface::subwork(const vector<MusItem>& items)
{
    bool end = false;
    while (!end)
    {
        system("cls");
        View().outputMusics(items);

        cout << "1. Listen composition\n"
            "2. Listen all\n"
            "3. Add composition to playlist\n"
            "0. Exit\n" << std::endl;

        int choice;
        cout << "Your choice: " << std::ends;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int num;

            cout << "Input number of composition" << std::endl;
            cin >> num;


            facade.listenMusic(items[--num], self_id);
            break;
        }
        case 2:
        {
            facade.listenMusic(items, self_id);
            break;
        }
        case 3:
        {
            int num1;

            cout << "Input number of composition" << std::endl;
            cin >> num1;

            vector<PlstItem> pitems = facade.getPlstByUser(self_id);
            View().outputPlaylists(pitems);

            cout << "Input number of playlist (to add)" << std::endl;
            int num2;
            cin >> num2;

            facade.updatePlaylist(pitems[--num2].id, items[--num1]);
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

void UserInterface::subwork(const vector<PlstItem>& items)
{
    {
        bool end = false;
        while (!end)
        {
            system("cls");
            vector<PlstItem> nitems = facade.getPlstByUser(self_id);
            View().outputPlaylists(nitems);

            cout << "1. Open Playlist\n"
                "2. Create playlist\n"
                "3. Delete Playlist\n"
                "0. Exit\n" << std::endl;

            int choice;
            cout << "Your choice: " << std::ends;
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                int num;

                cout << "Input number of playlist" << std::endl;
                cin >> num;

                subwork(facade.getMusicByPlaylist(nitems[--num].id));
                break;
            }
            case 2:
            {
                cout << "Input name of playlist" << std::endl;
                string name;
                cin >> name;

                facade.createPlaylist(self_id, name);
                break;
            }
            case 3:
            {
                int num;

                cout << "Input number of playlist" << std::endl;
                cin >> num;

                facade.deletePlaylist(nitems[--num].id);
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
}