#ifndef GUARD_MAIL_H
#define GUARD_MAIL_H

enum MailID
{
    ORANGE_MAIL,
    HARBOR_MAIL,
    GLITTER_MAIL,
    MECH_MAIL,
    WOOD_MAIL,
    WAVE_MAIL,
    BEAD_MAIL,
    SHADOW_MAIL,
    TROPIC_MAIL,
    DREAM_MAIL,
    FAB_MAIL,
    RETRO_MAIL,
    NUM_MAILS
};

// mail.h
void ReadMail(struct Mail *mail, void (*exitCallback)(void), bool8 hasText);

// mail_data.h
void ClearAllMail(void);
void ClearMail(struct Mail *mail);
bool8 MonHasMail(struct Pokemon *mon);
u8 GiveMailToMonByItemId(struct Pokemon *mon, u16 itemId);
u16 SpeciesToMailSpecies(u16 species, u32 personality);
u16 MailSpeciesToSpecies(u16 mailSpecies, u16 *buffer);
u8 GiveMailToMon(struct Pokemon *mon, struct Mail *mail);
void TakeMailFromMon(struct Pokemon *mon);
void ClearMailItemId(u8 mailId);
u8 TakeMailFromMonAndSave(struct Pokemon *mon);

#endif // GUARD_MAIL_H
