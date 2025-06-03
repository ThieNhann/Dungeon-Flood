#ifndef BOOST_H
#define BOOST_H

#include "raylib.h"
#include "Player.h"
#include <typeinfo>
#include "Config.h"

class Boost {
protected:
    float duration;
public:
    virtual ~Boost() {}
    void SetDuration(float d) {
        duration = d;
    }
    float GetDuration() {
        return duration;
    }
    virtual void Apply(Player& p) = 0;
    virtual void OnStart(Player& p) = 0;
    virtual void OnEnd(Player& p) = 0;
};

class FireSpeedBoostEffect : public Boost {
private:
    float originalCooldown;
public:
    FireSpeedBoostEffect() { duration = BOOST_DURATION; }
    void OnStart(Player& p) {
        originalCooldown = p.GetFireCooldown();
        p.SetFireCooldown(FIRESPEEDBOOST_COOLDOWN_FACTOR * originalCooldown);
    }
    void Apply(Player& p) {}
    void OnEnd(Player& p) {
        p.SetFireCooldown(originalCooldown);
    }
};

class MultishotEffect : public Boost {
private:
    float originalCooldown;
public:
    MultishotEffect() { duration = BOOST_DURATION; }
    void OnStart(Player& p) {
        p.SetMultishotMode(true);
    }
    void Apply(Player& p) {}
    void OnEnd(Player& p) {
        p.SetMultishotMode(false);
    }
};

class PiercingEffect : public Boost {
private:
    float originalCooldown;
public:
    PiercingEffect() { duration = BOOST_DURATION; }
    void OnStart(Player& p) {
        p.SetPiercingMode(true);
    }
    void Apply(Player& p) {}
    void OnEnd(Player& p) {
        p.SetPiercingMode(false);
    }
};

class BoostManager {
public:
    static std::vector<Boost*> boosts;
public:
    static void AddBoost(Boost* b, Player& p) {
        b->OnStart(p);
        boosts.push_back(b);
    }
    static void Update(Player& p) {
        for (auto it = boosts.begin(); it != boosts.end(); ) {
            (*it)->SetDuration((*it)->GetDuration() - GetFrameTime());
            (*it)->Apply(p);
            if ((*it)->GetDuration() <= 0) {
                (*it)->OnEnd(p);
                delete *it;
                it = boosts.erase(it);
            } else {
                ++it;
            }
        }
    }
    static void Destruct() {
        for (auto& b : boosts) {
            delete b;
        }
        boosts.clear();
    }
};

#endif