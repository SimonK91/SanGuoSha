#include "CardList.h"
#include "GameCard.h"
#include "HeroCard.h"
	
#include <algorithm>
#include <chrono>
#include <stdexcept>

namespace Object
{
  
  CardList::CardList(const std::string& setting)
  {
    image = loadImage("Images/Cards/back.png", true);
    if(setting == "empty")
      {
	//do nothing 
      }
    else if(setting == "standard_playing_cards")
      loadCardDeck();
    else if(setting == "hero_deck")
      loadHeroDeck();
    else
      throw std::runtime_error("no such deck type as: " + setting);
  }
  
  CardList::~CardList()
  {
    while(!set.empty())
      {
	delete set.back();
	set.pop_back();
      }
  }
  
  Card* CardList::drawCard()
  {
    if(empty())
      throw SGS_error("CardDeck is empty and cannot draw a card");
    Card* c = set.front();
    set.front() = nullptr; //peka bort så att vi inte tar bort c ^^
    set.erase(set.begin());
    return c;
  }
  
  bool CardList::empty()
  {
    return set.empty();
  }
  void CardList::pushBottom(Card* card)
  {
    set.push_back(card);
    card = nullptr;
  }
  
  void CardList::pushTop(Card* card)
  {
    set.insert(set.begin(), card);
    card = nullptr; 
  }
  
  void CardList::shuffle(unsigned leSeed)
  {
    if(leSeed == 0)
      seed = std::chrono::system_clock::now().time_since_epoch().count();
    else
      seed = leSeed;
    
    std::shuffle (set.begin(), set.end(), std::default_random_engine(seed));
  }

  


// <maxHP> <clan> <male> <abilities>
  void CardList::loadHeroDeck()
  {
    //lägger 3 emparors först för att underlätta grejer :)
    set.push_back(new HeroCard("CaoCao.png", "4 blue 1 CaoCao ability"));
    set.push_back(new HeroCard("LiuBei.png", "4 red 1 LiuBei ability"));
    set.push_back(new HeroCard("SunQuan.png", "4 green 1 SunQuan ability"));
    //resten
    set.push_back(new HeroCard("DaQiao.png", "3 green 0 DaQiao ability"));
    set.push_back(new HeroCard("DiaoChan.png", "3 gray 0 DiaoChan ability"));
    set.push_back(new HeroCard("ElderZhuge.png", "3 red 1 ElderZhuge ability"));
    set.push_back(new HeroCard("GanNing.png", "4 green 1 GanNing ability"));
    set.push_back(new HeroCard("GuanYu.png", "4 red 1 GuanYu ability"));
    set.push_back(new HeroCard("GuoJia.png", "3 blue 1 GuoJia ability"));
    set.push_back(new HeroCard("HuangGai.png", "4 green 1 HuangGai ability"));
    set.push_back(new HeroCard("HuangYueYing.png", "3 red 0 HuangYueYing ability"));
    set.push_back(new HeroCard("HuaTuo.png", "3 gray 1 HuaTuo ability"));
    set.push_back(new HeroCard("LuBu.png", "4 gray 1 LuBu ability"));
    set.push_back(new HeroCard("LuMeng.png", "4 green 1 LuMeng ability"));
    set.push_back(new HeroCard("LuXun.png", "3 green 1 LuXun ability"));
    set.push_back(new HeroCard("MaChao.png", "4 red 1 MaChao ability"));
    set.push_back(new HeroCard("SiMaYi.png", "3 blue 1 SiMaYi ability"));
    set.push_back(new HeroCard("SunShangXiang.png", "3 green 0 SunShangXiang ability"));
    set.push_back(new HeroCard("XiaHouDun.png", "4 blue 1 XiaHouDun ability"));
    set.push_back(new HeroCard("XuChu.png", "4 blue 1 XuChu ability"));
    set.push_back(new HeroCard("ZhangFei.png", "4 red 1 ZhangFei ability"));
    set.push_back(new HeroCard("ZhangLiao.png", "4 blue 1 ZhangLiao ability"));
    set.push_back(new HeroCard("ZhaoYun.png", "4 red 1 ZhaoYun ability"));
    set.push_back(new HeroCard("ZhenJi.png", "3 blue 0 ZhenJi ability"));
    set.push_back(new HeroCard("ZhouYu.png", "3 green 1 ZhouYu ability"));
  }
  
