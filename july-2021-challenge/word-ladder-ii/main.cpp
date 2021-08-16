#include <gtest/gtest.h>
#include <algorithm>
#include <cassert>
#include <queue>
#include <string>
#include <vector>
#include <iostream>

/**
 * A transformation sequence from word beginWord to word endWord using a
 * dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk
 * such that:
 *
 * Every adjacent pair of words differs by a single letter.
 * Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to
 * be in wordList. sk == endWord Given two words, beginWord and endWord, and a
 * dictionary wordList, return all the shortest transformation sequences from
 * beginWord to endWord, or an empty list if no such sequence exists. Each
 * sequence should be returned as a list of the words [beginWord, s1, s2, ...,
 * sk].
 *
 *
 *
 * Example 1:
 *
 * Input: beginWord = "hit", endWord = "cog", wordList =
 * ["hot","dot","dog","lot","log","cog"] Output:
 * [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
 * Explanation: There are 2 shortest transformation sequences: "hit" -> "hot" ->
 * "dot" -> "dog" -> "cog" "hit" -> "hot" -> "lot" -> "log" -> "cog"
 *
 * Example 2:
 *
 * Input: beginWord = "hit", endWord = "cog", wordList =
 * ["hot","dot","dog","lot","log"] Output: [] Explanation: The endWord "cog" is
 * not in wordList, therefore there is no valid transformation sequence.
 *
 *
 * Constraints:
 *
 * 1 <= beginWord.length <= 5
 * endWord.length == beginWord.length
 * 1 <= wordList.length <= 1000
 * wordList[i].length == beginWord.length
 *     beginWord, endWord, and wordList[i] consist of lowercase English letters.
 * beginWord != endWord
 *     All the words in wordList are unique.
 *
 */
namespace
{
bool connected(std::string const& word1, std::string const& word2)
{
    assert(std::size(word1) == std::size(word2));

    int numberOfDifferentCharacters = 0;
    for (std::size_t i = 0; i < std::size(word1) && numberOfDifferentCharacters < 2; ++i)
        numberOfDifferentCharacters += (word1[i] != word2[i]);
    return numberOfDifferentCharacters == 1;
}

auto generateConnections(std::vector<std::string> const& words)
{
    const auto size = std::size(words);
    std::vector<std::vector<std::size_t>> result;
    result.resize(size);

    for (std::size_t i = 0; i < size; ++i)
    {
        for (std::size_t j = i + 1; j < size; ++j)
        {
            if (connected(words[i], words[j]))
            {
                result[i].push_back(j);
                result[j].push_back(i);
            }
        }
    }
    return result;
}
using Path = std::vector<std::size_t>;

auto bsfAllPaths(std::vector<std::vector<std::size_t>> const& connections,
 std::size_t start,
 std::size_t finish)
{
    std::vector<Path> result;
    const auto numberOfVertexes = std::size(connections);
    auto bestPath               = numberOfVertexes;

    std::vector<std::size_t> bestPathToVertex(numberOfVertexes, numberOfVertexes);

    std::queue<Path> queue;
    queue.push(Path(1, start));
    while (!queue.empty())
    {
        auto currentPath = queue.front();
        queue.pop();
        auto currentVertex = currentPath.back();
        if (std::size(currentPath) > bestPath) // don't even look further
            continue;

        if (currentVertex == finish)
        {
            if (std::size(currentPath) < bestPath)
            {
                result.clear();
                bestPath = std::size(currentPath);
            }
            result.push_back(std::move(currentPath));
            continue;
        }
        for (auto vertex : connections[currentVertex])
        {
            if (bestPathToVertex[vertex] <= currentPath.size()) // don't calculate if we now it's longer
                continue;

            if (std::find(std::begin(currentPath), std::end(currentPath), vertex)
                != std::end(currentPath)) // don't check it twice
                continue;

            auto newPath = currentPath;
            newPath.push_back(vertex);
            bestPathToVertex[vertex] = std::size(newPath);
            queue.push(std::move(newPath));
        }
    }
    return result;
}

std::vector<std::vector<std::string>> mapVertexesToWords(std::vector<Path> const& paths,
 std::vector<std::string> const& words)
{
    std::vector<std::vector<std::string>> result;
    result.reserve(std::size(paths));
    for (auto const& path : paths)
    {
        std::vector<std::string> stringPath;
        stringPath.reserve(std::size(path));
        std::transform(std::cbegin(path),
         std::cend(path),
         std::back_inserter(stringPath),
         [&](auto val)
         {
             return words[val];
         });
        result.push_back(std::move(stringPath));
    }
    return result;
}

} // namespace
class Solution
{
public:
    std::vector<std::vector<std::string>> findLadders( // no-format
     std::string const& beginWord,
     std::string const& endWord,
     std::vector<std::string>& wordList)
    {
        auto endWordIt = std::find(std::begin(wordList), std::end(wordList), endWord);
        if (endWordIt == std::end(wordList))
            return {};
        const auto finish = endWordIt - std::begin(wordList);

        const auto start = [&]() -> std::size_t
        {
            auto beginWordIt = std::find(std::begin(wordList), std::end(wordList), beginWord);
            if (beginWordIt == std::end(wordList))
            {
                wordList.push_back(beginWord);
                return std::size(wordList) - 1;
            }
            return beginWordIt - std::begin(wordList);
        }();

        auto connections = generateConnections(wordList);
        auto allPaths    = bsfAllPaths(connections, // no-format
            start,
            finish);

        return mapVertexesToWords(allPaths, wordList);
    }
};

