//
//  Menu.hpp
//  ProjectTrains
//
//  Created by Olga on 2018-06-06.
//  Copyright © 2018 Olga. All rights reserved.
//

#ifndef Menu_hpp
#define Menu_hpp

#include <vector>
#include <string>
#include "MenuItem.hpp"

/* class MENU:
 * ----------
 The class manages data for a menu.
 */
class Menu
{
private: //class members
    std::vector<MenuItem> menu;
    std::string menuRubrik;
    
public:
    //set-functions
    void setMenuRubrik(std::string pMenuRubrik);
    //get-functions
    std::string getMenuRubrik() const {return menuRubrik;}
    
    void addMenuItem(std::string pItemName, bool enabled);
    void printMenuItems() const;
    int getMenuChoise() const;
    void enableMenuAll();
};
int getIntForMenu(std::string prompt);

#endif /* Menu_hpp */
