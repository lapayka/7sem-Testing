#pragma once
#include "BaseInterface.h"

#include "Facade.h"
#include "ConConfig.h"
#include <fstream>

class AdminInterface :
    public BaseInterface
{
private:
    Facade facade;
public:

    AdminInterface(Config& config, const string& email, const string& password)
        :
        facade(config, email, password, ADMIN_CONNECT)
    {

    }

    virtual void work() override
    {
        bool end = false;
        while (!end)
        {
            system("cls");
            std::cout << "1. Check requests\n"
                "2. Get graph\n"
                << std::endl;
            int choice;

            std::cin >> choice;

            switch (choice)
            {
            case 1:
            {
                vector<pair<string, string>> req = facade.checkRequests();
                subwork(req);

                break;
            }
            case 2:
            {
                visGraph(facade.getGraph());
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

    ~AdminInterface() = default;
private:
    void outRequsets(const vector<std::pair<string, string>>&items)
    {
        cout << "Requests:\n";
        int i = 1;

        for (const auto& item : items)
        {
            cout << i++ << ": " <<item.first << " " << item.second << "\n";
        }
        cout << std::endl;
    };

    void subwork(vector<std::pair<string, string>>& items)
    {
        while (true)
        {
            system("cls");
            outRequsets(items);

            cout << "To accept request input number of it (0 to exit)" << std::endl;

            int number;
            cin >> number;

            if (number == 0)
                return;

            number--;

            facade.createArtist(items[number].first, items[number].second);

            items = facade.checkRequests();
        }
    }

    void visGraph(const std::vector<std::pair<int, int>> & graph)
    {
        {
            ofstream str("graph.dot");

            str << "graph G {\n";
            for (const auto& pair : graph)
            {
                str << pair.first << " -- " << pair.second << ";\n";
            }

            str << "}";
        }

        system("dot -Tpng -ogr.png graph.dot && gr.png");
        //system("del gr.png && del graph.dot");
    }
};

