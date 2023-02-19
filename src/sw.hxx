/*
Copyright (c) 2020-21 Project re-Isearch and its contributors: See CONTRIBUTORS.
It is made available and licensed under the Apache 2.0 license: see LICENSE
*/
/******* Note: As of 2007 Sept. we support single character search
 so stopword lists must now contain, should they wish to exclude specific
 overly frequent single characters these words in the lists ***********/

#pragma execution_character_set("iso-8859-1")

/*
The only one-letter words in English are a and I. 
 */
static const char *english_builtin_stopwords [] = {
 "a",
 "about",
 "above",
 "across",
 "adj",
 "after",
 "again",
 "against",
 "all",
 "almost",
 "alone",
 "along",
 "also",
 "although",
 "always",
 "am",
 "among",
 "an",
 "and",
 "another",
 "any",
 "anybody",
 "anyone",
 "anything",
 "anywhere",
 "apart",
 "are",
 "around",
 "as",
 "aside",
 "at",
 "away",
 "be",
 "because",
 "been",
 "before",
 "behind",
 "being",
 "below",
 "besides",
 "between",
 "beyond",
 "both",
 "but",
 "by",
 "can",
 "cannot",
 "could",
 "deep",
 "did",
 "do",
 "does",
 "doing",
 "done",
 "down",
 "downwards",
 "during",
 "each",
 "either",
 "else",
 "enough",
 "etc",
 "even",
 "ever",
 "every",
 "everybody",
 "everyone",
 "except",
 "far",
 "few",
 "for",
 "forth",
 "from",
 "get",
 "gets",
 "got",
 "had",
 "hardly",
 "has",
 "have",
 "having",
 "her",
 "here",
 "herself",
 "him",
 "himself",
 "his",
 "how",
 "however",
 "i",
 "if",
 "in",
 "indeed",
 "instead",
 "into",
 "inward",
 "is",
 "it",
 "its",
 "itself",
 "just",
 "kept",
 "many",
 "maybe",
 "might",
 "mine",
 "more",
 "most",
 "mostly",
 "much",
 "must",
 "myself",
 "near",
 "neither",
 "next",
 "no",
 "nobody",
 "none",
 "nor",
 "not",
 "nothing",
 "nowhere",
 "of",
 "off",
 "often",
 "on",
 "only",
 "onto",
 "or",
 "other",
 "others",
 "ought",
 "our",
 "ours",
 "out",
 "outside",
 "over",
 "own",
 "per",
 "please",
 "plus",
 "pp",
 "quite",
 "rather",
 "really",
 "said",
 "seem",
 "self",
 "selves",
 "several",
 "shall",
 "she",
 "should",
 "since",
 "so",
 "some",
 "somebody",
 "somewhat",
 "still",
 "such",
 "than",
 "that",
 "the",
 "their",
 "theirs",
 "them",
 "themselves",
 "then",
 "there",
 "therefore",
 "these",
 "they",
 "this",
 "thorough",
 "thoroughly",
 "those",
 "through",
 "thus",
 "to",
 "together",
 "too",
 "toward",
 "towards",
 "under",
 "until",
 "up",
 "upon",
 "very",
 "was",
 "well",
 "were",
 "what",
 "whatever",
 "when",
 "whenever",
 "where",
 "whether",
 "which",
 "while",
 "who",
 "whom",
 "whose",
 "will",
 "with",
 "within",
 "without",
 "would",
 "yet",
 "young",
 "your",
 "yourself"
};

const char *finnish_builtin_stopwords [] = {
 "ja",
 "on",
 "du",
 "ei",
 "se",
 "on",
 "op",
 "in"
};

