//============================================================================
// Name        : main.cpp
// Author      : Rahman Salim Zengin
// Version     :
// Copyright   : rsz@gufatek.com
// Description :
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "chain.hpp"


int main() {

    std::vector<int> numbers(20);
    std::generate(numbers.begin(), numbers.end(), [](){return double(std::rand()) * 20 / RAND_MAX;});

    for (auto x : numbers)
		if (cmp::chain < 5 <= x < 15)
			std::cout << x << " ";
    std::cout << std::endl;

    for (auto x : numbers)
    	if (5 <= x && x < 15)
			std::cout << x << " ";
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
		if (cmp::chain < "abb" <= x < "abe")
			std::cout << x << " ";
	}
	std::cout << std::endl;

	for (auto& x : words) {
		if ("abb" <= x && x < "abe")
			std::cout << x << " ";
	}
	std::cout << std::endl;

	std::srand(0);
	for (int inx = 0; inx < 1000; ++inx) {
		double a = double(std::rand()) / RAND_MAX;
		double b = double(std::rand()) / RAND_MAX;
		double c = double(std::rand()) / RAND_MAX;

		if(cmp::chain < 0.4 < a <= b <= c < 0.6) {
			std::cout << "Round "<< inx << ") Variables in the range : " <<
					a << " <= " << b << " <= " << c << "\n";
		}
	}

	std::srand(0);
	for (int inx = 0; inx < 1000; ++inx) {
		double a = double(std::rand()) / RAND_MAX;
		double b = double(std::rand()) / RAND_MAX;
		double c = double(std::rand()) / RAND_MAX;

		if(0.4 < a && a <= b && b <= c && c < 0.6) {
			std::cout << "Round "<< inx << ") Variables in the range : " <<
					a << " <= " << b << " <= " << c << "\n";
		}
	}

	return 0;
}
