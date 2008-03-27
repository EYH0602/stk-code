//  $Id: challenge.hpp 1259 2007-09-24 12:28:19Z hiker $
//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2008 Joerg Henrichs
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_CHALLENGE_H
#define HEADER_CHALLENGE_H

#include <string>
#include <vector>

#include "lisp/lisp.hpp"
#include "lisp/parser.hpp"
#include "lisp/writer.hpp"


// A base class for all challenges
class Challenge
{
    enum {CH_INACTIVE,                 // challenge not yet possible
          CH_ACTIVE,                   // challenge possible, but not yet solved
          CH_SOLVED}         m_state;  // challenge was solved
    std::string              m_Id;                    // short, internal name for this challenge
    std::string              m_Name;                  // name used in menu for this challenge
    std::string              m_Description;           // description
    std::string              m_feature_description;   // Description of feature to unlock
    std::string              m_feature;               // Feature to unlock
    std::vector<std::string> m_prerequisites; 
public:
             Challenge(std::string id, std::string name);
    virtual ~Challenge() {};
    const std::string& getId() const             {return m_Id;                  }
    const std::string& getName() const           {return m_Name;                }
    void  setFeatureDescription(const std::string& f) 
                                                 {m_feature_description=f;      }
    const std::string&
          getFeatureDescription() const          {return m_feature_description; }
    void  setFeature(const std::string& s)       {m_feature=s;                  }
    const std::string& getFeature() const        {return m_feature;             }
    void  setChallengeDescription(const std::string& d) 
                                                 {m_Description=d;              }
    const std::string& 
          getChallengeDescription() const        {return m_Description;         }
    void  addDependency(const std::string id)    {m_prerequisites.push_back(id);}
    bool  isSolved() const                       {return m_state==CH_SOLVED;    }
    bool  isActive() const                       {return m_state==CH_ACTIVE;    }
    void  setSolved()                            {m_state = CH_SOLVED;          }
    void  setActive()                            {m_state = CH_ACTIVE;          }
    const std::vector<std::string>& 
          getPrerequisites() const               {return m_prerequisites;       }
    void  load(const lisp::Lisp* config);
    void  save(lisp::Writer* writer);

    // These functions are meant for customisation, e.g. load/save
    // additional state information specific to the challenge
    virtual void loadState(const lisp::Lisp* config) {};
    virtual void saveState(lisp::Writer* writer)     {};

    // These functions are called when a race/gp is finished. It allows
    // the challenge to unlock features (when returning true), otherwise
    // the feature remains locked.
    virtual bool raceFinished()                      {return false;}   // end of a race
    virtual bool grandPrixFinished()                 {return false;}   // end of a GP
};
#endif