/* One-Letter Words: a, y, o */
static const char *french_builtin_stopwords [] = {
 "a",
 "absent",
 "absente",
 "absentes",
 "absents",
 "ai",
 "ainsi",
 "alors",
 "apr�s",
 "as",
 "assez",
 "au",
 "aucun",
 "aucune",
 "aucunes",
 "aucuns",
 "aussi",
 "autour",
 "autre",
 "autres",
 "avaient",
 "avais",
 "avait",
 "avant",
 "avec",
 "avez",
 "aviez",
 "avions",
 "avons",
 "ayant",
 "beaucoup",
 "bien",
 "bon",
 "�a",
 "ce",
 "cela",
 "celle",
 "celles",
 "celui",
 "ces",
 "cet",
 "cette",
 "ceux",
 "chacun",
 "chacune",
 "chaque",
 "combien",
 "comme",
 "comment",
 "contre",
 "c�t�",
 "dans",
 "de",
 "dedans",
 "dehors",
 "depuis",
 "derri�re",
 "des",
 "devenons",
 "devenez",
 "devenu",
 "devenue",
 "devenues",
 "devenus",
 "devez",
 "deviennent",
 "deviens",
 "devient",
 "devons",
 "devrai",
 "devraient",
 "devrais",
 "devrait",
 "devriez",
 "devrions",
 "disaient",
 "disais",
 "disait",
 "disiez",
 "disions",
 "dois",
 "doit",
 "doivent",
 "donc",
 "effectivement",
 "elle",
 "elles",
 "en",
 "encore",
 "endroit",
 "ensemble",
 "ensuite",
 "entre",
 "es",
 "est",
 "et",
 "�taient",
 "�tais",
 "�tait",
 "�tant",
 "etc.",
 "�t�",
 "�tes",
 "�tiez",
 "�tions",
 "�tre",
 "eux",
 "except�",
 "ext�rieur",
 "ext�rieure",
 "ext�rieures",
 "ext�rieurs",
 "faire",
 "fais",
 "faisant",
 "faisons",
 "fait",
 "faite",
 "faites",
 "faits",
 "fini",
 "finie",
 "finies",
 "finis",
 "fonc�",
 "fonc�e",
 "fonc�es",
 "fonc�s",
 "font",
 "fr�quemment",
 "gu�re",
 "ici",
 "il",
 "ils",
 "int�rieur",
 "int�rieure",
 "int�rieures",
 "int�rieurs",
 "intime",
 "intimes",
 "jamais",
 "je",
 "jeune",
 "jeunes",
 "la",
 "laquelle",
 "laquelles",
 "le",
 "lequel",
 "lequels",
 "les",
 "lesquels",
 "leur",
 "leurs",
 "lieu",
 "loin",
 "lui",
 "mais",
 "malgr�",
 "me",
 "m�me",
 "m�mes",
 "mien",
 "mienne",
 "miennes",
 "miens",
 "minutieuse",
 "minutieusement",
 "minutieux",
 "ne",
 "ni",
 "non",
 "nos",
 "notre",
 "o",
 "ont",
 "ou",
 "outre",
 "par",
 "para�tre",
 "parmi",
 "partout",
 "pas",
 "pendant",
 "peine",
 "personne",
 "peut",
 "peut-�tre",
 "peuvent",
 "peux",
 "plus",
 "plusieurs",
 "plupart",
 "plut�t",
 "pour",
 "pourquoi",
 "pourraient",
 "pourrais",
 "pourrait",
 "pourriez",
 "pourrions",
 "pouvaient",
 "pouvais",
 "pouvait",
 "pouvez",
 "pouviez",
 "pouvions",
 "pouvons",
 "pr�s",
 "presque",
 "prochain",
 "prochaine",
 "prochaines",
 "prochains",
 "profond",
 "profonde",
 "profondes",
 "profonds",
 "propre",
 "propres",
 "puis",
 "quand",
 "que",
 "quel",
 "quelle",
 "quelles",
 "quels",
 "quelque",
 "quelques",
 "qui",
 "quoi",
 "quoique",
 "rien",
 "sa",
 "sans",
 "s�par�",
 "sera",
 "serai",
 "seraient",
 "serais",
 "serait",
 "seras",
 "serez",
 "seriez",
 "serions",
 "serons",
 "ses",
 "seul",
 "seule",
 "seulement",
 "seules",
 "seuls",
 "si",
 "soi",
 "soit",
 "sommes",
 "son",
 "sont",
 "sous",
 "souvent",
 "suffisamment",
 "suis",
 "suivant",
 "sur",
 "tel",
 "telle",
 "telles",
 "tels",
 "tenu",
 "tenue",
 "tenues",
 "tenus",
 "toujours",
 "tous",
 "tout",
 "toute",
 "toutes",
 "travers",
 "tr�s",
 "trop",
 "un",
 "une",
 "vers",
 "vos",
 "votre",
 "vous",
 "vraiment",
 "y"
};

