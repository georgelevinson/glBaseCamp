#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_list.h"

#define HP_SERIES_LENGTH 7
#define FPH_SERIES_LENGTH 3

static const char hp_names[HP_SERIES_LENGTH][50] = {"Philosopher's Stone","Chamber of Secrets", "Prisoner of Azkaban", "Goblet of Fire", "Order of the Phoenix", "Half-Blood Prince", "Deathly Hallows"};
static const unsigned int hp_release_years[HP_SERIES_LENGTH] = {1997,1998,1999,2000,2003,2005,2007};
static const char hp_language[8] = "English";
static const unsigned short hp_pages[HP_SERIES_LENGTH] = {223,251,317,636,766,607,607};
static const double hp_prices_GBP[HP_SERIES_LENGTH] = {14.48, 15.23, 9.99, 11.77, 13.27, 25.19, 25.42};
static const float hp_weights_kg[HP_SERIES_LENGTH] = {1.672812,1.682812,1.962812,2.032002,2.122812,2.322472,2.322472};

static const char fph_names[FPH_SERIES_LENGTH][50] = {"Volume I: Mainly mechanics, radiation, and heat", "Volume II: Mainly electromagnetism and matter", "Volume III: Quantum mechanics"};
static const unsigned int fph_release_years[FPH_SERIES_LENGTH] = {1964,1964,1964};
static const char fph_language[8] = "English";
static const unsigned short fph_pages[FPH_SERIES_LENGTH] = {560,592,379};
static const double fph_prices_GBP[FPH_SERIES_LENGTH] = {49.49,59.04,65.83};
static const float fph_weights_kg[FPH_SERIES_LENGTH] = {1.27, 1.35,1.07};

int main(void)
{
    Value hp_values[HP_SERIES_LENGTH];

    for(int i = 0; i < HP_SERIES_LENGTH; i++)
    {
        snprintf(hp_values[i].name, sizeof(hp_values[i].name), "Harry Potter and the %s", hp_names[i]);
        snprintf(hp_values[i].lang, sizeof(hp_values[i].lang), "%s", hp_language);
        hp_values[i].pages = hp_pages[i];
        hp_values[i].price_GBP = hp_prices_GBP[i];
        hp_values[i].year = hp_release_years[i];
        hp_values[i].weight_kg = hp_weights_kg[i];
    }

    Value fph_values[FPH_SERIES_LENGTH];

    for(int i = 0; i < FPH_SERIES_LENGTH; i++)
    {
        snprintf(fph_values[i].name, sizeof(fph_values[i].name), "The Feynman Lectures on Physics, %s", fph_names[i]);
        snprintf(fph_values[i].lang, sizeof(fph_values[i].lang), "%s", fph_language);
        fph_values[i].pages = fph_pages[i];
        fph_values[i].price_GBP = fph_prices_GBP[i];
        fph_values[i].year = fph_release_years[i];
        fph_values[i].weight_kg = fph_weights_kg[i];
    }

    ListPtr potter = init_list(hp_values, HP_SERIES_LENGTH);
    ListPtr feynman = init_list(fph_values, FPH_SERIES_LENGTH);

    print_list(potter);
    print_list(feynman);

    insert_elements(&feynman, potter, 4);
    print_list(potter);
    print_list(feynman); // pointers to memory with data-containing structs have been reinserted into a new list (dest list of insert_elements()), 
    // while original list structure feynman (allocated by init_list(&fph_values, FPH_SERIES_LENGTH)) have been freed (it now makes no sense since the data accessible via newly merged list)
    // dangling pointer to feynman has been assigned NULL by insert_elements(&feynman, potter, 4) to aviod invalid operations

    for(int i = 0; i < FPH_SERIES_LENGTH; i++)
        delete_nth(potter, 4);
    print_list(potter); // inserted data removed from list, memory that has initially been allocated by init_list(&fph_values, FPH_SERIES_LENGTH) got released by delete_nth()

    free_list(&potter);
    free_list(&feynman); // demo - it has already been freed, but this won't cause an error due to the NULL-pointer guard
    print_list(potter);

    return 0;
}
