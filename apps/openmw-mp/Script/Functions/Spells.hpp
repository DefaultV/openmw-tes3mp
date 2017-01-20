#ifndef OPENMW_SPELLS_HPP
#define OPENMW_SPELLS_HPP

#define SPELLAPI \
    {"GetSpellbookSize", SpellFunctions::GetSpellbookSize},\
    \
    {"AddSpell",         SpellFunctions::AddSpell},\
    {"RemoveSpell",      SpellFunctions::RemoveSpell},\
    {"ClearSpellbook",   SpellFunctions::ClearSpellbook},\
    \
    {"GetSpellId",       SpellFunctions::GetSpellId},\
    \
    {"SendSpells",       SpellFunctions::SendSpells}

class SpellFunctions
{
public:

    static unsigned int GetSpellbookSize(unsigned short pid) noexcept;

    static void AddSpell(unsigned short pid, const char* spellId) noexcept;
    static void RemoveSpell(unsigned short pid, const char* spellId) noexcept;
    static void ClearSpellbook(unsigned short pid) noexcept;

    static const char *GetSpellId(unsigned short pid, unsigned int i) noexcept;

    static void SendSpells(unsigned short pid) noexcept;
private:

};

#endif //OPENMW_SPELLS_HPP