/* German has NO single letter words */
static const char *german_builtin_stopwords [] = {
 "ab",
 "aber",
 "abgesehen",
 "alle",
 "allein",
 "aller",
 "alles",
 "als",
 "am",
 "an",
 "andere",
 "anderen",
 "anderenfalls",
 "anderer",
 "anderes",
 "anstatt",
 "auch",
 "auf",
 "aus",
 "aussen"
 "ausser"
 "ausserdem",
 "ausserhalb",
 "au�en",
 "au�er",
 "au�erdem",
 "au�erhalb",
 "behalten",
 "bei",
 "beide",
 "beiden",
 "beider",
 "beides",
 "beinahe",
 "bevor",
 "bin",
 "bis",
 "bist",
 "bitte",
 "bzw",
 "da",
 "daher",
 "danach",
 "dann",
 "dar�ber",
 "dar�berhinaus",
 "darum",
 "das",
 "dass",
 "da�",
 "dem",
 "den",
 "der",
 "des",
 "deshalb",
 "die",
 "diese",
 "diesem",
 "diesen",
 "dieser",
 "dieses",
 "dort",
 "d�rfte",
 "d�rften",
 "d�rftest",
 "d�rftet",
 "durch",
 "durfte",
 "durften",
 "durftest",
 "durftet",
 "eigene",
 "eigenem",
 "eigenen",
 "eigener",
 "eigenes",
 "ein",
 "eine",
 "einem",
 "einen",
 "einer",
 "eines",
 "einige",
 "einiger",
 "einiges",
 "entgegen",
 "entweder",
 "erscheinen",
 "es",
 "etwas",
 "fast",
 "fertig",
 "fort",
 "fuer",
 "f�r",
 "gegen",
 "gegen�ber",
 "gehalten",
 "geht",
 "gemacht",
 "gem�ss",
 "gem��",
 "genug",
 "getan",
 "getrennt",
 "gewesen",
 "gr�ndlich",
 "gut",
 "habe",
 "haben",
 "habt",
 "h�ufig",
 "hast",
 "hat",
 "hatte",
 "hatten",
 "hattest",
 "hattet",
 "hier",
 "hindurch",
 "hintendran",
 "hinter",
 "hinunter",
 "ich",
 "ihm",
 "ihnen",
 "ihr",
 "ihre",
 "ihrem",
 "ihren",
 "ihrer",
 "ihres",
 "ihrige",
 "ihrigen",
 "ihriges",
 "immer",
 "in",
 "indem",
 "innerhalb",
 "innerlich",
 "irgendetwas",
 "irgendwelche",
 "irgendwenn",
 "irgendwo",
 "irgendwohin",
 "ist",
 "jede",
 "jedem",
 "jeden",
 "jeder",
 "jedes",
 "jedoch",
 "jemals",
 "jemand",
 "jemandem",
 "jemanden",
 "jemandes",
 "jene",
 "jung",
 "junge",
 "jungem",
 "jungen",
 "junger",
 "junges",
 "kann",
 "kannst",
 "kaum",
 "kein",
 "keine",
 "keinem",
 "keinen",
 "keiner",
 "keines",
 "k�nnen",
 "k�nnt",
 "k�nnte",
 "k�nnten",
 "k�nntest",
 "k�nntet",
 "konnte",
 "konnten",
 "konntest",
 "konntet",
 "machen",
 "macht",
 "machte",
 "mehr",
 "mehrere",
 "mein",
 "meine",
 "meinem",
 "meinen",
 "meiner",
 "meines",
 "meistens",
 "mich",
 "mir",
 "mit",
 "m�ssen",
 "m�sst",
 "muss",
 "musst",
 "mu�",
 "mu�t",
 "nach",
 "nachdem",
 "n�chste",
 "nebenan",
 "nein",
 "nicht",
 "nichts",
 "niemand",
 "niemandem",
 "niemanden",
 "niemandes",
 "nirgendwo",
 "noch",
 "nur",
 "ob",
 "oben",
 "obwohl",
 "oder",
 "oft",
 "ohne",
 "pro",
 "sagte",
 "sagten",
 "sagtest",
 "sagtet",
 "scheinen",
 "sehr",
 "sei",
 "seid",
 "seien",
 "seiest",
 "seiet",
 "sein",
 "seine",
 "seinem",
 "seinen",
 "seiner",
 "seines",
 "seit",
 "selbst",
 "sich",
 "sie",
 "sind",
 "so",
 "sogar",
 "solche",
 "solchem",
 "solchen",
 "solcher",
 "solches",
 "sollte",
 "sollten",
 "solltest",
 "solltet",
 "sondern",
 "statt",
 "stets",
 "tats�chlich",
 "tief",
 "tun",
 "tut",
 "ber",
 "berall",
 "ua", // ?????
 "um",
 "und",
 "uns",
 "unser",
 "unsere",
 "unserem",
 "unseren",
 "unserer",
 "unseres",
 "unten",
 "unter",
 "unterhalb",
 "usw",
 "viel",
 "viele",
 "vielleicht",
 "von",
 "vor",
 "vorbei",
 "vorher",
 "vor�ber",
 "w�hrend",
 "wann",
 "war",
 "waren",
 "warst",
 "wart",
 "was",
 "weder",
 "weg",
 "wegen",
 "weil",
 "weit",
 "weiter",
 "weitere",
 "weiterem",
 "weiteren",
 "weiterer",
 "weiteres",
 "welche",
 "welchem",
 "welchen",
 "welcher",
 "welches",
 "wem",
 "wen",
 "wenige",
 "wenn",
 "wer",
 "werde",
 "werden",
 "werdet",
 "wessen",
 "wie",
 "wieder",
 "wir",
 "wird",
 "wirklich",
 "wirst",
 "wo",
 "wohin",
 "w�rde",
 "w�rden",
 "w�rdest",
 "w�rdet",
 "wurde",
 "wurden",
 "wurdest",
 "wurdet",
 "ziemlich",
 "zu",
 "zum",
 "zur",
 "zusammen",
 "zwischen"
};

