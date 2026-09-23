#include <stdio.h>
#include <string.h>

/* ============================================================
   PART 1: BASE CHARACTER STRUCT
   ============================================================ */

typedef struct Character Character;

struct Character {
    char name[50];
    int health;
    int level;

    void (*attack)(Character *self);
    void (*take_damage)(Character *self, int damage);
};

/* ============================================================
   PART 2: CHARACTER METHODS
   ============================================================ */

void character_attack(Character *self) {
    printf("%s attacks with a basic attack!\n", self->name);
}

void character_take_damage(Character *self, int damage) {
    self->health -= damage;

    if (self->health < 0) {
        self->health = 0;
    }

    printf("%s takes %d damage! Health: %d\n",
           self->name, damage, self->health);
}

void character_init(Character *character, const char *name,
                    int health, int level) {
    strcpy(character->name, name);
    character->health = health;
    character->level = level;

    character->attack = character_attack;
    character->take_damage = character_take_damage;
}

/* ============================================================
   PART 3: DERIVED CHARACTER TYPES
   ============================================================ */

typedef struct {
    Character base;
    int strength;
} Warrior;

typedef struct {
    Character base;
    int mana;
} Mage;

/* ============================================================
   PART 4: POLYMORPHIC METHODS
   ============================================================ */

void warrior_attack(Character *self) {
    printf("%s swings sword for heavy damage!\n", self->name);
}

void mage_attack(Character *self) {
    printf("%s casts a powerful magic spell!\n", self->name);
}

void warrior_init(Warrior *warrior, const char *name,
                  int health, int level, int strength) {
    character_init(&warrior->base, name, health, level);

    warrior->strength = strength;

    warrior->base.attack = warrior_attack;
}

void mage_init(Mage *mage, const char *name,
               int health, int level, int mana) {
    character_init(&mage->base, name, health, level);

    mage->mana = mana;

    mage->base.attack = mage_attack;
}

/* ============================================================
   MAIN
   ============================================================ */

int main(void) {

    /* Create a basic Character */
    Character character;
    character_init(&character, "Alex", 100, 1);

    /* Create a Warrior */
    Warrior warrior;
    warrior_init(&warrior, "Thorin", 120, 5, 20);

    /* Create a Mage */
    Mage mage;
    mage_init(&mage, "Gandalf", 80, 5, 100);

    printf("=== Individual Attacks ===\n");

    character.attack(&character);
    warrior.base.attack((Character *)&warrior);
    mage.base.attack((Character *)&mage);

    printf("\n=== Taking Damage ===\n");

    character.take_damage(&character, 20);
    warrior.base.take_damage((Character *)&warrior, 30);
    mage.base.take_damage((Character *)&mage, 15);

    printf("\n=== Polymorphism Test ===\n");

    Character *characters[3];

    characters[0] = &character;
    characters[1] = (Character *)&warrior;
    characters[2] = (Character *)&mage;

    for (int i = 0; i < 3; i++) {
        characters[i]->attack(characters[i]);
    }

    return 0;
}