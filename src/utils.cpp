
/*                                                */
/*                                                */
/*                                                */
/*    (`-').->(`-')          .->    _(`-')        */
/*    (OO )__ ( OO).->   (`(`-')/`)( (OO ).->     */
/*    ,--. ,'-'/    '._  ,-`( OO).', \    .'_     */
/*    |  | |  ||'--...__)|  |\  |  | '`'-..__)    */
/*    |  `-'  |`--.  .--'|  | '.|  | |  |  ' |    */
/*    |  .-.  |   |  |   |  |.'.|  | |  |  / :    */
/*    |  | |  |   |  |   |   ,'.   | |  '-'  /    */
/*    `--' `--'   `--'   `--'   '--' `------'     */
/*                                                */
/* Florian Suessmann                              */
/* 23/41/61                                       */

#include <iostream>
#include <fstream>
#include <ios>

#include "./includes/utils.hpp"

char* myitos(int n)     // converts an integer to an char*
{
    int len = 1;
    int cnt = n;
    if (n < 0) len++;

    while (cnt != 0)
    {
        cnt = cnt/10;
        len++;
    }
    char *str = new char[len + 1]();
    if (!str) {std::cout << "allocation failed in myitos!\n"; return nullptr;}

    sprintf(str, "%d", n);
    return str;
}

char* myitosTime(int n) // converts an integer to an char* in time format (leading zeros)
{
    int len = 1;
    int cnt = n;
    if (n < 0) len++;

    while (cnt != 0)
    {
        cnt = cnt/10;
        len++;
    }
    if (cnt != 2) len++;
    char *str = new char[len + 1]();
    if (!str) {std::cout << "allocation failed in myitos!\n"; return nullptr;}

    sprintf(str, "%02d", n);
    return str;
}
