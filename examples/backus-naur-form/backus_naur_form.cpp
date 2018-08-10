#include <string>
#include <iostream>
#include <vector>
#include <functional>

#include "noam.h"

using namespace noam;
using namespace noam::literals;
using namespace noam::utils;

using namespace std;

class BnfGrammar : public Grammar {
public:

    static NonTerminal SYNTAX;
    static NonTerminal RULE;
    static NonTerminal RULE_HEAD;
    static NonTerminal SUB_ALT;
    static NonTerminal SUB;
    static NonTerminal SYM;
    static NonTerminal NON_TERMINAL;
    static NonTerminal TERMINAL;

    static RegexTerminal name;

    BnfGrammar() : Grammar({
       SYNTAX >> RULE | RULE + SYNTAX ,
       RULE >> RULE_HEAD + "::="_P + SUB_ALT + ";"_P,
       RULE_HEAD >> NON_TERMINAL,
       SUB_ALT >> SUB | SUB_ALT + "|"_P + SUB,
       SUB >> SYM | SUB + SYM,
       SYM >> NON_TERMINAL | TERMINAL,
       NON_TERMINAL >> "<"_P + name + ">"_P,
       TERMINAL >> "\""_P + name  + "\""_P
    }) {}
};


NonTerminal BnfGrammar::SYNTAX = "SYNTAX"_N;
NonTerminal BnfGrammar::RULE = "RULE"_N;
NonTerminal BnfGrammar::RULE_HEAD = "RULE_HEAD"_N;
NonTerminal BnfGrammar::SUB_ALT = "SUB_ALT"_N;
NonTerminal BnfGrammar::SUB = "SUB"_N;
NonTerminal BnfGrammar::SYM = "SYM"_N;
NonTerminal BnfGrammar::NON_TERMINAL = "NON_TERMINAL"_N;
NonTerminal BnfGrammar::TERMINAL = "TERMINAL"_N;

RegexTerminal BnfGrammar::name = R"([^\s"<>| ]+)"_Tx;

class ParseGrammar : public ResultVisitor<Grammar> {
public:
    using G = BnfGrammar;

    void postVisit(const TokenNode &node) {
        const auto &token = node.getToken();
        if (*token.getSymbol() == BnfGrammar::name) {
            name = token.getExactValue();
        }
    }

    void postVisit(const RuleNode &node) {
        const auto &rule = node.getRule();
        if (rule == G::TERMINAL >> "\""_P + G::name  + "\""_P) {
            symbol = static_pointer_cast<Symbol>(make_shared<Terminal>(name));
        } else if (rule == G::NON_TERMINAL >> "<"_P + G::name + ">"_P) {
            nonTerminal = make_shared<NonTerminal>(name);
            symbol = static_pointer_cast<Symbol>(nonTerminal);
        } else if (rule == G::SUB >> G::SYM) {
            substitution = make_shared<Substitution>(*symbol);
        } else if (rule == G::SUB >> G::SUB + G::SYM) {
            *substitution + *symbol;
        } else if (rule == G::RULE_HEAD >> G::NON_TERMINAL) {
            ruleHead = nonTerminal;
        } else if (rule == G::SUB_ALT >> G::SUB) {
            altRule = make_shared<AlternativeRule>(SimpleRule{ruleHead, *substitution});
        } else if (rule == G::SUB_ALT >> G::SUB_ALT + "|"_P + G::SUB) {
            *altRule | *substitution;
        } else if (rule == G::RULE >> G::RULE_HEAD + "::="_P + G::SUB_ALT + ";"_P) {
            rules.push_back(*altRule);
        }
    }

    Grammar getResult() const override { return Grammar(rules); }

private:
    std::string name;
    shared_ptr<NonTerminal> ruleHead;
    shared_ptr<NonTerminal> nonTerminal;
    shared_ptr<Symbol> symbol;
    shared_ptr<Substitution> substitution;
    shared_ptr<AlternativeRule> altRule;
    vector<AlternativeRule> rules;

};

int main() {

    BnfGrammar bnfGrammar{};

    auto parseBnf = createDefaultParseFunc(bnfGrammar);

    auto terminals = getSymbolsOfType<Terminal>(bnfGrammar);
    cout << join(terminals, ", ") << endl;

    auto jsonBnf = R"(
        <JSON> ::= <OBJ> ;
        <OBJ> ::= "{"<ATTRS>"}" | "{""}";
        <ATTRS> ::= <ATTR> | <ATTRS> "," <ATTR> ;
        <ATTR> ::= <STRING>":"<VAL> ;
        <VAL> ::= <OBJ> | <ARR> | <INT> | <BOOL> | <FLOAT> | <STRING> ;
        <ARR> ::= "["<LIST>"]" | "[""]" ;
        <LIST> ::= <VAL> | <LIST> "," <VAL> ;
        <INT> ::= "1"|"2"|"3"|"4"|"5"|"6"|"7"|"8"|"9"|"0" ;
        <BOOL> ::= "true" | "false" ;
        <FLOAT> ::= <INT>"."<INT> ;
        <STRING> ::= "a"|"b"|"c"|<STRING><STRING> ;
        )"s;

    auto bnfAst = parseBnf(jsonBnf);

    auto jsonGrammar = visitAstResult<ParseGrammar>(bnfAst);

    cout << toString(jsonGrammar) << endl;

    auto parseJson = createDefaultParseFunc(jsonGrammar);

    auto jsonAst = parseJson("{ abba:1, bac:2.7, cab:[{baba:true}, {baca:false}, {}]}");
    cout << toString(jsonAst) << endl;
}