/*
One-Letter Words: e, a, i, o
*/
static const char *italian_builtin_stopwords [] = {
 "a",
 "abbastanza",
 "abbiamo",
 "alcune",
 "alcuni",
 "allora",
 "altra",
 "altre",
 "altri",
 "altro",
 "anche",
 "ancora",
 "attraverso",
 "avanti",
 "avendo",
 "avete",
 "aveva",
 "avevamo",
 "avevano",
 "avevate",
 "avevi",
 "avevo",
 "bene",
 "che",
 "chi",
 "chicchessia",
 "circa",
 "come",
 "completa",
 "completamente",
 "complete",
 "completi",
 "completo",
 "con",
 "contro",
 "cosa",
 "cos�",
 "da",
 "davvero",
 "dentro",
 "deve",
 "devi",
 "devo",
 "devono",
 "di",
 "dicemmo",
 "diceste",
 "dicesti",
 "diceva",
 "dicevamo",
 "dicevano",
 "dicevate",
 "dicevi",
 "dicevo",
 "dietro",
 "disse",
 "dissero",
 "dissi",
 "diventa",
 "diventai",
 "diventammo",
 "diventare",
 "diventarono",
 "diventaste",
 "diventasti",
 "divent�",
 "diversi",
 "diviso",
 "dobbiamo",
 "dopo",
 "dove",
 "dovere",
 "dovete",
 "dovrebbe",
 "dovrebbero",
 "dovrei",
 "dovremmo",
 "dovreste",
 "dovresti",
 "dunque",
 "durante",
 "e",
 "eccetera",
 "eccetto",
 "ella",
 "entrambe",
 "entrambi",
 "entro",
 "era",
 "eravamo",
 "erano",
 "eravate",
 "eri",
 "ero",
 "essa",
 "essendo",
 "essere",
 "esse",
 "essi",
 "esso",
 "facemmo",
 "facendo",
 "faceste",
 "facesti",
 "fare",
 "fatto",
 "fece",
 "fecero",
 "feci",
 "fino",
 "forse",
 "fra",
 "fuori",
 "giovane",
 "giovani",
 "gi�",
 "gli",
 "ha",
 "hai",
 "hanno",
 "ho",
 "il",
 "in",
 "inoltre",
 "insieme",
 "intorno",
 "invece",
 "i",
 "io",
 "la",
 "le",
 "lei",
 "li",
 "lo",
 "lontano",
 "loro",
 "lungo",
 "ma",
 "maggiorparte",
 "mai",
 "mentre",
 "mia",
 "minuziosa",
 "minuziosamente",
 "minuziose",
 "minuziosi",
 "minuzioso",
 "mio",
 "molta",
 "molte",
 "molti",
 "molto",
 "ne",
 "nessuna",
 "nessune",
 "nessuni",
 "nessuno",
 "niente",
 "no",
 "non",
 "nonostante",
 "nostra",
 "nostro",
 "o",
 "ogni",
 "ognuna",
 "ognuno",
 "oltre",
 "oppure",
 "ovunque",
 "per",
 "perch�",
 "perfino",
 "per�",
 "persino",
 "pi�",
 "piuttosto",
 "pochi",
 "poi",
 "potere",
 "poteva",
 "potevamo",
 "potevano",
 "potevate",
 "potevi",
 "potevo",
 "potrebbe",
 "potrebbero",
 "potrei",
 "potremmo",
 "potreste",
 "potresti",
 "prima",
 "profonda",
 "profonde",
 "profondi",
 "profondo",
 "proprio",
 "prossima",
 "prossime",
 "prossimi",
 "prossimo",
 "qualcuno",
 "quale",
 "quali",
 "qualsiasi",
 "quando",
 "quasi",
 "quei",
 "quella",
 "quelle",
 "quello",
 "questa",
 "queste",
 "questi",
 "questo",
 "qui",
 "quindi",
 "raramente",
 "se",
 "sebbene",
 "sei",
 "sembrare",
 "sempre",
 "senza",
 "siamo",
 "siete",
 "sola",
 "solamente",
 "sole",
 "soli",
 "solo",
 "sono",
 "sopra",
 "sotto",
 "spesso",
 "stata",
 "state",
 "stati",
 "stato",
 "stessa",
 "stesse",
 "stessi",
 "stesso",
 "su",
 "sua",
 "suo",
 "tale",
 "tenuto",
 "tra",
 "tu",
 "tua",
 "tuo",
 "tutta",
 "tuttavia",
 "tutte",
 "tutti",
 "tutto",
 "un",
 "una",
 "uno",
 "veramente",
 "verso",
 "via",
 "vicino"
};