  void CardList::loadCardDeck()
  {
    //attackses
    // 1 = targettable, 10 = weapon range
    set.push_back(new GameCard(7,spades,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(8,spades,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(9,spades,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(10,spades,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(8,spades,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(9,spades,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(10,spades,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(13,diamonds,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(6,diamonds,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(7,diamonds,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(8,diamonds,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(9,diamonds,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(10,diamonds,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(10,hearts,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(10,hearts,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(11,hearts,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(8,clubs,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(9,clubs,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(10,clubs,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(11,clubs,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(2,clubs,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(3,clubs,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(4,clubs,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(5,clubs,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(6,clubs,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(7,clubs,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(8,clubs,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(9,clubs,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(10,clubs,"attack.png","attack 1 10")); //ability id, target type, target range
    set.push_back(new GameCard(11,clubs,"attack.png","attack 1 10")); //ability id, target type, target range
    
    //dodges
    //0 = self/instant, 0 = no range
    set.push_back(new GameCard(2, diamonds, "dodge.png","dodge 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(3, diamonds, "dodge.png","dodge 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(4, diamonds, "dodge.png","dodge 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(5, diamonds, "dodge.png","dodge 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(6, diamonds, "dodge.png","dodge 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(7, diamonds, "dodge.png","dodge 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(8, diamonds, "dodge.png","dodge 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(9, diamonds, "dodge.png","dodge 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(10,diamonds, "dodge.png","dodge 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(11,diamonds, "dodge.png","dodge 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(11,diamonds, "dodge.png","dodge 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(2, diamonds, "dodge.png","dodge 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(2, hearts,   "dodge.png","dodge 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(13,hearts,   "dodge.png","dodge 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(2, hearts,   "dodge.png","dodge 0 0")); //ability id, target type, target range    
    //peaches
    //0 = self-instant, 0 = no range
    set.push_back(new GameCard(3,hearts,"peach.png","heal 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(9,hearts,"peach.png","heal 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(8,hearts,"peach.png","heal 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(7,hearts,"peach.png","heal 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(6,hearts,"peach.png","heal 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(12,hearts,"peach.png","heal 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(12,diamonds,"peach.png","heal 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(4,hearts,"peach.png","heal 0 0")); //ability id, target type, target range
        //horses
    // 5 = equipment, 0 = no range
    set.push_back(new GameCard(13,spades,"da_wan.png","off_horse 5 0")); //ability id, target type, target range
    set.push_back(new GameCard(5,hearts,"chi_tu.png","off_horse 5 0")); //ability id, target type, target range
    set.push_back(new GameCard(13,diamonds,"zi_xin.png","off_horse 5 0")); //ability id, target type, target range
    set.push_back(new GameCard(5,spades,"jue_ying.png","def_horse 5 0")); //ability id, target type, target range
    set.push_back(new GameCard(5,clubs,"di_lu.png","def_horse 5 0")); //ability id, target type, target range
    set.push_back(new GameCard(13,hearts,"zhua_huang.png","def_horse 5 0")); //ability id, target type, target range
    
    //weaponzies and shieldzes
    //
    set.push_back(new GameCard(6,spades,"blue_steel_blade.png",   			"weapon0 5 2")); //ability id, target type, target range
    set.push_back(new GameCard(2,spades,"double_gender_sword.png",			"weapon1 5 2")); //ability id, target type, target range
    set.push_back(new GameCard(5,spades,"green_dragon_cresent_blade.png",	"weapon2 5 3")); //ability id, target type, target range
    set.push_back(new GameCard(12,spades,"serpent_halberd.png",				"weapon3 5 3")); //ability id, target type, target range
    set.push_back(new GameCard(5,hearts,"unicorn_bow.png",					"weapon4 5 5")); //ability id, target type, target range
    set.push_back(new GameCard(1,clubs,"zhuge_crossbow.png",				"weapon5 5 1")); //ability id, target type, target range
    set.push_back(new GameCard(1,diamonds,"zhuge_crossbow.png",				"weapon5 5 1")); //ability id, target type, target range
    set.push_back(new GameCard(5,diamonds,"rock_cleaving_axe.png",			"weapon6 5 3")); //ability id, target type, target range
    set.push_back(new GameCard(12,diamonds,"Heaven_Scorcher_Halberd.png",	"weapon7 5 4")); //ability id, target type, target range
    set.push_back(new GameCard(2,spades,"frost_blade.png",					"weapon8 5 2")); //ability id, target type, target range
    set.push_back(new GameCard(2,spades,"ba_gua_shield.png",				"shield0 5 0")); //ability id, target type, target range
    set.push_back(new GameCard(2,clubs,"ba_gua_shield.png",					"shield0 5 0")); //ability id, target type, target range
    set.push_back(new GameCard(2,clubs,"ren_wang_shield.png",				"shield1 5 0")); //ability id, target type, target range
    
    //toolcardses
    // 0
    set.push_back(new GameCard(12,diamonds,"negate.png","negate 3 0")); //ability id, target type, target range
    set.push_back(new GameCard(13,clubs,"negate.png","negate 3 0")); //ability id, target type, target range
    set.push_back(new GameCard(12,clubs,"negate.png","negate 3 0")); //ability id, target type, target range
    set.push_back(new GameCard(11,spades,"negate.png","negate 3 0")); //ability id, target type, target range
    set.push_back(new GameCard(1,spades,"duel.png","duel 1 0")); //ability id, target type, target range
    set.push_back(new GameCard(1,clubs,"duel.png","duel 1 0")); //ability id, target type, target range
    set.push_back(new GameCard(1,diamonds,"duel.png","duel 1 0")); //ability id, target type, target range
    set.push_back(new GameCard(1,hearts,"peach_garden.png","peach_garden 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(9,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(8,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(7,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(12,hearts,"lightning.png","lightning 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(1,clubs,"lightning.png","lightning 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(1,hearts,"raining_arrows.png","raining_arrows 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(4,hearts,"harvest.png","harvest 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(3,hearts,"harvest.png","harvest 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(13,clubs,"duress.png","duress 3 0")); //ability id, target type, target range
    set.push_back(new GameCard(12,clubs,"duress.png","duress 3 0")); //ability id, target type, target range
    set.push_back(new GameCard(4,diamonds,"steal.png","steal 1 1")); //ability id, target type, target range
    set.push_back(new GameCard(3,diamonds,"steal.png","steal 1 1")); //ability id, target type, target range
    set.push_back(new GameCard(11,spades,"steal.png","steal 1 1")); //ability id, target type, target range
    set.push_back(new GameCard(4,spades,"steal.png","steal 1 1")); //ability id, target type, target range
    set.push_back(new GameCard(3,spades,"steal.png","steal 1 1")); //ability id, target type, target range
    set.push_back(new GameCard(13,spades,"barbarian.png","barbarian 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(7,clubs,"barbarian.png","barbarian 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(7,spades,"barbarian.png","barbarian 0 0")); //ability id, target type, target range
    set.push_back(new GameCard(6,hearts,"acedia.png","acedia 2 0")); //ability id, target type, target range
    set.push_back(new GameCard(6,clubs,"acedia.png","acedia 2 0")); //ability id, target type, target range
    set.push_back(new GameCard(6,spades,"acedia.png","acedia 2 0")); //ability id, target type, target range
    set.push_back(new GameCard(12,hearts,"dismantle.png","dismantle 1 0")); //ability id, target type, target range
    set.push_back(new GameCard(12,spades,"dismantle.png","dismantle 1 0")); //ability id, target type, target range
    set.push_back(new GameCard(3,clubs,"dismantle.png","dismantle 1 0")); //ability id, target type, target range
    set.push_back(new GameCard(4,clubs,"dismantle.png","dismantle 1 0")); //ability id, target type, target range
    set.push_back(new GameCard(3,spades,"dismantle.png","dismantle 1 0")); //ability id, target type, target range
    set.push_back(new GameCard(4,spades,"dismantle.png","dismantle 1 0")); //ability id, target type, target range    
  }  
} //namespace
