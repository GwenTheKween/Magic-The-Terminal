#include "game_menu.h"
#include "player.h"
#include "database.h"

game_menu::game_menu()
    : menu () {
    std::vector<std::string> options ={
        "1 player game",
        "2 player game",
        "return"
    };

    int x, y;
    getmaxyx(stdscr, y, x);
    windows = newwin(y, x, 0, 0);
    panels = new_panel(windows);
    box(windows, 0, 0);
    keypad(windows, true);

    menu.startup(windows, options);

    update_panels();
    doupdate();
}

game_menu::~game_menu(){
    del_panel(panels);
    delwin(windows);
}

void game_menu::move_menu(int key) {
    menu.move_menu(key);
}

int game_menu::select_item(){
    return menu.select_item();
}

int game_menu::get_input(){
    return wgetch(windows);
}

//================= FINISH GAME_MENU CLASS =============================

/* Define how the player will work. This will decide the deck
   and what AI will be used.  The parameter defines if this is
   a human player or not.  */
static Player define_player(bool);
/* Choose which deck the human will use.  */
static deck human_choose_deck();
/* Choose which deck the computer will use.  */
static deck computer_choose_deck();

/* Main game loop, receives two players ready to play and runs
   through every step of the turn and calls relevant functions.  */
static void run_game_loop(Player, Player);

//==================== FUNCTION DECLARATIONS ===========================

void card_game_loop (){
    game_menu m;
    int c, selected = 0;
    while(selected == 0) {
        c = m.get_input();
        switch (c) {
            case KEY_UP:
            case KEY_DOWN:
            case 'j':
            case 'k':
            case 'w':
            case 's':
                m.move_menu(c);
                break;
            case '\n':
            case ' ':
            case 'e':
                selected = m.select_item();
                break;
            case 'q':
                selected = -1;
                break;
            default:
                /* unknown key was pressed, do nothing.  */
                break;
        }
        switch(selected) {
            case -1:
                /* Quit was chosen.  Exit the function.  */
                return;
            case 0:
                /* No option was selected.  */
                break;
            case 2:
                /* Two player game was requested.  */
                run_game_loop(define_player(true),
                              define_player(true));
            default:
                mvprintw(0,0, "Not yet implemented");
                refresh();
                break;
        }
        selected = 0;
    }
}

Player define_player(bool human){
    if(!human){
        debug_assert("Not yet implemented");
    } else {
        /* Prepare the human player.  Ask the player for which deck he
           wants to use.  */

        return Player(human_choose_deck(), HUMAN);
    }
}

deck human_choose_deck(){
    /* TODO: This is just a placeholder for now.  An actual deck
        choice should be implemented at some point.  */
    return deck("goblin1", get_card_database());
}

deck computer_choose_deck(){
    /* TODO: This is just a placeholder for now.  An actual deck
        choice should be implemented at some point.  */
    return deck("goblin1", get_card_database());
}

void run_game_loop(Player p1, Player p2) {
    return;
}
