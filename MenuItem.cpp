//
//  MenuItem.cpp
//  ProjectTrains
//
//  Created by Olga on 2018-06-06.
//  Copyright © 2018 Olga. All rights reserved.
//

#include "MenuItem.hpp"

#include <string>
using namespace std;

/* Default constructor.
 */
MenuItem::MenuItem()
{
    menuItemName = "";
    enabled = false;
}

/* Pre-defined constructor.
*/
MenuItem::MenuItem(string pMenuItemName, bool pEnabled)
{
    menuItemName = pMenuItemName;
    enabled = pEnabled;
}

/* Set-functions */
void MenuItem::setItemName(string pMenuItemName)
{
    menuItemName = pMenuItemName;
}

void MenuItem::setStatus(bool pEnabled)
{
    enabled = pEnabled;
}
