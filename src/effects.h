#ifndef _EFFECTS_H
#define _EFFECTS_H

/* source file used to define a lot of things related to
 * effects that can affect cards. this .h file is meant
 * to define the class and a lot of enums regarding how
 * to process each effect.
 *
 * Effects are used for extra things, not just what are
 * explicitly effects in the game. for example, when a 
 * card enters tapped, there will be a free effect that
 * taps the creature
 */
#include <string>
#include "log.h"
#include "utils.h"
#include "mana.h"

/* what triggers allow the player to activate the effect */
enum effectTrigger{
    TRIGGER_INVALID,
    TRIGGER_ANYTIME, /* basically, the effect is equivalent to casting an instant */
    TRIGGER_SORCERY_LIKE, /* whenever the player can cast a sorcery, it can use the effect */
    TRIGGER_ENTER_FIELD, /* effect triggers when the card enters the field */
    TRIGGER_OTHER_ENTER_FIELD, /* effect triggers when other cards enter the field */
    TRIGGER_ATTACK, /* effect triggers when the creture attacks */
    TRIGGER_GET_ATTACKED, /* triggers when the creature gets attacked */
    TRIGGER_RECEIVE_TOKEN, /* triggers when the creature receives a token */
};
effectTrigger stringToEffectTrigger(std::string);

enum effectCost {
    EFFECT_COST_INVALID,
    EFFECT_COST_FREE, /* the effect happens for free */
    EFFECT_COST_TAP, /* the creature needs to be tapped */
    EFFECT_COST_PAY_MANA, /* there is a mana cost to using this effect */
    EFFECT_COST_SACRIFICE_CARD /* a card has to be sacrificed for the effect, uses effectTargetType */
};
effectCost stringToEffectCost(std::string);

enum effectResult{
    RESULT_INVALID,
    RESULT_GENERATE_MANA, /* the effect generates a mana string */
    RESULT_TAP_TARGET, /* the effect taps a target, uses effectTargetType to decide the target */
    RESULT_DEAL_DAMAGE, /* deals N damage to the target, uses effectTargetType */
    RESULT_ADD_COUNTER, /* adds N counters to the target, uses effectTargetType and counterType */
};
effectResult stringToEffectResult(std::string);

enum effectTargetType {
    TARGET_INVALID,
    TARGET_SELF, /* targets the card that generated the event */
    TARGET_CHOOSE_ANY_PERMANENT, /* targets any permanent on the board */
    TARGET_CHOOSE_OPPONENT_PERMANENT, /* targets any permanent of your opponent */
    TARGET_CHOOSE_OPPONENT_LAND, /* targets any land of your opponent */
    TARGET_CHOOSE_OWN_PERMANENT, /* targets any permanent that you control */
    TARGET_CHOOSE_OWN_LAND, /* targets any land you control */
};
effectTargetType stringToEffectTargetType(std::string);

class Effect {
public:
    const std::string name; /* the name of the effect. must be unique */

    /* bitmasks from the enums */
    const int trigger; /* what kinds of things trigger this effect */
    const int cost; /* what is the cost of the effect */
    const int result; /* what this effect do */
    const int target; /* what are the kinds of targets that this effect can have */

    /* Members that are only defined in certain situations */
    const mana mana_cost; /* this can be the cost or the generation */
    const int n; /* this can stand for counters, damage or other 'N' stuff */

    /*
     * this is not expected to be used directly. pass the string to
     * make_effect, which can create the correct effects more easily
     */
    Effect(std::string nam, int tr, int c, int res, int tar, mana cst, int N);
};

Effect make_effect(std::string line);

#endif