#include "EventLoader.h"
#include "stdlib.h"

void StringCopy(char String1[], char String2[]){

    int CharacterIndex = 0;
    String2 = (char*)malloc(5*sizeof(char));
    char c = String1[0];
    while (c != '\n'){
        c = String1[CharacterIndex];
        String2 = (char*)realloc(String2, sizeof(char));
        String2[CharacterIndex] = c;

        CharacterIndex += 1;
    }

}


void CreateEvent(Event* ev, int Day, int Month, int Year, int AllDay, char Name[], char Location[], char PeopleInvovled[]){
    ev->Day = Day;
    ev->Month = Month;
    ev->Year = Year;
    ev->AllDay = AllDay;
    
    
}