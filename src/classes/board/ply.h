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
                return this->dep == p.dep
                        && this->stop == p.stop
                        && this->promote == p.promote
                        && this->prom == p.prom;
            } else {
                return false;
            }
        }

        std::string toString () {
            std::string res = this->dep.row + std::to_string(this->dep.line);
            res += this->stop.row + std::to_string(this->stop.line);
            if (this->promote)
                res += this->prom;
            return res;
        }

        Square dep;
        Square stop;
        bool promote = false;
        char prom;
        bool is_init = true;
};