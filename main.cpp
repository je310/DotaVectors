
#include <iostream>
#include "csv.h"
class creep{
public:
    std::string name;
    int xp;
    int gold;
    int hp;
    
    int mg();
    int me();
    

    
};

enum PRIat{
    strength,
   agility,
    intelegence
};

class hero{
public:
    std::string name;
    PRIat PRI;
    int level;
    double STR,STRp,AGI,AGIp,INT,INTp;
    double T,Tp,LVL25,MOV,AR,DMGmin,DMGmax,RG,BAT,ATKPT,ATKBS,VSminD,VSminN,TR,COL,HPs,L;

    // return the armour at a particular level, depends on agility.
    float ARatLvl (int level){
        return AR + ((level * AGIp)+ AGI) * (1/7);
    }

    // return the attack speet at a particular level, depends on agility.
    float attackSpeed(int level){
        float bonus = 0.01 * (AGI + level*AGIp);
        return BAT + bonus;
    }

    // return the health of a hero at a particular level, depends on strength
    float health(int level){
        return 200 + 20*(STR + STRp* level);
    }

    // returns the attack damage at a particular level. Depends on the primary attribute of teh hero.
    float AttackDmg(int level = 1){
        float bonus;
        switch (PRI){
        case agility:
            bonus = AGI + level*AGIp;
            break;
        case strength:
            bonus = STR + level*STRp;
            break;
        case intelegence:
            bonus = INT + level*INTp;
            break;
        }
        return 0.5*(DMGmax + DMGmin) + bonus;
    }

    float timeToKill(hero enemy, int level = 1){
        float enemyArmour = enemy.ARatLvl(level);
        float armourMult = 1 - 0.06 * enemyArmour / (1 + 0.06 * fabs(enemyArmour));
        float attackDmg = AttackDmg(level);
        attackDmg *= armourMult;
        float healPerAttack = enemy.HPs * attackSpeed(level);
        float totalDmg = attackDmg - healPerAttack;
        float numberOfAttacksNeeded = enemy.health(level) / totalDmg;
        return numberOfAttacksNeeded*attackSpeed(level);

    }
    

        
    
};


std::string bmg(creep one, creep two);
std::string bme(creep one, creep two);

