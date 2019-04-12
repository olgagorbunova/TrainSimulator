//
//  MenuItem.hpp
//  ProjectTrains
//
//  Created by Olga on 2018-06-06.
//  Copyright © 2018 Olga. All rights reserved.
//

#ifndef MenuItem_hpp
#define MenuItem_hpp

#include <string>

/* class MENU ITEM:
 * ---------------
 The class manages data for menu alternatives
 */
class MenuItem
{
private: //class members
    std::string menuItemName; //menu alternative name
    bool enabled; //indicates if menu option is enabled
    
public:
    MenuItem(); //default constructor
    MenuItem(std::string pMenuItemName, bool pEnabled); //constructor
    
    //set-functions
    void setItemName(std::string pMenuItemName);
    void setStatus(bool pEnabled);
    
    //get-functions
    std::string getItemName () const {return menuItemName;}
    bool isAvailable () const {return enabled;}
};

#endif /* MenuItem_hpp */
