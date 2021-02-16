#pragma once
#include "square.h"

class Ply {
    public :
        Ply () {
            this->is_init = false;
        };

        Ply (Square s1, Square s2) {
            this->dep = s1;
            this->stop = s2;
        };

        Ply (Square s1, Square s2, bool promote, char prom) {
            this->dep = s1;
            this->stop = s2;
            this->promote = promote;
            this->prom = prom;
        };

        bool operator== (Ply p) {
            if (this->is_init && p.is_init) {

                if (this->promote && p.promote) {
                    return this->dep == p.dep
                            && this->stop == p.stop
                            && this->promote == p.promote
                            && this->prom == p.prom;
                } else {
                    return this->dep == p.dep && this->stop == p.stop;
                }
            } else {
                return false;
            }
        }

        bool operator== (std::string p) {
            return this->toString() == p;
        }

        std::string toString () {
            std::string res = this->dep.toString() + this->stop.toString();
            if (this->promote)
                res += std::string(1, this->prom);
            return res;
        }

        Square dep;
        Square stop;
        bool promote = false;
        char prom;
        bool is_init = true;
};