int main(int argc, const char * argv[]) {
    
    // Here we declare the object that reads the CSV (comma seperated variable) file. Don't worry too much about how it works!
    io::CSVReader<25> in("/home/josh/dota_code/dotaStats.csv");       // change the number in <> to the number of atributes you are reading
    in.read_header(io::ignore_extra_column, "A","PRI","STR","STR+","AGI","AGI+","INT","INT+","T","T+","LVL25","MOV","AR","DMG(MIN)","DMG(MAX)","RG","BAT","ATKPT","ATKBS","VS-D","VS-N","TR","COL","HP/S","L");     // "attribute" should match the first line in the csv file

    // Declare some variables to temperarily store the atributes of a hero when we are scrolling through the CSV file.
    std::string A,PRI;
    double STR,STRp,AGI,AGIp,INT,INTp,T,Tp,LVL25,MOV,AR,DMGmin,DMGmax,RG,BAT,ATKPT,ATKBS,VSminD,VSminN,TR,COL,HPs,L;

    // Declare a vector of heros. This is the key part of the lesson! A vector is just a list of variables, you can then use this list as a way of refering to all of its contents.
    // The vector starts emptly (there are no heros in the list). You can then add them one at a time using the heros.push_back(HeroToAdd) function. Each time you use this function
    // the vector gets one longer.
    std::vector<hero> heros;
    while(in.read_row(A,PRI,STR,STRp,AGI,AGIp,INT,INTp,T,Tp,LVL25,MOV,AR,DMGmin,DMGmax,RG,BAT,ATKPT,ATKBS,VSminD,VSminN,TR,COL,HPs,L)){ //in.readrow is collecting the next line and saveing the values to the varibles.
        //assign the variables read from the CSV file to a new hero. Notice we reuse the 'newHero' many times, each time we go around the while loop. I changed the definition of the hero class (look near the top of the file)
        // to have all of the variables that are in the file.
        hero newHero;
        newHero.name = A;

        newHero.STR = STR;
        newHero.STRp = STRp;
        newHero.AGI = AGI;
        newHero.AGIp = AGIp;
        newHero.INT = INT;
        newHero.INTp = INTp;
        newHero.T = T;
        newHero.Tp = Tp;
        newHero.LVL25 = LVL25;
        newHero.MOV = MOV;
        newHero.AR = AR;
        newHero.DMGmin = DMGmin;
        newHero.DMGmax = DMGmax;
        newHero.RG = RG;
        newHero.BAT = BAT;
        newHero.ATKPT = ATKPT;
        newHero.ATKBS = ATKBS;
        newHero.VSminD = VSminD;
        newHero.VSminN = VSminN;
        newHero.TR = TR;
        newHero.COL = COL;
        newHero.HPs = HPs;
        newHero.L = L ;
        // due to the fact that the primary attribute is not a 'number' we need some if statements to assign it. (I assign it an enumeration or enum for short, which is equivelent to saying
        // that strength = 0, agility = 1, intelegence = 2. This is defined near the top of the file.
        if(PRI.compare("strength")) newHero.PRI = strength;
        if(PRI.compare("agility")) newHero.PRI = agility;
        if(PRI.compare("intelegence")) newHero.PRI = intelegence;

        //now we have a new hero populated with all the information we need we can add him/her to the list of all heros so far!
        heros.push_back(newHero);
    }
    //When we get here the heros vector contains all the heros in the game. Understanding the vector stuff above will be usefull but it is not critical. You can instead just
    // believe that heros is a list of all heros with all attributs assigned to the heros. Lets try it out.

    std::cout << "The first hero in the list is " << heros[0].name << " they  have a Hp regeneration of " << heros[0].HPs << std::endl;

    //I picked 2 heros at random, number 4 and number 5, which is stronger at level 1 and level25;
    if(heros[4].STR > heros[5].STR) std::cout << heros[4].name << " is stronger than " << heros[5].name << " (at lvl 1!)" << std::endl;
    else std::cout << heros[5].name << " is stronger than " << heros[4].name << " (at lvl 1!)" << std::endl;


    if(heros[4].STR + heros[4].STRp *  25 > heros[5].STR + heros[5].STRp *  25) std::cout << heros[4].name << " is stronger than " << heros[5].name << " (at lvl 25!)" << std::endl;
    else std::cout << heros[5].name << " is stronger than " << heros[4].name << " (at lvl 25!)" << std::endl;

    // Can you see the power of using a vector? Think about how we were doing things with the creeps. (below) . Each creep needed a variable (golem or centaur in this case)
    // To do this for all creeps would mean we would have to have lots of variables that we could not refer to efficiently in a loop. With the heros (above) we can refer to them by their
    // position in the list. We do not care about thier names until we want to print out to the user, so hero 5 is 'Axe', but in the software we can just use heros[5]. (continue below the creep code)


    creep golem;
    golem.name = "golem";
    golem.xp = 42;
    golem.gold = 32;
    golem.hp = 800;

    creep centaur;
    centaur.name = "centaur";
    centaur.xp = 119;
    centaur.hp = 1100;
    centaur.gold = 72;

    // If we want to use the power of programming to solve a problem we can use the vector with loops to solve things in very few lines of code.

    // Here is a fun quiz for your dota knowledge :P

    // Who is the fastest hero (movement speed)

    float fastestMovement = 0; // variable for holding the current fastest.
    int heroNum = 0; // variable for holding the current winner of the fastest hero competition.

    for (int i  = 0; i  < heros.size(); i++ ){
        if(heros[i].MOV > fastestMovement){     //if this hero has a faster movement speed than the best up till now, update our fastest hero.
            fastestMovement = heros[i].MOV;
            heroNum = i ;                       // save the number that corresponds the the hero so we can use this to find out more details about them if needed. (like their name)
        }
    }

    //uncomment next line to print the answer!
    //std::cout << "The fastest hero in Dota is " << heros[heroNum].name << " with a move speed of " << heros[heroNum].MOV << std::endl;
    
    //using the code below we can find the time for a hero to kill another!
    int hero1 = 35;
    int hero2 = 24;
    int atLevel =10;
    //uncomment to find the result of the fight.
    //std::cout << "it takes " << heros[hero1].timeToKill(heros[hero2],atLevel) << " seconds for " << heros[hero1].name << " to kill " << heros[hero2].name << " at level " << atLevel<< std::endl;
    

    //because we are using vecors to hold the heros we can make powerfull loops to check more complicated things.
    // here we are using 2 for loops inside each other (the same way we searched all the pixels in the thermal image) to check all matches between all heros!
    // If the match is shorter than the shortest match we save the heros involved, if it is longer than the longest match we also save. Uncomment the cout lines below for the answers.
    float fastestKill = 1000000;
    float slowestKill = 0;
    int fastAttacker = 0;
    int fastDefender = 0;
    int slowAttacker = 0;
    int slowDefender = 0;
    
    for (int i  = 0; i  < heros.size(); i++ ){
        for (int j  = 0; j  < heros.size(); j++ ){
            if(heros[i].timeToKill(heros[j],atLevel)  < fastestKill){
                fastestKill = heros[i].timeToKill(heros[j],atLevel);
                fastAttacker = i;
                fastDefender = j;
            }
            if(heros[i].timeToKill(heros[j],atLevel) > slowestKill){
                slowestKill = heros[i].timeToKill(heros[j],atLevel);
                slowAttacker = i;
                slowDefender = j;
            }
        }
    }

    //uncomment for answers to the quickest / slowest fights.
//    std::cout << "At level " << atLevel << " the shortest fight is " << heros[fastAttacker].name << " attacking " << heros[fastDefender].name << " which takes " << fastestKill << "s" << std::endl;
//    std::cout << "At level " << atLevel << " the longest fight is " << heros[slowAttacker].name << " attacking " << heros[slowDefender].name << " which takes " << slowestKill << "s" << std::endl;


    //reset our variables.
    fastestKill = 1000000;
    slowestKill = 0;
    int fastLevel =0;
    int slowLevel =0;
    //we can even make an extra loop to try all levels!
    for (int k = 1 ; k <= 25; k ++ ){
        for (int i  = 0; i  < heros.size(); i++ ){
            for (int j  = 0; j  < heros.size(); j++ ){
                if(heros[i].timeToKill(heros[j],k)  < fastestKill){
                    fastestKill = heros[i].timeToKill(heros[j],k);
                    fastAttacker = i;
                    fastDefender = j;
                    fastLevel = k;
                }
                if(heros[i].timeToKill(heros[j],k) > slowestKill){
                    slowestKill = heros[i].timeToKill(heros[j],k);
                    slowAttacker = i;
                    slowDefender = j;
                    slowLevel = k ;
                }
            }
        }
    }

      //uncomment to find out the longest and shortest possible fights.
//    std::cout <<"the shortest possible right click fight is between " << heros[fastAttacker].name << " and " << heros[fastDefender].name << " at level " << fastLevel << " lasting " << fastestKill << "s" << std::endl;
//    std::cout <<"the longest possible right click fight is between " << heros[slowAttacker].name << " and " << heros[slowDefender].name << " at level " << slowLevel << " lasting " << slowestKill << "s" << std::endl;

    //uncomment to find how many fights we checked
    //std::cout << "We have checked " << 25 * heros.size() * heros.size() << " combinations of battle in only ~ 20 lines of code!" << std::endl;
}

int creep::mg(){
    return 220;
}

int creep::me(){
    return xp * 1.75;
}

std::string bmg(creep one, creep two){
    return(one.gold < two.gold ? one.name:two.name);
    
}

std::string bme(creep one, creep two){
    return(one.xp > two.xp ? one.name:two.name);
}







