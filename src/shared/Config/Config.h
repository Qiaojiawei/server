/*
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 * Copyright (C) 2009-2011 MaNGOSZero <https://github.com/mangos/zero>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "Common.h"
#include <ace/Recursive_Thread_Mutex.h>
#include <ace/Singleton.h>
#include "Platform/Define.h"
#include "ace/Configuration_Import_Export.h"

class ACE_Configuration_Heap;

class MANGOS_DLL_SPEC Config
{
    friend class ACE_Singleton<Config, ACE_Recursive_Thread_Mutex>;
    public:

        Config();
        ~Config();

        bool SetSource(const char *file);
        bool Reload();

        std::string GetStringDefault(const char* name, const char* def);
        bool GetBoolDefault(const char* name, const bool def = false);
        int32 GetIntDefault(const char* name, const int32 def);
        float GetFloatDefault(const char* name, const float def);

        std::string GetFilename() const { return mFilename; }
        bool GetValueHelper(const char* name, ACE_TString &result);

    private:

        std::string mFilename;
        ACE_Configuration_Heap *mConf;

        typedef ACE_Thread_Mutex LockType;
        typedef ACE_Guard<LockType> GuardType;

        std::string _filename;
        LockType m_configLock;
};

// Nostalrius : multithreading lock
#define sConfig (*ACE_Singleton<Config, ACE_Recursive_Thread_Mutex>::instance())

#endif
