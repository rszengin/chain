//============================================================================
// Name        : main.cpp
// Author      : Rahman Salim Zengin
// Version     :
// Copyright   : rsz@gufatek.com
// Description :
//============================================================================

#include <iostream>
#include <vector>
#include "chain.hpp"
using namespace std;

int main() {

	for (int inx = 0; inx < 20; ++inx) {
		if (cmp::chain < 5 < inx < 15)
			std::cout << inx << " ";

		if ((5 < inx) && (inx < 15))
			std::cout << inx << " ";
	}
	std::cout << std::endl;

	std::vector<std::string> words { "aback", "abaft", "abandon", "abandoned",
			"abandonment", "abase", "abash", "abashment", "abate", "abatement",
			"abbey", "abbreviate", "abbreviatio", "abdicate", "abdomen",
			"abduct", "abduction", "abecedarian", "aberrant", "aberrated",
			"aberration", "aberrationa", "abet", "abetment", "abettor",
			"abeyance", "abhor", "abhorrence", "abhorrent", "abidance", "abide",
			"abiding", "ability", "abject", "abjection", "abjectly", "abjure",
			"ablaze", "able", "ably", "abnegate", "abnegation", "abnormal",
			"abnormality", "abode", "aboil", "abolish", "abolishment",
			"abolition", "abominable", "abominate", "abomination", "aboriginal",
			"aborigine", "aborning", "abort", "abortion", "abortive", "abound",
			"abounding", "about", "above", "abracadabra", "abrade", "abrasion",
			"abrasive", "abreast", "abridge", "abridgment", "abrogate",
			"abrogation", "abrupt", "abruptly", "abscond", "absence", "absent",
			"absentminde", "absolute", "absolutenes", "absolution",
			"absolutism", "absolve", "absorb", "absorbed", "absorbent",
			"absorbing", "absorption", "abstain", "abstainer", "abstemious",
			"abstentious", "abstinence", "abstinent", "abstract", "abstracted",
			"abstraction", "abstruse", "absurd", "absurdity", "abubble",
			"abundance", "abundant", "abuse", "abusive", "abut", "abutting",
			"abuzz", "abysm", "abysmal", "abyss", "academe", "academic",
			"academy", "accede", "accelerate", "accent", "accentuate",
			"accentuation", "accept", "acceptability", "acceptable",
			"acceptably", "access", "accessible", "accession", "accessorial",
			"accessory", "accident", "accidental", "acclaim", "acclamation",
			"acclimate", "acclimation", "acclimatization", "acclimatize",
			"acclivity", "accolade", "accommodate", "accommodating",
			"accommodation", "accommodative", "accompaniment", "accompany",
			"accompanying", "accomplice", "accomplish", "accomplished",
			"accomplishment", "accord", "accordance", "accordant",
			"accordingly", "accouchement", "account", "accountable",
			"accounting", "accoutre", "accoutrement", "accredit",
			"accreditation", "accrete", "accretion", "accretive", "accrual",
			"accumulate", "accumulating", "accumulation", "accumulative",
			"accuracy", "accurate", "accurateness", "accursed", "accuse",
			"accustom", "accustomed", "ace", "acerb", "acerbic", "acerbity",
			"ache", "achievable", "achieve", "achievement", "aching",
			"achingly", "achy", "acid", "acidic", "acidity", "acidness",
			"acidulous", "acknowledge", "acknowledgment", "acme", "acolyte" };

	for (auto& x : words) {
		if (cmp::chain < "abb" < x < "abe")
			std::cout << x << " ";
	}
	std::cout << std::endl;

	return 0;
}