namespace
{
TEST(SolutionTests, All)
{
    std::vector<std::string> example1 = {"hot", "dot", "dog", "lot", "log", "cog"};

    auto answer1 = Solution{}.findLadders( // no-format
     "hit",
     "cog",
     example1);
    EXPECT_EQ(2, std::size(answer1));

    std::vector<std::string> example2 = {"hot", "dot", "dog", "lot", "log"};

    auto answer2 = Solution{}.findLadders( // no-format
     "hit",
     "cog",
     example2);
    EXPECT_EQ(0, std::size(answer2));

    std::vector<std::string> example3 = {"kid",
     "tag",
     "pup",
     "ail",
     "tun",
     "woo",
     "erg",
     "luz",
     "brr",
     "gay",
     "sip",
     "kay",
     "per",
     "val",
     "mes",
     "ohs",
     "now",
     "boa",
     "cet",
     "pal",
     "bar",
     "die",
     "war",
     "hay",
     "eco",
     "pub",
     "lob",
     "rue",
     "fry",
     "lit",
     "rex",
     "jan",
     "cot",
     "bid",
     "ali",
     "pay",
     "col",
     "gum",
     "ger",
     "row",
     "won",
     "dan",
     "rum",
     "fad",
     "tut",
     "sag",
     "yip",
     "sui",
     "ark",
     "has",
     "zip",
     "fez",
     "own",
     "ump",
     "dis",
     "ads",
     "max",
     "jaw",
     "out",
     "btu",
     "ana",
     "gap",
     "cry",
     "led",
     "abe",
     "box",
     "ore",
     "pig",
     "fie",
     "toy",
     "fat",
     "cal",
     "lie",
     "noh",
     "sew",
     "ono",
     "tam",
     "flu",
     "mgm",
     "ply",
     "awe",
     "pry",
     "tit",
     "tie",
     "yet",
     "too",
     "tax",
     "jim",
     "san",
     "pan",
     "map",
     "ski",
     "ova",
     "wed",
     "non",
     "wac",
     "nut",
     "why",
     "bye",
     "lye",
     "oct",
     "old",
     "fin",
     "feb",
     "chi",
     "sap",
     "owl",
     "log",
     "tod",
     "dot",
     "bow",
     "fob",
     "for",
     "joe",
     "ivy",
     "fan",
     "age",
     "fax",
     "hip",
     "jib",
     "mel",
     "hus",
     "sob",
     "ifs",
     "tab",
     "ara",
     "dab",
     "jag",
     "jar",
     "arm",
     "lot",
     "tom",
     "sax",
     "tex",
     "yum",
     "pei",
     "wen",
     "wry",
     "ire",
     "irk",
     "far",
     "mew",
     "wit",
     "doe",
     "gas",
     "rte",
     "ian",
     "pot",
     "ask",
     "wag",
     "hag",
     "amy",
     "nag",
     "ron",
     "soy",
     "gin",
     "don",
     "tug",
     "fay",
     "vic",
     "boo",
     "nam",
     "ave",
     "buy",
     "sop",
     "but",
     "orb",
     "fen",
     "paw",
     "his",
     "sub",
     "bob",
     "yea",
     "oft",
     "inn",
     "rod",
     "yam",
     "pew",
     "web",
     "hod",
     "hun",
     "gyp",
     "wei",
     "wis",
     "rob",
     "gad",
     "pie",
     "mon",
     "dog",
     "bib",
     "rub",
     "ere",
     "dig",
     "era",
     "cat",
     "fox",
     "bee",
     "mod",
     "day",
     "apr",
     "vie",
     "nev",
     "jam",
     "pam",
     "new",
     "aye",
     "ani",
     "and",
     "ibm",
     "yap",
     "can",
     "pyx",
     "tar",
     "kin",
     "fog",
     "hum",
     "pip",
     "cup",
     "dye",
     "lyx",
     "jog",
     "nun",
     "par",
     "wan",
     "fey",
     "bus",
     "oak",
     "bad",
     "ats",
     "set",
     "qom",
     "vat",
     "eat",
     "pus",
     "rev",
     "axe",
     "ion",
     "six",
     "ila",
     "lao",
     "mom",
     "mas",
     "pro",
     "few",
     "opt",
     "poe",
     "art",
     "ash",
     "oar",
     "cap",
     "lop",
     "may",
     "shy",
     "rid",
     "bat",
     "sum",
     "rim",
     "fee",
     "bmw",
     "sky",
     "maj",
     "hue",
     "thy",
     "ava",
     "rap",
     "den",
     "fla",
     "auk",
     "cox",
     "ibo",
     "hey",
     "saw",
     "vim",
     "sec",
     "ltd",
     "you",
     "its",
     "tat",
     "dew",
     "eva",
     "tog",
     "ram",
     "let",
     "see",
     "zit",
     "maw",
     "nix",
     "ate",
     "gig",
     "rep",
     "owe",
     "ind",
     "hog",
     "eve",
     "sam",
     "zoo",
     "any",
     "dow",
     "cod",
     "bed",
     "vet",
     "ham",
     "sis",
     "hex",
     "via",
     "fir",
     "nod",
     "mao",
     "aug",
     "mum",
     "hoe",
     "bah",
     "hal",
     "keg",
     "hew",
     "zed",
     "tow",
     "gog",
     "ass",
     "dem",
     "who",
     "bet",
     "gos",
     "son",
     "ear",
     "spy",
     "kit",
     "boy",
     "due",
     "sen",
     "oaf",
     "mix",
     "hep",
     "fur",
     "ada",
     "bin",
     "nil",
     "mia",
     "ewe",
     "hit",
     "fix",
     "sad",
     "rib",
     "eye",
     "hop",
     "haw",
     "wax",
     "mid",
     "tad",
     "ken",
     "wad",
     "rye",
     "pap",
     "bog",
     "gut",
     "ito",
     "woe",
     "our",
     "ado",
     "sin",
     "mad",
     "ray",
     "hon",
     "roy",
     "dip",
     "hen",
     "iva",
     "lug",
     "asp",
     "hui",
     "yak",
     "bay",
     "poi",
     "yep",
     "bun",
     "try",
     "lad",
     "elm",
     "nat",
     "wyo",
     "gym",
     "dug",
     "toe",
     "dee",
     "wig",
     "sly",
     "rip",
     "geo",
     "cog",
     "pas",
     "zen",
     "odd",
     "nan",
     "lay",
     "pod",
     "fit",
     "hem",
     "joy",
     "bum",
     "rio",
     "yon",
     "dec",
     "leg",
     "put",
     "sue",
     "dim",
     "pet",
     "yaw",
     "nub",
     "bit",
     "bur",
     "sid",
     "sun",
     "oil",
     "red",
     "doc",
     "moe",
     "caw",
     "eel",
     "dix",
     "cub",
     "end",
     "gem",
     "off",
     "yew",
     "hug",
     "pop",
     "tub",
     "sgt",
     "lid",
     "pun",
     "ton",
     "sol",
     "din",
     "yup",
     "jab",
     "pea",
     "bug",
     "gag",
     "mil",
     "jig",
     "hub",
     "low",
     "did",
     "tin",
     "get",
     "gte",
     "sox",
     "lei",
     "mig",
     "fig",
     "lon",
     "use",
     "ban",
     "flo",
     "nov",
     "jut",
     "bag",
     "mir",
     "sty",
     "lap",
     "two",
     "ins",
     "con",
     "ant",
     "net",
     "tux",
     "ode",
     "stu",
     "mug",
     "cad",
     "nap",
     "gun",
     "fop",
     "tot",
     "sow",
     "sal",
     "sic",
     "ted",
     "wot",
     "del",
     "imp",
     "cob",
     "way",
     "ann",
     "tan",
     "mci",
     "job",
     "wet",
     "ism",
     "err",
     "him",
     "all",
     "pad",
     "hah",
     "hie",
     "aim",
     "ike",
     "jed",
     "ego",
     "mac",
     "baa",
     "min",
     "com",
     "ill",
     "was",
     "cab",
     "ago",
     "ina",
     "big",
     "ilk",
     "gal",
     "tap",
     "duh",
     "ola",
     "ran",
     "lab",
     "top",
     "gob",
     "hot",
     "ora",
     "tia",
     "kip",
     "han",
     "met",
     "hut",
     "she",
     "sac",
     "fed",
     "goo",
     "tee",
     "ell",
     "not",
     "act",
     "gil",
     "rut",
     "ala",
     "ape",
     "rig",
     "cid",
     "god",
     "duo",
     "lin",
     "aid",
     "gel",
     "awl",
     "lag",
     "elf",
     "liz",
     "ref",
     "aha",
     "fib",
     "oho",
     "tho",
     "her",
     "nor",
     "ace",
     "adz",
     "fun",
     "ned",
     "coo",
     "win",
     "tao",
     "coy",
     "van",
     "man",
     "pit",
     "guy",
     "foe",
     "hid",
     "mai",
     "sup",
     "jay",
     "hob",
     "mow",
     "jot",
     "are",
     "pol",
     "arc",
     "lax",
     "aft",
     "alb",
     "len",
     "air",
     "pug",
     "pox",
     "vow",
     "got",
     "meg",
     "zoe",
     "amp",
     "ale",
     "bud",
     "gee",
     "pin",
     "dun",
     "pat",
     "ten",
     "mob"};
    [[maybe_unused]] auto answer3     = Solution{}.findLadders( // no-format
     "cet",
     "ism",
     example3);
    std::cout << answer3.size();
}
} // unnamed namespace