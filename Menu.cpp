//
//  Menu.cpp
//  ProjectTrains
//
//  Created by Olga on 2018-06-06.
//  Copyright © 2018 Olga. All rights reserved.
//

#include "Menu.hpp"

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

/* Set-function for setting menu rubrik. */
void Menu::setMenuRubrik(string pMenuRubrik)
{
    menuRubrik = pMenuRubrik;
}

/* addMenuItem:
 * -----------
 * Adds an MenuItem object to a menu vector.
 */
void Menu::addMenuItem(string pItemName, bool pEnabled)
{
    MenuItem tmpItem;
    tmpItem.setItemName(pItemName);
    tmpItem.setStatus(pEnabled);
    menu.push_back(tmpItem);
}

/* printMenuItems:
 * ---------------
 * Prints all items from a menu. Marks items that are not enabled as "unavailable".
 */
void Menu::printMenuItems() const
{
    int count = 1;
    for(auto idx: menu)
    {
        if(idx.isAvailable())
        {
            cout << count << ". " << idx.getItemName() << endl;
        }
        else
        {
            cout << count << ". " << setw(40) << left << setfill(' ') << idx.getItemName() << "/unavailable/" << endl;
        }
        count++;
    }
}

/* getMenuChoise:
 * -------------
 * Returns user choise from the menu list (int).
 * User is not allowed to choose an item which is unavailable; user is prompted to choose another item until an uvailable item is chosen; input is validated.
 */
int Menu::getMenuChoise() const
{
    bool again = true;
    int choice;
    
    do
    {
        choice = getIntForMenu(">>> ");
        
        bool enabled;
        enabled = menu[choice-1].isAvailable(); //check if MenuItem object that user chose is enabled
        
        if(choice < 1 || choice > menu.size()) //validate input (number in scope of menu size)
            cout << "Invalid input, please try again... ";
        else if(!enabled) //if MenuItem object "unavailbale" - ask user to make another choice
            cout << "This menu option is unavailable, please choose another option... ";
        else
            again = false;
        
        cout << endl;
        
    }while(again);
    
    return choice;
}

/* enableMenuAll:
 * -------------
 * Sets status of all MenuItem objects to "available". For those menu alternatives that have status "unavailable".
 */
void Menu::enableMenuAll()
{
    for(int i = 0; i < menu.size(); i++)
    {
        if(menu[i].isAvailable() == false) //checking if current menu alternatives status is "unavailable" and needs to be changed
            menu[i].setStatus(true);
    }
}

/* getIntForMenu:
 * -------------
 * Validating user input where integer is expected as an input.
 */
int getIntForMenu(string prompt) {
    bool valid = false;
    string input;
    
    while (valid == false) {
        cout << prompt;
        getline(cin, input);
        
        for (auto c : input) {
            if (isdigit(c))
                valid = true;
            else {
                valid = false;
                break;
            }
        }
    }
    return stoi(input);
}