const char *portuguese_builtin_stopwords [] = {
 "D",
 "Le",
 "L�",
 "O",
 "a",
 "ao",
 "as",
 "com",
 "como",
 "d",
 "da",
 "das",
 "de",
 "do",
 "dos",
 "e",
 "em",
 "em",
 "esta",
 "le",
 "l�",
 "na",
 "nos",
 "o",
 "os",
 "para",
 "por",
 "que",
 "se",
 "ser",
 "seu",
 "sua",
 "uns",
 "vre",
 "",
 "�",
 "�",
 "�"
};

/*
One-Letter Words: a, e, o, u, y 
*/
static const char *spanish_builtin_stopwords [] = {
 "a",
 "adelante",
 "adem�s",
 "adonde",
 "algo",
 "alguien",
 "algunas",
 "algunos",
 "all�",
 "all�",
 "alrededor",
 "ambas",
 "ambos",
 "antes",
 "aparte",
 "aproximadamente",
 "arriba",
 "as�",
 "atr�s",
 "aun",
 "a�n",
 "bastante",
 "bien",
 "cada",
 "casi",
 "cerca",
 "como",
 "completa",
 "completamente",
 "completas",
 "completo",
 "completos",
 "con",
 "contra",
 "cual",
 "cuales",
 "cuando",
 "cuya",
 "cuyas",
 "cuyo",
 "cuyos",
 "de",
 "debajo",
 "debe",
 "deb�is",
 "debemos",
 "deben",
 "deber",
 "debes",
 "debo",
 "debr�a",
 "debr�ais",
 "debr�amos",
 "debr�an",
 "debr�as",
 "dec�a",
 "dec�an",
 "dec�as",
 "delante",
 "dentro",
 "desde",
 "despu�s",
 "detr�s",
 "devengo",
 "deven�is",
 "devenimos",
 "devenir",
 "deviene",
 "devienen",
 "devienes",
 "devino",
 "dec�s",
 "decimos",
 "dije",
 "dijemos",
 "dijeron",
 "dijiste",
 "dijist�is",
 "dijo",
 "donde",
 "durante",
 "e",
 "el",
 "ella",
 "ellas",
 "ellos",
 "en",
 "encima",
 "entonces",
 "entorno",
 "entre",
 "era",
 "erais",
 "�ramos",
 "eran",
 "eras",
 "eres",
 "es",
 "esa",
 "esas",
 "ese",
 "eses",
 "eso",
 "estando",
 "estar",
 "estas",
 "estos",
 "etc�tera",
 "excepto",
 "frecuentemente",
 "fuera",
 "hab�a",
 "hab�ais",
 "hab�amos",
 "hab�an",
 "hab�as",
 "habiendo",
 "hace",
 "hacer",
 "hacia",
 "hac�ais",
 "hac�amos",
 "hac�an",
 "hac�as",
 "hasta",
 "hecho",
 "hice",
 "hiciendo",
 "hicieron",
 "hicimos",
 "hiciste",
 "hicist�is",
 "hizo",
 "interior",
 "interiores",
 "joven",
 "jovenes",
 "juntas",
 "juntos",
 "la",
 "las",
 "le",
 "lejos",
 "les",
 "lo",
 "los",
 "mantenido",
 "m�s",
 "mayor�a",
 "mientras",
 "minuciosa",
 "minuciosamente",
 "minuciosas",
 "minucioso",
 "minuciosos",
 "misma",
 "mismas",
 "mismo",
 "mismos",
 "mucha",
 "muchas",
 "mucho",
 "muchos",
 "muy",
 "nada",
 "nadie",
 "ni",
 "ning�n",
 "ninguna",
 "ningunas",
 "ninguno",
 "ningunos",
 "no",
 "nuestra",
 "nuestras",
 "nuestro",
 "nuestros",
 "nunca",
 "o",
 "otra",
 "otras",
 "otro",
 "otros",
 "para",
 "parecer",
 "pero",
 "po�ia",
 "pod�ais",
 "pod�amos",
 "pod�an",
 "pod�as",
 "podr�a",
 "podr�ais",
 "podr�amos",
 "podr�an",
 "podr�as",
 "porque",
 "pod�is",
 "podemos",
 "poder",
 "por",
 "profunda",
 "produndas",
 "profundo",
 "profundos",
 "propia",
 "propias",
 "propio",
 "proprios",
 "pr�xima",
 "pr�ximas",
 "pr�ximo",
 "pr�ximos",
 "puede",
 "pueden",
 "puedes",
 "puedo",
 "principalmente",
 "que",
 "quien",
 "quienes",
 "raramente",
 "salvo",
 "ser",
 "si",
 "sido",
 "siempre",
 "siendo",
 "sin",
 "sobre",
 "sola",
 "solamente",
 "solas",
 "solo",
 "solos",
 "somos",
 "son",
 "soy",
 "su",
 "sus",
 "tambi�n",
 "ten�is",
 "tenemos",
 "tengo",
 "teniendo",
 "tiene",
 "tienen",
 "tienes",
 "toda",
 "todas",
 "todav�a",
 "todo",
 "todos",
 "trav�s",
 "tu",
 "tus",
 "u",
 "un",
 "una",
 "ustedes",
 "varias",
 "varios",
 "verdaderamente",
 "y",
 "yo"
};

