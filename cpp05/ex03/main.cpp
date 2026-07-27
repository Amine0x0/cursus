#include "AForm.hpp"
#include "Intern.hpp"

static const std::string PurpleColor = "\e[0;35m";
static const std::string DefaultColor = "\e[0;37m";

static void sep(std::string context){
    std::cout << PurpleColor 
    << "----------------"
    << context
    << "----------------"
    << DefaultColor
    << std::endl;
}

enum TEST_CASES {
    INTERN_VALID,
    INTERN_INVALID,
    INTERN_EMPTY_STRING
};

static void runInternValid() {
    sep("Intern Valid Forms");
    Intern someRandomIntern;
    AForm* rrf;
    AForm* scf;
    AForm* ppf;

    rrf = someRandomIntern.makeForm("robotomy request", "Bender");
    if (rrf) delete rrf;

    scf = someRandomIntern.makeForm("shrubbery creation", "Garden");
    if (scf) delete scf;

    ppf = someRandomIntern.makeForm("presidential pardon", "Criminal");
    if (ppf) delete ppf;
}

static void runInternInvalid() {
    sep("Intern Invalid Forms");
    Intern someRandomIntern;
    AForm* rrf;

    rrf = someRandomIntern.makeForm("coffee making", "Bender");
    if (rrf) delete rrf;
}

static void runInternEmptyString() {
    sep("Intern Empty Input");
    Intern someRandomIntern;
    AForm* rrf;

    rrf = someRandomIntern.makeForm("", "");
    if (rrf) delete rrf;
}

static void test(TEST_CASES c) {
    switch (c) {
        case INTERN_VALID:        runInternValid();        break;
        case INTERN_INVALID:      runInternInvalid();      break;
        case INTERN_EMPTY_STRING: runInternEmptyString();  break;
        default: break;
    }
}

int main() {
    test(INTERN_VALID);
    test(INTERN_INVALID);
    test(INTERN_EMPTY_STRING);
    return 0;
}