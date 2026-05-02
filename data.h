#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>

struct Akun {
    int ID;
    string Username;
    string Password;
    string Role;
};

const string PLANT_CLASS[]   = {"guardian","kabloom","mega-grow","smarty","solar"};
const string ZOMBIE_CLASS[]  = {"beastly","brainy","crazy","hearty","sneaky"};
const string CATEGORY[]      = {"fighter","trick","environment"};
const string RARITY[]        = {"common","uncommon","rare","super-rare","legendary","event"};
const string CARD_SET[]      = {"none","premium","galactic","colossal","triassic"};
const string PLANT_TRIBES[]  = {"bean","mushroom","pea","leafy","nut","flower","berry",
                                 "root","animal","cactus","corn","dragon","flytrap",
                                 "fruit","mime","moss","pinecone","seed","squash","tree"};
const string ZOMBIE_TRIBES[] = {"imp","pirate","dancing","science","gargantuar",
                                 "mustache","sports","gourmet","professional","pet",
                                 "history","barrel","mime","monster","party"};
const string PLANT_TRAITS[]  = {"double-strike","team-up"};
const string ZOMBIE_TRAITS[] = {"deadly","frenzy","gravestone","overshoot"};
const string GLOBAL_TRAITS[] = {"amphibious","anti-hero","armored","bullseye","hunt",
                                  "splash","strikethrough","untrickable"};
const string EFFECTS[]       = {"bonus-attack","bounce","conjure","destroy", "dino-roar", "draw",
                                  "evolution", "freeze", "fusion","heal","make","move","shield","shuffle","transform"};

struct CardTags {
    vector <string> tribes;
    vector<string> traits;
    vector<string> effects;
    string desc;
};

struct Card {
    int      id;
    string   name;
    string   team;        
    string   cardClass;   
    string   category;    
    int      cost;
    int      strength;    
    string   rarity;
    string   cardSet;     
    CardTags tags;
};

extern vector<Akun> List_Akun;
extern bool Menu_Login;
extern string Input_Username;
extern string Input_Pw;
extern int Pilihan_Login;

#endif