const char *swedish_builtin_stopwords [] = {
 "ar",
 "att",
 "av",
 "den",
 "en",
 "er",
 "for",
 "fr�n",
 "f�r",
 "har",
 "i",
 "med",
 "ni",
 "om",
 "pa",
 "p�",
 "ser",
 "som",
 "st�d",
 "ta",
 "ung",
 "ut",
 "vad",
 "vi",
 "�r",
 "�r",
 "�t"
};

const char *bokmal_builtin_stopwords [] = {
 "at",
 "av",
 "de",
 "det",
 "din",
 "du",
 "en",
 "er",
 "for",
 "fra",
 "har",
 "her",
 "hva",
 "i",
 "kan",
 "les",
 "med",
 "mer",
 "m�",
 "og",
 "om",
 "oss",
 "p�",
 "se",
 "som",
 "st�r",
 "s�",
 "tid",
 "til",
 "ut",
 "ved",
 "vi",
 "�"
};

const char *nynorsk_builtin_stopwords [] = {
 "at",
 "av",
 "de",
 "det",
 "din",
 "du",
 "en",
 "er",
 "for",
 "fra",
 "har",
 "her",
 "hva",
 "i",
 "kan",
 "les",
 "med",
 "mer",
 "m�",
 "og",
 "om",
 "oss",
 "p�",
 "se",
 "som",
 "st�r",
 "s�",
 "tid",
 "til",
 "ut",
 "ved",
 "vi",
 "�"
};



