//
// Created by danie on 2024-12-02.
//

#ifndef MAPLEOS_SYSTEMCOLORS_H
#define MAPLEOS_SYSTEMCOLORS_H

#define GREEN 2
#define CYAN 3
#define RED 4
#define PURPLE 5
#define YELLOW_DARK 6
#define DEFAULT_WHITE 7
#define GRAY 8
#define BRIGHT_BLUE 9
#define BRIGHT_GREEN 10
#define BRIGHT_CYAN 11
#define BRIGHT_RED 12
#define PINK_MAGENTA 13
#define YELLOW 14
#define BRIGHT_WHITE 15
#define DEFAULT 7
class SystemColors
{
public:
    static void PrintColored(const char* content, int color);
};


#endif //MAPLEOS_SYSTEMCOLORS_H