const char *danish_builtin_stopwords [] = {
 "Den",
 "Du",
 "F�",
 "Til",
 "af",
 "at",
 "del",
 "den",
 "det",
 "din",
 "du",
 "en",
 "er",
 "et",
 "for",
 "fra",
 "f�",
 "hr",
 "i",
 "kan",
 "med",
 "mit",
 "n�r",
 "og",
 "om",
 "p�",
 "ser",
 "sig",
 "som",
 "til"
};

const char *dutch_builtin_stopwords [] = {
 "De",
 "Het",
 "Ik",
 "Op",
 "aan",
 "al",
 "auf",
 "dat",
 "de",
 "een",
 "en",
 "er",
 "het",
 "ik",
 "in",
 "is",
 "kan",
 "met",
 "om",
 "op",
 "per",
 "te",
 "u",
 "van",
 "voor",
 "wat"
};



#define DefLang(_l, _x) { _l, _x##_builtin_stopwords, sizeof(_x##_builtin_stopwords)/sizeof(char *) -1 }

const struct internal_stoplist {
  const char *language;
  const char **words;
  const size_t size;
} internal_stoplists[] = {
  DefLang("C",   english),
  DefLang("en",  english),
  DefLang("en.iso-8859-1", english),
  DefLang("eng", english),
  DefLang("eng.iso-8859-1", english),
  DefLang("da", danish),
  DefLang("da.iso-8859-1", danish),
  DefLang("dan",  danish),
  DefLang("dan.iso-8859-1", danish),
  DefLang("de",  german),
  DefLang("de.iso-8859-1", german),
  DefLang("es",  spanish),
  DefLang("es.iso-8859-1", spanish),
  DefLang("esl", spanish),
  DefLang("esl.iso-8859-1", spanish),
  DefLang("fi",  finnish),
  DefLang("fi.iso-8859-1",  finnish),
  DefLang("fin", finnish),
  DefLang("fin.iso-8859-1",  finnish),
  DefLang("fr",  french),
  DefLang("fr.iso-8859-1",  french),
  DefLang("fra", french),
  DefLang("fra.iso-8859-1",  french),
  DefLang("fre", french),
  DefLang("fre.iso-8859-1",  french),
  DefLang("ger", german),
  DefLang("ger.iso-8859-1", german),
  DefLang("it",  italian),
  DefLang("it.iso-8859-1",  italian),
  DefLang("ita", italian),
  DefLang("ita.iso-8859-1",  italian),
  DefLang("no", nynorsk),
  DefLang("no.iso-88591-", nynorsk),
  DefLang("no-bok", bokmal),
  DefLang("no-bok.iso-8859-1", bokmal),
  DefLang("no-nyn", nynorsk),
  DefLang("no-nyn.iso-8859-1", nynorsk),
  DefLang("nl", dutch),
  DefLang("nl.iso-8859-1", dutch),
  DefLang("nld", dutch),
  DefLang("nld.iso-8859-1",  dutch),
  DefLang("por", portuguese),
  DefLang("por.iso-8859-1", portuguese),
  DefLang("pt", portuguese),
  DefLang("pt.iso-8859-1",  portuguese),
  DefLang("sv", swedish),
  DefLang("sv.iso-8859-1",  swedish),
  DefLang("sve", swedish),
  DefLang("sve.iso-8859-1", swedish)
};


#undef DefLang
